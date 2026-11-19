# Question 3: Default Arguments and Function Overloading

## 1. Problem Context: Courier Charge Calculator
A courier office calculates dispatch charges based on package weight, with optional express delivery and insurance add-ons. 
The developer initially declared:
```cpp
double charge(double weight);
double charge(double weight, bool express);
double charge(double weight, bool express = false, bool insured = false);
```
This failed to compile due to function call ambiguity.

---

## 2. Diagnosis of the Compiler Error (Ambiguity)
When the caller invokes `charge(5.0)`:
- Candidate 1: `charge(double)` matches with 1 argument.
- Candidate 3: `charge(double, bool = false, bool = false)` can also be called with 1 argument by supplying default arguments for the 2nd and 3rd parameters.

Because both candidates match the argument list with equal fidelity (exact match of type `double`), the compiler cannot determine which function the programmer intended to call. The compiler emits:
```text
error: call of overloaded 'charge(double)' is ambiguous
```
Similarly, `charge(5.0, true)` creates an ambiguity between Candidate 2 and Candidate 3.

---

## 3. Redesigned Solution
To eliminate ambiguity while supporting short common calls and diverse input types:
1. **Consolidate default arguments:** Remove redundant overloads `charge(double)` and `charge(double, bool)`. A single signature handles 1, 2, or 3 arguments:
   ```cpp
   double charge(double weightKg, bool express = false, bool insured = false);
   ```
2. **Support different units via overloading:** Handle weights provided in grams:
   ```cpp
   double charge(int weightGrams, bool express = false, bool insured = false);
   ```
3. **Support aggregate objects:** Pass structured package information:
   ```cpp
   double charge(const Parcel& p);
   ```

---

## 4. Prediction vs. Actual Overload Resolution

| Call | Passed Type | Predicted Overload | Executed Overload | Resolution Reason |
| :--- | :--- | :--- | :--- | :--- |
| `charge(2.5)` | `double` | `charge(double, ...)` | `charge(double, ...)` | **Exact Match**: `2.5` is `double`. |
| `charge(500)` | `int` | `charge(int, ...)` | `charge(int, ...)` | **Exact Match**: `500` is `int`. |
| `charge(2)` | `int` | `charge(int, ...)` | `charge(int, ...)` | **Exact Match**: `2` is `int` (not `double`). |
| `charge(2.0f)` | `float` | `charge(double, ...)` | `charge(double, ...)` | **Promotion**: `float` $\to$ `double` is a floating-point promotion, which outranks conversion (`float` $\to$ `int`). |
| `charge(3.0, true)` | `double, bool` | `charge(double, ...)` | `charge(double, ...)` | **Exact Match**: matches 2 arguments; `insured` defaults to `false`. |
| `charge(Parcel{...})` | `Parcel` | `charge(const Parcel&)` | `charge(const Parcel&)` | **Exact Match**: User-defined type. |

---

## 5. Inquiry: C++ Overload Resolution Rules

The compiler resolves overloaded function calls in strict hierarchical tiers:
1. **Exact Match:** Parameter types match argument types exactly (including trivial adjustments like array-to-pointer or adding `const`).
2. **Promotion:**
   - Integral promotions (e.g., `char`, `short`, `bool` $\to$ `int`).
   - Floating-point promotions (e.g., `float` $\to$ `double`).
3. **Standard Conversion:** Converting numeric types across families (e.g., `int` $\to$ `double`, `double` $\to$ `int`, pointer conversions).
4. **User-Defined Conversion:** Invoking single-argument constructors or conversion operators.
5. **Ellipsis (`...`):** Catch-all match.

### Why Default Arguments Must Be Given from the Right
In C++, function call arguments are bound strictly **positionally from left to right**. 
If a function had `void f(int a = 10, int b);`, and the caller invoked `f(5)`, the compiler would bind `5` to `a`, leaving `b` unbound with no legal way to supply an argument. Thus, the C++ language grammar mandates that any parameter with a default value must have all subsequent parameters to its right also defaulted.

---

## 6. Alternative Concept and Complexity Analysis

### Alternative: Single Parcel Structure with Optional Fields
Instead of multiple overloads, accept a single configuration struct:
```cpp
struct ParcelOptions {
    double weightKg;
    bool express = false;
    bool insured = false;
};
double charge(const ParcelOptions& opt);
```

### Performance & Scalability Comparison:
- **Time Complexity of Overload Resolution:** Exactly **$O(1)$ at compile time** with zero run-time overhead. The compiler generates direct jumps/calls to the mangled symbol.
- **Space Copied per Call:**
  - Overloaded functions: Only scalar parameters are pushed to registers/stack ($8$ bytes for double, $1$ byte for bools).
  - `Parcel` passed by const reference (`const Parcel&`): Transmits only an 8-byte pointer, regardless of how many fields are added.
- **Handling New Options:** Adding a new option (e.g., `bool fragile`) to overloads requires updating all default lists, potentially causing exponential overload explosions. With a `Parcel` struct, adding fields requires zero changes to existing call sites that utilize default struct initializers.
