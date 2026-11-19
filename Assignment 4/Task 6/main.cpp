#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Abstract Base Class
class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool isRented;

public:
    Vehicle(const std::string& reg, double rate)
        : regNo(reg), dailyRate(rate), isRented(false) {}
    virtual ~Vehicle() = default;

    virtual double calculateCharge(int days, int lateDays, double energyUsed) const = 0;
    virtual std::string getType() const = 0;

    void rent() { isRented = true; }
    void returnVehicle() { isRented = false; }
    bool getIsRented() const { return isRented; }
    std::string getRegNo() const { return regNo; }

    virtual void display() const {
        std::cout << "[" << getType() << "] Reg: " << regNo << " | Daily Rate: Rs " 
                  << std::fixed << std::setprecision(2) << dailyRate 
                  << " | Status: " << (isRented ? "RENTED" : "AVAILABLE") << '\n';
    }
};

// 1. Bicycle
class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate = 150.0) : Vehicle(reg, rate) {}

    double calculateCharge(int days, int lateDays, double) const override {
        double lateFee = lateDays * (dailyRate * 1.5);
        return (days * dailyRate) + lateFee;
    }
    std::string getType() const override { return "Bicycle"; }
};

// 2. MotorVehicle (Abstract intermediate class)
class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    std::string serviceDueDate;

public:
    MotorVehicle(const std::string& reg, double rate, double energy, const std::string& date)
        : Vehicle(reg, rate), fuelOrChargeLevel(energy), serviceDueDate(date) {}
};

// 3. TwoWheeler
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double fuel, const std::string& date)
        : MotorVehicle(reg, rate, fuel, date) {}

    double calculateCharge(int days, int lateDays, double fuelConsumedLiters) const override {
        double lateFee = lateDays * (dailyRate * 1.5);
        double fuelCost = fuelConsumedLiters * 105.0; // Rs 105 per litre
        return (days * dailyRate) + lateFee + fuelCost;
    }
    std::string getType() const override { return "Two-Wheeler"; }
};

// 4. Car
class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(const std::string& reg, double rate, double fuel, const std::string& date, int seats)
        : MotorVehicle(reg, rate, fuel, date), seatingCapacity(seats) {}

    double calculateCharge(int days, int lateDays, double fuelConsumedLiters) const override {
        double lateFee = lateDays * (dailyRate * 2.0);
        double fuelCost = fuelConsumedLiters * 105.0;
        return (days * dailyRate) + lateFee + fuelCost;
    }
    std::string getType() const override { return "Car"; }
};

// 5. ElectricCar
class ElectricCar : public Car {
private:
    double batteryCapacityKWh;

public:
    ElectricCar(const std::string& reg, double rate, double chargeLevel, const std::string& date, int seats, double batCap)
        : Car(reg, rate, chargeLevel, date, seats), batteryCapacityKWh(batCap) {}

    double calculateCharge(int days, int lateDays, double kwhUsed) const override {
        double lateFee = lateDays * (dailyRate * 2.0);
        double electricityCost = kwhUsed * 12.0; // Rs 12 per kWh
        return (days * dailyRate) + lateFee + electricityCost;
    }
    std::string getType() const override { return "Electric Car"; }
};

// 6. Extensibility Demonstration: ElectricBus added without modifying existing classes
class ElectricBus : public Vehicle {
private:
    int passengerCapacity;
    double batteryKWh;

public:
    ElectricBus(const std::string& reg, double rate, int cap, double bat)
        : Vehicle(reg, rate), passengerCapacity(cap), batteryKWh(bat) {}

    double calculateCharge(int days, int lateDays, double kwhUsed) const override {
        double lateFee = lateDays * (dailyRate * 2.5);
        double powerCost = kwhUsed * 14.0;
        return (days * dailyRate) + lateFee + powerCost;
    }
    std::string getType() const override { return "Electric Bus (Extension)"; }
};

int main() {
    std::cout << "--- [Vehicle Rental Fleet Simulation] ---\n";

    std::vector<Vehicle*> fleet = {
        new Bicycle("CYC-01", 200.0),
        new TwoWheeler("TN-09-BK-1122", 500.0, 5.0, "2026-12-01"),
        new Car("TN-01-CR-9900", 2500.0, 30.0, "2026-12-15", 5),
        new ElectricCar("TN-02-EV-4433", 3500.0, 95.0, "2027-01-10", 5, 60.0),
        new ElectricBus("TN-03-EB-7788", 8000.0, 40, 250.0) // seamless extension
    };

    std::cout << "1. Current Fleet Directory:\n";
    for (const auto* v : fleet) v->display();

    std::cout << "\n2. Processing Rentals and Returns:\n";
    // Rent Car for 3 days, returned 1 day late, consumed 15 litres fuel
    fleet[2]->rent();
    double carBill = fleet[2]->calculateCharge(3, 1, 15.0);
    fleet[2]->returnVehicle();
    std::cout << "Car Rental Invoice: Rs " << carBill << '\n';

    // Rent Electric Bus for 2 days, on time, 80 kWh consumed
    fleet[4]->rent();
    double busBill = fleet[4]->calculateCharge(2, 0, 80.0);
    fleet[4]->returnVehicle();
    std::cout << "Electric Bus Rental Invoice: Rs " << busBill << '\n';

    for (auto* v : fleet) delete v;

    std::cout << "\n[TASK 6 VEHICLE RENTAL DESIGN CHALLENGE COMPLETED]\n";
    return 0;
}
