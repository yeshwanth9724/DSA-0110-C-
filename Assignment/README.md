# ASSIGNMENT 2 – CO2: Object-Oriented Programming in C++

**Course Module:** CO2 Coverage – Functions & Object-Oriented Programming Concepts  
**Bloom’s Taxonomy Assessment Level:** K5 – Evaluate  
**Author / Student:** Yeshwanth (GitHub: [@yeshwanth9724](https://github.com/yeshwanth9724))  
**Repository:** [https://github.com/yeshwanth9724/DSA-0110-C-](https://github.com/yeshwanth9724/DSA-0110-C-)  
**Compiler & Version:** `g++ (MinGW-W64 x86_64-ucrt-posix-seh) 14.2.0`  
**Standard & Compilation Flags:** `g++ -std=c++17 -Wall -Wextra` (with `-O2` for performance investigations)  

---

## Repository & Assignment Architecture

The work is organized within the `Assignment` folder, partitioned into dedicated subdirectories per task. Each folder contains the standalone C++ source code (`main.cpp`), high-resolution executed terminal output screenshots (`output.png`), and an in-depth analytical report (`README.md`).

```
Assignment/
├── README.md                  # Comprehensive Assignment 2 Evaluation Report
├── Q1/                        # Q1 - Call by Value, by Reference, and by Pointer
│   ├── main.cpp
│   ├── output.png
│   └── README.md
├── Q2/                        # Q2 - Return by Reference and Its Dangers
│   ├── main.cpp
│   ├── output.png
│   └── README.md
├── Q3/                        # Q3 - Default Arguments and Function Overloading
│   ├── main.cpp
│   ├── output.png
│   └── README.md
├── Q4/                        # Q4 - Specifying a Class with an Array Inside It
│   ├── main.cpp
│   ├── output.png
│   └── README.md
├── Q5/                        # Q5 - Static Members and Arrays of Objects
│   ├── main.cpp
│   ├── output.png
│   └── README.md
├── Q6/                        # Q6 - Friend Functions and Inline Functions
│   ├── main.cpp
│   ├── output.png
│   └── README.md
└── Q7/                        # Q7 - Day-4 Design Challenge: Diagnose, Redesign & Validate
    ├── main.cpp
    ├── output.png
    └── README.md
```

---

## Compilation and Execution Guide

To compile and run any task independently from the repository root:

```powershell
# Navigate into the desired task folder
cd Assignment/Q1

# Compile with strict warnings
g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe

# Execute binary
.\main.exe
```

For performance benchmark tasks (Q6 and Q7):
```powershell
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o main.exe
.\main.exe
```

---

## Task Summaries and Evaluation Evidence

### Task 01: Call by Value, by Reference, and by Pointer (Q1)
- **Problem Context:** Hostel Fee Concession Updater (Merit 10%, Sports 15%, Single Parent 25%).
- **Key Concepts Evaluated:**
  - *Call by Value:* Copies parameter into function stack frame; modifications discard upon return (`45000` remains `45000`).
  - *Call by Reference & Pointer:* Binds directly to caller's lvalue / dereferences memory address; mutates caller fee (`45000` becomes `40500`).
  - *Const Reference:* Used for non-trivial objects to eliminate copy overhead while enforcing read-only safety.
- **Predict the Output Program:**
  - Predictions: `1 12 13` | `1 100` | `16 13 6 `
  - Actual Output: `1 12 13` | `1 100` | `16 13 6 ` (100% Exact Match).
- **Alternative Design:** Pure functional return style (`long long apply(long long, int)`) defended for transaction auditability and pure immutability.
- **Executed Screenshot:** `Assignment/Q1/output.png`

---

### Task 02: Return by Reference and Its Dangers (Q2)
- **Problem Context:** Examination Marks Register with moderation (+2 grace marks applied to highest score).
- **Key Concepts Evaluated:**
  - Returning an lvalue reference (`int&`) allows the function call itself to appear on the left-hand side of an assignment (`findHighestMark(marks, n) += 2;`).
  - Returning a reference to an automatic local variable creates a **dangling reference**, diagnosed by GCC warning `[-Wreturn-local-addr]`, leading to Undefined Behavior (UB).
  - *Const Reference vs. Copy:* `const int&` forbids LHS assignment; value copy creates an independent rvalue.
- **Changed Condition (std::vector growth):** Dynamic reallocation invalidates existing references/pointers when internal buffers relocate to new heap addresses.
- **Alternative Design:** Returning an array/vector **index (`int`)** defended as the only approach completely immune to container memory relocations.
- **Executed Screenshot:** `Assignment/Q2/output.png`

---

### Task 03: Default Arguments and Function Overloading (Q3)
- **Problem Context:** Courier Charge Calculator by weight with optional express delivery and insurance.
- **Key Concepts Evaluated:**
  - *Ambiguity Diagnosis:* Having both `charge(double)` and `charge(double, bool = false, bool = false)` creates an unresolvable compiler ambiguity when invoked with a single double literal.
  - *Redesign:* Consolidated default arguments from right to left; overloaded across data types (`int` grams, `double` kg, `Parcel` struct).
  - *Overload Resolution Hierarchy:* Exact match $\succ$ Promotion (`float` to `double`) $\succ$ Standard Conversion (`float` to `int`).
- **Executed Screenshot:** `Assignment/Q3/output.png`

---

### Task 04: Specifying a Class with an Array Inside It (Q4)
- **Problem Context:** Savings Account ATM Mini-Statement remembering the last 10 transactions.
- **Key Concepts Evaluated:**
  - *Encapsulation:* Private transaction array prevents external state tampering and decouples storage implementation from public contracts.
  - *Scope Resolution Operator:* Member functions defined inside class (`deposit`) vs outside using `SavingsAccount::withdraw`.
  - *11th Transaction Arrival:* Fixed array shifting costs $O(k)$ copy operations; Circular Ring Buffer costs strictly $O(1)$.
- **Extension to 50 Transactions:** Circular buffer design defended as it scales seamlessly with zero data movement penalty.
- **Executed Screenshot:** `Assignment/Q4/output.png`

---

### Task 05: Static Members and Arrays of Objects (Q5)
- **Problem Context:** College Bus Seat Tickets with fixed capacity and automatic waiting list.
- **Key Concepts Evaluated:**
  - *Class-Level State:* Static data member `BusTicket::issued` defined once at file scope; accessible via `BusTicket::count()`.
  - *Static Member Function Restrictions:* Cannot access `this` pointer or instance variables because it operates without instance context.
  - *Array Initialization:* Constructing `BusTicket trip[4]` sequentially executes constructors, allocating seats 1, 2, 3 and placing passenger 4 on Waiting list.
- **Multi-Bus Scalability:** Evaluated static members vs. a dedicated `TicketOffice` domain object, proving the latter allows multiple concurrent buses.
- **Executed Screenshot:** `Assignment/Q5/output.png`

---

### Task 06: Friend Functions and Inline Functions (Q6)
- **Problem Context:** Train Journey Planner calculating durations between private `Time` instances.
- **Key Concepts Evaluated:**
  - *Symmetry of Binary Operators:* Friend functions (`minutesBetween(a, b)`) model symmetric operations without favoring one operand.
  - *Encapsulation Defense:* Private `h` and `m` enforce domain invariants ($0 \le h < 24$, $0 \le m < 60$) that public fields would forfeit.
  - *Inline Function Optimization:* Eliminates subroutine calling overhead (stack frame allocation and call/ret instructions).
- **10,000,000 Call Benchmark:**
  - `-O0` (Debug): $33.13\text{ ms}$
  - `-O2` (Release): $4.84\text{ ms}$ ($\approx 7.0\times$ speedup)
- **Executed Screenshot:** `Assignment/Q6/output.png`

---

### Task 07: Day-4 Design Challenge – Diagnose, Redesign and Validate (Q7)
- **Problem Selected:** Q4 Savings Account Mini-Statement Buffer.
- **Diagnose (Limitation):** The linear shifting array copies $k - 1$ elements on every transaction once full ($O(k)$ penalty), causing severe throughput degradation as capacity $k$ increases.
- **Objective:** Achieve strict $O(1)$ constant-time insertion with zero dynamic heap allocation.
- **Redesign:** Templated Zero-Heap Circular Ring Buffer (`CircularSavingsAccount<Capacity>`) with modular pointer arithmetic (`(head + 1) % Capacity`).
- **Empirical Validation ($N = 100,000$ Transactions):**
  - $k = 10$: $1.504\text{ ms} \to 0.480\text{ ms}$ (**$3.1\times$ faster**)
  - $k = 50$: $1.891\text{ ms} \to 0.686\text{ ms}$ (**$2.8\times$ faster**)
  - $k = 500$: $5.949\text{ ms} \to 0.571\text{ ms}$ (**$10.4\times$ faster**)
- **Parity Check:** Functional parity confirmed 100% identical transaction logs.
- **Executed Screenshot:** `Assignment/Q7/output.png`

---

## Progressive Commit History

Per assignment instructions, each task was completed, verified, and committed progressively:
1. `Task 01: Complete Q1 - Call by Value, Reference, and Pointer with test execution and output screenshot`
2. `Task 02: Complete Q2 - Return by Reference and Its Dangers with vector invalidation test and output screenshot`
3. `Task 03: Complete Q3 - Default Arguments and Overload Resolution with 6 test calls and output screenshot`
4. `Task 04: Complete Q4 - Specifying a Class with an Array Inside It and Mini-Statement with output screenshot`
5. `Task 05: Complete Q5 - Static Members and Arrays of Objects with multi-bus test and output screenshot`
6. `Task 06: Complete Q6 - Friend Functions, Inline Functions and 10M Benchmark with output screenshot`
7. `Task 07: Complete Day-4 Design Challenge - Diagnose, Redesign and Validate with empirical benchmark and output screenshot`
8. `Assignment: Add Master README documentation and evaluation summary`
