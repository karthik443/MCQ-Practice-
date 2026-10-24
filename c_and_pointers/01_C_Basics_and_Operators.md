# 01 — C Basics, Data Types & Operators

## 1. Program Structure & Compilation ⭐
```c
#include <stdio.h>
int main(void) { printf("Hello\n"); return 0; }
```
**Stages:** Source → **Preprocessor** (`#include`, `#define`, removes comments) → **Compiler** (assembly) → **Assembler** (object file `.o`) → **Linker** (resolves symbols, libraries → executable) → **Loader** (runs).
- `gcc -E` preprocess only, `-S` assembly, `-c` object, `-Wall` warnings.
- **Compile-time errors:** syntax, type errors. **Link errors:** undefined reference (function declared but not defined). **Runtime errors:** segfault, divide by zero.
- **Declaration vs definition:** declaration says a name exists (`extern int x;`, function prototype); definition allocates storage / gives the body.
- `main` returns `int`; `return 0` = success. `void main()` is non-standard.

## 2. Data Types & Sizes ⭐⭐
| Type | Size (typical 64-bit) | Range / note |
|------|:--:|------|
| `char` | 1 | −128..127 (signed on x86) or 0..255 |
| `short` | 2 | −32768..32767 |
| `int` | 4 | −2³¹..2³¹−1 (≈ ±2.147×10⁹) |
| `long` | **8 (Linux 64-bit), 4 (Windows)** | |
| `long long` | 8 | |
| `float` | 4 | ~6–7 digits precision |
| `double` | 8 | ~15–16 digits |
| `long double` | 16 (on x86-64 GCC) | |
| **pointer** | **8** (4 on 32-bit) | Same size for every pointer type |
| `size_t` | 8 | unsigned; result type of `sizeof` |

- Only guaranteed: `sizeof(char) == 1`, `short ≤ int ≤ long`, `float ≤ double`.
- `unsigned` has range 0..2ⁿ−1. **n-bit signed range: −2ⁿ⁻¹ .. 2ⁿ⁻¹ − 1** (two's complement).
- **Type modifiers:** `signed`, `unsigned`, `short`, `long`. `long int = long`.
- `sizeof` is an **operator**, evaluated at **compile time**, and its operand is **not evaluated** (`sizeof(i++)` leaves `i` unchanged). Its result type is `size_t` → print with `%zu`.
- `'A'` is of type **`int` in C** (so `sizeof('A') == 4`), but `char` in C++.
- `void` has no size; `sizeof(void)` is a GNU extension (1).

### Integer overflow
- **Unsigned** overflow **wraps** (well-defined, modulo 2ⁿ): `unsigned char c = 255; c++` → `0`.
- **Signed** overflow is **undefined behaviour** (in practice wraps: `INT_MAX + 1` → `INT_MIN`).
- **Two's complement:** `-x = ~x + 1`. `~0 = -1`. `~5 = -6`. Sign bit = MSB.

### Floating point
- Not exact in binary: `0.1 + 0.2 == 0.3` is **false**. Compare with a tolerance `fabs(a-b) < 1e-9`.
- Float literal `3.14f` (float), `3.14` (**double** by default).
- Integer division truncates toward zero: `7/2 = 3`, `-7/2 = -3`. `%` takes the sign of the **dividend**: `-7 % 2 = -1`, `7 % -2 = 1`. `%` doesn't work on floats.
- `5/2 = 2` but `5/2.0 = 2.5`. `double d = 10/4;` → `2.0` (integer division happens first).

## 3. Type Conversion ⭐⭐
- **Integer promotion:** `char`/`short` → `int` in expressions.
- **Usual arithmetic conversions:** if operands differ, convert toward: `int → unsigned → long → unsigned long → float → double → long double`.
- **Signed/unsigned trap:** `-1 < 0u` is **false** because `-1` is converted to `UINT_MAX`. `sizeof(int) - 5 > 0` is **true** since `size_t` is unsigned (wraps to a huge number).
- Float → int **truncates** (`(int)3.99 = 3`, `(int)-3.99 = -3`).
- **Assigning to a smaller type:** `char c = 300` → `44` (300 mod 256). `char c = 200` → `-56` (signed, implementation-defined).
- **Explicit cast:** `(double)a / b` converts `a` first, so real division happens.
- Ternary: `1 ? 'a' : 0` has type `int` → prints `97` with `%d`.

## 4. Operators & Precedence ⭐⭐⭐
### Precedence (high → low)
1. `()` `[]` `->` `.` `x++` `x--` (postfix)
2. `++x` `--x` `+x` `-x` `!` `~` `*p` `&x` `sizeof` `(type)` (prefix/unary, **right-to-left**)
3. `*` `/` `%`
4. `+` `-`
5. `<<` `>>`
6. `<` `<=` `>` `>=`
7. `==` `!=`
8. `&`
9. `^`
10. `|`
11. `&&`
12. `||`
13. `?:` (right-to-left)
14. `=` `+=` `-=` … (right-to-left)
15. `,`

**Memory aid:** unary > arithmetic > shift > relational > equality > bitwise (&, ^, |) > logical (&&, ||) > ternary > assignment > comma.

### Classic traps
- **`==` binds tighter than `&`:** `x & 1 == 0` means `x & (1 == 0)` = `x & 0` = 0. **Write `(x & 1) == 0`.**
- **Chained comparison:** `5 > 3 > 1` → `(5 > 3) > 1` → `1 > 1` → **0**. `1 < 2 < 3` → `1 < 3` → **1**.
- **`=` vs `==`:** `if (x = 5)` assigns and is always true.
- **Unary `*` and `++`:** `*p++` = `*(p++)` (value, then pointer moves). `(*p)++` increments the pointed value. `*++p` moves, then reads. (See file 02.)
- **`!`:** `!5 = 0`, `!0 = 1`, `!!7 = 1`.
- **Logical operators return 0 or 1.** `5 && 0 = 0`, `5 || 0 = 1`.
- **Comma operator:** `int x = (1, 2, 3);` → `3`. `int x = 1, 2;` is a syntax error (declaration).
- **Associativity:** `a = b = c` right-to-left; `a - b - c` left-to-right.

### Short-circuit evaluation ⭐
- `a && b`: `b` is **not evaluated** if `a` is false. `a || b`: `b` is **not evaluated** if `a` is true.
```c
int i = 0;  if (i++ && i++) {}  // i++ gives 0 (false); second i++ skipped → i == 1
int j = 1;  if (j++ || j++) {}  // j++ gives 1 (true); second skipped → j == 2
```
- `&&`, `||`, `?:`, `,` have a **sequence point** after the left operand.

### Sequence points & undefined behaviour ⭐⭐⭐
Modifying a variable **more than once**, or modifying and reading it (other than to compute the new value), **between sequence points = UB**:
- `i = i++ + ++i;` UB · `a[i] = i++;` UB · `printf("%d %d", i, i++);` UB/unspecified · `x = x++;` UB.
- **Order of evaluation of function arguments and operands is unspecified:** `f(a(), b())` any order; `printf("%d %d", counter(), counter())` may print `2 1` or `1 2`.
- **Safe:** `i++; j = i;` (separate statements).
- Other UB: signed overflow, null/dangling dereference, out-of-bounds access, using uninitialized variables, modifying a string literal, shifting by ≥ width or by a negative, division by zero, `free` twice, modifying a `const` object.

### Bitwise operators ⭐
`&` AND, `|` OR, `^` XOR, `~` NOT, `<<` left shift (×2ⁿ), `>>` right shift (÷2ⁿ; **arithmetic for negative signed = implementation-defined**).
- `7 & 3 = 3`, `7 | 8 = 15`, `5 ^ 5 = 0`, `-8 >> 1 = -4`.
- `1 << 31` on a signed `int` is UB-ish; use `1u << 31`.
- **Tricks:** check bit k: `(n >> k) & 1`; set: `n |= (1 << k)`; clear: `n &= ~(1 << k)`; toggle: `n ^= (1 << k)`; **power of 2:** `n && !(n & (n-1))`; **count set bits (Kernighan):** `while (n) { n &= n-1; c++; }`; **odd/even:** `n & 1`; **swap without temp:** `a ^= b; b ^= a; a ^= b;`; **lowest set bit:** `n & -n`.
- Bitwise vs logical: `5 & 2 = 0` but `5 && 2 = 1`.

## 5. Control Flow Traps ⭐
```c
switch (2) { case 1: printf("1"); case 2: printf("2"); case 3: printf("3"); break; default: printf("d"); }
// prints "23": fall-through until break
```
- `switch` works on **integral types** (int, char, enum), **not float/string**. `case` labels must be **constant, distinct**. `default` can appear anywhere; it runs only if nothing matches, **and falls through** if it's not last.
- `break` exits the loop/switch; `continue` skips to the next iteration. `goto` exists (avoid).
- `for(;;)` and `while(1)` = infinite loops. `while (n-- > 0)` runs n times and leaves `n == -1`.
- A stray `;` after `if(...)`, `for(...)`, `while(...)` makes an **empty body**.
- `if (0); else ...` is legal.
- Dangling else binds to the **nearest** `if`.
- Loop variable declared in `for (int i...)` needs C99.

## 6. `printf` / `scanf` ⭐
| Format | Meaning |
|--------|---------|
| `%d` / `%i` | int |
| `%u` | unsigned int |
| `%ld` / `%lld` / `%lu` | long / long long / unsigned long |
| `%zu` | `size_t` |
| `%f` | float/double (printf) · `%lf` double for **scanf** |
| `%e` | scientific |
| `%c` | char |
| `%s` | string |
| `%p` | pointer address |
| `%x` / `%X` / `%o` | hex / octal |
| `%%` | literal `%` |
| `%5d`, `%-5d`, `%05d`, `%.2f`, `%*d` | width, left-align, zero-pad, precision, width from argument |

- **`printf` returns the number of characters printed**: `printf("%d", printf("Hello"))` prints `Hello5`.
- **`scanf` returns the number of items successfully read** (or `EOF`). Needs `&` for non-array variables: `scanf("%d", &n)`; arrays/strings don't need it: `scanf("%s", str)`. `%s` stops at whitespace and doesn't check bounds. **`gets` is removed (dangerous); use `fgets`.**
- Mismatched format specifier = UB (`printf("%d", 3.5)` garbage). Fewer arguments than specifiers = UB.
- **Leftover `\n` in the buffer:** `scanf("%d")` then `scanf("%c")` reads the newline → use `" %c"` (space skips whitespace).
- `puts(s)` appends `\n`; `printf` doesn't. `putchar`, `getchar` (returns `int`, so EOF works).
- **`printf("%s", NULL)`** → UB (often prints `(null)` or crashes).
- Escape sequences: `\n`, `\t`, `\\`, `\"`, `\0` (null char), `\a`.
- Octal/hex literals: `010 = 8`, `0x1F = 31`. `'\0'` = 0.

## 7. Storage Classes & Scope ⭐⭐
| Class | Storage | Default init | Scope | Lifetime |
|-------|---------|:--:|-------|----------|
| **auto** (default for locals) | Stack | **Garbage** | Block | Until block exit |
| **register** | CPU register (hint) | Garbage | Block | Block. **Can't take `&`** |
| **static** (local) | Data segment | **0** | Block | **Whole program** (retains value between calls) |
| **static** (global/function) | Data segment | 0 | **File only** (internal linkage) | Program |
| **extern** | Data segment | 0 | Whole program (external linkage) | Program |

- **Globals and statics are zero-initialized; locals and `malloc` memory are not** (garbage).
- **`static` local:** initialized **once**, keeps its value between calls (`static int c = 0; return ++c;` → 1, 2, 3…).
- **`extern`:** declares a variable defined elsewhere (another file).
- **Scope:** block, function, file, prototype. **Inner variable shadows outer.** Linkage: external / internal / none.
- **`const`**: read-only (a variable, not a true compile-time constant in C). **`volatile`**: the value may change outside the program's flow (hardware registers, signal handlers), so don't optimize reads. **`restrict`**: promise that a pointer is the only access to that object.
- **Enum / `#define` vs `const`:** macros have no type; `const` has type and scope.

## 8. Functions ⭐
- **Pass by value:** C copies arguments. To modify the caller's variable, pass its **address** (pointer).
```c
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }   // works
void noswap(int a, int b) { int t = a; a = b; b = t; }       // caller unchanged
```
- **Arrays decay to pointers** when passed: `sizeof(arr)` inside the function gives **8** (pointer size), not the array size. Pass the length separately.
- **Function prototype:** `int add(int, int);`. Without a prototype, old C assumed `int` return (implicit declaration, an error in modern C).
- **Recursion:** needs a base case; each call uses a stack frame; too deep → **stack overflow**. `fact(5) = 120`, `fib(10) = 55`.
- **Returning a pointer to a local variable = dangling pointer (UB).** Fix: `static`, heap (`malloc`), or caller-supplied buffer.
- **Variable arguments:** `int f(int n, ...)` with `<stdarg.h>` (`va_list`, `va_start`, `va_arg`, `va_end`). `printf` is the example.
- **`inline`**, **`static` functions** (file-private).
- `main(int argc, char *argv[])`: `argc` = argument count (includes the program name), `argv[0]` = program name.
- **Default return:** `void` returns nothing; `int f()` (empty parens) = unspecified args in C (vs `int f(void)` = none).
- **`exit(n)`** ends the program (flushes buffers); `return` in `main` is similar. `abort()` ends abnormally.

## 9. Common Interview Questions
1. Compilation stages in C?
2. Declaration vs definition?
3. Size of `int`, `long`, pointer on your machine? Does it depend on the type pointed to? (No.)
4. `sizeof` vs `strlen`?
5. What is undefined behaviour? Examples?
6. What are sequence points? Why is `i = i++ + ++i` UB?
7. Short-circuit evaluation?
8. Static vs global vs local variables? Default initial values?
9. `static` keyword uses (3)? `extern`? `volatile`? `register`?
10. `++i` vs `i++`?
11. Explain pass-by-value in C. How do you modify a caller's variable?
12. `=` vs `==`? Bitwise vs logical?
13. `int main()` vs `int main(void)`; what does `main` return?
14. Signed vs unsigned; what happens on overflow?
15. `printf` return value; `scanf` return value?
16. What is a segmentation fault and common causes?
17. How do you check if a number is a power of 2 / count set bits / swap without a temp?

## MCQ Traps
- **Uninitialized local = garbage; global/static = 0.**
- **`sizeof` is compile-time; operand not evaluated; returns `size_t`.**
- **`sizeof('A') == 4` in C.**
- **Signed–unsigned comparison converts to unsigned.**
- **Integer division truncates; `%` sign follows the dividend.**
- **`&&`/`||` short-circuit; function-argument evaluation order is unspecified.**
- **Array parameter is really a pointer.**
- **`printf` returns the character count; `scanf` returns the items read.**
- **Switch falls through without `break`.**
- **`char` signedness and `long` size are platform-dependent.**
- **`x & 1 == 0` is wrong because of precedence.**

## Practice MCQs
1. `printf("%d", 7/2 + 7%2);` → 3 + 1 = **4**
2. `unsigned char c = 255; c++;` → **0**
3. Default value of a static local → **0**
4. `int a = 5; printf("%d", a++ + 1);` → **6** (then `a` is 6)
5. Which operator has the lowest precedence? **(a) `&&` (b) `?:` (c) `=` (d) `,`** → **`,`**
