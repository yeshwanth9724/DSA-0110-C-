# Assignment 4 - Task 5: Pointers to Objects and the `this` Pointer

## 1. Problem Context: Shopping Cart Object
A grocery delivery application manages customer shopping carts, utilizing method chaining for fluent product additions and member-parameter disambiguation via the `this` pointer.

---

## 2. Functions of the `this` Pointer
1. **Method Chaining:** Returning `*this` by reference (`Cart&`) allows sequential invocations in a single statement:
   ```cpp
   c.add("Rice", 60).add("Dal", 120).setDiscount(10);
   ```
2. **Disambiguation:** Differentiates the instance member variable from a constructor/method parameter having the identical name:
   ```cpp
   this->discount = discount;
   ```
3. **Execution Output:** `324.00` (Items totaling Rs 360 minus 10% discount = Rs 324.00).
