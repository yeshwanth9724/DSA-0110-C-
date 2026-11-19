# Assignment 4 - Task 2: From Requirement to Hierarchy

## 1. Problem Context: University People Management
In a university data management system:
- A `Person` encapsulates common personal identity (`name`, `id`, `phone`).
- `Student` and `Staff` inherit from `Person`.
- A `TeachingAssistant` is simultaneously a `Student` and a `Staff` member, creating a diamond inheritance structure.

---

## 2. Resolving the Diamond Problem via Virtual Base Classes
- **The Problem:** Without virtual inheritance, `TeachingAssistant` inherits two distinct copies of `Person` (one via `Student` and one via `Staff`). This causes ambiguous member access (`ta.name` fails to compile) and redundant memory bloat.
- **The Solution:** Declaring `virtual public Person` in both `Student` and `Staff` ensures that only **one shared `Person` sub-object** is constructed.
- **Construction Order Rule:** In virtual inheritance, the **most-derived class** (`TeachingAssistant`) is solely responsible for initializing the virtual base class (`Person`). The constructor sequence is:
  `Person` $\to$ `Student` $\to$ `Staff` $\to$ `TeachingAssistant`.
- **Output:** `Person Student Staff TA `
