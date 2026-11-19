# Assignment 4 - Task 3: Constructors in Derived Classes and Member Classes

## 1. Problem Context: Order of Construction and Destruction
Managing class composition (`Address` inside `Student`) along with class inheritance (`Student : public Person`) requires understanding the strict order of initialization and cleanup in C++.

---

## 2. Order of Construction & Destruction Rules
1. **Construction Order:**
   - Base class constructors execute first (in declaration order: `Vehicle`).
   - Member object constructors execute second (in declaration order: `Engine e`).
   - The derived class constructor body executes last (`Car`).
2. **Destruction Order (Strict Reverse):**
   - The derived class destructor executes first (`~Car`).
   - Member object destructors execute second (`~Engine`).
   - Base class destructors execute last (`~Vehicle`).
3. **Trace Output:** `Vehicle Engine Car | ~Car ~Engine ~Vehicle `

---

## 3. Initializer Lists in Derived Classes
Derived classes cannot directly initialize base class private/protected members inside the constructor body. They must pass parameters through the constructor initializer list:
```cpp
Student(const std::string& n, int a, long long r, const std::string& c, int p)
    : Person(n, a), regNo(r), home(c, p) {}
```
Output: `192311001 Kavya (19) Salem-636001`
