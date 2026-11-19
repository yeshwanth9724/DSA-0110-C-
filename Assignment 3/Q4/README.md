# Assignment 3 - Question 4: Overloading Arithmetic and Stream Operators

## 1. Problem Context: Money Arithmetic for a Billing Counter
A billing counter calculates monetary totals using integer `paise` internally to eliminate floating-point precision inaccuracies (such as $0.1 + 0.2 \ne 0.3$).

---

## 2. Design of Operators
- **Binary `+` and `-` (Return by value):** Produces a new independent `Money` object representing the sum/difference without modifying either operand.
- **Compound `+=` (Return by reference `Money&`):** Mutates the left operand in place and returns `*this` to support assignment chaining (`(m1 += m2) += m3`).
- **Stream Insertion `<<` (Non-member Friend):** Must be a non-member function because the left-hand operand is `std::ostream&` (e.g., `std::cout`), not `Money`.

---

## 3. Inquiry Questions & Evaluation (K5)
- **Why `operator+` returns a new object while `operator+=` returns `*this`:**
  `+` is a non-mutating arithmetic operator; `a + b` leaves both `a` and `b` unchanged, requiring a freshly constructed rvalue. Conversely, `+=` is an assignment operator with the side-effect of modifying the left-hand operand in place.
- **Why `operator<<` cannot be a member function of `Money`:**
  In C++, a member operator places the invoking object implicitly as the left operand. If `<<` were a member function, invocation syntax would awkwardly be `m << std::cout` instead of `std::cout << m`.
