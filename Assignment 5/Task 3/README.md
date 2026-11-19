# Assignment 5 - Task 3: Virtual Functions vs. switch vs. Exceptions: The Cost

## 1. Problem Context: Empirical Cost Analysis
A hospital billing engine processes millions of daily transactions. We benchmark:
1. Virtual dynamic dispatch vs. explicit tag-and-switch structures.
2. Return codes vs. C++ exception handling under variable failure rates.

---

## 2. Empirical Benchmark Findings
*Compiled with GCC 14.2.0 at `-O2` optimization for $1,000,000$ operations:*

| Architecture Pattern | Execution Time (1M Bills) | Per-Bill Cost | Extensibility Impact |
| :--- | :--- | :--- | :--- |
| **Tagged `switch`** | $4.56\text{ ms}$ | $\approx 4.56\text{ ns}$ | Modifies existing functions whenever a new type is added (Violates OCP). |
| **Virtual Dispatch (`vtable`)**| $4.58\text{ ms}$ | $\approx 4.58\text{ ns}$ | Zero modification to existing classes; runtime polymorphism preserves OCP. |

---

## 3. Cost of Exception Handling
- **Zero-Cost Exception Model:** In modern Itanium/x86_64 ABI C++, `try` blocks incur **zero runtime cost** on the normal execution path ($0.00\text{ ms}$ for $1\text{M}$ successful validations).
- **Throw & Unwind Cost:** When an exception is thrown, the runtime must search metadata unwinding tables and invoke local destructors ($28.70\text{ ms}$ for $10,000$ throws).
- **Engineering Rule:** Exceptions should be reserved for truly exceptional error conditions (e.g., hardware/network failures, out-of-range cover violations), never for standard loop control flow.
