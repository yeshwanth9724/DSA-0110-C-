# Assignment 4 - Task 1: Class Design Review

## 1. Problem Context: Diagnosing and Repairing Duplicated Classes
A college payroll program contained three isolated classes (`Professor`, `LabAssistant`, and `GuestFaculty`) authored independently by different developers without an inheritance hierarchy.

---

## 2. Identified Design Deficiencies
1. **Repeated State & Behavior:** `name`, `id`, `basic`, and `da` were duplicated across multiple classes.
2. **Breach of Encapsulation:** All fields were made `public`, exposing data invariants to arbitrary tampering.
3. **Inconsistent Naming:** Attributes representing identical semantics had divergent names (`name` vs `nm`, `id` vs `code`).
4. **Hardcoded Magic Numbers:** The Dearness Allowance multiplier `0.42` was hardcoded inside member functions rather than encapsulated as a named constant.
5. **Inability to Uniformly Process Staff:** Without a common polymorphic base class, processing all staff in a single iteration was impossible, violating the Open-Closed Principle (OCP).

---

## 3. Repaired Class Hierarchy
A polymorphic base class `Staff` was introduced with a virtual `pay()` method:
- `RegularStaff` encapsulates permanent employees receiving basic pay and DA.
- `Professor` inherits from `RegularStaff` and adds research allowances.
- `LabAssistant` inherits from `RegularStaff` directly.
- `GuestFaculty` inherits from `Staff` and computes pay as `hours * hourlyRate`.
