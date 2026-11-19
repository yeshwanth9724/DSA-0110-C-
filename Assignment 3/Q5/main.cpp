#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

// Predict the Output Counter from Specification
struct Counter {
    int v;
    Counter& operator++() { ++v; return *this; } // prefix
    Counter operator++(int) { Counter old = *this; ++v; return old; } // postfix
};

void runCounterPrediction() {
    std::cout << "--- [Specification Predict the Output: Counter Increment] ---\n";
    Counter c{5};
    Counter a = c++;
    Counter b = ++c;
    std::cout << a.v << ' ' << b.v << ' ' << c.v << "\n\n";
}

// Track Time with Prefix and Postfix ++
class Time {
private:
    int hours, minutes, seconds;

public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}

    // Prefix increment (++t): increments and returns reference
    Time& operator++() {
        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
                hours++;
            }
        }
        return *this;
    }

    // Postfix increment (t++): dummy int parameter, returns old copy
    Time operator++(int) {
        Time temp = *this;
        ++(*this); // reuse prefix logic
        return temp;
    }

    bool operator==(const Time& o) const {
        return hours == o.hours && minutes == o.minutes && seconds == o.seconds;
    }

    bool operator<(const Time& o) const {
        if (hours != o.hours) return hours < o.hours;
        if (minutes != o.minutes) return minutes < o.minutes;
        return seconds < o.seconds;
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << std::setfill('0') << std::setw(2) << t.hours << ":"
           << std::setfill('0') << std::setw(2) << t.minutes << ":"
           << std::setfill('0') << std::setw(2) << t.seconds;
        return os;
    }
};

// Playlist with Subscript Operator Overloading
class Playlist {
private:
    std::string tracks[5];
    int count;

public:
    Playlist() : count(0) {}

    void add(const std::string& track) {
        if (count < 5) tracks[count++] = track;
    }

    int size() const { return count; }

    // Non-const subscript (permits modification)
    std::string& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        return tracks[index];
    }

    // Const subscript (read-only access)
    const std::string& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        return tracks[index];
    }
};

int main() {
    runCounterPrediction();

    std::cout << "--- [Time Increment & Rollover Verification] ---\n";
    Time t(0, 59, 59);
    std::cout << "Initial Time: " << t << '\n';
    ++t;
    std::cout << "After ++t (Rollover): " << t << '\n';

    Time tPost = t++;
    std::cout << "After tPost = t++ -> tPost: " << tPost << " | New t: " << t << '\n';

    std::cout << "\n--- [Playlist Subscript Operator & Range Check] ---\n";
    Playlist pl;
    pl.add("Track 1 - Beethoven");
    pl.add("Track 2 - Mozart");
    pl.add("Track 3 - Chopin");

    std::cout << "Valid access pl[1]: " << pl[1] << '\n';

    try {
        std::cout << "Accessing pl[-1]: ";
        std::cout << pl[-1] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    try {
        std::cout << "Accessing pl[pl.size()]: ";
        std::cout << pl[pl.size()] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    std::cout << "\n[Q5 INCREMENT, COMPARISON, AND SUBSCRIPT OPERATORS COMPLETED]\n";
    return 0;
}
