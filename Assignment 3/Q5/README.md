# Assignment 3 - Question 5: Overloading Increment, Comparison and Subscript Operators

## 1. Problem Context: Music Playlist and Track Timer
A media playback engine requires a precise `Time` accumulator supporting prefix/postfix increment operations and a `Playlist` supporting safe subscript indexing with bounds validation.

---

## 2. Syntax & Mechanics of Increment Overloading
- **Prefix `++t` (`Type& operator++()`):** Directly increments state and returns a reference to `*this`. Incurs zero temporary object allocation.
- **Postfix `t++` (`Type operator++(int)`):** Requires a dummy `int` parameter to distinguish its signature from prefix `++`. Must preserve the pre-increment state in a local temporary copy, increment `*this`, and return the copy by value. Hence, postfix `++` is inherently slower for non-trivial class types.

---

## 3. Subscript Overloading: Const vs. Non-Const Overloads
```cpp
// Non-const: provides writeable lvalue reference
std::string& operator[](int index);

// Const: provides read-only const reference for const Playlist instances
const std::string& operator[](int index) const;
```
If an out-of-range index is passed (e.g., negative or $\ge \text{count}$), the operator throws `std::out_of_range`, preventing undefined buffer overreads.
