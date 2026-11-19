#include <iostream>
#include <iomanip>
#include <string>

// ============================================================================
// PART 1: The Redesigned Non-Ambiguous Courier Charge Functions
// ============================================================================

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

// Base pricing constants
constexpr double RATE_PER_KG = 50.0;
constexpr double EXPRESS_SURCHARGE = 100.0;
constexpr double INSURANCE_SURCHARGE = 75.0;

// Overload 1: Weight in kg as double with default arguments from the right
double charge(double weightKg, bool express = false, bool insured = false)
{
    std::cout << "  [Selected: charge(double, bool, bool)] -> ";
    double total = weightKg * RATE_PER_KG;
    if (express) total += EXPRESS_SURCHARGE;
    if (insured) total += INSURANCE_SURCHARGE;
    return total;
}

// Overload 2: Weight in grams as int (converts to kg)
double charge(int weightGrams, bool express = false, bool insured = false)
{
    std::cout << "  [Selected: charge(int, bool, bool)]    -> ";
    double weightKg = weightGrams / 1000.0;
    double total = weightKg * RATE_PER_KG;
    if (express) total += EXPRESS_SURCHARGE;
    if (insured) total += INSURANCE_SURCHARGE;
    return total;
}

// Overload 3: Single Parcel object
double charge(const Parcel& p)
{
    std::cout << "  [Selected: charge(const Parcel&)]       -> ";
    double total = p.weightKg * RATE_PER_KG;
    if (p.express) total += EXPRESS_SURCHARGE;
    if (p.insured) total += INSURANCE_SURCHARGE;
    return total;
}

// ============================================================================
// MAIN DEMONSTRATION & SIX PREDICTED CALLS
// ============================================================================

int main()
{
    std::cout << "=========================================================\n";
    std::cout << "  ASSIGNMENT 2 - CO2 | QUESTION 3 EXECUTION & VERIFICATION\n";
    std::cout << "=========================================================\n\n";

    std::cout << "--- [Analysis of Original Ambiguity] ---\n";
    std::cout << "Original code had:\n";
    std::cout << "  1. charge(double weight)\n";
    std::cout << "  2. charge(double weight, bool express)\n";
    std::cout << "  3. charge(double weight, bool express = false, bool insured = false)\n";
    std::cout << "Ambiguity: Calling charge(5.0) matched both (1) and (3).\n";
    std::cout << "Resolution: Removed redundant overloads (1) and (2); unified into (3).\n\n";

    std::cout << "--- [Execution of Six Designed Test Calls] ---\n";

    // Call 1: charge(2.5) -> double literal
    std::cout << "Call 1: charge(2.5)\n";
    double c1 = charge(2.5);
    std::cout << "Cost: Rs " << std::fixed << std::setprecision(2) << c1 << "\n\n";

    // Call 2: charge(500) -> int literal (grams)
    std::cout << "Call 2: charge(500)\n";
    double c2 = charge(500);
    std::cout << "Cost: Rs " << c2 << "\n\n";

    // Call 3: charge(2) -> int literal (2 grams)
    std::cout << "Call 3: charge(2)\n";
    double c3 = charge(2);
    std::cout << "Cost: Rs " << c3 << "\n\n";

    // Call 4: charge(2.0f) -> float literal (promoted to double)
    std::cout << "Call 4: charge(2.0f)\n";
    double c4 = charge(2.0f);
    std::cout << "Cost: Rs " << c4 << "\n\n";

    // Call 5: charge(3.0, true) -> double with express=true, insured defaulted
    std::cout << "Call 5: charge(3.0, true)\n";
    double c5 = charge(3.0, true);
    std::cout << "Cost: Rs " << c5 << "\n\n";

    // Call 6: charge(Parcel{4.0, true, true}) -> Parcel object
    std::cout << "Call 6: charge(Parcel{4.0, true, true})\n";
    Parcel p{4.0, true, true};
    double c6 = charge(p);
    std::cout << "Cost: Rs " << c6 << "\n\n";

    std::cout << "[ALL 6 OVERLOAD SELECTIONS EXECUTED SUCCESSFULLY]\n";
    return 0;
}
