# Assignment 3 - Question 1: Constructors and Constructor Overloading

## 1. Problem Context: Library Book Records
A library management system manages records for books acquired under various scenarios: newly purchased books with full metadata, donated books with only titles, and placeholder records.

---

## 2. Design and Implementation Principles
- **Member Initializer Lists:** Member variables are initialized directly during object construction, avoiding default construction followed by copy assignment.
- **Constructor Delegation (`C++11`):** Constructors invoke the primary canonical constructor, eliminating code duplication.
- **Explicit Constructors:** Single-parameter constructors are qualified with `explicit` to prevent unintentional implicit conversions from `std::string` literals to `Book` objects.

---

## 3. Inquiry and Analysis (K5 Level)

### When Does the Compiler Supply a Default Constructor?
- The compiler generates a synthetic default constructor only when **no user-declared constructors exist**.
- Once any parameterized constructor is defined, the implicit default constructor is suppressed. If an array of objects is declared (`Book catalog[10];`), a default constructor must be explicitly provided.

### Member Initialization Order
- Members are initialized strictly in the order they are **declared inside the class definition**, not the order in which they appear in the constructor initializer list. Specifying initializers out of order prompts compiler warning `-Wreorder`.

### Explicit Constructor Evaluation
```cpp
void processBook(const Book& b);

// Without explicit:
processBook("Design Patterns"); // Implicitly converts string to Book (accidental temporary)

// With explicit:
processBook(Book("Design Patterns")); // Requires explicit instantiation, preventing bugs
```
