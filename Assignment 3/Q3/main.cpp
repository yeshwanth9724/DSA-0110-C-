#include <iostream>
#include <string>

// Dynamic 2D Auditorium Seat Map
class AuditoriumEvent {
private:
    std::string eventName;
    int rows;
    int seatsPerRow;
    char** seatMap;

public:
    AuditoriumEvent(const std::string& name, int r, int s)
        : eventName(name), rows(r), seatsPerRow(s) {
        seatMap = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            seatMap[i] = new char[seatsPerRow];
            for (int j = 0; j < seatsPerRow; ++j) {
                seatMap[i][j] = 'O'; // 'O' for Open
            }
        }
        std::cout << "[Event Created: " << eventName << " (" << rows << "x" << seatsPerRow << " seats)]\n";
    }

    ~AuditoriumEvent() {
        int booked = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < seatsPerRow; ++j) {
                if (seatMap[i][j] == 'X') booked++;
            }
            delete[] seatMap[i];
        }
        delete[] seatMap;
        std::cout << "[Event Closed: " << eventName << " | Final Booked Seats: " << booked << "]\n";
    }

    bool bookSeat(int r, int s) {
        if (r >= 0 && r < rows && s >= 0 && s < seatsPerRow && seatMap[r][s] == 'O') {
            seatMap[r][s] = 'X';
            return true;
        }
        return false;
    }

    bool cancelSeat(int r, int s) {
        if (r >= 0 && r < rows && s >= 0 && s < seatsPerRow && seatMap[r][s] == 'X') {
            seatMap[r][s] = 'O';
            return true;
        }
        return false;
    }
};

// Predict the Output Verification from Specification
struct Logger {
    std::string n;
    Logger(const std::string& s) : n(s) { std::cout << '+' << n << ' '; }
    Logger(const Logger& o) : n(o.n + "c") { std::cout << "copy" << n << ' '; }
    ~Logger() { std::cout << '-' << n << ' '; }
};

void use(Logger) { std::cout << "use "; }

void runLoggerPrediction() {
    std::cout << "--- [Specification Predict the Output: Logger Lifetimes] ---\n";
    {
        Logger a("A");
        {
            Logger b("B");
        }
        use(a);
        Logger* p = new Logger("P");
        delete p;
        std::cout << "end ";
    }
    std::cout << "\n\n";
}

int main() {
    runLoggerPrediction();

    std::cout << "--- [Auditorium Seat Booking Simulation] ---\n";
    {
        AuditoriumEvent symp("Tech Symposium", 3, 5);
        symp.bookSeat(0, 0);
        symp.bookSeat(0, 1);
        symp.bookSeat(1, 2);
        symp.cancelSeat(0, 1);
    } // destructor automatically executes here via RAII

    std::cout << "\n[Q3 DYNAMIC CONSTRUCTORS AND DESTRUCTORS COMPLETED]\n";
    return 0;
}
