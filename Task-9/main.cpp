Task 9 — Table-Driven Fare Tests

#include <iostream>

using namespace std;

 

long long calculateFare(int base, int hour) {

    bool peak = (hour >= 8 && hour < 10) ||

                (hour >= 17 && hour < 20);

    return peak ? base + base * 20 / 100 : base;

}

 

int main() {

    struct Test { int base, hour; long long expected; };

    Test tests[] = {

        {1000, 7, 1000}, {1000, 8, 1200},

        {2000, 10, 2000}, {3000, 17, 3600},

        {3000, 20, 3000}

    };

 

    for (const Test& t : tests) {

        long long actual = calculateFare(t.base, t.hour);

        cout << "Hour " << t.hour << ": expected " << t.expected

             << ", actual " << actual

             << (actual == t.expected ? " PASS" : " FAIL") << '\n';

    }

}
