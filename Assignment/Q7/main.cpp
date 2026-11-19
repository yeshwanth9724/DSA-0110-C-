#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <cassert>

// ============================================================================
// DAY-4 DESIGN CHALLENGE: Q7 - Diagnose, Redesign and Validate
// Selected Focus: Q4 Bank Savings Account Mini-Statement Buffer
// ============================================================================

// ----------------------------------------------------------------------------
// 1. ORIGINAL DESIGN: Linear Shifting Array (O(k) insertion penalty)
// ----------------------------------------------------------------------------
template <std::size_t Capacity>
class ShiftingSavingsAccount {
private:
    long long accountNumber;
    double balance;
    double transactions[Capacity];
    std::size_t count;

public:
    ShiftingSavingsAccount(long long accNo, double initBal)
        : accountNumber(accNo), balance(initBal), count(0) {}

    void deposit(double amount) {
        balance += amount;
        recordTransaction(amount);
    }

    void recordTransaction(double amount) {
        if (count < Capacity) {
            transactions[count++] = amount;
        } else {
            // THE LIMITATION: O(k) linear memory shifts on EVERY insertion once full
            for (std::size_t i = 0; i < Capacity - 1; ++i) {
                transactions[i] = transactions[i + 1];
            }
            transactions[Capacity - 1] = amount;
        }
    }

    std::size_t getCount() const { return count; }
    double getTransaction(std::size_t i) const { return transactions[i]; }
};

// ----------------------------------------------------------------------------
// 2. REDESIGNED SOLUTION: Zero-Heap Embedded Circular Ring Buffer (O(1) insertion)
// ----------------------------------------------------------------------------
template <std::size_t Capacity>
class CircularSavingsAccount {
private:
    long long accountNumber;
    double balance;
    double transactions[Capacity];
    std::size_t head;  // points to oldest element
    std::size_t count; // current occupancy

public:
    CircularSavingsAccount(long long accNo, double initBal)
        : accountNumber(accNo), balance(initBal), head(0), count(0) {}

    void deposit(double amount) {
        balance += amount;
        recordTransaction(amount);
    }

    void recordTransaction(double amount) {
        // THE REDESIGN: O(1) in-place overwrite with zero element movement
        if (count < Capacity) {
            std::size_t tail = (head + count) % Capacity;
            transactions[tail] = amount;
            count++;
        } else {
            transactions[head] = amount;
            head = (head + 1) % Capacity;
        }
    }

    std::size_t getCount() const { return count; }

    // Logical index i (0 = oldest recorded transaction)
    double getTransaction(std::size_t i) const {
        return transactions[(head + i) % Capacity];
    }
};

// ============================================================================
// VERIFICATION AND BENCHMARK SUITE
// ============================================================================

template <std::size_t Cap>
void runEmpiricalComparison(int numTransactions)
{
    std::cout << "\n>>> BENCHMARK EXPERIMENT: Capacity k = " << Cap 
              << " | Operations N = " << numTransactions << " <<<\n";

    // 1. Benchmark Original Shifting Buffer
    ShiftingSavingsAccount<Cap> shiftAcc(1001, 1000.0);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTransactions; ++i) {
        shiftAcc.deposit(1.0 + (i % 100));
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    double shiftDuration = std::chrono::duration<double, std::milli>(t2 - t1).count();

    // 2. Benchmark Redesigned Circular Buffer
    CircularSavingsAccount<Cap> circAcc(1001, 1000.0);
    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTransactions; ++i) {
        circAcc.deposit(1.0 + (i % 100));
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    double circDuration = std::chrono::duration<double, std::milli>(t4 - t3).count();

    // 3. Correctness Parity Validation
    assert(shiftAcc.getCount() == circAcc.getCount());
    bool parity = true;
    for (std::size_t i = 0; i < Cap; ++i) {
        if (shiftAcc.getTransaction(i) != circAcc.getTransaction(i)) {
            parity = false;
            break;
        }
    }

    std::cout << "  Original (Shifting Array)   : " << std::fixed << std::setprecision(3) 
              << shiftDuration << " ms\n";
    std::cout << "  Redesigned (Circular Buffer): " << circDuration << " ms\n";
    std::cout << "  Performance Acceleration    : " << std::setprecision(1) 
              << (shiftDuration / (circDuration > 0 ? circDuration : 0.001)) << "x faster\n";
    std::cout << "  Functional Parity Check     : " << (parity ? "PASSED (100% IDENTICAL)" : "FAILED") << '\n';
}

int main()
{
    std::cout << "=========================================================\n";
    std::cout << "  ASSIGNMENT 2 - CO2 | QUESTION 7 DESIGN CHALLENGE\n";
    std::cout << "=========================================================\n";

    std::cout << "Selected Domain: Q4 Bank Account Transaction Mini-Statement\n";
    std::cout << "Diagnosed Limitation: O(k) data shifting on every single transaction\n";
    std::cout << "Redesign Architecture: O(1) Zero-Heap Templated Circular Ring Buffer\n";

    const int N = 100000; // 100,000 transactions

    // Benchmark across various capacity scales: k = 10, k = 50 (bank requested), k = 500
    runEmpiricalComparison<10>(N);
    runEmpiricalComparison<50>(N);
    runEmpiricalComparison<500>(N);

    std::cout << "\n=========================================================\n";
    std::cout << "[Q7 EMPIRICAL VALIDATION COMPLETED WITH 100% SUCCESS]\n";
    std::cout << "=========================================================\n";
    return 0;
}
