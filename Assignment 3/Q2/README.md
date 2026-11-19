# Assignment 3 - Question 2: Copy Constructors: Shallow and Deep Copies

## 1. Problem Context: Hospital Prescription Records
Hospital prescriptions store an array of dynamically allocated medicine names (`std::string* medicines`). Without a user-defined copy constructor, memberwise shallow copy replicates the pointer address, leaving multiple objects referencing identical heap memory.

---

## 2. Dangers of Shallow Copy (Double Free Bug)
- **Shared Heap Pointer:** A shallow copy assigns `medicines = other.medicines`.
- **Double Delete Error:** When both objects exit scope, each destructor attempts `delete[] medicines` on the identical address, causing heap corruption and crash (`double free or corruption`).

---

## 3. The Rule of Three
If a class manages raw heap resources and defines any of the following, it must define all three:
1. **Destructor:** To free the dynamically allocated resource.
2. **Copy Constructor:** To perform a deep copy into a newly allocated buffer.
3. **Copy Assignment Operator:** To guard against self-assignment (`if (this != &other)`), deallocate old storage, and allocate/copy new elements.
