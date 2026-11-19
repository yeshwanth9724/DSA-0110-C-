# Assignment 3 - Question 7: Design a Complex-Number Class from First Principles

## 1. Problem Context: AC Circuit Impedance Calculator
Electrical engineering systems model AC electrical impedances using complex numbers where resistance is purely real ($R + 0j$) and reactive elements are purely imaginary ($Z_L = 0 + j\omega L$, $Z_C = 0 - j/(\omega C)$).

---

## 2. Four-Stage K5 Design Process

### Stage 1: Interpret the Problem
- **Data Attributes:** Cartesian components `double real` and `double imag`.
- **Operations Required:** Addition ($Z_{\text{series}}$), subtraction, multiplication, division ($Z_{\text{parallel}}$), magnitude computation $\sqrt{r^2 + i^2}$, and stream insertion.

### Stage 2: Operator Overloading Design
- **Formulas:**
  - Addition: $(a + jb) + (c + jd) = (a + c) + j(b + d)$
  - Multiplication: $(a + jb)(c + jd) = (ac - bd) + j(ad + bc)$
  - Division: $\frac{a + jb}{c + jd} = \frac{ac + bd}{c^2 + d^2} + j\frac{bc - ad}{c^2 + d^2}$ (guarded by denominator check $c^2 + d^2 > 0$).

### Stage 3: Implementation & Empirical Verification
- **Test Case:** $R = 10\,\Omega$, $L = 0.05\,\text{H}$, $C = 100\,\mu\text{F}$, $\omega = 314.159\,\text{rad/s}$.
  - $Z_R = 10.00 + j0.00$
  - $Z_L = 0.00 + j15.71$
  - $Z_C = 0.00 - j31.83$
  - $Z_{\text{series}} = 10.00 - j16.12\,\Omega$, $|Z_{\text{series}}| = 18.97\,\Omega$.
  - Hand verification matches code execution exactly.

### Stage 4: Comparison with `std::complex<double>`
- Custom `Complex` class encapsulates domain-specific formatted streaming `(R + jX)` and explicit zero-division exception handling.
- `std::complex<double>` yields `(inf, inf)` on zero division rather than throwing domain exceptions.
