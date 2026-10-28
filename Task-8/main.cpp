#include <iostream>

#include <iomanip>

#include <limits>

using namespace std;

 

int main() {

    int hour;

    cout << "Enter hour (0-23): ";

    while (!(cin >> hour) || hour < 0 || hour > 23) {

        cout << "Invalid hour. Enter again: ";

        if (cin.fail()) {

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }

    }

 

    cout << "Hour accepted: " << hour << '\n';

    long long amount = 1234;

    cout << "Fare Rs " << amount / 100 << '.' << setw(2)

         << setfill('0') << amount % 100 << setfill(' ') << '\n';

}
