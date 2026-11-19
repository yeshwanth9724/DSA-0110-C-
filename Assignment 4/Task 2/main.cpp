#include <iostream>
#include <string>

// Virtual Base Class
class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n = "", int i = 0, const std::string& p = "")
        : name(n), id(i), phone(p) {
        std::cout << "Person ";
    }
    virtual ~Person() = default;
};

// Virtually inheriting derived class 1
class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n = "", int i = 0, const std::string& p = "",
            const std::string& prog = "", double g = 0.0)
        : Person(n, i, p), programme(prog), cgpa(g) {
        std::cout << "Student ";
    }
};

// Virtually inheriting derived class 2
class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n = "", int i = 0, const std::string& p = "",
          const std::string& dept = "", double sal = 0.0)
        : Person(n, i, p), department(dept), salary(sal) {
        std::cout << "Staff ";
    }
};

// Most-derived class resolving diamond inheritance
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double g,
                      const std::string& dept, double sal)
        : Person(n, i, p), Student(n, i, p, prog, g), Staff(n, i, p, dept, sal) {
        std::cout << "TA ";
    }
};

int main() {
    std::cout << "--- [Specification Predict the Output: Diamond Hierarchy Construction] ---\n";
    TeachingAssistant ta("Karthik", 1004, "9876543210", "M.Tech CSE", 9.4, "CSE Dept", 25000.0);
    std::cout << '\n';

    std::cout << "\n[TASK 2 HIERARCHY AND DIAMOND RESOLUTION COMPLETED]\n";
    return 0;
}
