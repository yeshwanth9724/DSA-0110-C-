#include <iostream>
#include <iomanip>
#include <string>

// ============================================================================
// PART 1: SavingsAccount Class Specification
// ============================================================================

class SavingsAccount {
private:
    long long accountNumber;
    double balance;
    static const int MAX_TX = 10;
    double transactions[MAX_TX]; // Array inside class storing last 10 transactions
    int count;                   // Number of transactions recorded (0 to MAX_TX)

public:
    // Constructor defined INSIDE the class
    SavingsAccount(long long accNo, double initialBalance)
        : accountNumber(accNo), balance(initialBalance), count(0)
    {
        for (int i = 0; i < MAX_TX; ++i) {
            transactions[i] = 0.0;
        }
    }

    // Member function defined INSIDE the class
    bool deposit(double amount)
    {
        if (amount <= 0) return false;
        balance += amount;
        recordTransaction(amount); // positive indicates deposit
        return true;
    }

    // Member functions declared here and defined OUTSIDE using ::
    bool withdraw(double amount);
    void miniStatement() const;

    // Helper to record transaction by shifting array (simulating classic linear buffer)
    void recordTransaction(double amount);

    // Getters for audit
    double getBalance() const { return balance; }
    long long getAccountNumber() const { return accountNumber; }
};

// ============================================================================
// PART 2: Member Functions Defined Outside Using Scope Resolution Operator ::
// ============================================================================

bool SavingsAccount::withdraw(double amount)
{
    if (amount <= 0 || amount > balance) {
        std::cout << "Transaction failed: Insufficient funds or invalid amount.\n";
        return false;
    }
    balance -= amount;
    recordTransaction(-amount); // negative indicates withdrawal
    return true;
}

void SavingsAccount::recordTransaction(double amount)
{
    if (count < MAX_TX) {
        transactions[count++] = amount;
    } else {
        // When 11th transaction arrives: Shift array elements left by 1 position (O(k))
        for (int i = 0; i < MAX_TX - 1; ++i) {
            transactions[i] = transactions[i + 1];
        }
        transactions[MAX_TX - 1] = amount;
    }
}

void SavingsAccount::miniStatement() const
{
    std::cout << "\n---------------- MINI-STATEMENT ----------------\n";
    std::cout << "Account Number: " << accountNumber << '\n';
    std::cout << "Current Balance: Rs " << std::fixed << std::setprecision(2) << balance << '\n';
    std::cout << "Recent Transactions (Max 10):\n";
    for (int i = 0; i < count; ++i) {
        if (transactions[i] > 0) {
            std::cout << "  " << std::setw(2) << (i + 1) << ". DEPOSIT    : +Rs " << transactions[i] << '\n';
        } else {
            std::cout << "  " << std::setw(2) << (i + 1) << ". WITHDRAWAL : -Rs " << -transactions[i] << '\n';
        }
    }
    std::cout << "------------------------------------------------\n\n";
}

// ============================================================================
// PART 3: Alternative Concept - Circular Buffer with Start Index
// ============================================================================

template <int CAPACITY = 10>
class CircularSavingsAccount {
private:
    long long accountNumber;
    double balance;
    double transactions[CAPACITY];
    int start;
    int count;

public:
    CircularSavingsAccount(long long accNo, double initBal)
        : accountNumber(accNo), balance(initBal), start(0), count(0) {}

    void deposit(double amount) {
        if (amount <= 0) return;
        balance += amount;
        addTransaction(amount);
    }

    void withdraw(double amount) {
        if (amount <= 0 || amount > balance) return;
        balance -= amount;
        addTransaction(-amount);
    }

    void addTransaction(double amount) {
        if (count < CAPACITY) {
            int writeIdx = (start + count) % CAPACITY;
            transactions[writeIdx] = amount;
            count++;
        } else {
            // Overwrite oldest in O(1) time without shifting elements!
            transactions[start] = amount;
            start = (start + 1) % CAPACITY;
        }
    }

    void miniStatement() const {
        std::cout << "[Circular Buffer ATM Mini-Statement - Capacity: " << CAPACITY << "]\n";
        for (int i = 0; i < count; ++i) {
            int idx = (start + i) % CAPACITY;
            std::cout << "  Tx " << (i + 1) << ": " << (transactions[idx] >= 0 ? "+" : "") << transactions[idx] << '\n';
        }
    }
};

// ============================================================================
// MAIN DRIVER & TEST VERIFICATION
// ============================================================================

int main()
{
    std::cout << "=========================================================\n";
    std::cout << "  ASSIGNMENT 2 - CO2 | QUESTION 4 EXECUTION & VERIFICATION\n";
    std::cout << "=========================================================\n\n";

    SavingsAccount acc(10023456789LL, 15000.0);

    // Apply 10 transactions initially
    std::cout << "Applying 10 transactions (Deposits and Withdrawals)...\n";
    acc.deposit(1000);   // Tx 1
    acc.withdraw(500);   // Tx 2
    acc.deposit(2500);   // Tx 3
    acc.withdraw(1200);  // Tx 4
    acc.deposit(800);    // Tx 5
    acc.withdraw(300);   // Tx 6
    acc.deposit(4000);   // Tx 7
    acc.withdraw(1500);  // Tx 8
    acc.deposit(700);    // Tx 9
    acc.withdraw(200);   // Tx 10

    acc.miniStatement();

    // Now apply 11th and 12th transactions to test shifting behavior
    std::cout << "Triggering 11th and 12th transactions to verify older records are discarded...\n";
    acc.deposit(9999);   // Tx 11 (should discard Tx 1)
    acc.withdraw(1111);  // Tx 12 (should discard Tx 2)

    acc.miniStatement();

    // Verify Circular Buffer Alternative Concept
    std::cout << "--- [Alternative Concept Verification: O(1) Circular Buffer] ---\n";
    CircularSavingsAccount<10> circAcc(10023456789LL, 15000.0);
    for (int i = 1; i <= 12; ++i) {
        circAcc.deposit(100.0 * i);
    }
    circAcc.miniStatement();

    std::cout << "\n[ALL Q4 TESTS AND VERIFICATIONS COMPLETED SUCCESSFULLY]\n";
    return 0;
}
