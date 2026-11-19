#include <iostream>
#include <string>

// Specification Predict the Output Structs
struct Engine {
    Engine() { std::cout << "Engine "; }
    ~Engine() { std::cout << "~Engine "; }
};

struct Vehicle {
    Vehicle() { std::cout << "Vehicle "; }
    ~Vehicle() { std::cout << "~Vehicle "; }
};

struct Car : Vehicle {
    Engine e;
    Car() { std::cout << "Car "; }
    ~Car() { std::cout << "~Car "; }
};

void runVehiclePrediction() {
    std::cout << "--- [Specification Predict the Output: Construction & Destruction Order] ---\n";
    {
        Car c;
        std::cout << "| ";
    }
    std::cout << "\n\n";
}

// Complete the Code Classes
class Person {
protected:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {}
};

class Address {
private:
    std::string city;
    int pin;

public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Student : public Person {
private:
    long long regNo;
    Address home;

public:
    // Initializer list passing to base Person and member Address
    Student(const std::string& n, int a, long long r, const std::string& c, int p)
        : Person(n, a), regNo(r), home(c, p) {}

    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") " << home.str() << '\n';
    }
};

int main() {
    runVehiclePrediction();

    std::cout << "--- [Specification Complete the Code Output] ---\n";
    Student s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();

    std::cout << "\n[TASK 3 CONSTRUCTORS IN DERIVED AND MEMBER CLASSES COMPLETED]\n";
    return 0;
}
