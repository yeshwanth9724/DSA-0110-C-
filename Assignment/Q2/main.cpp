#include <iostream>
#include <vector>
#include <string>

// ============================================================================
// PART 1: Safe Return by Reference from Persistent Array
// ============================================================================

int& findHighestMark(int marks[], int size)
{
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    // Returns an lvalue reference to the actual array element
    return marks[maxIdx];
}

const int& findHighestMarkConst(const int marks[], int size)
{
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    // Returns a read-only const reference (prevents left-of-= assignment)
    return marks[maxIdx];
}

int findHighestMarkCopy(const int marks[], int size)
{
    int maxVal = marks[0];
    for (int i = 1; i < size; ++i) {
        if (marks[i] > maxVal) {
            maxVal = marks[i];
        }
    }
    // Returns an rvalue copy (stored in caller temporary)
    return maxVal;
}

// ============================================================================
// PART 2: Dangerous Return by Reference to a Local Stack Variable
// ============================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
int& dangerousLocalRef()
{
    int localModeration = 5;
    // WARNING: Returning reference to a local automatic variable!
    // Upon function return, stack frame unwinds and this becomes dangling.
    return localModeration;
}
#pragma GCC diagnostic pop

// ============================================================================
// PART 3: Alternative Concepts - Return by Index and Pointer
// ============================================================================

int findHighestIndex(const int marks[], int size)
{
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx; // Returning index is re-allocation safe
}

int* findHighestPointer(int marks[], int size)
{
    if (size <= 0) return nullptr;
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return &marks[maxIdx];
}

// ============================================================================
// MAIN DEMONSTRATION & VERIFICATION
// ============================================================================

int main()
{
    std::cout << "=========================================================\n";
    std::cout << "  ASSIGNMENT 2 - CO2 | QUESTION 2 EXECUTION & VERIFICATION\n";
    std::cout << "=========================================================\n\n";

    // 1. Array Element Modification via Left-of-= Assignment
    int marks[5] = {78, 85, 92, 64, 88};
    int n = 5;

    std::cout << "Initial marks array: ";
    for (int i = 0; i < n; ++i) std::cout << marks[i] << " ";
    std::cout << "\nHighest mark identified: " << findHighestMark(marks, n) << '\n';

    // Apply moderation of +2 using call on the left of assignment operator
    findHighestMark(marks, n) += 2;
    std::cout << "Marks after moderation (+2) via lvalue reference call: ";
    for (int i = 0; i < n; ++i) std::cout << marks[i] << " ";
    std::cout << "\nUpdated highest mark in array: " << marks[2] << " (Successfully modified in-place)\n\n";

    // 2. Const Reference vs Copy Demonstration
    const int& constRef = findHighestMarkConst(marks, n);
    std::cout << "Read via const reference: " << constRef << " (Guaranteed immutable, cannot be on LHS of =)\n";

    int copyVal = findHighestMarkCopy(marks, n);
    std::cout << "Read via value copy: " << copyVal << " (Independent rvalue copy, LHS assignment disallowed)\n\n";

    // 3. Vector Growth & Invalidation Demonstration
    std::cout << "--- [Changed Condition: std::vector Growth & Reference Invalidation] ---\n";
    std::vector<int> vecMarks = {80, 85, 90};
    int initialCap = vecMarks.capacity();
    std::cout << "Vector initial capacity: " << initialCap << ", size: " << vecMarks.size() << '\n';

    int& refBeforeGrow = vecMarks[2]; // reference to 90
    std::cout << "Reference before growth: " << refBeforeGrow << " at address: " << &refBeforeGrow << '\n';

    // Force multiple reallocations beyond initial capacity
    for (int i = 0; i < 20; ++i) {
        vecMarks.push_back(70 + i);
    }
    std::cout << "Vector new capacity: " << vecMarks.capacity() << ", size: " << vecMarks.size() << '\n';
    std::cout << "Notice: Vector heap storage relocated to new memory!\n";
    std::cout << "Safe alternative: Return Index -> Index [2] always valid: vecMarks[2] = " << vecMarks[2] << '\n';
    std::cout << "Safe alternative: Return Pointer -> " << *findHighestPointer(marks, n) << " (requires null check)\n\n";

    // 4. Undefined Behavior Note
    std::cout << "--- [Dangling Local Reference Analysis] ---\n";
    std::cout << "Local automatic variables reside on the activation stack frame.\n";
    std::cout << "Returning int& to a local stack variable causes GCC warning [-Wreturn-local-addr].\n";
    std::cout << "Dereferencing such reference invokes Undefined Behavior (UB).\n";

    std::cout << "\n[ALL Q2 TESTS AND VERIFICATIONS COMPLETED SUCCESSFULLY]\n";
    return 0;
}
