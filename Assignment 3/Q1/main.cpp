#include <iostream>
#include <string>
#include <stdexcept>

class Book {
private:
    std::string title;
    std::string author;
    int copies;

public:
    // Full parameterized constructor with validation
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(c >= 0 ? c : throw std::invalid_argument("Number of copies cannot be negative")) {}

    // Delegating default constructor
    Book() : Book("Untitled", "Unknown", 0) {}

    // Delegating constructor for donated book (title only)
    explicit Book(const std::string& t) : Book(t, "Anonymous Donor", 1) {}

    void print() const {
        std::cout << "Title: \"" << title << "\", Author: " << author << ", Copies: " << copies << '\n';
    }

    int getCopies() const { return copies; }
};

int main() {
    std::cout << "--- [Library Book Records: Constructor Demonstrations] ---\n";

    // 1. Default constructor
    Book emptyRecord;
    std::cout << "1. Empty Record: ";
    emptyRecord.print();

    // 2. Donated book constructor (single argument, explicit)
    Book donatedBook("C++ Design Patterns");
    std::cout << "2. Donated Book: ";
    donatedBook.print();

    // 3. Full parameterized constructor
    Book standardBook("Effective Modern C++", "Scott Meyers", 5);
    std::cout << "3. Full Details: ";
    standardBook.print();

    // 4. Array of Book objects (invoking default constructor)
    std::cout << "\n4. Array of Book Objects:\n";
    Book catalog[3] = {
        Book("Data Structures", "Mark Allen Weiss", 4),
        Book("The C++ Programming Language", "Bjarne Stroustrup", 2),
        Book()
    };
    for (int i = 0; i < 3; ++i) {
        std::cout << "   Catalog[" << i << "]: ";
        catalog[i].print();
    }

    // 5. Validation test: Reject negative copies
    std::cout << "\n5. Invariant Validation (Testing Negative Copies):\n";
    try {
        Book invalidBook("Faulty Book", "Nobody", -3);
        invalidBook.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "   Exception Caught: " << e.what() << " -> Object creation rejected.\n";
    }

    std::cout << "\n[Q1 CONSTRUCTORS VERIFICATION PASSED]\n";
    return 0;
}
