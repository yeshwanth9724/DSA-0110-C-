# Assignment 4 - Task 4: Pointers to Derived Classes: Forensics

## 1. Defect Identification & Forensics
1. **Static Early Binding of Non-Virtual Functions:** Calling `a->rate()` through an `Account*` pointer executes `Account::rate()` at compile time, ignoring the overridden `SeniorAccount::rate()` implementation.
2. **Memory Leak via Non-Virtual Destructor:** Deleting a derived object through a base pointer (`Account*`) with a non-virtual destructor invokes only `~Account()`, completely bypassing `~SeniorAccount()`. Any dynamically allocated memory (such as `history`) is leaked.
3. **Object Slicing:** Assigning a `SeniorAccount` to an `Account` value object slices off the derived portion, retaining only the base object slice.

---

## 2. Prevention Rules
- Any polymorphic base class possessing virtual functions must declare a **virtual destructor** (`virtual ~Base() = default;`).
- Use the `override` keyword on all overriding functions in derived classes so the compiler detects signature mismatches at compile time.
