#include <iostream>

using namespace std;

 

class SmartCard {

    long long balance;

public:

    SmartCard(long long b) : balance(b) {}

    bool canTravel(long long fare) const {

        return fare >= 0 && balance >= fare && balance - fare >= 5000;

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

    if (card.deduct(3600)) cout << "Journey allowed\n";

    else cout << "Journey denied\n";

    cout << "Balance: " << card.getBalance() << " paise\n";

}
