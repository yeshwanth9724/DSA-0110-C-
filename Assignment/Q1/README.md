# Question 1: Call by Value, by Reference, and by Pointer

## 1. Problem Context: Hostel Fee Concession Updater
The hostel administration applies various concessions (e.g., Merit 10%, Sports 15%, Single Parent 25%) to students' hostel fees. When concessions are applied using pass-by-value, the changes take place only on a local copy inside the function's stack frame, leaving the student's stored record unchanged upon function return.

---

## 2. Parameter Passing Mechanisms & Implementations

### C++ Implementations
```cpp
// 1. Pass by Value
void applyByValue(long long fee, int percent) {
    fee -= (fee * percent) / 100; // Operates strictly on a local stack copy
}

// 2. Pass by Reference
void applyConcession(long long& fee, int percent) {
    fee -= (fee * percent) / 100; // Directly mutates caller's lvalue variable
}

// 3. Pass by Pointer
void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee -= (*fee * percent) / 100; // Dereferences address to mutate caller's variable
    }
}
```

### Parameter Storage and Memory Semantics
| Mechanism | Parameter Storage Location | Effect on Caller Variable | Reassignment Safety |
| :--- | :--- | :--- | :--- |
| **Pass by Value** | Allocated anew on the callee function's activation record (stack frame). Value copied into local memory. | **None.** Caller variable remains unchanged. | Only modifies isolated local memory. |
| **Pass by Reference** | An alias (internally managed address binding) directly bound to the caller's variable. No separate storage for variable content. | **Direct Mutation.** Modifies caller's memory directly. | Bound at call site; cannot be rebound to another object. |
| **Pass by Pointer** | Pointer variable allocated on callee stack frame storing memory address of caller's variable. | **Direct Mutation** via `*ptr` dereferencing. | Pointer can be checked for `nullptr`; can be rebound. |

---

## 3. Inquiry Questions & Evaluation (K5)

### Q: Why do only two of them change the caller's fee?
- **Pass by Value** creates a completely independent copy of the 8-byte `long long` variable in the callee's stack frame. When arithmetic mutations occur, only this local copy changes. When the function returns, its stack frame is unwound and destroyed, leaving the caller's fee at `45000`.
- **Pass by Reference** and **Pass by Pointer** supply the function with access to the caller's actual memory location. Reference does so implicitly via an lvalue alias, while pointer does so explicitly via memory address dereferencing (`*fee`). Hence, assignments mutate the exact memory cell belonging to the caller.

### Q: When should a `const` reference parameter be used instead?
A `const` reference parameter (`const T&`) should be used when:
1. The argument is a large or non-trivial object (e.g., `std::string`, `std::vector`, or a custom class like `Student`) where pass-by-value would cause an expensive copy constructor invocation and memory allocation ($O(N)$ or multi-byte payload copy).
2. The function is strictly a read-only observer that does **not** intend to mutate the caller's object.
3. It allows binding to temporary rvalues (e.g., literals or return expressions) safely, which non-const lvalue references prohibit.

---

## 4. Design Decision: In-Place Mutation vs. Return New Fee
### Evaluated Options:
1. **In-Place Mutation (`void apply(long long& fee, int percent)`)**:
   - *Pros:* Direct modification of student records stored in arrays or databases; zero return value management.
   - *Cons:* Side-effects make functions impure; harder to verify intermediate steps or rollback.
2. **Functional Return Value (`long long apply(long long fee, int percent)`)**:
   - *Pros:* Pure function without side-effects; highly testable; allows expressive function chaining:
     ```cpp
     long long finalFee = applyConcession(applyConcession(baseFee, 10), 15);
     ```
   - *Cons:* Requires caller to explicitly reassign the result to the record.
- **Defended Choice:** For a financial accounting and hostel fee concession system, **returning the new fee** is superior because it preserves immutability, facilitates audit trails, avoids inadvertent side effects, and cleanly chains multiple concessions without side-effect dependency order hazards.

---

## 5. Predict the Output Analysis

### Program Trace
```cpp
int a = 1, b = 2, c = 3;
change(a, b, &c);
// a is passed by value (unchanged in caller: a = 1)
// b is passed by reference (mutated in caller: b = 2 + 10 = 12)
// &c is passed by pointer (mutated via dereference: c = 3 + 10 = 13)
// Output: 1 12 13

bigger(a, c) = 100;
// bigger(a, c) evaluates (1 > 13 ? a : c) -> returns reference to c
// Assignment assigns 100 to c! a remains 1.
// Output: 1 100

show(1);          // uses y=5, z=10 -> 1 + 5 + 10 = 16
show(1, 2);       // uses z=10      -> 1 + 2 + 10 = 13
show(1, 2, 3);    // no defaults    -> 1 + 2 + 3  = 6
// Output: 16 13 6 
```

### Prediction vs. Actual Output Comparison
| Code Segment | Predicted Output | Actual Executed Output | Match Status |
| :--- | :--- | :--- | :--- |
| `change(a, b, &c)` | `1 12 13` | `1 12 13` | Exact Match |
| `bigger(a, c) = 100` | `1 100` | `1 100` | Exact Match |
| `show(...)` calls | `16 13 6 ` | `16 13 6 ` | Exact Match |

---

## 6. Alternative Concept and Complexity Analysis

### Time & Space Complexity
- **Time Complexity:** $O(1)$ for all three passing conventions (simple arithmetic instruction sequence).
- **Space Complexity Comparison:**
  - For `long long`:
    - By value: 8 bytes copied onto stack frame.
    - By reference: 8 bytes (address/pointer size under x86-64).
    - By pointer: 8 bytes address copied onto stack frame.
  - For a large `Student` object (e.g., 512 bytes with strings and grade arrays):
    - **By Value:** Copies entire 512 bytes plus deep copies of strings. $O(S)$ copy overhead, invoking copy constructors and heap allocations.
    - **By Reference (`Student&`) / Const Reference (`const Student&`):** Transmits an 8-byte pointer under the hood. $O(1)$ space, zero object copy overhead.
