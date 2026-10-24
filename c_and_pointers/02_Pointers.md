# 02 — Pointers

## 1. Pointer Basics ⭐⭐⭐
A **pointer** is a variable that stores the **memory address** of another variable.
```c
int x = 10;
int *p = &x;      // p holds the address of x
printf("%d", *p); // dereference: 10
*p = 20;          // x is now 20
```
- **`&`** = address-of. **`*`** = dereference (in a declaration, `*` means "pointer to").
- **All pointers are the same size** (8 B on 64-bit), regardless of the pointed-to type. The type tells the compiler **how many bytes to read** and **how far to step**.
- **Print an address with `%p`** (cast to `void *`).
- **Declaration trap:** `int *p, q;` → `p` is a pointer, **`q` is a plain `int`**. Use `int *p, *q;`.
- **Initialize pointers.** A pointer with no valid address is a **wild/uninitialized pointer**; dereferencing it is UB. Set unused pointers to `NULL`.

### Special pointers ⭐
| Kind | Meaning | Danger |
|------|---------|--------|
| **NULL pointer** | Points to nothing (`(void*)0`). `if (p)` tests for non-NULL | **Dereferencing = crash (segfault)** |
| **Wild / uninitialized** | Holds garbage | UB |
| **Dangling** | Points to memory that's been **freed** or whose scope ended | UB (use-after-free) |
| **Void pointer** `void *` | Generic, no type | Must be cast before deref; no arithmetic (standard C) |
| **Function pointer** | Points to code | |
| **Double / multi-level** | Pointer to a pointer | |
- **Dangling sources:** returning the address of a local variable, `free(p)` then using `p`, a reallocated block. **Fix:** set `p = NULL` after `free`.
- **NULL vs 0 vs '\0' vs "":** `NULL` = null pointer; `'\0'` = null character (value 0); `""` = empty string (1 byte: `\0`); `0` = integer.
- **Memory leak:** allocated memory never freed (lost pointer).

## 2. Pointer Arithmetic ⭐⭐⭐
Adding `n` to a pointer moves it by **n × sizeof(pointed type)** bytes.
```c
int a[] = {10, 20, 30, 40, 50};
int *p = a;
p + 1      // address of a[1] (+4 bytes)
*(p + 2)   // 30
p++        // now points to a[1]
```
- **Allowed:** `p + n`, `p - n`, `p++`, `p--`, `p1 - p2` (**same array**; result in **elements**, type `ptrdiff_t`), comparisons (`<`, `==`) within the same array.
- **Not allowed:** adding two pointers, multiplying/dividing pointers.
- **Pointer subtraction:** `&a[4] - &a[1]` = **3** (elements, not bytes). `(char*)(a+3) - (char*)a` = **12** bytes.
- `p[i]` ≡ `*(p + i)`. Consequently `a[i] ≡ i[a]`. (`2[a]` is legal and equals `a[2]`.)
- **`char*`** steps 1 byte; **`int*`** 4; **`double*`** 8; **`struct*`** by struct size.
- **`void *` arithmetic** is illegal in standard C (GCC allows it as a byte-step extension). Cast to `char *` for byte arithmetic.
- Going **outside** an array (except one past the end) is UB.

### `*p++`, `(*p)++`, `*++p`, `++*p` ⭐⭐⭐ (very common)
Start with `int a[]={1,2,3,4,5}; int *p=a;` each time.
| Expression | Meaning | Result | After |
|------------|---------|--------|-------|
| `*p++` | value of `*p`, **then move pointer** (`*(p++)`) | `1` | `p` → `a[1]` |
| `(*p)++` | return value, **then increment the pointed value** | `1` | `a[0] == 2`, `p` unchanged |
| `*++p` | **move pointer first**, then read | `2` | `p` → `a[1]` |
| `++*p` | **increment the pointed value**, then read | `2` | `a[0] == 2` |
| `*(p+1)` | value of the next element, no move | `2` | unchanged |
| `*p + 1` | value plus 1 | `2` | unchanged |
**Rule:** postfix `++` has higher precedence than `*`, but returns the **old** value.

## 3. Pointers and Arrays ⭐⭐⭐
- An **array name decays to a pointer to its first element** in most expressions: `a` ≡ `&a[0]`.
- **Exceptions (no decay):** `sizeof(a)`, `&a`, and string-literal initializers of char arrays.
```c
int a[5];
sizeof(a)  = 20      // whole array
sizeof(&a) = 8       // pointer to int[5]
a + 1                // next int (+4 bytes)
&a + 1               // next whole array (+20 bytes)
*(&a + 1) - a        // 5 (classic way to get the length)
```
- **`a` vs `&a`:** same address, **different types** (`int *` vs `int (*)[5]`).
- **An array name is NOT a modifiable pointer:** `a++` and `a = p` are errors. A pointer variable can be reassigned.
- **`sizeof` of a pointer ≠ array size:** `int *p = a; sizeof(p)` = 8; `sizeof(a)` = 20.
- **Arrays can't be assigned or returned directly** and are **passed as pointers**: `void f(int a[])` ≡ `void f(int *a)` so `sizeof(a)` inside is **8**.

### 2-D arrays & pointer notation ⭐
```c
int m[2][3] = {{1,2,3},{4,5,6}};
m[i][j] == *(*(m + i) + j) == *(m[i] + j)
```
- `m` → pointer to the first **row** (`int (*)[3]`); `m + 1` moves by one **row** (12 bytes). `*m` / `m[0]` → the first element's address (`int *`).
- `sizeof(m) = 24`, `sizeof(m[0]) = 12`, `sizeof(m[0][0]) = 4`.
- Passing a 2-D array to a function: `void f(int a[][3])` or `int (*a)[3]`; **column size is required.**

### Array of pointers vs pointer to array ⭐⭐⭐
```c
int *ap[3];     // ARRAY of 3 pointers to int      → sizeof = 24
int (*pa)[3];   // POINTER to an array of 3 ints   → sizeof = 8
```
**Decode declarations** with the **right-left (spiral) rule**: start at the name, go right, then left, parentheses first.
- `int *p[3]` → p is an array of 3 pointers to int
- `int (*p)[3]` → p is a pointer to an array of 3 ints
- `int *f()` → f is a function returning a pointer to int
- `int (*f)()` → f is a pointer to a function returning int
- `int (*f[3])(int)` → f is an array of 3 pointers to functions(int) returning int
- `int **pp` → pointer to pointer to int
- `const int *p` / `int const *p` → pointer to const int
- `int *const p` → const pointer to int

## 4. Pointer to Pointer ⭐⭐
```c
int v = 5; int *p = &v; int **pp = &p;
**pp = 9;     // v is 9
```
- `pp` → `p` → `v`. `*pp` is `p`; `**pp` is `v`.
- **Why?** To **modify a pointer itself** inside a function (e.g. allocate memory, reassign a list head), or for **arrays of strings** (`char **argv`).
```c
void alloc(int **pp) { *pp = malloc(sizeof(int)); **pp = 42; }
int *q; alloc(&q);   // q now valid
```
- Passing just `int *p` to a function and assigning `p = malloc(...)` changes only the **local copy** (caller's pointer is unchanged → leak).

## 5. `const` with Pointers ⭐⭐⭐ (favourite MCQ)
| Declaration | Can change `*p` (data)? | Can change `p` (address)? |
|-------------|:--:|:--:|
| `int *p` | ✔ | ✔ |
| `const int *p` (= `int const *p`) | **✘** | ✔ |
| `int *const p` | ✔ | **✘** |
| `const int *const p` | ✘ | ✘ |
**Read right to left:** `int *const p` → "p is a **const pointer** to int". `const int *p` → "p is a pointer to **const int**".
- **Trick:** `const` applies to whatever is **immediately to its left** (or to its right if nothing is on the left). Whether it's before or after `*` decides.
- Modifying a `const` object through a cast pointer = UB.
- `const` globals may live in read-only memory.

## 6. `void *` ⭐
- Generic pointer; any object pointer converts to/from it without a cast (in C). `malloc` returns `void *`.
- **Can't dereference or do arithmetic** (standard C). Must cast: `*(int *)vp`.
- Used for generic functions: `memcpy(void*, const void*, size_t)`, `qsort` comparators, `swap` for any type.
```c
void *vp = &x;            // x is int
printf("%d", *(int *)vp);
```

## 7. Function Pointers ⭐⭐
```c
int add(int a, int b) { return a + b; }
int (*fp)(int, int) = add;     // or = &add
fp(2, 3);  (*fp)(2, 3);        // both call add → 5
int (*ops[2])(int,int) = {add, sub};   // array of function pointers
typedef int (*BinOp)(int,int);         // typedef to simplify
```
- **Use cases:** **callbacks** (`qsort` comparator), **dispatch tables / state machines**, plugin architecture, simulating **polymorphism** in C.
- **Precedence:** `int (*fp)(int)` (pointer to function) vs `int *fp(int)` (function returning `int *`).
- Can't do arithmetic on function pointers.
- `qsort(base, n, size, cmp)` with `int cmp(const void *a, const void *b) { return *(int*)a - *(int*)b; }` (**beware overflow**; prefer `(x>y)-(x<y)`).

## 8. Pointers & Functions
- **Pass by pointer** to modify caller data (swap).
- **Return a pointer:** only to `static` / heap / caller-owned data. **Never return the address of a local** (dangling).
```c
int *bad()  { int x = 5; return &x; }         // UB: x dies on return
int *good() { static int x = 5; return &x; }  // OK
int *heap() { int *p = malloc(sizeof *p); *p = 5; return p; }  // caller must free
```
- **Pointer to a struct:** `p->field` ≡ `(*p).field`.
- **Pointer to constant data in params:** `void print(const char *s)` (promises not to modify).

## 9. Common Pointer Bugs ⭐
| Bug | Example | Result |
|-----|---------|--------|
| **NULL dereference** | `int *p = NULL; *p = 1;` | Segfault |
| **Uninitialized pointer** | `int *p; *p = 1;` | UB / segfault |
| **Dangling (use-after-free)** | `free(p); *p = 1;` | UB |
| **Double free** | `free(p); free(p);` | UB (crash) |
| **Returning a local's address** | `return &local;` | UB |
| **Buffer overflow** | `a[5]` on `int a[5]` | UB, possible corruption |
| **Modifying a string literal** | `char *s = "hi"; s[0]='H';` | UB (typically segfault) |
| **Memory leak** | `p = malloc(..); p = NULL;` | Lost memory |
| **`sizeof` on a pointer param** | `sizeof(arr)` inside a function | 8, not the array size |
| **Wrong `free`** | `free` a stack/non-heap pointer, or pointer not at the start of the block | UB |
| **Mismatched type** | `double *` to an `int` | Misinterpreted bytes |
- **Segmentation fault:** accessing memory the process isn't allowed to (NULL, freed, out of range, writing read-only memory, stack overflow).
- **Tools:** `valgrind`, `-fsanitize=address`, `gdb`.

## 10. Pointer Applications (what interviewers ask you to code)
- **Swap** via pointers; **reverse an array/string** with two pointers; **linked list** (`Node *next`); **dynamic arrays**; **string functions** (`strlen`, `strcpy` implementations); **binary tree**; **pass-by-reference emulation**; **callbacks**.
```c
int my_strlen(const char *s) { const char *p = s; while (*p) p++; return p - s; }
void my_strcpy(char *d, const char *s) { while ((*d++ = *s++)); }
```

## 11. Common Interview Questions
1. What is a pointer? Size of a pointer? Does it depend on the type?
2. Null vs void vs dangling vs wild pointer?
3. `*p++` vs `(*p)++` vs `*++p`?
4. Array vs pointer: differences? `a` vs `&a`? `sizeof`?
5. `const int *p` vs `int *const p` vs `const int *const p`?
6. Pointer to pointer: why needed?
7. Function pointers: what and why? Write the declaration.
8. `int *p[3]` vs `int (*p)[3]`?
9. Why is array-decay a problem when passing arrays to functions?
10. Pointer arithmetic: what does `p + 1` do for `int *`, `char *`, `double *`?
11. What is a segmentation fault? List causes.
12. How do you avoid a dangling pointer?
13. Can you return a pointer to a local variable? What are the alternatives?
14. Why can't we dereference a `void *`?
15. `p->x` vs `(*p).x` vs `p.x`?
16. How do you detect a memory leak?
17. Implement `strlen`, `strcpy` using pointers. Reverse a string using pointers.

## MCQ Traps
- **`p + 1` adds `sizeof(*p)` bytes, not 1.**
- **Pointer − pointer = number of elements (same array only).**
- **Can't add two pointers.**
- **`int *p, q;` → `q` is an int.**
- **`sizeof(array)` = total bytes; `sizeof(pointer)` = 8.**
- **Array parameter = pointer; `sizeof` gives 8 inside the function.**
- **`const int *p`: data constant; `int *const p`: pointer constant.**
- **`a` and `&a` have the same address but different types/steps.**
- **`void *` can't be dereferenced or incremented (standard C).**
- **Postfix `++` returns the old value; `*p++` moves the pointer.**
- **Returning the address of a local variable is UB.**
- **`free(NULL)` is safe; double free is not.**

## Practice MCQs
1. `int a[5]; printf("%d", (int)(&a[4]-&a[1]));` → **3**
2. `int *p; p++` on a 64-bit machine moves the address by → **4 bytes**
3. Which can't be modified? `int *const p` → **The pointer `p`**
4. `sizeof(char*) == sizeof(double*)`? → **Yes (both 8)**
5. `int (*f)(int)` declares → **A pointer to a function taking int and returning int**
