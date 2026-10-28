#include <iostream>

#include <climits>

using namespace std;

 

int main() {

    long long balancePaise = 10000;

    long long farePaise = 3600;

    long long remainingPaise = balancePaise - farePaise;

    long long dailyJourneys = 3000000;

    long long networkTotalPaise = dailyJourneys * 3000;

 

    cout << "Balance: " << balancePaise << " paise\n";

    cout << "Fare: " << farePaise << " paise\n";

    cout << "Remaining: " << remainingPaise << " paise\n";

    cout << "Network total: " << networkTotalPaise << " paise\n";

    cout << "INT_MAX: " << INT_MAX << '\n';

    cout << "sizeof(int): " << sizeof(int) << '\n';

    cout << "sizeof(long long): " << sizeof(long long) << '\n';

    cout << "sizeof(double): " << sizeof(double) << '\n';

}
