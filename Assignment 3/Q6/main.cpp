#include <iostream>
#include <cstring>

class Text {
private:
    std::size_t len;
    char* str;

public:
    // Constructor
    Text(const char* s = "") {
        if (!s) s = "";
        len = std::strlen(s);
        str = new char[len + 1];
        std::strcpy(str, s);
    }

    // Copy Constructor (Deep Copy)
    Text(const Text& other) : len(other.len), str(new char[other.len + 1]) {
        std::strcpy(str, other.str);
    }

    // Copy Assignment Operator with Self-Assignment Guard
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* newStr = new char[other.len + 1];
            std::strcpy(newStr, other.str);
            delete[] str;
            str = newStr;
            len = other.len;
        }
        return *this;
    }

    // Destructor
    ~Text() {
        delete[] str;
    }

    // Overload + for string concatenation
    Text operator+(const Text& other) const {
        Text result;
        delete[] result.str;
        result.len = len + other.len;
        result.str = new char[result.len + 1];
        std::strcpy(result.str, str);
        std::strcat(result.str, other.str);
        return result;
    }

    // Overload == and !=
    bool operator==(const Text& other) const {
        return std::strcmp(str, other.str) == 0;
    }

    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    std::size_t length() const { return len; }

    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        os << t.str;
        return os;
    }
};

int main() {
    std::cout << "--- [SMS Gateway Text Class Verification] ---\n";

    Text msg1("Your OTP is: ");
    Text msg2("482910");
    Text fullMsg = msg1 + msg2;

    std::cout << "Concatenated Message: " << fullMsg << '\n';
    std::cout << "Message Length: " << fullMsg.length() << " chars\n";

    Text copyMsg = fullMsg;
    std::cout << "Equality Check (fullMsg == copyMsg): " << std::boolalpha << (fullMsg == copyMsg) << '\n';

    // Self-assignment safety check
    fullMsg = fullMsg;
    std::cout << "After Self-Assignment (p = p): " << fullMsg << '\n';

    // Empty text test
    Text empty;
    std::cout << "Empty Text Length: " << empty.length() << " | Display: \"" << empty << "\"\n";

    std::cout << "\n[Q6 OPERATOR OVERLOADING RULES COMPLETED SUCCESSFULLY]\n";
    return 0;
}
