# Assignment 5 - Task 2: Runtime Binding and Exception Strategy

## 1. Problem Context: Insurance Claim Settlement & Audit
Processing medical insurance claims involves multi-tier validation: checking for non-negative bill values and verifying patient coverage thresholds.

---

## 2. Virtual Function Table (vtable) Mechanics
- When `b->show()` is invoked on a `Bill*` pointing to an `OPBill` instance, `show()` calls `this->total()`.
- Because `total()` is declared virtual, the compiler generates a dynamic indirect call dereferencing the object's `_vptr` into the `OPBill` vtable, invoking `OPBill::total()` and outputting `500`.
- Calling `delete b` triggers `~OPBill()` followed by `~Bill()`, preventing memory leaks:
  `500 ~OPBill ~Bill `

---

## 3. Exception Rethrowing & Slicing Prevention
- In `settle()`, the intermediate audit catch block intercepts `ClaimError`:
  ```cpp
  catch (const ClaimError& e) {
      std::cout << "audit: " << e.what() << '\n';
      throw; // Rethrows the original polymorphic exception object
  }
  ```
- **Why `throw;` vs `throw e;`:**
  Writing `throw e;` creates a brand new exception copy, slicing derived exception types down to their base catch type. Writing `throw;` preserves the exact original active exception object and its dynamic polymorphic type.
- **Output:**
  ```text
  approved 40000
  audit: exceeds cover
  claim rejected: exceeds cover
  error: negative amount
  ```
