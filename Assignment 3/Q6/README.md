# Assignment 3 - Question 6: The Rules of Operator Overloading

## 1. Problem Context: Custom Text Class for an SMS Gateway
A high-reliability SMS gateway implements a custom memory-controlled `Text` class wrapping raw heap `char*` strings.

---

## 2. Fundamental Rules of Operator Overloading in C++
1. **Operators that Cannot Be Overloaded:**
   - `::` (Scope Resolution): Essential for symbol name lookup at compile time.
   - `.` (Member Access): Core mechanism for accessing members directly.
   - `.*` (Pointer-to-Member Dereference): Built into type system semantics.
   - `?:` (Ternary Conditional): Evaluates operands conditionally (short-circuiting); overloading would evaluate all expressions.
   - `sizeof` / `typeid` / `alignof`: Evaluated at compile time to query object layouts.
2. **Precedence and Arity are Immutable:** An overloaded `*` always has higher precedence than `+`; binary operators cannot become unary or ternary.
3. **User-Defined Type Requirement:** At least one operand must be a user-defined class/struct/enum type. Primitive operator behaviors cannot be modified.
4. **Member-Only Operators:** `operator=`, `operator[]`, `operator()`, and `operator->` must be non-static member functions to prevent hijacking standard object assignment and invocation semantics.
