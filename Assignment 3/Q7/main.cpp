#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructors
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    // Arithmetic operators
    Complex operator+(const Complex& o) const {
        return Complex(real + o.real, imag + o.imag);
    }

    Complex operator-(const Complex& o) const {
        return Complex(real - o.real, imag - o.imag);
    }

    Complex operator*(const Complex& o) const {
        return Complex(real * o.real - imag * o.imag, real * o.imag + imag * o.real);
    }

    Complex operator/(const Complex& o) const {
        double denom = o.real * o.real + o.imag * o.imag;
        if (denom == 0.0) {
            throw std::runtime_error("Division by zero in complex arithmetic");
        }
        return Complex((real * o.real + imag * o.imag) / denom,
                       (imag * o.real - real * o.imag) / denom);
    }

    bool operator==(const Complex& o) const {
        return std::abs(real - o.real) < 1e-9 && std::abs(imag - o.imag) < 1e-9;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << std::fixed << std::setprecision(2);
        os << '(' << c.real;
        if (c.imag >= 0) {
            os << " + j" << c.imag;
        } else {
            os << " - j" << -c.imag;
        }
        os << ')';
        return os;
    }
};

int main() {
    std::cout << "--- [AC Circuit Impedance Calculator] ---\n";

    // Component parameters: R = 10 Ohm, L = 0.05 H, C = 100 uF (1e-4 F), freq = 50 Hz -> omega = 314.159 rad/s
    double R = 10.0;
    double omega = 314.159;
    double L = 0.05;
    double C = 100e-6;

    Complex Zr(R, 0.0);
    Complex Zl(0.0, omega * L);
    Complex Zc(0.0, -1.0 / (omega * C));

    std::cout << "Resistor Impedance (Zr): " << Zr << " Ohms | Magnitude: " << Zr.magnitude() << " Ohms\n";
    std::cout << "Inductor Impedance (Zl): " << Zl << " Ohms | Magnitude: " << Zl.magnitude() << " Ohms\n";
    std::cout << "Capacitor Impedance(Zc): " << Zc << " Ohms | Magnitude: " << Zc.magnitude() << " Ohms\n\n";

    // 1. Series RLC Circuit: Z_series = Zr + Zl + Zc
    Complex Zseries = Zr + Zl + Zc;
    std::cout << "Series RLC Total Impedance: " << Zseries << " Ohms\n";
    std::cout << "Series Magnitude: " << Zseries.magnitude() << " Ohms\n\n";

    // 2. Parallel LC Network: Z_parallel = (Zl * Zc) / (Zl + Zc)
    Complex Zparallel_lc = (Zl * Zc) / (Zl + Zc);
    std::cout << "Parallel LC Total Impedance: " << Zparallel_lc << " Ohms\n";
    std::cout << "Parallel Magnitude: " << Zparallel_lc.magnitude() << " Ohms\n\n";

    // 3. Division by Zero Safety Test
    std::cout << "--- [Division by Zero Safety Test] ---\n";
    try {
        Complex zeroImpedance(0.0, 0.0);
        Complex testDiv = Zr / zeroImpedance;
        std::cout << "Result: " << testDiv << '\n';
    } catch (const std::runtime_error& e) {
        std::cout << "Caught Exception: " << e.what() << " -> Safely handled without crash.\n";
    }

    std::cout << "\n[Q7 COMPLEX NUMBER CLASS DESIGN COMPLETED SUCCESSFULLY]\n";
    return 0;
}
