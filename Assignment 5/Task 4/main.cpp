#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// Base Bill Interface
class Bill {
protected:
    std::string patient;
public:
    explicit Bill(const std::string& p) : patient(p) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    std::string getPatient() const { return patient; }
};

// Existing Bill Types (Unmodified)
class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(const std::string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OutPatient"; }
};

class InPatient : public Bill {
    int days;
    double perDay, surgery;
public:
    InPatient(const std::string& p, int d, double rate, double s)
        : Bill(p), days(d), perDay(rate), surgery(s) {}
    double total() const override { return days * perDay + surgery; }
    std::string type() const override { return "InPatient"; }
};

// Base Payer Interface
class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual std::string payerName() const = 0;
};

// Existing Payer Implementations (Unmodified)
class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override {
        return 0.0; // patient pays 100% out of pocket
    }
    std::string payerName() const override { return "Self-Pay"; }
};

class Insurance : public Payer {
    double coverLimit;
    double coPayPercent;
public:
    Insurance(double limit, double coPay) : coverLimit(limit), coPayPercent(coPay) {}
    double amountCovered(const Bill& b) const override {
        double eligible = std::min(b.total(), coverLimit);
        return eligible * (1.0 - coPayPercent / 100.0);
    }
    std::string payerName() const override { return "Insurance (Co-pay)"; }
};

// ============================================================================
// PRACTICAL EXTENSION: Added without modifying ANY existing class (OCP)
// ============================================================================

// 1. New Bill Type: DayCareSurgeryBill
class DayCareSurgeryBill : public Bill {
    double packageFee;
    double consumables;
public:
    DayCareSurgeryBill(const std::string& p, double pkg, double cons)
        : Bill(p), packageFee(pkg), consumables(cons) {}
    double total() const override { return packageFee + consumables; }
    std::string type() const override { return "DayCareSurgery"; }
};

// 2. New Payer Type: CorporateTieUp (Direct Corporate Billing with Negotiated Discount)
class CorporateTieUp : public Payer {
    std::string corporateName;
    double negotiatedCoveragePercent;
public:
    CorporateTieUp(const std::string& corp, double covPercent)
        : corporateName(corp), negotiatedCoveragePercent(covPercent) {}
    double amountCovered(const Bill& b) const override {
        return b.total() * (negotiatedCoveragePercent / 100.0);
    }
    std::string payerName() const override { return "Corporate (" + corporateName + ")"; }
};

// Production Bill Settlement Pipeline
void processClaim(const Bill& bill, const Payer& payer) {
    double totalBilled = bill.total();
    double covered = payer.amountCovered(bill);
    double patientLiability = totalBilled - covered;

    std::cout << "[" << bill.type() << " Bill for " << bill.getPatient() << "]\n";
    std::cout << "  Total Amount    : Rs " << std::fixed << std::setprecision(2) << totalBilled << '\n';
    std::cout << "  Payer           : " << payer.payerName() << '\n';
    std::cout << "  Covered Amount  : Rs " << covered << '\n';
    std::cout << "  Patient Balance : Rs " << patientLiability << "\n\n";
}

int main() {
    std::cout << "--- [Hospital Multi-Payer Billing System - Seamless Extension] ---\n";

    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatient>("Aarav", 800.0, 1500.0));
    bills.push_back(std::make_unique<InPatient>("Bhavna", 5, 3000.0, 50000.0));
    // Newly extended bill:
    bills.push_back(std::make_unique<DayCareSurgeryBill>("Chetan", 22000.0, 4500.0));

    Insurance generalInsurance(60000.0, 10.0); // 10% copay, up to 60k
    CorporateTieUp googleCorporate("Google Health Network", 95.0); // 95% covered

    processClaim(*bills[0], generalInsurance);
    processClaim(*bills[1], generalInsurance);
    processClaim(*bills[2], googleCorporate); // processing extended bill with extended payer

    std::cout << "[TASK 4 FINAL ENGINEERING EXTENSION COMPLETED WITH ZERO LEAKS]\n";
    return 0;
}
