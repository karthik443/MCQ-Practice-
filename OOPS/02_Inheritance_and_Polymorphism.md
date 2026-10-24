# 02 — Inheritance & Polymorphism

## 1. Inheritance ⭐⭐
A class acquires the **fields and methods** of another class. **"is-a"** relationship. Benefits: **code reuse, extensibility, polymorphism.**
```java
class Animal { void eat() { System.out.println("eat"); } }
class Dog extends Animal { void bark() { System.out.println("bark"); } }
```
```cpp
class Dog : public Animal { public: void bark() {} };
```
**Terms:** superclass/base/parent; subclass/derived/child. Private members are **not accessible** in the subclass (they exist in the object but aren't visible). Constructors are **not inherited** (but the parent constructor runs first).

### Types of inheritance ⭐
| Type | Structure | Java | C++ | Python |
|------|-----------|:--:|:--:|:--:|
| **Single** | A → B | ✔ | ✔ | ✔ |
| **Multilevel** | A → B → C | ✔ | ✔ | ✔ |
| **Hierarchical** | A → B, A → C | ✔ | ✔ | ✔ |
| **Multiple** | A, B → C | **✘ via classes** (✔ via **interfaces**) | ✔ | ✔ |
| **Hybrid** | Combination | via interfaces | ✔ | ✔ |

### Diamond problem ⭐⭐
With multiple inheritance, **B and C both inherit A; D inherits B and C** → D gets **two copies of A** (ambiguity: which `A::foo()`?).
- **Java:** avoids it by **not allowing multiple class inheritance.** Interfaces with **default methods** that conflict must be **overridden explicitly** (`B.super.foo()`).
- **C++:** solved with **virtual inheritance** (`class B : virtual public A`), so one shared A subobject. Or resolve ambiguity with the scope operator `B::foo()`.
- **Python:** **MRO (C3 linearization)** defines the lookup order; `ClassName.__mro__`.

### `super` (Java) / `Base::` (C++)
- `super.method()` calls the parent version; `super(...)` calls the parent constructor (first statement). If you don't write it, the **no-arg** `super()` is inserted (error if the parent has no no-arg constructor).

### Inheritance in C++: access modes
| Base member | public inheritance | protected inheritance | private inheritance |
|-------------|--------------------|-----------------------|---------------------|
| public | public | protected | private |
| protected | protected | protected | private |
| private | inaccessible | inaccessible | inaccessible |

### Constructor & destructor order ⭐
- **Constructors:** Base → Derived (top-down). **Destructors:** Derived → Base (reverse).
- With multiple bases, constructors follow the **declaration order** in the class list.

### Composition over inheritance
Prefer **has-a** (flexible, loose coupling) when the relationship isn't a true "is-a". Inheritance creates **tight coupling** (fragile base class problem).

## 2. Polymorphism ⭐⭐⭐
### Compile-time (static) polymorphism
#### Method overloading
**Same method name, different parameter list** (number, type, or order) **in the same class.** The return type alone **can't** distinguish overloads.
```java
int add(int a, int b)        { return a + b; }
double add(double a, double b){ return a + b; }
int add(int a, int b, int c) { return a + b + c; }
```
- Resolved at **compile time** (early binding). Also possible across inheritance.
- **Ambiguity:** `add(5, 10L)` picks the closest match (widening); ambiguous calls cause compile errors.
- **Operator overloading:** C++ yes (`operator+`), **Python** yes (`__add__`), **Java no** (except built-in `+` for strings).

### Run-time (dynamic) polymorphism
#### Method overriding
A **subclass provides its own implementation of a method already defined in the parent**, with the **same signature and compatible return type.**
```java
class Shape  { void draw() { System.out.println("Shape"); } }
class Circle extends Shape { @Override void draw() { System.out.println("Circle"); } }
Shape s = new Circle();   // upcasting
s.draw();                 // prints "Circle"  (decided at runtime)
```
- **Rules (Java):**
  - Same **name, parameters**; return type same or **covariant** (subtype).
  - Access can't be **more restrictive** (widening allowed: protected → public).
  - **Can't override:** `static`, `final`, `private` methods, or constructors.
  - May throw the **same or narrower** checked exceptions (not broader).
  - `@Override` makes the compiler check.
- **Dynamic method dispatch:** the JVM picks the method based on the **actual object type**, not the reference type.
- **Fields are NOT polymorphic:** field access uses the **reference type.** (`Parent p = new Child(); p.x` gives Parent's x.)
- **Static methods** called through a parent reference run the **parent's** version (method hiding).

### C++: virtual functions ⭐⭐
```cpp
class Shape { public: virtual void draw() { cout << "Shape"; } virtual ~Shape() {} };
class Circle : public Shape { public: void draw() override { cout << "Circle"; } };
Shape* s = new Circle();
s->draw();   // "Circle" since draw() is virtual. Without virtual → "Shape"
```
- **In C++ you must declare the base method `virtual`** for runtime polymorphism (in Java all non-static, non-final, non-private methods are virtual by default).
- **vtable / vptr:** each class with virtual functions has a **vtable** (table of function pointers); each object holds a hidden **vptr** to it. The call is resolved through the vtable at runtime.
- **Pure virtual function:** `virtual void f() = 0;` → makes the class **abstract.**
- **Virtual destructor:** **needed in a base class** if you `delete` a derived object via a base pointer. Otherwise the derived destructor isn't called → leak/undefined behaviour.
- **Constructors can't be virtual.** Calling a virtual function **inside a constructor/destructor** calls the **current class's** version (no derived override yet).
- **Object slicing:** assigning a derived object to a base **object** (by value) slices off derived parts and loses polymorphism. Use pointers/references.
- `override` and `final` specifiers (C++11).

### Overloading vs Overriding ⭐⭐⭐
| | **Overloading** | **Overriding** |
|--|-----------------|----------------|
| Polymorphism type | **Compile-time** | **Run-time** |
| Where | **Same class** (or inherited) | **Parent–child** classes |
| Signature | **Must differ** in parameters | **Must be the same** |
| Return type | Can differ (but not alone) | Same / covariant |
| Inheritance required | No | **Yes** |
| Access modifier | Any | Can't be stricter |
| `static` / `private` / `final` | Can be overloaded (static, private) | **Can't be overridden** |
| Binding | Early | Late |

### Upcasting & Downcasting
- **Upcasting:** child → parent reference (implicit, safe): `Animal a = new Dog();`. Only parent-declared members are accessible.
- **Downcasting:** parent → child reference (explicit; may fail): `Dog d = (Dog) a;` → `ClassCastException` if the object isn't a Dog. Check first with `instanceof` (Java) / `dynamic_cast` (C++).

## 3. Abstraction Mechanisms ⭐⭐⭐
### Abstract class
- Declared `abstract` (Java) / has at least one **pure virtual function** (C++). **Can't be instantiated.** May contain **abstract and concrete methods, fields, constructors.** A subclass must implement all abstract methods (else it's abstract too).
- Use when classes share **common state/behaviour** plus some must-implement parts. **"is-a" with partial implementation.**

### Interface
- A **contract** of methods a class promises to implement. All methods are **public abstract** by default (Java); fields are **`public static final` constants.** Since **Java 8: `default` and `static` methods; Java 9: `private` methods.**
- A class can **implement multiple interfaces** → Java's answer to multiple inheritance. **C++ has no interface keyword** (use a class with only pure virtual functions).

| | **Abstract class** | **Interface** |
|--|--------------------|---------------|
| Instantiable | No | No |
| Methods | Abstract + concrete | Abstract (+ default/static since Java 8) |
| Variables | Any (instance, static, final) | Only `public static final` constants |
| Constructors | **Yes** | **No** |
| Multiple inheritance | **No** (extend one) | **Yes** (implement many) |
| Access modifiers on members | Any | Public |
| Keyword | `extends` | `implements` (class), `extends` (interface→interface) |
| Use | Shared base with common code ("is-a") | Capability / contract ("can-do") |

- **Can an abstract class have a constructor?** Yes (invoked by the subclass constructor). **Can it be `final`?** No (contradiction). **Can abstract methods be `private`/`static`/`final`?** No.
- **Marker interface:** an empty interface (`Serializable`, `Cloneable`). **Functional interface:** exactly one abstract method (lambda target; `Runnable`, `Comparator`).

## 4. Other Related Concepts
- **Method hiding:** static method redefined in a child.
- **Covariant return types:** overridden method returns a subtype.
- **Dynamic binding vs static binding:** runtime vs compile-time method resolution. **Static binding applies to** `private`, `static`, `final` methods and overloads.
- **Polymorphism with arrays/collections:** `List<Shape>` holding Circle/Rectangle; calling `draw()` works for each.
- **Duck typing (Python):** "if it quacks like a duck": no common parent required, only matching method names.
- **Python overriding:** any method redefined; no overloading by signature (last definition wins; use default args/`*args`).

## 5. Common Interview Questions
1. What is inheritance? Types? Why not multiple inheritance in Java?
2. What is the diamond problem and how do Java/C++/Python solve it?
3. Overloading vs overriding?
4. What is runtime polymorphism? Dynamic method dispatch?
5. Can we override static / private / final methods? Constructors?
6. Abstract class vs interface? When to use which?
7. Can an interface have a constructor? Variables? Default methods?
8. What is a virtual function? Pure virtual function? vtable?
9. Why do you need a virtual destructor?
10. What is object slicing?
11. `super` keyword uses?
12. Upcasting vs downcasting? `instanceof`?
13. Composition vs inheritance?
14. Are fields overridden? (No, hidden.)
15. Can we overload `main`? (Yes, but the JVM calls only `main(String[])`.)

## MCQ Traps
- **Overloading = compile-time; overriding = runtime.**
- **Return type alone can't overload.**
- **Static, private, final methods and constructors can't be overridden.**
- **Overriding can't reduce visibility or throw broader checked exceptions.**
- **Java: no multiple inheritance with classes; interfaces are OK.**
- **C++: base method must be `virtual` for runtime polymorphism; base destructor should be virtual.**
- **Interface fields are implicitly `public static final`.**
- **Abstract classes can have constructors; interfaces can't.**
- **Fields aren't polymorphic: the reference type decides the field.**
- **Constructors: Base → Derived; Destructors: Derived → Base.**
- **Pure virtual (`= 0`) → abstract class.**
- **Downcasting a wrong type → `ClassCastException`.**

## Practice MCQs
1. Method binding that happens at runtime → **Overriding / dynamic dispatch**
2. A class with a pure virtual function is → **Abstract**
3. Can `final` methods be overridden? → **No**
4. Which inheritance is not supported with classes in Java? → **Multiple**
5. `Parent p = new Child();` calling a non-virtual (C++) method → **Parent's version is called**
