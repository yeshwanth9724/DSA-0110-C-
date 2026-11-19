#include <iomanip>
#include <iostream>

class Money {
private:
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // Overload + as member function returning a new Money object
    Money operator+(const Money& other) const {
        Money res;
        res.paise = this->paise + other.paise;
        return res;
    }

    // Overload - as member function
    Money operator-(const Money& other) const {
        Money res;
        res.paise = this->paise - other.paise;
        return res;
    }

    // Overload += as member function returning reference to *this
    Money& operator+=(const Money& other) {
        this->paise += other.paise;
        return *this;
    }

    // Overload == as member function
    bool operator==(const Money& other) const {
        return this->paise == other.paise;
    }

    // Overload < as member function
    bool operator<(const Money& other) const {
        return this->paise < other.paise;
    }

    // Overload << as friend function for formatted printing
    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long r = m.paise / 100;
        int p = m.paise % 100;
        if (p < 0) p = -p;
        os << "Rs " << r << '.' << (p < 10 ? "0" : "") << p;
        return os;
    }
};

int main() {
    // 1. Specification Expected Test Case
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    // 2. Additional Test: Paise carry into rupees (Rs 0.75 + Rs 0.50 = Rs 1.25)
    Money p1(0, 75), p2(0, 50);
    Money p3 = p1 + p2;
    std::cout << "Carry test (0.75 + 0.50): " << p3 << '\n';

    // 3. Subtraction and compound addition
    Money d = c - Money(50, 0);
    std::cout << "After subtraction (200 - 50): " << d << '\n';
    d += Money(10, 50);
    std::cout << "After += (150 + 10.50): " << d << '\n';

    return 0;
}
