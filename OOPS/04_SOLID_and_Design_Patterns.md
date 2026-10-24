# 04 — SOLID Principles & Design Patterns

## 1. Good Design Basics ⭐
- **Coupling:** how much one class depends on another. **Aim: loose (low) coupling.** Achieved with interfaces, dependency injection.
- **Cohesion:** how closely a class's responsibilities relate. **Aim: high cohesion.**
- **DRY** (Don't Repeat Yourself), **KISS** (Keep It Simple), **YAGNI** (You Aren't Gonna Need It), **Law of Demeter** (talk only to close friends), **Composition over inheritance**, **Program to an interface, not an implementation**, **Separation of concerns**.

## 2. SOLID ⭐⭐⭐
### S — Single Responsibility Principle (SRP)
**A class should have only one reason to change** (one responsibility).
- ✘ `Employee` handles salary calculation **and** saving to DB **and** report printing.
- ✔ Split into `Employee`, `EmployeeRepository`, `ReportPrinter`.

### O — Open/Closed Principle (OCP)
**Open for extension, closed for modification.** Add new behaviour by adding new code (subclasses / new implementations), not by editing existing tested code.
```java
interface Shape { double area(); }
class Circle implements Shape { ... }
class Square implements Shape { ... }
// AreaCalculator works with any Shape; adding Triangle needs no change to it
```
- ✘ A giant `if/else` or `switch` on type that must grow for each new type.

### L — Liskov Substitution Principle (LSP)
**Subtypes must be substitutable for their base types without breaking correctness.**
- Classic violation: `Square extends Rectangle` (setting width changes height, which breaks Rectangle's expectations). Another: `Ostrich extends Bird` with `fly()` throwing an exception.
- Fix: better abstractions (`Bird` / `FlyingBird`), composition.
- An overridden method shouldn't strengthen preconditions, weaken postconditions, or throw unexpected exceptions.

### I — Interface Segregation Principle (ISP)
**Clients shouldn't be forced to depend on methods they don't use.** Prefer several small, specific interfaces over one fat interface.
- ✘ `Worker { work(); eat(); }`, so a `Robot` must implement `eat()`.
- ✔ `Workable`, `Eatable`.

### D — Dependency Inversion Principle (DIP)
**High-level modules shouldn't depend on low-level modules; both should depend on abstractions.**
- ✘ `OrderService` does `new MySQLDatabase()` internally.
- ✔ `OrderService(Database db)`, where `Database` is an interface → swap MySQL/Mongo/mock for tests.
- **Dependency Injection (DI)** is the technique (constructor / setter injection); **IoC (Inversion of Control)** is the principle (framework like **Spring** controls object creation). DIP ≠ DI ≠ IoC, but they're related.

| Letter | Principle | One-liner |
|:--:|-----------|-----------|
| S | Single Responsibility | One class, one reason to change |
| O | Open/Closed | Extend, don't modify |
| L | Liskov Substitution | Children must work wherever the parent does |
| I | Interface Segregation | Small, focused interfaces |
| D | Dependency Inversion | Depend on abstractions |

## 3. Design Patterns ⭐⭐
Reusable solutions to common design problems (**Gang of Four (GoF): 23 patterns in 3 categories**).
| Category | Purpose | Examples |
|----------|---------|----------|
| **Creational** | Object **creation** | **Singleton**, **Factory Method**, **Abstract Factory**, **Builder**, Prototype |
| **Structural** | Class/object **composition** | **Adapter**, **Decorator**, **Facade**, Proxy, Composite, Bridge, Flyweight |
| **Behavioral** | **Communication** / responsibility | **Observer**, **Strategy**, **Command**, State, Iterator, Template Method, Chain of Responsibility, Mediator |

### Singleton ⭐⭐⭐
**Ensure a class has only one instance and provide a global access point.** Uses: config, logger, cache, connection pool.
```java
class Singleton {
    private static volatile Singleton instance;
    private Singleton() {}                        // private constructor
    public static Singleton getInstance() {
        if (instance == null) {                   // 1st check (no lock)
            synchronized (Singleton.class) {
                if (instance == null)             // 2nd check
                    instance = new Singleton();
            }
        }
        return instance;
    }
}
```
- Ways: **eager** (create at class load; simple, thread-safe), **lazy** (create on first use; needs sync), **double-checked locking** (`volatile` needed), **Bill Pugh / holder class**, **enum singleton** (safest; survives serialization/reflection).
- **Pitfalls:** hidden global state, hard to test, thread-safety, can be broken by **reflection, serialization, cloning.**

### Factory Method / Simple Factory
**Creates objects without exposing the creation logic;** the client asks for a type and gets an object that implements a common interface.
```java
interface Shape { void draw(); }
class ShapeFactory {
    static Shape create(String type) {
        switch (type) { case "circle": return new Circle(); case "square": return new Square(); }
        throw new IllegalArgumentException();
    }
}
```
- Benefits: decouples the client from concrete classes, supports OCP. **Abstract Factory** = a factory of **families of related objects** (e.g. `WindowsUIFactory` / `MacUIFactory`).

### Builder
Construct a **complex object step by step** (many optional parameters). Avoids telescoping constructors. `new Pizza.Builder().size(12).cheese().build();`

### Prototype
Create new objects by **cloning** an existing one.

### Adapter
**Converts one interface to another the client expects** (a wrapper). Example: a power-plug adapter; wrapping a legacy API.

### Decorator
**Adds behaviour to an object dynamically** by wrapping it (instead of subclassing). Example: Java I/O `new BufferedReader(new FileReader(f))`; coffee + milk + sugar.

### Facade
A **simplified single interface** to a complex subsystem. (Example: `OrderFacade.placeOrder()` hides inventory, payment, and shipping calls.)

### Proxy
A **stand-in** controlling access to another object (lazy loading, access control, caching, logging).

### Observer ⭐⭐
**One-to-many dependency:** when the **subject** changes state, all its **observers** are notified automatically. **Publish–subscribe.** Examples: YouTube subscribers, event listeners, MVC (Model notifies Views).
```java
interface Observer { void update(String msg); }
class Subject { List<Observer> obs = new ArrayList<>();
  void subscribe(Observer o){ obs.add(o); }
  void notifyAll(String m){ for (Observer o: obs) o.update(m); } }
```

### Strategy ⭐
**Define a family of interchangeable algorithms, encapsulate each, and select one at runtime.** Replaces `if/else` on behaviour. Example: payment methods (`CardPay`, `UPIPay`), sorting strategies, `Comparator`.

### Command, State, Template Method, Iterator, Chain of Responsibility (one-liners)
- **Command:** wrap a request as an object (undo/redo, queues). **State:** behaviour changes with internal state (traffic light, order status). **Template Method:** skeleton algorithm in a base class; subclasses fill in steps. **Iterator:** traverse a collection without exposing its structure. **Chain of Responsibility:** pass a request along a chain of handlers (middleware, logging levels).

### MVC (architectural pattern)
**Model** (data/logic), **View** (UI), **Controller** (handles input, updates the model/view). Separation of concerns. Variants: MVP, MVVM.

## 4. UML Class Diagram Essentials ⭐
- Class box: **Name / attributes / methods.** Visibility: **`+` public, `-` private, `#` protected**.
- Relationships: **Association** (line), **Aggregation** (hollow diamond ◇ at the whole), **Composition** (filled diamond ◆ at the whole), **Inheritance/Generalization** (hollow triangle arrow to the parent), **Realization/implements interface** (dashed line + hollow triangle), **Dependency** (dashed arrow).
- **Multiplicity:** 1, 0..1, *, 1..*.
- Other UML: use-case, sequence, activity diagrams.

## 5. Choosing Patterns (quick guide)
| Problem | Pattern |
|---------|---------|
| Only one instance needed | **Singleton** |
| Create objects without specifying the exact class | **Factory** |
| Many optional constructor params | **Builder** |
| Incompatible interfaces | **Adapter** |
| Add features at runtime without subclassing | **Decorator** |
| Hide subsystem complexity | **Facade** |
| Notify many objects of changes | **Observer** |
| Swap algorithms at runtime | **Strategy** |
| Undo/redo | **Command** |
| Behaviour depends on state | **State** |

## 6. Common Interview Questions
1. Explain SOLID with examples.
2. Give an example of an LSP violation.
3. What is Dependency Injection? DIP vs DI vs IoC?
4. What is a design pattern? Categories? Examples of each.
5. Implement a thread-safe Singleton. How can you break it? How to prevent it?
6. Factory vs Abstract Factory?
7. Observer pattern: real examples?
8. Strategy vs State? (Strategy: the client picks the algorithm. State: the object switches its own behaviour.)
9. Decorator vs inheritance? Adapter vs Facade?
10. Aggregation vs composition (UML)?
11. Coupling and cohesion?
12. Design a parking lot / library / ATM / elevator system using OOP. (Identify classes, relationships, apply SOLID, use patterns where natural.)

## MCQ Traps
- **SRP = one reason to change; OCP = extend, not modify; LSP = substitutability; ISP = small interfaces; DIP = depend on abstractions.**
- **Singleton = private constructor + static instance + static accessor.**
- **Creational (Singleton, Factory, Builder), Structural (Adapter, Decorator, Facade, Proxy), Behavioral (Observer, Strategy, Command).**
- **Observer = one-to-many notification (pub–sub).**
- **Adapter changes an interface; Facade simplifies one; Decorator adds behaviour.**
- **Low coupling + high cohesion = good design.**
- **Square–Rectangle = classic LSP violation.**
- **UML: ◆ composition, ◇ aggregation.**
- **DI is a technique to implement DIP/IoC.**

## Practice MCQs
1. "A class should have only one reason to change" → **SRP**
2. Pattern ensuring a single instance → **Singleton**
3. Pattern for adding responsibilities dynamically → **Decorator**
4. Which pattern is used in event listeners (subscribe/notify)? → **Observer**
5. A `Robot` forced to implement `eat()` violates → **ISP**
