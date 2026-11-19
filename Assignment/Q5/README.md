# Question 5: Static Members and Arrays of Objects

## 1. Problem Context: College Bus Seat Tickets
A college bus transport system issues tickets to students. A bus has a fixed seating capacity (e.g., 3 seats). 
- Every created `BusTicket` object must obtain the next sequential seat number.
- When capacity is reached, subsequent tickets receive seat number `0` (indicating the student is on the waiting list).
- The transport office must be able to query the global number of issued seats without inspecting any individual ticket object.

---

## 2. Core OOP Principle: Class-Level State
> *"Data that belongs to the whole class – not to any one object – should exist only once, however many objects are created."*

### Determining Member Types:
1. **Static Data Member (`static int issued`):** Shared across every instance of `BusTicket`. Resides in the static storage area, not in per-object instance memory.
2. **Static Member Function (`static int count()`):** Can be called directly on the class (`BusTicket::count()`) without requiring an existing object instance.
3. **Non-Static Instance Members (`int seat`, `std::string name`):** Each ticket maintains its own passenger name and assigned seat number.

### Where Static Data Members Must Be Defined
A `static` data member is only **declared** inside the class definition. It must be explicitly **defined and initialized outside the class** at namespace/file scope in a single compilation unit:
```cpp
int BusTicket::issued = 0; // Definition allocating storage
```
Without this definition, the linker raises an `undefined reference to BusTicket::issued` error.

---

## 3. Inquiry Questions & Evaluation (K5)

### Q: Why can a static member function not use `this` or non-static members?
In C++, non-static member functions receive an implicit first parameter: the `this` pointer (pointing to the specific calling instance). 
Static member functions are invoked at the class level (`ClassName::function()`) without an instance context. Therefore:
1. No `this` pointer is passed in the function's calling convention.
2. The compiler cannot identify which instance's member variables should be accessed.
3. Consequently, accessing instance variables or calling non-static member functions from a static member function is a compilation error unless an explicit object reference is passed.

### Q: How is an array of `BusTicket` objects created and initialized?
When an array of objects is declared:
```cpp
BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"), BusTicket("Chitra"), BusTicket("Dev")};
```
The runtime sequentially invokes the constructor for index `0`, then `1`, `2`, and `3`. Each constructor execution accesses the shared `static int issued` counter, which increments monotonically until `CAPACITY` is reached.

### Q: What happens to the count when tickets are created inside a loop or function?
Because static variables reside in the program's static data segment rather than on the call stack:
1. The static counter **persists** across function invocations and loop iterations.
2. Even if temporary `BusTicket` objects go out of scope and are destroyed, `issued` continues to reflect the cumulative total issued unless explicitly decremented in a destructor.

---

## 4. Predict the Output Analysis (Token Class)

### Code Trace
```cpp
Token counter[3]; // Constructor executes 3 times: next becomes 101, 102, 103
Token extra;      // Constructor executes 1 time:  next becomes 104

// counter[0].get() -> 101
// counter[2].get() -> 103
// extra.get()      -> 104
// Token::issued()  -> 104 - 100 = 4
```
- **Predicted Output:** `101 103 104 4`
- **Actual Executed Output:** `101 103 104 4` (Exact match)
- **Constructor Invocations:** Exactly 4 times.

---

## 5. Alternative Concept and Complexity Analysis

### Comparison: Global Variable vs. Static Member vs. `TicketOffice` Object

| Architectural Approach | Encapsulation & Security | Multi-Bus Scalability (e.g., 2+ buses) | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **1. Global Variable (`int g_issued`)** | **Poor:** Accessible and modifiable anywhere in the global namespace; vulnerable to tampering. | **Fails:** One global variable cannot track multiple independent buses simultaneously. | $O(1)$ | 4 bytes total |
| **2. Static Class Member (`BusTicket::issued`)** | **Strong:** Encapsulated inside `BusTicket`; access controlled via access specifiers (`private`). | **Limited:** All tickets share the exact same static counter, coupling all instances to a single bus. | $O(1)$ | 4 bytes total |
| **3. `TicketOffice` Entity Object** | **Superior:** High cohesion; encapsulates seat allocation policy per bus instance. | **Excellent:** Each bus instance has its own `TicketOffice` object (`morningBusOffice`, `eveningBusOffice`). | $O(1)$ | 8 bytes per bus office |

**Defended Design:** While static class members elegantly solve single-resource tracking, in a commercial transport system operating a fleet of buses, passing a reference to a dedicated **`TicketOffice`** object is the superior design pattern, ensuring complete domain decoupling and independent bus capacity management.
