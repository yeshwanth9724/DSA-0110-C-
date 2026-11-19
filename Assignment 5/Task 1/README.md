# Assignment 5 - Task 1: Polymorphic Bill Hierarchy

## 1. Problem Context: Hospital Billing System
A multi-speciality hospital processes heterogeneous billing records: Out-Patient (consultation + tests) and In-Patient (daily room charges + surgery fees).

---

## 2. Polymorphic Architecture
- **Abstract Base Class `Bill`:** Defines pure virtual `total() const = 0` and virtual `type() const`.
- **Runtime Binding:** When invoking `b->print()` and `b->total()` across a collection of `Bill*`, dynamic dispatch via the virtual method table (vtable) selects the derived override matching the runtime dynamic type.
- **Output:**
  ```text
  OP Ravi: 1700
  IP Meena: 47500
  Total 49200
  ```
