#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>

// ============================================================================
// PART 1: Time Class Specification with Friend Functions (Pages 12-13)
// ============================================================================

class Time {
private:
    int h, m;

public:
    Time(int hh = 0, int mm = 0) : h(hh), m(mm) {}

    // Public getters (for alternative design comparison)
    int getHours() const { return h; }
    int getMinutes() const { return m; }

    // Member function alternative
    int minutesTo(const Time& b) const {
        return std::abs((h * 60 + m) - (b.h * 60 + b.m));
    }

    bool isEarlier(const Time& b) const {
        if (h != b.h) return h < b.h;
        return m < b.m;
    }

    // Friend functions declarations
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
    friend inline int minutesBetweenInline(const Time& a, const Time& b);
    friend inline bool earlierInline(const Time& a, const Time& b);
};

// ============================================================================
// PART 2: Friend Functions Implementations (TODO 1 & TODO 2)
// ============================================================================

int minutesBetween(const Time& a, const Time& b)
{
    // TODO 1: Using the private members h and m, return the absolute difference between
    // the two times in minutes
    int totalA = a.h * 60 + a.m;
    int totalB = b.h * 60 + b.m;
    return std::abs(totalA - totalB);
}

bool earlier(const Time& a, const Time& b)
{
    // TODO 2: Return true if a is earlier in the day than b
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
}

// Inline versions for performance comparison
inline int minutesBetweenInline(const Time& a, const Time& b)
{
    int totalA = a.h * 60 + a.m;
    int totalB = b.h * 60 + b.m;
    return std::abs(totalA - totalB);
}

inline bool earlierInline(const Time& a, const Time& b)
{
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
}

// ============================================================================
// PART 3: Correctness Checks & 10,000,000 Iteration Benchmark
// ============================================================================

void runSpecificationTest()
{
    std::cout << "--- [Specification Complete the Code Output (Page 13)] ---\n";
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';
    std::cout << '\n';
}

void runCorrectnessChecks()
{
    std::cout << "--- [Correctness Checks: Either side of noon & identical times] ---\n";

    // Test 1: Across noon (11:45 and 12:15)
    Time t1(11, 45), t2(12, 15);
    int diff1 = minutesBetween(t1, t2);
    bool ear1 = earlier(t1, t2);
    std::cout << "Times 11:45 and 12:15:\n";
    std::cout << "  Minutes between: " << diff1 << " mins (Hand calc: 15 mins to noon + 15 mins after = 30 mins) -> "
              << (diff1 == 30 ? "VERIFIED" : "FAILED") << '\n';
    std::cout << "  Is 11:45 earlier than 12:15? " << std::boolalpha << ear1 << " -> " 
              << (ear1 ? "VERIFIED" : "FAILED") << '\n';

    // Test 2: Identical times (10:30 and 10:30)
    Time t3(10, 30), t4(10, 30);
    int diff2 = minutesBetween(t3, t4);
    bool ear2 = earlier(t3, t4);
    std::cout << "\nTimes 10:30 and 10:30:\n";
    std::cout << "  Minutes between: " << diff2 << " mins (Hand calc: 0 mins) -> "
              << (diff2 == 0 ? "VERIFIED" : "FAILED") << '\n';
    std::cout << "  Is 10:30 earlier than 10:30? " << std::boolalpha << ear2 << " -> " 
              << (!ear2 ? "VERIFIED" : "FAILED") << '\n';
    std::cout << '\n';
}

void runGrowthInvestigation()
{
    std::cout << "--- [Growth Investigation: 10,000,000 Call Benchmark] ---\n";
    const int ITERATIONS = 10000000;
    Time tA(8, 30), tB(17, 45);

    // Benchmark standard function
    volatile int dummy1 = 0;
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        dummy1 += minutesBetween(tA, tB);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    double timeStandard = std::chrono::duration<double, std::milli>(end1 - start1).count();

    // Benchmark inline function
    volatile int dummy2 = 0;
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        dummy2 += minutesBetweenInline(tA, tB);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    double timeInline = std::chrono::duration<double, std::milli>(end2 - start2).count();

    std::cout << "Benchmark results for 10,000,000 iterations:\n";
    std::cout << "  Standard Friend Function : " << std::fixed << std::setprecision(2) << timeStandard << " ms\n";
    std::cout << "  Inline Friend Function   : " << timeInline << " ms\n";
    std::cout << "  Speedup Factor           : " << (timeStandard / (timeInline > 0 ? timeInline : 0.001)) << "x\n";
}

// ============================================================================
// MAIN DRIVER
// ============================================================================

int main()
{
    std::cout << "=========================================================\n";
    std::cout << "  ASSIGNMENT 2 - CO2 | QUESTION 6 EXECUTION & VERIFICATION\n";
    std::cout << "=========================================================\n\n";

    runSpecificationTest();
    runCorrectnessChecks();
    runGrowthInvestigation();

    std::cout << "\n[ALL Q6 TESTS AND VERIFICATIONS COMPLETED SUCCESSFULLY]\n";
    return 0;
}
