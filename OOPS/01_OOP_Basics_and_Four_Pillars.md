# 01 — OOP Basics & the Four Pillars

## 1. Procedural vs Object-Oriented Programming ⭐
| Procedural (C) | Object-Oriented (Java, C++, Python) |
|----------------|-------------------------------------|
| Focus on **functions / steps** | Focus on **objects** (data + behaviour) |
| Data and functions separate | Data and methods **bundled** in a class |
| Top-down design | Bottom-up design |
| Global data, less secure | **Data hiding**, more secure |
| Hard to reuse/scale | Reusable, extensible, maintainable |

**Why OOP?** Modularity, reusability (inheritance), maintainability, security (encapsulation), real-world modelling.

## 2. Class & Object ⭐
- **Class:** blueprint/template that defines **attributes (fields/state)** and **methods (behaviour).** No memory for the data until an object exists (except static members).
- **Object:** an **instance** of a class, with its own state. Occupies memory. Has **identity, state, behaviour**.
```java
class Car {
    String color;            // state
    void drive() { ... }     // behaviour
}
Car c1 = new Car();          // object
```
```cpp
class Car { public: string color; void drive() {} };
Car c1;                      // on stack
Car* c2 = new Car();         // on heap (must delete)
```
- **Java:** objects are always on the **heap**; variables hold **references**. **C++:** objects can be on the stack or the heap.
- **Message passing:** objects communicate by calling each other's methods.

## 3. Constructors ⭐⭐
Special method that **initializes** an object when created. **Same name as the class, no return type.** Called automatically.
| Type | Description |
|------|-------------|
| **Default** | No arguments. **Compiler provides one only if you define no constructor** |
| **Parameterized** | Takes arguments |
| **Copy constructor** | Creates an object from another of the same class (C++: `Car(const Car&)`; Java has none built in, so write your own) |
| **Private constructor** | Prevents instantiation (Singleton, utility classes) |

- **Constructor overloading:** many constructors with different parameters.
- **Constructor chaining:** `this(...)` calls another constructor of the **same class**; `super(...)` calls the **parent** constructor. **Must be the first statement.**
- **Constructors can't be `static`, `final`, `abstract`, or (in Java) inherited.** C++ constructors **can't be virtual.**
- Constructor order in inheritance: **Base → Derived**.
- **Initializer list (C++):** `Car(int s) : speed(s) {}`. Required for **const and reference members** and base-class constructors with arguments.
- **Java:** default field values: `int → 0`, `boolean → false`, objects → `null`. **Local variables have no default.**
- **Python:** `__init__` initializes (object is created by `__new__`); `self` is explicit.

## 4. `this`, `static`, `final` ⭐
### `this`
Reference to the **current object.** Uses: disambiguate field vs parameter (`this.name = name`), call another constructor, pass the current object, return it (method chaining). **Not available in static methods.**

### `static`
Belongs to the **class**, not any object.
- **Static variable:** one copy shared by all objects (e.g. object counter). **Static method:** called via the class name; **can't use `this` or access non-static members directly.**
- **Static block (Java):** runs once when the class loads.
- **Static methods can't be overridden** (they're hidden, since they bind at compile time).
- `main` is static so the JVM can call it without creating an object.

### `final` (Java) / `const` (C++)
- Variable: constant after initialization. Method: **can't be overridden.** Class: **can't be inherited** (`String`, wrapper classes).
- `final` reference → the reference can't change, but the **object's contents can** (for mutable objects).

## 5. Access Modifiers ⭐
| Modifier | Same class | Same package | Subclass (other pkg) | Everywhere |
|----------|:--:|:--:|:--:|:--:|
| **private** | ✔ | ✘ | ✘ | ✘ |
| **default (package-private)** | ✔ | ✔ | ✘ | ✘ |
| **protected** | ✔ | ✔ | ✔ | ✘ |
| **public** | ✔ | ✔ | ✔ | ✔ |

- **C++:** `private` (default for **class**), `protected`, `public` (default for **struct**).
- **Python:** no true private; convention `_protected`, `__private` (name mangling).

## 6. The Four Pillars ⭐⭐⭐

### (1) Encapsulation
**Binding data and the methods that work on it into one unit (class), and restricting direct access to the data** (data hiding). Achieved by **private fields + public getters/setters.**
```java
class Account {
    private double balance;
    public void deposit(double amt) { if (amt > 0) balance += amt; }
    public double getBalance() { return balance; }
}
```
- **Benefits:** control over data (validation), security, flexibility (change internals without breaking users), maintainability.
- **Real-life:** a medicine capsule; a bank account where you can't edit the balance directly.
- **Fully encapsulated class:** all fields private + accessors.

### (2) Abstraction
**Showing only essential features and hiding implementation details.** Focus on **what** it does, not **how**.
- Achieved with **abstract classes and interfaces.**
- **Real-life:** ATM / car's steering & accelerator / TV remote.
- **Abstraction vs Encapsulation ⭐:**
  | Abstraction | Encapsulation |
  |-------------|---------------|
  | **Design level**: hides complexity | **Implementation level**: hides data |
  | What to show | How to protect |
  | Abstract classes, interfaces | Access modifiers, getters/setters |
  | Solves design problems | Solves security/maintenance problems |

### (3) Inheritance
A class (**child/subclass/derived**) **acquires properties and methods of another class (parent/superclass/base)**. **"is-a" relationship.** Promotes **reusability**. (Details in file 02.)

### (4) Polymorphism
**"Many forms": the same interface/method name behaves differently based on context.**
- **Compile-time (static) polymorphism:** **method/operator overloading.** Decided at compile time (**early binding**).
- **Run-time (dynamic) polymorphism:** **method overriding**, via a parent reference to a child object. Decided at runtime (**late binding**). (Details in file 02.)
- **Real-life:** a person is a student, a son, and an employee; `+` adds numbers or concatenates strings.

## 7. Other Core Terms
| Term | Meaning |
|------|---------|
| **Method signature** | Method name + **parameter types/order** (return type is **not** part of it) |
| **Instance vs class variable** | Per object vs shared (static) |
| **Local variable** | Inside a method; no default value |
| **Package / namespace / module** | Groups related classes and avoids name clashes |
| **Object lifecycle** | Creation → use → destruction/garbage collection |
| **Coupling** | How dependent classes are on each other. **Aim: low** |
| **Cohesion** | How focused a class is on one purpose. **Aim: high** |
| **Abstract data type (ADT)** | Data + operations, implementation hidden |
| **Message passing** | Method calls between objects |
| **Anonymous object / class** | Created without a name/reference |
| **Wrapper classes (Java)** | Object forms of primitives (`Integer`); **autoboxing / unboxing** |
| **Struct vs class (C++)** | Struct members default to **public**; class to **private** |

## 8. Relationships Between Classes ⭐
| Relation | Meaning | Lifetime | Example |
|----------|---------|----------|---------|
| **Association** | "uses-a" / "knows-a" | Independent | Teacher–Student |
| **Aggregation** | **"has-a" (weak)**: whole–part, part can exist alone | Independent | Department has Professors |
| **Composition** | **"has-a" (strong)**: part **cannot exist without** the whole | Part dies with the whole | House has Rooms |
| **Inheritance** | "is-a" | | Dog is an Animal |
| **Dependency** | Temporarily uses another class (as a parameter / local variable) | | Driver uses Car |

## 9. Common Interview Questions
1. What is OOP? Why is it better than procedural programming?
2. Class vs object? Give a real-life example.
3. Explain the four pillars with examples.
4. Encapsulation vs abstraction?
5. What is a constructor? Types? Can it be private? Can it be inherited?
6. What is `this`? What is `static`? Can you override a static method?
7. Access modifiers?
8. What is the difference between `struct` and `class` in C++?
9. Aggregation vs composition?
10. What is coupling and cohesion?
11. What are the advantages of OOP? Any disadvantages? (More memory/CPU overhead, steeper learning curve, overuse of inheritance.)
12. Is Java fully object-oriented? (No. Primitives aren't objects. Also `static`.)

## MCQ Traps
- **Class = blueprint (no memory for instance data); object = instance.**
- **Constructor has no return type and the same name as the class.**
- **The default constructor exists only if no other constructor is defined.**
- **`this()` / `super()` must be the first statement.**
- **Static methods can't access non-static members directly and have no `this`.**
- **C++ class members default to private; struct members default to public.**
- **Encapsulation = data hiding + bundling; abstraction = hiding implementation complexity.**
- **Composition is stronger than aggregation.**
- **Method signature excludes the return type.**
- **Java: default `int` field = 0, local variables = no default.**
- **Java objects live on the heap; references on the stack.**

## Practice MCQs
1. Which concept wraps data and methods together? → **Encapsulation**
2. Constructors can't be → **static / final / abstract / inherited (Java)**
3. "Has-a" where the part dies with the whole → **Composition**
4. Default access in a C++ class → **private**
5. Hiding implementation details and showing only essentials → **Abstraction**
