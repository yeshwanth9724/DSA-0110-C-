#include <iostream>

// Predict the Output Specification Program
struct Account {
    double rate() const { return 3.5; }
    virtual double vrate() const { return 3.5; }
    virtual ~Account() = default;
};

struct SeniorAccount : Account {
    double rate() const { return 4.0; }
    double vrate() const override { return 4.0; }
};

void runForensicPrediction() {
    std::cout << "--- [Specification Predict the Output: Virtual vs Non-Virtual Binding] ---\n";
    SeniorAccount s;
    Account* p = &s;
    Account copy = s;
    std::cout << p->rate() << ' ' << p->vrate() << ' ' << copy.vrate() << "\n\n";
}

// Repaired Forensic Account Hierarchy
class BankAccount {
public:
    virtual ~BankAccount() {
        // Virtual destructor ensures complete cleanup
    }
    virtual double getInterestRate() const {
        return 3.5;
    }
};

class SeniorBankAccount : public BankAccount {
private:
    double* transactionHistory;

public:
    SeniorBankAccount() : transactionHistory(new double[100]) {}
    ~SeniorBankAccount() override {
        delete[] transactionHistory;
    }
    double getInterestRate() const override {
        return 4.0;
    }
};

int main() {
    runForensicPrediction();

    std::cout << "--- [Repaired Bank Account Polymorphic Processing] ---\n";
    BankAccount* accounts[2] = { new BankAccount(), new SeniorBankAccount() };

    for (int i = 0; i < 2; ++i) {
        std::cout << "Account [" << i << "] Polymorphic Rate: " << accounts[i]->getInterestRate() << "%\n";
    }

    for (int i = 0; i < 2; ++i) {
        delete accounts[i]; // virtual destructor cleans up SeniorBankAccount without leak
    }

    std::cout << "\n[TASK 4 POINTERS TO DERIVED CLASSES COMPLETED]\n";
    return 0;
}
