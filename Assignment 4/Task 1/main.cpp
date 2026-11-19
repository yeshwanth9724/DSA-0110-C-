#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Staff {
protected:
    std::string name;
    int id;

public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;

    virtual double pay() const = 0;
    virtual void print() const {
        std::cout << "ID: " << id << " | Name: " << name << " | Monthly Pay: Rs " 
                  << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

class RegularStaff : public Staff {
protected:
    double basic;
    static constexpr double DA_RATE = 0.42;

public:
    RegularStaff(const std::string& n, int i, double b)
        : Staff(n, i), basic(b) {}

    double pay() const override {
        return basic + (basic * DA_RATE);
    }
};

class Professor : public RegularStaff {
private:
    double researchAllowance;

public:
    Professor(const std::string& n, int i, double b, double research)
        : RegularStaff(n, i, b), researchAllowance(research) {}

    double pay() const override {
        return RegularStaff::pay() + researchAllowance;
    }
};

class LabAssistant : public RegularStaff {
public:
    LabAssistant(const std::string& n, int i, double b)
        : RegularStaff(n, i, b) {}
};

class GuestFaculty : public Staff {
private:
    double hours;
    double hourlyRate;

public:
    GuestFaculty(const std::string& n, int i, double h, double rate)
        : Staff(n, i), hours(h), hourlyRate(rate) {}

    double pay() const override {
        return hours * hourlyRate;
    }
};

int main() {
    std::cout << "--- [College Payroll Class Hierarchy Demonstration] ---\n";

    std::vector<Staff*> payroll = {
        new Professor("Dr. Aris", 101, 75000.0, 15000.0),
        new LabAssistant("Mr. Raman", 202, 35000.0),
        new GuestFaculty("Ms. Priya", 303, 40.0, 1200.0)
    };

    double totalPayroll = 0.0;
    for (const Staff* s : payroll) {
        s->print();
        totalPayroll += s->pay();
    }

    std::cout << "------------------------------------------------------\n";
    std::cout << "Total Department Payroll: Rs " << totalPayroll << '\n';

    for (Staff* s : payroll) delete s;

    std::cout << "\n[TASK 1 CLASS DESIGN REVIEW COMPLETED]\n";
    return 0;
}
