#include <iostream>

using namespace std;

 

bool canTravel(long long balance, long long fare) {

    return fare >= 0 && balance >= fare && balance - fare >= 5000;

}

bool deductFare(long long& balance, long long fare) {

    if (!canTravel(balance, fare)) return false;

    balance -= fare;

    return true;

}

int main() {

    long long balance = 10000, fare = 3600;

    if (deductFare(balance, fare)) cout << "Journey allowed\n";

    else cout << "Journey denied\n";

    cout << "Balance: " << balance << " paise\n";

}
