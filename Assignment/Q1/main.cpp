#include <iostream>
#include <iomanip>
#include <string>

// ============================================================================
// PART 1: "Complete the Code" Program from Assignment Specification (Page 4)
// ============================================================================

void applyByValue(long long fee, int percent)
{
    fee -= fee * percent / 100; // changes only the local copy
}

void applyConcession(long long& fee, int percent)
{
    // TODO 1: Reduce the caller's fee by percent using integer arithmetic (call by reference)
    fee -= fee * percent / 100;
}

void runCompletedCodeSnippet()
{
    std::cout << "--- [Specification Complete the Code Output] ---\n";
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    std::cout << "after call by value : " << hostelFee << '\n';
    applyConcession(hostelFee, 10);
    std::cout << "after call by reference: " << hostelFee << '\n';
    std::cout << '\n';
}

// ============================================================================
// PART 2: Three Ways Challenge - Pass by Value, Reference, Pointer
// Context: Hostel Fee Concession Updater (Merit 10%, Sports 15%, Single Parent 25%)
// ============================================================================

void applyConcessionByValue(long long fee, int percent)
{
    fee -= (fee * percent) / 100;
}

void applyConcessionByReference(long long& fee, int percent)
{
    fee -= (fee * percent) / 100;
}

void applyConcessionByPointer(long long* fee, int percent)
{
    if (fee != nullptr) {
        *fee -= (*fee * percent) / 100;
    }
}

// Alternative Concept: Pure functional style (return new fee)
long long calculateNewFee(long long fee, int percent)
{
    return fee - (fee * percent) / 100;
}

void runThreeWaysChallenge()
{
    std::cout << "--- [Hostel Fee Concession Challenge: Three Parameter Passings] ---\n";
    const long long baseFee = 60000;

    // 1. Pass by Value (Merit 10%)
    long long feeVal = baseFee;
    applyConcessionByValue(feeVal, 10);
    std::cout << "Initial: " << baseFee << " | Merit (10%) by Value     -> Stored Fee: " << feeVal 
              << " (Unchanged - local parameter modified)\n";

    // 2. Pass by Reference (Sports 15%)
    long long feeRef = baseFee;
    applyConcessionByReference(feeRef, 15);
    std::cout << "Initial: " << baseFee << " | Sports (15%) by Reference -> Stored Fee: " << feeRef 
              << " (Changed in caller)\n";

    // 3. Pass by Pointer (Single Parent 25%)
    long long feePtr = baseFee;
    applyConcessionByPointer(&feePtr, 25);
    std::cout << "Initial: " << baseFee << " | Parent (25%) by Pointer   -> Stored Fee: " << feePtr 
              << " (Changed in caller)\n";

    // Multi-concession demonstration using Reference (chained)
    long long studentFee = baseFee;
    applyConcessionByReference(studentFee, 10); // Merit 10%: 60000 -> 54000
    applyConcessionByReference(studentFee, 15); // Sports 15%: 54000 -> 45900
    std::cout << "Cumulative (Merit 10% + Sports 15%) via Reference   -> Stored Fee: " << studentFee << '\n';

    // Functional alternative demonstration
    long long functionalFee = calculateNewFee(calculateNewFee(baseFee, 10), 15);
    std::cout << "Cumulative via Pure Return Functional Approach     -> Result Fee: " << functionalFee << '\n';
    std::cout << '\n';
}

// ============================================================================
// PART 3: Predict the Output Verification Program (Pages 2-3)
// ============================================================================

void change(int a, int& b, int* c)
{
    a += 10;
    b += 10;
    *c += 10;
}

int& bigger(int& p, int& q)
{
    return p > q ? p : q;
}

void show(int x, int y = 5, int z = 10)
{
    std::cout << x + y + z << ' ';
}

void runPredictTheOutputProgram()
{
    std::cout << "--- [Predict the Output Verification (Pages 2-3)] ---\n";
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    std::cout << a << ' ' << b << ' ' << c << '\n';

    bigger(a, c) = 100;
    std::cout << a << ' ' << c << '\n';

    show(1);
    show(1, 2);
    show(1, 2, 3);
    std::cout << '\n';
}

// ============================================================================
// MAIN DRIVER
// ============================================================================

int main()
{
    std::cout << "=========================================================\n";
    std::cout << "  ASSIGNMENT 2 - CO2 | QUESTION 1 EXECUTION & VERIFICATION\n";
    std::cout << "=========================================================\n\n";

    runCompletedCodeSnippet();
    runThreeWaysChallenge();
    runPredictTheOutputProgram();

    std::cout << "\n[ALL Q1 TESTS AND VERIFICATIONS COMPLETED SUCCESSFULLY]\n";
    return 0;
}
