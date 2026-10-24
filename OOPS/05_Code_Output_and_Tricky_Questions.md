# 05 — Code Output & Tricky Questions

**Predict the output before reading the answer.** Each one tests a classic rule.

## Section A: Java

### Q1. Overriding and dynamic dispatch
```java
class A { void show() { System.out.println("A"); } }
class B extends A { void show() { System.out.println("B"); } }
public class Main { public static void main(String[] a) { A obj = new B(); obj.show(); } }
```
**Output: `B`.** Runtime polymorphism: the **object's actual type** decides.

### Q2. Fields are not polymorphic
```java
class A { int x = 10; }
class B extends A { int x = 20; }
A obj = new B();
System.out.println(obj.x);
```
**Output: `10`.** Field access uses the **reference type** (A).

### Q3. Static method "overriding"
```java
class A { static void f() { System.out.println("A"); } }
class B extends A { static void f() { System.out.println("B"); } }
A obj = new B();
obj.f();
```
**Output: `A`.** Static methods are **hidden, not overridden**, and resolved at compile time using the reference type.

### Q4. Constructor order
```java
class A { A() { System.out.println("A"); } }
class B extends A { B() { System.out.println("B"); } }
new B();
```
**Output: `A` then `B`.** Base constructor first (implicit `super()`).

### Q5. Virtual call in a constructor
```java
class A { A() { show(); } void show() { System.out.println("A"); } }
class B extends A { int x = 5; void show() { System.out.println("B " + x); } }
new B();
```
**Output: `B 0`.** The overridden method runs **before B's fields are initialized** (x is still the default 0). Never call overridable methods in constructors.

### Q6. Overloading resolution
```java
static void f(int x)    { System.out.println("int"); }
static void f(long x)   { System.out.println("long"); }
static void f(Integer x){ System.out.println("Integer"); }
f(5);
```
**Output: `int`.** Exact match > widening > boxing > varargs.
(If `f(int)` is removed: `long` wins via widening before boxing.)

### Q7. Overloading with null
```java
static void f(Object o) { System.out.println("Object"); }
static void f(String s) { System.out.println("String"); }
f(null);
```
**Output: `String`.** The **most specific** type is chosen. (With `String` and `Integer` overloads, the call is **ambiguous → compile error**.)

### Q8. String equality
```java
String a = "hi", b = "hi", c = new String("hi");
System.out.println((a == b) + " " + (a == c) + " " + a.equals(c) + " " + (a == c.intern()));
```
**Output: `true false true true`.** String pool: literals share one object; `new` creates a separate object; `intern()` returns the pooled one.

### Q9. Pass by value
```java
static void change(StringBuilder sb) { sb.append("X"); sb = new StringBuilder("New"); }
StringBuilder s = new StringBuilder("A");
change(s);
System.out.println(s);
```
**Output: `AX`.** The reference is copied. Mutating the object persists; re-pointing the local reference doesn't.

### Q10. finally with return
```java
static int f() { try { return 1; } finally { System.out.println("fin"); } }
System.out.println(f());
```
**Output: `fin` then `1`.** `finally` runs before the method actually returns.
**Trap:** if `finally` also has `return 2`, the result is **2** (it overrides).

### Q11. Exception order
```java
try { int[] a = new int[2]; a[5] = 1; }
catch (ArrayIndexOutOfBoundsException e) { System.out.println("AIOOBE"); }
catch (Exception e) { System.out.println("Exception"); }
finally { System.out.println("finally"); }
```
**Output: `AIOOBE`, `finally`.** The first matching catch runs. (Reversing the order → **compile error**.)

### Q12. Integer caching
```java
Integer a = 127, b = 127, c = 128, d = 128;
System.out.println((a == b) + " " + (c == d));
```
**Output: `true false`.** Integers **−128..127 are cached**; `==` on larger boxed values compares references.

### Q13. `char` + int
```java
System.out.println('a' + 1);
System.out.println((char)('a' + 1));
System.out.println("a" + 1 + 2);
System.out.println(1 + 2 + "a");
```
**Output:** `98`, `b`, `a12`, `3a`.

### Q14. Static counter
```java
class C { static int count = 0; C() { count++; } }
new C(); new C(); new C();
System.out.println(C.count);
```
**Output: `3`.** One shared static variable.

### Q15. Interface default/diamond
```java
interface A { default void hi() { System.out.println("A"); } }
interface B { default void hi() { System.out.println("B"); } }
class C implements A, B { public void hi() { A.super.hi(); } }
new C().hi();
```
**Output: `A`.** The class **must override** to resolve the conflict; `A.super.hi()` picks A's version.

## Section B: C++

### Q16. Virtual vs non-virtual
```cpp
class A { public: void f(){ cout<<"A"; } virtual void g(){ cout<<"A"; } };
class B : public A { public: void f(){ cout<<"B"; } void g(){ cout<<"B"; } };
A* p = new B();
p->f(); p->g();
```
**Output: `AB`.** Non-virtual `f` → static binding (A); virtual `g` → dynamic (B).

### Q17. Missing virtual destructor
```cpp
class A { public: ~A(){ cout<<"~A"; } };
class B : public A { public: ~B(){ cout<<"~B"; } };
A* p = new B(); delete p;
```
**Output: `~A`** only. Undefined behaviour in general. The fix is `virtual ~A()`, giving `~B~A`.

### Q18. Constructor / destructor order
```cpp
class A { public: A(){cout<<"A";} ~A(){cout<<"~A";} };
class B : public A { public: B(){cout<<"B";} ~B(){cout<<"~B";} };
{ B b; }
```
**Output: `AB~B~A`.**

### Q19. Object slicing
```cpp
class A { public: virtual void f(){ cout<<"A"; } };
class B : public A { public: void f(){ cout<<"B"; } };
B b; A a = b; a.f();
```
**Output: `A`.** Copying by value **slices** the object, so `a` is a real `A`, with no polymorphism.

### Q20. Default access in C++
```cpp
class A { int x; };  struct S { int x; };
A a; S s;
a.x = 1;   // ?
s.x = 1;   // ?
```
**`a.x` → compile error** (class default = private); **`s.x` OK** (struct default = public).

### Q21. Calling a virtual function from a constructor
```cpp
class A { public: A(){ f(); } virtual void f(){ cout<<"A"; } };
class B : public A { public: void f(){ cout<<"B"; } };
B b;
```
**Output: `A`.** During A's constructor, the object is only an A, so the override isn't used yet.

### Q22. Copy constructor calls
```cpp
class T { public: T(){} T(const T&){ cout<<"copy "; } };
void f(T t) {}
T a; f(a); T b = a; T c(a);
```
**Output: `copy copy copy `.** Pass by value, copy-initialization, and direct initialization. (`T b; b = a;` would call the **assignment operator**, not the copy constructor.)

### Q23. Static member
```cpp
class A { public: static int n; };
int A::n = 0;
```
A static data member must be **defined outside the class** (pre-C++17) and is shared.

## Section C: Python

### Q24. Mutable default argument
```python
def f(x, lst=[]):
    lst.append(x); return lst
print(f(1), f(2))
```
**Output: `[1, 2] [1, 2]`.** The default list is created **once** and shared.

### Q25. Method resolution order
```python
class A: 
    def hi(self): print("A")
class B(A): 
    def hi(self): print("B")
class C(A): 
    def hi(self): print("C")
class D(B, C): pass
D().hi(); print([k.__name__ for k in D.__mro__])
```
**Output: `B`, then `['D', 'B', 'C', 'A', 'object']`.** C3 MRO.

### Q26. Class vs instance variable
```python
class A:
    x = 1
a, b = A(), A()
a.x = 5
print(a.x, b.x, A.x)
```
**Output: `5 1 1`.** Assigning via an instance creates an **instance attribute** that shadows the class attribute.

## Section D: Conceptual "Trick" Questions
| Question | Answer |
|----------|--------|
| Can a constructor be `final` / `static` / `abstract` (Java)? | **No** |
| Can an abstract class have a constructor? | **Yes** |
| Can an interface have a constructor? | **No** |
| Can we override a `private` method? | **No** (it's not visible; a same-named method in the child is a new method) |
| Can we override a `static` method? | **No, it's hidden** |
| Can we overload `main`? | **Yes**, but the JVM runs `main(String[])` |
| Can a class be both `abstract` and `final`? | **No** |
| Can we instantiate an abstract class? | **No** (only via an anonymous subclass) |
| Can we have a method with the same name as the class in Java? | Yes (it's a normal method, not a constructor) |
| Is Java 100% object-oriented? | No: primitives, `static` |
| Can an interface extend a class? | **No** (an interface extends interfaces) |
| Can a class extend multiple classes (Java)? | **No** |
| What if `super()` isn't first? | **Compile error** |
| Does `finally` run after `System.exit()`? | **No** |
| Does `this` exist in a static method? | **No** |
| Can a constructor be virtual (C++)? | **No** |
| Can a constructor be private? | **Yes** (Singleton, factory) |
| Can a destructor be virtual? | **Yes (and should be in a polymorphic base)** |
| Can a pure virtual function have a body (C++)? | **Yes**, defined separately, but the class is still abstract |
| Can we create an object of a class with a private destructor on the stack? | **No** |

## Quick Self-Test (answers below)
1. `class A { A(int x){} } class B extends A { }` → compiles? 
2. `static` method calls an instance method directly → ?
3. `final int[] a = {1,2}; a[0] = 5;` → allowed?
4. `Parent p = new Child(); p.childOnly();` → ?
5. `abstract class X { abstract void f(); } new X();` → ?

**Answers:** 1. **Compile error**: B's implicit `super()` has no matching A() constructor. 2. **Compile error**: a non-static method can't be called without an object. 3. **Allowed**: `final` fixes the reference, not the contents. 4. **Compile error**: the reference type `Parent` has no `childOnly()` (needs a downcast). 5. **Compile error**: abstract classes can't be instantiated.
