# Question 4: Specifying a Class with an Array Inside It

## 1. Problem Context: Savings Account Mini-Statement
An automated teller machine (ATM) requires a `SavingsAccount` class to record and display the last 10 financial transactions (deposits and withdrawals) for printing mini-statements. Older transactions beyond the 10 most recent entries must be discarded.

---

## 2. Class Specification and Scope Resolution Design

### Member Function Placement
- **Defined Inside Class:** `deposit(double amount)` and constructors (inlined for rapid execution of frequent transactions).
- **Defined Outside Class (via `::`):** `withdraw(double amount)` and `miniStatement()` (separates interface from implementation, reducing header clutter and compilation dependencies).

```cpp
class SavingsAccount {
private:
    long long accountNumber;
    double balance;
    static const int MAX_TX = 10;
    double transactions[MAX_TX]; // Fixed-size array embedded inside object
    int count;

public:
    SavingsAccount(long long accNo, double initBal);
    bool deposit(double amount);                   // Defined inside
    bool withdraw(double amount);                  // Defined outside
    void miniStatement() const;                    // Defined outside
    void recordTransaction(double amount);
};
```

---

## 3. Inquiry Questions & Evaluation (K5)

### Q: Why must the array be private?
1. **Encapsulation & Data Invariant Preservation:** The transaction history must strictly reflect actual deposits and withdrawals. If `transactions[]` were public, client code could tamper with transaction logs without adjusting `balance`, creating irreconcilable audit discrepancies.
2. **Implementation Hiding:** Client code is shielded from the underlying storage mechanism (shifting array vs. circular buffer vs. linked list), allowing maintainers to optimize storage without breaking public APIs.

### Q: What happens when the 11th transaction arrives? (Shifting vs. Circular Buffer)
- **Shifting Fixed Array:**
  - *Mechanism:* Elements at indices $1 \dots 9$ are shifted left to indices $0 \dots 8$, overwriting the oldest transaction at index $0$. The new transaction is written at index $9$.
  - *Cost:* Requires $(k - 1)$ copy assignments. For $k$ elements, time complexity is **$O(k)$**.
- **Circular Buffer (Ring Buffer):**
  - *Mechanism:* Employs a `start` pointer/index. The new transaction directly overwrites `transactions[start]`, and the pointer advances: `start = (start + 1) % CAPACITY`.
  - *Cost:* Involves exactly one array write and one modular increment. Time complexity is strictly **$O(1)$**.

---

## 4. Design Decision: Scaling from 10 to 50 Transactions

### Problem:
The bank extends the requirement to remember the last 50 transactions.

### Evaluation of Options:
1. **Shifting Array of Size 50:**
   - Every single transaction now incurs 49 element shifts ($O(50)$). Under high ATM transaction volume, this wastes processor cycles in data movement.
2. **Circular Buffer / Templated Ring Buffer:**
   - Changing capacity from 10 to 50 merely changes the buffer constant (`CAPACITY = 50`).
   - Insertion time remains strictly **$O(1)$** (1 single write).
   - Zero element data movement.

**Defended Decision:** The **Circular Buffer design** changes least in algorithmic overhead. It guarantees $O(1)$ constant-time insertion regardless of whether the bank requests 10, 50, or 10,000 transactions.

---

## 5. Alternative Concept and Complexity Analysis

| Data Structure / Strategy | Add Transaction Time | Mini-Statement Time | Auxiliary Space per Account | Heap Allocation Overhead |
| :--- | :--- | :--- | :--- | :--- |
| **Fixed Array (Shifting)** | $O(k)$ | $O(k)$ | Exactly $k \times 8$ bytes | None (contiguous inside object) |
| **Fixed Array (Circular Buffer)** | **$O(1)$** | $O(k)$ | $(k \times 8) + 8$ bytes (indices) | None (contiguous inside object) |
| **`std::deque` (`push_back` / `pop_front`)** | Amortized $O(1)$ | $O(k)$ | Dynamic node map + chunk overhead | Incurs heap allocation and pointer dereference overhead |

**Conclusion:** The **Circular Buffer embedded directly in the class** achieves optimal $O(1)$ time complexity while avoiding heap allocation fragments, maximizing CPU cache locality and ATM transaction throughput.
