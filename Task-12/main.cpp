#include <iostream>
#include <array>
using namespace std;
enum class Zone { Inner, Middle, Outer, Airport };
constexpr array<long long, 4> BASE = {1000, 2000, 3000, 6000};
long long calculateFare(Zone z, int hour, bool weekend) {
    if (hour < 0 || hour > 23) return -1;
    int index = static_cast<int>(z);
    if (index < 0 || index >= 4) return -1;
    long long amount = BASE[index];
    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);
    if (weekend) amount = amount * 90 / 100;
    else if (peak) amount = amount * 120 / 100;
    return amount;

}
class SmartCard {

    long long balance;

public:

    SmartCard(long long b) : balance(b) {}

    bool pay(long long fare) {

        if (fare < 0 || balance < fare || balance - fare < 5000)

            return false;

        balance -= fare;

        return true;

    }

    long long getBalance() const { return balance; }

};

 

class Pass {

    bool active;

    Zone first, second;

public:

    Pass(bool a, Zone x, Zone y) : active(a), first(x), second(y) {}

    bool covers(Zone z) const {

        return active && (z == first || z == second);

    }

};

 

int main() {

    SmartCard card(20000);

    Pass monthlyPass(true, Zone::Inner, Zone::Middle);

    Zone tripZone = Zone::Airport;

 

    if (monthlyPass.covers(tripZone)) {

        cout << "Journey covered by monthly pass\n";

    } else {

        long long fare = calculateFare(tripZone, 18, true);

        if (card.pay(fare)) cout << "Fare paid: " << fare << " paise\n";

        else cout << "Journey denied\n";

    }

    cout << "Balance: " << card.getBalance() << " paise\n";

}
