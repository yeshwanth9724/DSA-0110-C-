#include <iostream>

#include <string>

using namespace std;

 

enum class Zone { Inner, Middle, Outer };

enum class PassengerType { Regular, Student, Senior };

 

class FareTable {

public:

    static long long baseFare(Zone zone) {

        switch (zone) {

            case Zone::Inner: return 1000;

            case Zone::Middle: return 2000;

            case Zone::Outer: return 3000;

        }

        return 0;

    }

 

    static long long calculate(Zone zone, bool peak) {

        long long fare = baseFare(zone);

        if (peak) fare += fare * 20 / 100;

        return fare;

    }

};

 

class SmartCard {

    long long balance;

public:

    explicit SmartCard(long long amount) : balance(amount) {}

 

    bool canTravel(long long fare) const {

        return fare >= 0 && balance >= fare &&

               balance - fare >= 5000;

    }

 

    bool deduct(long long fare) {

        if (!canTravel(fare)) return false;

        balance -= fare;

        return true;

    }

 

    long long getBalance() const { return balance; }

};

 

int main() {

    SmartCard card(10000);

    long long fare = FareTable::calculate(Zone::Outer, true);

 

    if (card.deduct(fare))

        cout << "Journey allowed\n";

    else

        cout << "Journey denied\n";

 

    cout << "Balance: " << card.getBalance() << " paise\n";

}
