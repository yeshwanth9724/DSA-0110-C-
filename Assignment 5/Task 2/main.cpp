#include <iostream>
#include <stdexcept>

// Predict the Output 1: Virtual Destructor and Late Binding
struct BillPreview {
    virtual ~BillPreview() { std::cout << "~Bill "; }
    virtual double total() const = 0;
    void show() const { std::cout << total() << ' '; }
};

struct OPBillPreview : BillPreview {
    ~OPBillPreview() override { std::cout << "~OPBill "; }
    double total() const override { return 500; }
};

void runBindingPrediction() {
    std::cout << "--- [Specification Predict the Output: vtable & Destruction] ---\n";
    BillPreview* b = new OPBillPreview;
    b->show();
    delete b;
    std::cout << "\n\n";
}

// Complete the Code Specification Program
class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    if (billed < 0 || cover < 0) {
        throw std::invalid_argument("negative amount");
    }
    if (billed > cover) {
        throw ClaimError("exceeds cover");
    }
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        std::cout << "audit: " << e.what() << '\n';
        throw; // rethrow the exact active exception object without slicing
    }
}

int main() {
    runBindingPrediction();

    std::cout << "--- [Specification Complete the Code Output: Claim Settlement] ---\n";
    double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};

    for (auto& c : cases) {
        try {
            double paid = settle(c[0], c[1]);
            std::cout << "approved " << paid << '\n';
        } catch (const ClaimError& e) {
            std::cout << "claim rejected: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }

    std::cout << "\n[TASK 2 RUNTIME BINDING AND EXCEPTION ENGINEERING COMPLETED]\n";
    return 0;
}
