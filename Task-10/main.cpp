#include <iostream>

#include <iomanip>

using namespace std;

 

int main() {

    long long counts[] = {20000, 500000, 3000000};

    for (long long n : counts) {

        long long totalPaise = n * 3000;

        double totalRupees = static_cast<double>(n) * 30.0;

        cout << "Journeys: " << n << '\n';

        cout << "Total paise: " << totalPaise << '\n';

        cout << fixed << setprecision(2);

        cout << "Total rupees: " << totalRupees << "\n\n";

    }

}
