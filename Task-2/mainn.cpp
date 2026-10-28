#include <iostream>
using namespace std;
enum class Zone { Inner, Middle, Outer };
constexpr long long INNER_FARE = 1000;
constexpr long long MIDDLE_FARE = 2000;
constexpr long long OUTER_FARE = 3000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;
int main() {

    cout << INNER_FARE << '\n';

    cout << MIDDLE_FARE << '\n';

    cout << OUTER_FARE << '\n';

    cout << PEAK_SURCHARGE_PERCENT << '\n';

    cout << MIN_BALANCE_PAISE << '\n';

}
