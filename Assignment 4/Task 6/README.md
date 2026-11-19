# Assignment 4 - Task 6: Vehicle Rental Fleet Design Challenge

## 1. Problem Context: Polymorphic Vehicle Rental System
A commercial vehicle rental company manages diverse vehicle categories: Bicycles, Two-Wheelers, Cars, Electric Cars, and newly added Electric Buses.

---

## 2. Design Evaluation: Open-Closed Principle (OCP)
- **Abstract Base Class (`Vehicle`):** Exposes pure virtual interfaces `calculateCharge()` and `getType()`.
- **Extensibility without Modification:** Adding `ElectricBus` required zero alterations to existing vehicle implementations.
- **Polymorphic Collection:** All fleet elements are operated uniformly via `std::vector<Vehicle*>` with virtual destructors ensuring dynamic memory integrity.
