# 04 — Structures, Unions, Enums, Preprocessor & Misc

## 1. Structures ⭐⭐
```c
struct Student { int id; char name[20]; float cgpa; };
struct Student s1 = {1, "Asha", 8.5};
struct Student *p = &s1;
printf("%d %d", s1.id, p->id);       // . for objects, -> for pointers; p->id ≡ (*p).id
typedef struct { int x, y; } Point;   // alias; no 'struct' keyword needed
```
- Members are laid out **in declaration order**; each struct is a **contiguous block**.
- **Structs can be assigned (`s2 = s1`)**: a **shallow memberwise copy** (arrays inside are copied, **pointers are copied as addresses**). **Can't compare with `==`.** Can be passed and returned **by value** (copying) or by pointer (efficient).
- **Nested structs**, **arrays of structs**, **pointers to structs**, **self-referential** (`struct Node *next`).
- **Designated init (C99):** `struct Point p = {.y = 5, .x = 1};`
- **Flexible array member:** `struct { int n; int data[]; }` (allocate with extra space).
- **Empty struct** is non-standard; GCC gives size 0.

### Struct padding & alignment ⭐⭐⭐
The compiler inserts **padding** so each member sits at an address that's a **multiple of its size (alignment)**, and the total size is a **multiple of the largest member's alignment**.
```c
struct S1 { char c; int i; char d; };     // c(1)+pad(3) + i(4) + d(1)+pad(3) = 12
struct S2 { int i; char c; char d; };     // i(4) + c(1) + d(1) + pad(2)       = 8
struct S3 { char c; double d; char e; };  // 1+7pad + 8 + 1+7pad                = 24
struct S4 { char a; char b; char c; };    // 3 (alignment 1, no padding)
```
- **Reordering members (largest first) reduces padding.** `offsetof(type, member)` from `<stddef.h>`.
- **`#pragma pack(1)`** / `__attribute__((packed))` removes padding (slower/unaligned access, non-portable).
- **`sizeof(struct)` ≥ sum of member sizes.**
- **Why padding?** Aligned access is faster (and required on some CPUs).
- **Can't compare structs with `memcmp`** reliably (padding bytes have indeterminate values).

## 2. Unions ⭐⭐
All members **share the same memory**; size = **largest member** (rounded for alignment). Only **one member is valid at a time**.
```c
union U { int i; char c[4]; float f; };   // sizeof = 4
union U u; u.i = 0x41424344;
// u.c[0] = 'D', u.c[3] = 'A' on little-endian
```
- **Writing one member and reading another** reinterprets the bytes (type punning; legal in C for unions, but the value may be implementation-defined).
- **Uses:** save memory, hardware registers, **tagged unions** (a `type` tag + union), **checking endianness**, protocol parsing.
| Struct | Union |
|--------|-------|
| Each member has its own memory | Members **share** memory |
| Size = sum (+ padding) | Size = **largest** member |
| All members usable at once | **One at a time** |

### Endianness ⭐
- **Little-endian:** **least significant byte at the lowest address** (x86, most ARM). **Big-endian:** MSB first (network byte order).
- `0x12345678` little-endian in memory: `78 56 34 12`.
```c
int one = 1; 
if (*(char *)&one) puts("little"); else puts("big");
```
- **Network byte order** = big-endian (`htons`, `htonl`, `ntohs`, `ntohl`).

## 3. Enums
```c
enum Color { RED, GREEN, BLUE };          // 0, 1, 2
enum E { A, B = 5, C, D = 2, F };         // 0, 5, 6, 2, 3   (continues from the previous + 1)
enum Color c = GREEN;
```
- Enums are **integer constants** (type `int`) and can be used in `switch`. No type safety in C (you can assign any int). Names share the **enclosing scope** (no clashes allowed). `sizeof(enum)` = 4 typically.
- **Better than `#define`** for related constants (debuggers show names).

## 4. Bit-fields
```c
struct Flags { unsigned a : 3; unsigned b : 5; };   // 8 bits used, sizeof = 4 (unit of unsigned)
```
- Specify **bit widths**. Values wrap (`a` holds 0–7). **Can't take the address** of a bit-field. Layout/order is **implementation-defined**. Used for flags/hardware registers.

## 5. typedef
`typedef unsigned long ulong;` `typedef struct Node Node;` `typedef int (*BinOp)(int,int);` **Creates an alias (no new type);** unlike `#define`, it is handled by the compiler and respects scope. `#define PINT int*` then `PINT a, b;` → `int *a, b;` (b is an `int`), whereas `typedef int* PINT; PINT a, b;` makes both pointers.

## 6. Preprocessor ⭐⭐
Runs **before** compilation; performs **textual substitution** (no type checking, no evaluation).

### `#define` macros
```c
#define PI 3.14159
#define SQ(x)  x*x           // BAD
#define SQ2(x) ((x)*(x))     // better
#define MAX(a,b) ((a)>(b)?(a):(b))
```
- **Missing parentheses trap:** `SQ(2+3)` → `2+3*2+3` = **11** (not 25). `10/SQ(2)` → `10/2*2` = **10** (not 2.5 → 2).
- **Side effects trap:** `SQ2(i++)` expands to `((i++)*(i++))` → **UB**; `MAX(i++, j)` may evaluate `i++` twice.
- **No semicolon** after `#define` (it becomes part of the replacement). A macro's scope is from its definition to the end of the file (or `#undef`).
- **Multi-line macros:** `\` continuation; wrap in **`do { ... } while (0)`** so they behave like a single statement.
- **Stringize `#`:** `#define STR(x) #x` → `STR(abc)` = `"abc"`. **Token pasting `##`:** `#define CAT(a,b) a##b` → `CAT(x,1)` = `x1`.
- **Predefined:** `__FILE__`, `__LINE__`, `__DATE__`, `__TIME__`, `__func__`, `__STDC__`.
- **Macro vs function:** macros are inlined (no call overhead), type-generic, but **no type checking, double evaluation risk, harder to debug, code bloat**. `inline` functions are safer.

### Other directives
- **`#include <file>`** (system headers) vs **`#include "file"`** (local first, then system).
- **Include guards:** `#ifndef X_H / #define X_H / ... / #endif` (or `#pragma once`) prevent double inclusion.
- **Conditional compilation:** `#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, `#endif` (platform/debug code). `#undef`. `#error`, `#pragma`.
- **Header file** contains declarations, macros, types, **not** function definitions (to avoid multiple-definition link errors).

## 7. Bit Manipulation Recap ⭐
```c
n & 1                    // odd/even
n & (n-1)                // clears the lowest set bit
n && !(n & (n-1))        // power of two
n & -n                   // isolate the lowest set bit
(n >> k) & 1             // k-th bit
n |= 1<<k; n &= ~(1<<k); n ^= 1<<k;   // set / clear / toggle
a ^= b; b ^= a; a ^= b;  // swap without temp (fails if a and b are the same variable)
```
- Count bits: `while (n) { n &= n-1; c++; }`. Reverse bits, find the single non-repeating number with XOR (`x ^ x = 0`, `x ^ 0 = x`).
- **Multiply by 2ⁿ:** `x << n`. **Divide by 2ⁿ:** `x >> n` (for non-negative).

## 8. Recursion Recap ⭐
```c
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }   // 120 for 5
int fib(int n)  { return n < 2 ? n : fib(n-1) + fib(n-2); } // 55 for 10 (exponential time)
void pr(int n)  { if (!n) return; pr(n-1); printf("%d ", n); }  // prints 1 2 3 4 for pr(4)
```
- **Needs a base case; each call adds a stack frame** → too deep = **stack overflow**. **Tail recursion** can be optimized. **Print before vs after** the recursive call changes order (pre/post-order). Memoization or iteration avoids repeated work.
- **Recursion vs iteration:** recursion is concise but uses stack memory.

## 9. File Handling (brief)
```c
FILE *fp = fopen("a.txt", "r");    // modes: r, w, a, r+, w+, a+ (add b for binary)
if (fp == NULL) { perror("open"); return 1; }
fprintf(fp, ...); fscanf(fp, ...); fgets(buf, n, fp); fgetc(fp); fputs(...);
fread(buf, size, count, fp); fwrite(...); fseek(fp, 0, SEEK_END); ftell(fp); rewind(fp);
while (fgets(buf, sizeof buf, fp)) { ... }     // read line by line
fclose(fp);
```
- **`w` truncates** an existing file; **`a` appends**; **`r`** fails if the file is missing (returns `NULL`). **`feof`** is true **after** a read hits the end (so `while(!feof(fp))` often reads the last item twice; check the read function's return instead).
- **Text vs binary mode.** `stdin`, `stdout`, `stderr` are predefined `FILE *`s. **`fflush(stdout)`** forces buffered output. `stdout` is line-buffered (terminal) or fully buffered (file/pipe); `stderr` is unbuffered.
- **`exit()` flushes buffers; `_exit()`/`abort()` may not.**

## 10. Miscellaneous Tricky Facts ⭐
- **`main` can't be called recursively in C++ but can in C** (legal but odd).
- **`#include` order and header guards.**
- **`int a[]` param ≡ `int *a`.**
- **Implicit function declaration**: calling an undeclared function assumes `int f()` (C89); an error/warning in modern C.
- **`const` ≠ compile-time constant in C**: `const int n = 5; int a[n];` is a VLA, not a fixed array, at file scope it's an error.
- **Character set:** ASCII: `'0'` = 48, `'A'` = 65, `'a'` = 97, `'\n'` = 10, `'\0'` = 0.
- **Keywords:** 32 in C89 (`auto, break, case, char, const, continue, default, do, double, else, enum, extern, float, for, goto, if, int, long, register, return, short, signed, sizeof, static, struct, switch, typedef, union, unsigned, void, volatile, while`). Later: `inline`, `restrict`, `_Bool`, etc. **`main`, `printf` are not keywords.**
- **Identifiers:** letters, digits, `_`; can't start with a digit; case-sensitive; can't be a keyword.
- **C vs C++ differences:** `'A'` is `int` in C / `char` in C++; `void *` converts implicitly in C only; no function overloading/classes/references/`new` in C; C needs `struct` keyword unless `typedef`'d; `const` global has internal linkage in C++ only.
- **`volatile` + `const`** can coexist (read-only hardware register).
- **`long` = 8 bytes on Linux 64, 4 on Windows 64.** Use `<stdint.h>` types (`int32_t`, `uint64_t`) for fixed sizes.
- **`size_t`** is unsigned, so `for (size_t i = n-1; i >= 0; i--)` is an **infinite loop** (`i >= 0` always true).

## 11. Common Interview Questions
1. Struct vs union? Size of each? Give a use for a union.
2. What is structure padding? Why? How do you reduce or disable it?
3. What is endianness? How do you check it?
4. Macro vs function vs `inline`? Problems with macros?
5. `#include <>` vs `""`? What are include guards?
6. `typedef` vs `#define`?
7. What are enums? Default values?
8. What are bit-fields?
9. `++` precedence questions? (See file 02.)
10. Write code to count set bits / check power of 2 / swap without a temp.
11. Recursion: factorial, Fibonacci, reverse a string, sum of digits; how recursion uses the stack?
12. File modes; `fgets` vs `gets`; why not `while(!feof())`?
13. `struct` copy: shallow or deep? What if it contains pointers?
14. Difference between C and C++?
15. What is `volatile`? `restrict`? `inline`?

## MCQ Traps
- **Struct size includes padding; union size = largest member.**
- **Reordering members can change `sizeof`.**
- **Macros don't add parentheses for you: `SQ(2+3)` = 11.**
- **`SQ(i++)` is UB.**
- **Enum values continue from the previous value + 1.**
- **Structs are copied by `=` (shallow); can't compare with `==`.**
- **`#define PINT int*; PINT a, b;` → `b` is an `int`.**
- **Bit-field address can't be taken.**
- **`'A'` is `int` in C.**
- **`for (size_t i = n-1; i >= 0; i--)` never ends.**

## Practice MCQs
1. `struct { char c; int i; }` size → **8**
2. `union { int i; char c; double d; }` size → **8**
3. `#define SQ(x) x*x` → `SQ(1+2)` → **5** (1+2*1+2)
4. `enum {X=3, Y, Z};` Z = → **5**
5. Byte order with LSB at the lowest address → **Little-endian**
