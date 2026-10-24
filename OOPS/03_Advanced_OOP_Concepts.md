# 03 — Advanced OOP Concepts

## 1. Copy Constructor, Shallow vs Deep Copy ⭐⭐
- **Copy constructor (C++):** `Student(const Student& other)`. Called when an object is **initialized from another**, **passed by value**, or **returned by value**. **The argument must be passed by reference** (passing by value would recurse infinitely).
- If you don't write one, the compiler gives a **default memberwise (shallow) copy.**

| **Shallow copy** | **Deep copy** |
|------------------|---------------|
| Copies **references/pointers** only | Copies the **pointed-to data** as well |
| Both objects share the same underlying memory | Independent copies |
| A change in one affects the other | No side effects |
| Can cause **double free / dangling pointers** in C++ | Safe |
| Default behaviour | Must be implemented manually |

```cpp
class Buf { int* p; public:
  Buf(int v){ p = new int(v); }
  Buf(const Buf& o){ p = new int(*o.p); }   // deep copy
  ~Buf(){ delete p; } };
```
- **Java:** `obj2 = obj1` copies the **reference** (both point to the same object). `clone()` (needs `Cloneable`) is shallow by default. Deep copy: manual copy constructor, serialization, or library.
- **Python:** `copy.copy()` (shallow), `copy.deepcopy()`.
- **Rule of Three (C++):** if you define a **destructor, copy constructor, or copy assignment operator**, you likely need all three. **Rule of Five** adds the **move constructor** and **move assignment**. **Rule of Zero:** prefer smart pointers/containers and define none.
- **Assignment operator vs copy constructor:** copy constructor creates a **new** object; assignment operator works on an **existing** object (`a = b`).

## 2. Destructors & Memory Management ⭐
- **C++ destructor** `~Class()`: runs when an object goes out of scope or is `delete`d. **No parameters, no return type, one per class, can be virtual.** Frees resources (heap memory, files, locks).
- **RAII (Resource Acquisition Is Initialization):** tie resource lifetime to object lifetime (constructor acquires, destructor releases). Smart pointers: **`unique_ptr`** (sole owner), **`shared_ptr`** (reference-counted), `weak_ptr` (breaks cycles).
- `new` / `delete` (single), `new[]` / `delete[]` (arrays). **`malloc`/`free` don't call constructors/destructors.** Memory leak = `new` without `delete`. **Dangling pointer** = pointer to freed memory. **Double delete** = undefined behaviour.
- **Stack vs heap:** stack = automatic, fast, limited; heap = manual (C++) / GC (Java), larger.
- **Java Garbage Collector:** automatically frees **unreachable** objects. `System.gc()` is only a hint. `finalize()` is **deprecated** (use try-with-resources / `AutoCloseable`). **Memory leaks still possible** (lingering references).
- **Python:** reference counting + cycle collector; `__del__`.

## 3. `final`, `static`, `const`, `abstract` — recap
| Keyword | Variable | Method | Class |
|---------|----------|--------|-------|
| **final (Java)** | Constant | Can't override | Can't extend |
| **static** | Shared per class | Belongs to the class | Nested static class |
| **abstract** | — | No body, must override | Can't instantiate |
| **const (C++)** | Read-only | `const` method = doesn't modify `this` | — |

- **`const` method (C++):** `int get() const;` can be called on const objects and can't modify members (unless `mutable`).
- **`final` vs `finally` vs `finalize` (Java):** modifier / block always executed after try-catch / GC hook (deprecated).
- **Immutable class (Java `String`):** fields `private final`, no setters, class `final`, defensive copies. Benefits: thread-safe, cacheable (**String pool**), safe as map keys.
- **`String` vs `StringBuilder` vs `StringBuffer`:** immutable / mutable, not thread-safe (fast) / mutable, **thread-safe** (synchronized, slower).
- **`==` vs `.equals()` (Java):** `==` compares **references** (for objects); `equals()` compares **content** (if overridden). Override `hashCode()` whenever you override `equals()` (**contract:** equal objects → equal hashCodes). `String s1 = "hi"; String s2 = new String("hi"); s1 == s2 → false; s1.equals(s2) → true`.

## 4. Object Class & Common Methods (Java)
Every class extends **`Object`**: `toString()`, `equals()`, `hashCode()`, `clone()`, `getClass()`, `finalize()`, `wait()/notify()/notifyAll()`.

## 5. Exception Handling ⭐
Mechanism to handle runtime errors without crashing.
```java
try { int x = 10 / 0; }
catch (ArithmeticException e) { System.out.println("error"); }
finally { System.out.println("always runs"); }
```
- **Hierarchy (Java):** `Throwable` → **`Error`** (unrecoverable: `OutOfMemoryError`, `StackOverflowError`) and **`Exception`** → **Checked** (compile-time enforced: `IOException`, `SQLException`) and **Unchecked / RuntimeException** (`NullPointerException`, `ArrayIndexOutOfBounds`, `ArithmeticException`, `ClassCastException`).
- **`throw`** (throw an exception object) vs **`throws`** (declare in a method signature).
- **`finally`** runs whether or not an exception occurs (even with `return`), **except `System.exit()`**/JVM crash.
- **Multiple catch:** more specific exceptions **before** general ones; else compile error.
- **try-with-resources** auto-closes `AutoCloseable` resources. **Custom exceptions:** extend `Exception` (checked) or `RuntimeException`.
- **C++:** `try / catch / throw`; `catch(...)`; **never throw from a destructor**; exceptions are any type; no `finally` (use RAII).
- **Python:** `try / except / else / finally`; `raise`.
- Overriding method can't throw **broader checked** exceptions.

## 6. Generics & Templates
- **Generics (Java):** type-safe collections; **type erasure** at runtime; no primitives (`List<int>` ✘ → `List<Integer>`). Bounded types `<T extends Comparable<T>>`, wildcards `<?>`.
- **C++ templates:** compile-time code generation (`template<typename T>`). Function and class templates. **Template specialization.** Zero runtime overhead; code bloat possible.
- **Benefits:** reusability, type safety (no casting), compile-time error detection.

## 7. Inner / Nested Classes & Misc (Java)
- **Static nested**, **inner (non-static)** (needs outer instance), **local**, **anonymous** classes. Lambdas (Java 8) for functional interfaces.
- **Enums:** fixed constants (can have fields/methods). **Packages** and imports. **Varargs** `int... nums`. **Reflection** (inspect classes at runtime).
- **Singleton via enum** is the safest.
- **Pass by value:** Java is **always pass-by-value** (for objects, the **reference value** is copied). Reassigning a parameter reference doesn't affect the caller's; mutating the object does.
- **C++:** pass by value / pointer / **reference**. **`friend`** functions/classes can access private members (breaks encapsulation slightly; **not inherited, not mutual**).
- **Function pointers, lambdas, `std::function`.**

## 8. Java vs C++ vs Python ⭐
| Feature | **Java** | **C++** | **Python** |
|---------|----------|---------|-----------|
| Compilation | Bytecode → JVM (platform independent) | Native code (platform dependent) | Interpreted (bytecode + PVM) |
| Memory | **Garbage collector** | **Manual** (new/delete) / RAII | GC (refcount) |
| Pointers | No explicit pointers (references) | **Yes** | No |
| Multiple inheritance | Interfaces only | **Yes** | **Yes** |
| Operator overloading | No | **Yes** | Yes (dunder methods) |
| Destructor | No (finalize deprecated) | **Yes** | `__del__` |
| Typing | Static, strong | Static | **Dynamic** |
| Everything an object? | Mostly (primitives exist) | No (procedural + OOP) | **Yes** |
| Virtual by default | **Yes** | **No** (`virtual` keyword) | Yes |
| Access control | public/protected/default/private | public/protected/private | Convention only |
| `main` | `public static void main(String[] a)` | `int main()` | `if __name__ == "__main__"` |
| Templates/Generics | Generics (erasure) | Templates (compile-time) | Duck typing |

- **Platform independence (Java):** "write once, run anywhere": **JVM** executes bytecode. **JDK** (dev kit) ⊃ **JRE** (runtime) ⊃ **JVM**. **JIT compiler** optimizes at runtime.

## 9. Concurrency Basics (OOP interviews)
- **Thread creation (Java):** `extends Thread` or `implements Runnable` (preferred: allows extending another class). `start()` creates a new thread; `run()` runs in the **current** thread.
- **`synchronized`**, `volatile`, `wait/notify`, `ExecutorService`. **Thread-safe Singleton** needs care (double-checked locking with `volatile`).
- **Deadlock** (see OS notes).

## 10. Common Interview Questions
1. Shallow vs deep copy? Copy constructor? Why pass by reference?
2. What is the rule of three / five?
3. What is a destructor? Virtual destructor? RAII?
4. How does garbage collection work? Can you force it?
5. `final` vs `finally` vs `finalize`?
6. `==` vs `equals()`? `equals()` and `hashCode()` contract?
7. String vs StringBuilder vs StringBuffer? Why is String immutable?
8. Checked vs unchecked exceptions? `throw` vs `throws`?
9. Does `finally` always run?
10. Generics vs templates? Type erasure?
11. Java: pass by value or reference?
12. Why is Java platform independent? JDK vs JRE vs JVM?
13. What is a friend function? Is it a violation of encapsulation?
14. `Runnable` vs `Thread`?
15. Java vs C++ vs Python for OOP?
16. What is an immutable class? How do you create one?

## MCQ Traps
- **Copy constructor parameter must be a reference.**
- **Default copy = shallow**, so shared pointers → double free. Fix with a deep copy.
- **Java is always pass-by-value.**
- **`finally` runs even when `return` is in the try (except `System.exit`).**
- **Catch specific exceptions before general ones.**
- **`Error` is not meant to be caught; `Exception` includes checked and unchecked.**
- **`equals` override ⇒ override `hashCode`.**
- **`run()` doesn't start a new thread; `start()` does.**
- **`StringBuffer` is thread-safe; `StringBuilder` is faster.**
- **C++ `malloc` doesn't call constructors.**
- **Friend functions aren't inherited or mutual.**
- **`delete` on arrays needs `delete[]`.**

## Practice MCQs
1. A copy constructor in C++ takes → **A const reference to the same class**
2. Which of these is unchecked? **(a) IOException (b) SQLException (c) NullPointerException** → **c**
3. `new String("a") == "a"` → **false**
4. In Java, to allow a class to inherit from two sources you use → **Interfaces**
5. Which collects unreachable objects automatically? → **Garbage collector**
