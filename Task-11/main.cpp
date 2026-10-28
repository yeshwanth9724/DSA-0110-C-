#include <iostream>

#include <array>

using namespace std;

 

enum class Zone { Inner, Middle, Outer };

constexpr array<long long, 3> FARES = {1000, 2000, 3000};

 

long long calculateFare(Zone z, bool peak) {

    long long amount = FARES[static_cast<int>(z)];

    if (peak) amount += amount * 20 / 100;

    return amount;

}

 

class SmartCard {

    long long balance;

public:

    SmartCard(long long b) : balance(b) {}

    bool pay(long long f) {

        if (f < 0 || balance < f || balance - f < 5000) return false;

        balance -= f;

        return true;

    }

    long long getBalance() const { return balance; }

};

 

int main() {

    SmartCard card(10000);

    long long f = calculateFare(Zone::Outer, true);

    if (card.pay(f)) cout << "Payment successful\n";

    else cout << "Insufficient balance\n";

    cout << "Remaining balance: " << card.getBalance() << " paise\n";

}
