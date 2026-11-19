# Assignment 5 - Task 4: Final Engineering Decision

## 1. Production Decision for the Hospital Network
The hospital network operates 15 multi-speciality hospitals processing 200,000 daily bills, adding 2 new bill categories and 3 new insurance/corporate payers annually.

---

## 2. Evaluation of Architectural Suitability
1. **Adherence to Open-Closed Principle (OCP):**
   - Incorporating `DayCareSurgeryBill` and `CorporateTieUp` required zero lines of code changes in existing base interfaces or settlement pipelines.
2. **Scalability:**
   - As proven in Task 3 benchmarks, virtual method dispatch processes $1,000,000$ bills in $4.58\text{ ms}$, exceeding the daily throughput requirement ($200,000$ bills) in under $1\text{ ms}$ of CPU time.
3. **Resource Safety with Modern RAII:**
   - Using `std::unique_ptr<Bill>` guarantees automated destruction without memory leaks, even when exceptions are thrown during claim verification.
