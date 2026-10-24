# 06 — Quick Revision (Read this right before the interview)

## A. One-line definitions
| Term | One-liner |
|------|-----------|
| Class | Blueprint defining fields and methods |
| Object | Instance of a class with its own state |
| Encapsulation | Bundle data + methods; hide data behind access control |
| Abstraction | Expose essentials, hide implementation |
| Inheritance | Child acquires parent's members ("is-a") |
| Polymorphism | One interface, many forms (overload / override) |
| Constructor | Special method that initializes an object; no return type |
| `this` / `super` | Current object / parent class reference |
| `static` | Belongs to the class, shared by all objects |
| `final` | Constant variable / non-overridable method / non-inheritable class |
| Overloading | Same name, different parameters; compile-time |
| Overriding | Child redefines parent's method; run-time |
| Abstract class | Partly implemented, can't be instantiated |
| Interface | Pure contract; multiple implementation allowed |
| Virtual function (C++) | Enables runtime polymorphism through the vtable |
| Virtual destructor | Ensures the derived destructor runs via a base pointer |
| Shallow copy | Copies references (shared data) |
| Deep copy | Copies the actual data (independent) |
| Composition | Strong has-a; part can't outlive the whole |
| Aggregation | Weak has-a; part can exist alone |
| Coupling / Cohesion | Dependency between classes (low) / focus of a class (high) |
| SOLID | SRP, OCP, LSP, ISP, DIP |
| Singleton | Exactly one instance, global access |
| Factory | Create objects without exposing concrete classes |
| Observer | One-to-many notify on change |
| Strategy | Swap algorithms at runtime |
| Decorator | Add behaviour dynamically by wrapping |
| Dependency Injection | Pass dependencies in rather than creating them inside |
| Garbage collection | Automatic freeing of unreachable objects |
| RAII | Tie resource lifetime to object lifetime |

## B. Comparison tables ⭐

### Overloading vs Overriding
| | Overloading | Overriding |
|--|-------------|------------|
| Binding | Compile-time | Run-time |
| Scope | Same class | Parent–child |
| Signature | Different | Same |
| Static/private/final | Allowed | Not allowed |

### Abstract class vs Interface
| | Abstract class | Interface |
|--|----------------|-----------|
| Constructor | Yes | No |
| State (instance variables) | Yes | No (constants only) |
| Inheritance | Single | Multiple |
| Method bodies | Yes | default/static only |

### Encapsulation vs Abstraction
| | Encapsulation | Abstraction |
|--|---------------|-------------|
| Goal | Protect/bundle data | Hide complexity |
| How | Access modifiers | Abstract classes, interfaces |
| Level | Implementation | Design |

### Composition vs Aggregation vs Inheritance
| Composition | Aggregation | Inheritance |
|-------------|-------------|-------------|
| Strong has-a | Weak has-a | is-a |
| Part dies with whole | Part independent | Type hierarchy |

### Java vs C++ vs Python (key)
| | Java | C++ | Python |
|--|------|-----|--------|
| Memory | GC | Manual/RAII | GC |
| Multiple inheritance | Interfaces | Yes | Yes |
| Operator overloading | No | Yes | Yes |
| Virtual by default | Yes | No | Yes |
| Typing | Static | Static | Dynamic |

### Access modifiers (Java)
private < default < protected < public

## C. "Which one…?" quick answers
- Hide data → **Encapsulation**; hide implementation → **Abstraction**
- Reuse code through "is-a" → **Inheritance**
- Same method name, different parameters → **Overloading**
- Different behaviour in the child → **Overriding**
- Multiple inheritance in Java → **Interfaces**
- Diamond problem in C++ → **Virtual inheritance**
- Polymorphic delete in C++ → **Virtual destructor**
- Single instance → **Singleton**
- Create objects by type name → **Factory**
- Incompatible interfaces → **Adapter**
- Notify subscribers → **Observer**
- Swap behaviour at runtime → **Strategy**
- Simplify a complex subsystem → **Facade**
- One class, one reason to change → **SRP**
- Depend on abstractions → **DIP**
- Copy with independent data → **Deep copy**
- Per-class shared counter → **static variable**
- Immutable object → **`final` fields, no setters, `final` class**
- Release resources automatically → **try-with-resources (Java) / RAII (C++)**

## D. Top 50 interview questions (answer out loud)
**Basics**
1. What is OOP? Advantages?
2. Class vs object; real-life example?
3. Four pillars with examples?
4. Encapsulation vs abstraction?
5. Constructor types; can it be private/inherited/virtual?
6. `this`, `super`, `static`, `final` uses?
7. Access modifiers?
8. Procedural vs OOP?
9. Aggregation vs composition vs association?
10. Coupling and cohesion?

**Inheritance & polymorphism**
11. Types of inheritance? Why no multiple inheritance in Java?
12. Diamond problem and solutions?
13. Overloading vs overriding?
14. Runtime polymorphism / dynamic dispatch?
15. Can we override static/private/final methods?
16. Virtual function, pure virtual function, vtable?
17. Virtual destructor: why?
18. Abstract class vs interface; when to use?
19. Default methods in interfaces; why added?
20. Upcasting/downcasting; `instanceof`?
21. Object slicing?
22. Fields aren't overridden. Explain.

**Advanced**
23. Shallow vs deep copy? Copy constructor?
24. Rule of three/five?
25. Destructor, RAII, smart pointers?
26. Garbage collection in Java?
27. `final` vs `finally` vs `finalize`?
28. `==` vs `equals()`; `hashCode` contract?
29. String vs StringBuilder vs StringBuffer; String immutability?
30. Exception handling; checked vs unchecked; `throw` vs `throws`?
31. Does `finally` always execute?
32. Generics vs templates; type erasure?
33. Pass by value vs reference in Java?
34. JDK vs JRE vs JVM; platform independence?
35. Immutable class: how to create?
36. Thread: `Runnable` vs `Thread`; `start()` vs `run()`?
37. Friend function in C++?
38. Java vs C++ vs Python?

**Design**
39. SOLID with examples?
40. LSP violation example?
41. Dependency injection; DIP vs DI vs IoC?
42. Singleton: thread-safe implementation; how to break it?
43. Factory vs Abstract Factory?
44. Observer, Strategy, Decorator examples?
45. Adapter vs Facade vs Proxy?
46. Builder: when to use?
47. MVC?
48. UML relationships?
49. Design a parking lot / ATM / library management system.
50. Composition over inheritance: why?

## E. How to answer "Design X" (LLD) questions
1. **Clarify requirements** (actors, features, constraints).
2. **Identify entities/classes** (nouns → classes; verbs → methods).
3. **Define relationships** (is-a, has-a, uses).
4. **Apply SOLID**; pick patterns only where natural (Strategy for pricing, Observer for notifications, Factory for vehicle types, Singleton for the manager).
5. **Write core classes/interfaces and key methods**; talk through one flow.
6. **Discuss extensions**: concurrency, persistence, scalability, edge cases.

## F. Last-minute traps checklist
- [ ] Overloading = compile time; overriding = run time
- [ ] Static/private/final/constructors can't be overridden
- [ ] Fields use the reference type; methods use the object type (non-static, virtual)
- [ ] C++ needs `virtual`; Java is virtual by default
- [ ] Base destructor virtual in polymorphic hierarchies
- [ ] Constructors Base→Derived; destructors Derived→Base
- [ ] `this()`/`super()` first statement
- [ ] Java: pass by value; no multiple class inheritance; interface constants are `public static final`
- [ ] Copy constructor takes a reference
- [ ] `equals` ⇒ `hashCode`
- [ ] `finally` runs even after `return` (not after `System.exit`)
- [ ] C++ class default private; struct default public
- [ ] Composition > inheritance; low coupling, high cohesion
