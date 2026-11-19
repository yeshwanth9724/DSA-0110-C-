# Assignment 3 - Question 3: Dynamic Constructors and Destructors

## 1. Problem Context: Auditorium Seat Booking
An auditorium management application allocates a 2D seat matrix (`char** seatMap`) dynamically based on varying row and column configurations for different events.

---

## 2. RAII (Resource Acquisition Is Initialization)
- **Acquisition in Constructor:** The 2D array is allocated via `new char*[rows]` followed by `new char[seatsPerRow]` for each row.
- **Release in Destructor:** The destructor cleans up each row with `delete[]` and the top-level pointer table, guaranteeing leak-free cleanup regardless of exit pathways.

---

## 3. Predict the Output Analysis (Logger Lifetimes)
- Program Trace:
  1. `Logger a("A")`: Output `+A `
  2. Nested Block `{ Logger b("B"); }`: Output `+B -B ` (constructed, then destroyed at closing brace)
  3. `use(a)`: Pass-by-value invokes copy constructor: `copyAc `, then `use `, then temporary destroyed: `-Ac `
  4. Heap object `Logger* p = new Logger("P")`: Output `+P `
  5. `delete p`: Explicit destruction: Output `-P `
  6. Final message and stack unwinding: Output `end -A `
- **Final Output:** `+A +B -B copyAc use -Ac +P -P end -A `
