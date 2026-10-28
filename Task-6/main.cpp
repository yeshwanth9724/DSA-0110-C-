#include <iostream>

#include <iomanip>

using namespace std;

 

enum class Zone { Inner, Middle, Outer };

constexpr long long BASE[] = {1000, 2000, 3000};

constexpr long long MIN_BALANCE = 5000;

 

long long fare(Zone z, bool peak) {

    long long amount = 0;

    switch (z) {

        case Zone::Inner: amount = BASE[0]; break;

        case Zone::Middle: amount = BASE[1]; break;

        case Zone::Outer: amount = BASE[2]; break;

    }

    if (peak) amount += amount * 20 / 100;

    return amount;

}

 

bool canTravel(long long balance, long long f) {

    return f >= 0 && balance >= f && balance - f >= MIN_BALANCE;

}

 

int main() {

    long long balance = 10000;

    struct Trip { Zone zone; bool peak; };

    Trip trips[] = {

        {Zone::Inner, false}, {Zone::Outer, true}, {Zone::Middle, false}

    };

 

    for (const Trip& t : trips) {

        long long f = fare(t.zone, t.peak);

        if (canTravel(balance, f)) {

            balance -= f;

            cout << "Fare Rs " << f / 100 << '.' << setw(2)

                 << setfill('0') << f % 100 << setfill(' ');

        } else {

            cout << "Denied (low balance)";

        }

        cout << " balance Rs " << balance / 100 << '\n';

    }

}
