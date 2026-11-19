#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// PART 1: Predict the Output Token Program (Pages 8-9)
// ============================================================================

class Token {
    static int next;
    int id;
public:
    Token() { id = ++next; }
    int get() const { return id; }
    static int issued() { return next - 100; }
};

int Token::next = 100; // Definition and initialization of static member

void runTokenPrediction()
{
    std::cout << "--- [Predict the Output: Token Class Verification] ---\n";
    Token counter[3];
    Token extra;
    std::cout << counter[0].get() << ' ' << counter[2].get() << ' ' << extra.get()
              << ' ' << Token::issued() << '\n';
    std::cout << "Explanation: The constructor ran 4 times. Token::next started at 100 and reached 104.\n\n";
}

// ============================================================================
// PART 2: BusTicket Class with Static Members (Pages 9-10)
// ============================================================================

class BusTicket {
    static int issued; // shared by all BusTicket objects
    static const int CAPACITY = 3;
    int seat;
    std::string name;

public:
    explicit BusTicket(const std::string& n = "") : seat(0), name(n)
    {
        // TODO 1: If fewer than CAPACITY tickets have been issued, increase issued and
        // give this ticket the next seat number; otherwise leave seat as 0 (waiting list)
        if (issued < CAPACITY) {
            seat = ++issued;
        }
    }

    static int count()
    {
        // TODO 2: Return the number of seats issued so far
        return issued;
    }

    static void resetForNewBus()
    {
        issued = 0;
    }

    void print() const
    {
        std::cout << name << ": "
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting"))
                  << '\n';
    }

    int getSeat() const { return seat; }
};

int BusTicket::issued = 0; // definition of the static data member outside class

void runSpecificationCompleteTheCode()
{
    std::cout << "--- [Specification Complete the Code Output (Pages 10-11)] ---\n";
    BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"),
                         BusTicket("Chitra"), BusTicket("Dev")};

    for (const BusTicket& t : trip) t.print();
    std::cout << "Issued: " << BusTicket::count() << '\n';
    std::cout << '\n';
}

// ============================================================================
// PART 3: Calling Inside a Function Called Twice (Page 11)
// ============================================================================

void bookTicketsInBatch(int batchNumber)
{
    std::cout << "Executing batch " << batchNumber << " ticket booking:\n";
    BusTicket b1("BatchUserA_" + std::to_string(batchNumber));
    BusTicket b2("BatchUserB_" + std::to_string(batchNumber));
    b1.print();
    b2.print();
    std::cout << "Current total issued across all function calls: " << BusTicket::count() << "\n\n";
}

// ============================================================================
// PART 4: Alternative Concept - TicketOffice Object (Running Multiple Buses)
// ============================================================================

class TicketOffice {
private:
    int issued;
    int capacity;
public:
    TicketOffice(int cap) : issued(0), capacity(cap) {}

    int issueSeat() {
        if (issued < capacity) {
            return ++issued;
        }
        return 0; // waiting list
    }

    int getIssued() const { return issued; }
    int getCapacity() const { return capacity; }
};

class OfficeBusTicket {
    int seat;
    std::string name;
public:
    OfficeBusTicket(const std::string& n, TicketOffice& office)
        : name(n)
    {
        seat = office.issueSeat();
    }

    void print(const std::string& busName) const {
        std::cout << "[" << busName << "] " << name << ": " 
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n';
    }
};

void runMultipleBusAlternative()
{
    std::cout << "--- [Alternative Concept: TicketOffice Objects for Multiple Buses] ---\n";
    TicketOffice morningBusOffice(2);
    TicketOffice eveningBusOffice(2);

    OfficeBusTicket t1("Kavya", morningBusOffice);
    OfficeBusTicket t2("Rahul", morningBusOffice);
    OfficeBusTicket t3("Suresh", morningBusOffice); // should be waiting for morning bus

    OfficeBusTicket t4("Ananya", eveningBusOffice); // gets Seat 1 on evening bus independently!

    t1.print("Morning Bus");
    t2.print("Morning Bus");
    t3.print("Morning Bus");
    t4.print("Evening Bus");

    std::cout << "Morning Bus Issued: " << morningBusOffice.getIssued() << " / " << morningBusOffice.getCapacity() << '\n';
    std::cout << "Evening Bus Issued: " << eveningBusOffice.getIssued() << " / " << eveningBusOffice.getCapacity() << '\n';
}

// ============================================================================
// MAIN DRIVER
// ============================================================================

int main()
{
    std::cout << "=========================================================\n";
    std::cout << "  ASSIGNMENT 2 - CO2 | QUESTION 5 EXECUTION & VERIFICATION\n";
    std::cout << "=========================================================\n\n";

    runTokenPrediction();
    runSpecificationCompleteTheCode();

    std::cout << "--- [Investigation: Tickets Created Inside Function Called Twice] ---\n";
    // Reset static count to demonstrate clean batch behavior
    BusTicket::resetForNewBus();
    bookTicketsInBatch(1);
    bookTicketsInBatch(2);

    runMultipleBusAlternative();

    std::cout << "\n[ALL Q5 TESTS AND VERIFICATIONS COMPLETED SUCCESSFULLY]\n";
    return 0;
}
