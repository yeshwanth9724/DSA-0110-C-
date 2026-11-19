#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

// Approach A: Virtual Functions
class PolymorphicBill {
public:
    virtual ~PolymorphicBill() = default;
    virtual double total() const = 0;
};

class PolyOPBill : public PolymorphicBill {
    double consultation, tests;
public:
    PolyOPBill(double c, double t) : consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
};

class PolyIPBill : public PolymorphicBill {
    int days;
    double perDay, surgery;
public:
    PolyIPBill(int d, double rate, double s) : days(d), perDay(rate), surgery(s) {}
    double total() const override { return days * perDay + surgery; }
};

// Approach B: Single Struct with Type Tag & Switch
enum class BillType { OutPatient, InPatient };

struct SwitchBill {
    BillType type;
    double consultation;
    double tests;
    int days;
    double perDay;
    double surgery;

    double total() const {
        switch (type) {
            case BillType::OutPatient:
                return consultation + tests;
            case BillType::InPatient:
                return days * perDay + surgery;
        }
        return 0.0;
    }
};

void runSmallDataValidation() {
    std::cout << "--- [B3.1: Small Data Correctness Verification] ---\n";
    // 5 OP and 5 IP bills
    std::vector<PolymorphicBill*> polyBills;
    std::vector<SwitchBill> switchBills;

    for (int i = 0; i < 5; ++i) {
        polyBills.push_back(new PolyOPBill(500.0 + i * 50, 1200.0));
        switchBills.push_back(SwitchBill{BillType::OutPatient, 500.0 + i * 50, 1200.0, 0, 0.0, 0.0});

        polyBills.push_back(new PolyIPBill(3 + i, 2500.0, 40000.0));
        switchBills.push_back(SwitchBill{BillType::InPatient, 0.0, 0.0, 3 + i, 2500.0, 40000.0});
    }

    double sumPoly = 0.0;
    for (const auto* b : polyBills) sumPoly += b->total();

    double sumSwitch = 0.0;
    for (const auto& b : switchBills) sumSwitch += b.total();

    std::cout << "Polymorphic Bills Total : Rs " << sumPoly << '\n';
    std::cout << "Switch-Based Bills Total: Rs " << sumSwitch << '\n';
    std::cout << "Parity Verification     : " << (sumPoly == sumSwitch ? "PASSED (100% MATCH)" : "FAILED") << "\n\n";

    for (auto* b : polyBills) delete b;
}

void runBenchmarkScaling() {
    std::cout << "--- [B3.2: Virtual Call vs Switch Performance Scaling] ---\n";
    const int N = 1000000; // 1 Million bills

    std::vector<SwitchBill> switchDataset(N, SwitchBill{BillType::OutPatient, 600.0, 1400.0, 0, 0.0, 0.0});
    for (int i = 1; i < N; i += 2) {
        switchDataset[i] = SwitchBill{BillType::InPatient, 0.0, 0.0, 4, 3000.0, 45000.0};
    }

    // Benchmark Switch
    volatile double dummySwitch = 0.0;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        dummySwitch += switchDataset[i].total();
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    double switchDuration = std::chrono::duration<double, std::milli>(t2 - t1).count();

    std::cout << "1,000,000 Bills Processed via Tagged Switch : " << std::fixed << std::setprecision(2) 
              << switchDuration << " ms\n";

    // Virtual Benchmark
    PolyOPBill opSample(600.0, 1400.0);
    PolyIPBill ipSample(4, 3000.0, 45000.0);
    std::vector<PolymorphicBill*> polyDataset(N, &opSample);
    for (int i = 1; i < N; i += 2) {
        polyDataset[i] = &ipSample;
    }

    volatile double dummyPoly = 0.0;
    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        dummyPoly += polyDataset[i]->total();
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    double polyDuration = std::chrono::duration<double, std::milli>(t4 - t3).count();

    std::cout << "1,000,000 Bills Processed via vtable Call   : " << polyDuration << " ms\n\n";
}

// B3.3: Cost of Exceptions benchmark
bool validateReturnCode(double billed, double cover) {
    if (billed < 0 || cover < 0 || billed > cover) return false;
    return true;
}

void validateException(double billed, double cover) {
    if (billed < 0 || cover < 0 || billed > cover) throw std::runtime_error("Invalid");
}

void runExceptionCostBenchmark() {
    std::cout << "--- [B3.3: Cost of Exceptions vs Return Codes (1,000,000 Operations)] ---\n";
    const int TOTAL = 1000000;

    // Test 0% invalid
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < TOTAL; ++i) {
        validateReturnCode(5000.0, 10000.0);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    double retCodeZero = std::chrono::duration<double, std::milli>(t2 - t1).count();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < TOTAL; ++i) {
        try {
            validateException(5000.0, 10000.0);
        } catch (...) {}
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    double excZero = std::chrono::duration<double, std::milli>(t4 - t3).count();

    std::cout << "0% Invalid Claims:\n";
    std::cout << "  Return Code Validation: " << retCodeZero << " ms\n";
    std::cout << "  Zero-Cost Exception   : " << excZero << " ms (Happy path is virtually cost-free)\n";

    // Test 1% invalid (10,000 throws)
    auto t5 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < TOTAL; ++i) {
        try {
            validateException((i % 100 == 0) ? 20000.0 : 5000.0, 10000.0);
        } catch (...) {}
    }
    auto t6 = std::chrono::high_resolution_clock::now();
    double excOnePercent = std::chrono::duration<double, std::milli>(t6 - t5).count();

    std::cout << "1% Invalid Claims (10,000 throws & unwinds):\n";
    std::cout << "  Exception Unwinding   : " << excOnePercent << " ms\n";
}

int main() {
    runSmallDataValidation();
    runBenchmarkScaling();
    runExceptionCostBenchmark();

    std::cout << "\n[TASK 3 VIRTUAL VS SWITCH VS EXCEPTIONS BENCHMARK COMPLETED]\n";
    return 0;
}
