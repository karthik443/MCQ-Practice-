# 06 — Quick Revision (Read this right before the interview / OA)

## A. One-line definitions
| Term | One-liner |
|------|-----------|
| Pointer | Variable holding a memory address |
| NULL pointer | Points to nothing; dereferencing crashes |
| Wild pointer | Uninitialized pointer (garbage address) |
| Dangling pointer | Points to freed / out-of-scope memory |
| `void *` | Generic pointer; cast before use; no arithmetic |
| Pointer arithmetic | `p + n` moves by `n * sizeof(*p)` bytes |
| Array decay | Array name → pointer to the first element (except `sizeof`, `&`) |
| Function pointer | Pointer to code; used for callbacks/dispatch |
| Pointer to pointer | Lets a function modify the caller's pointer |
| `const int *p` | Data read-only, pointer movable |
| `int *const p` | Pointer fixed, data changeable |
| Segmentation fault | Access to memory the process can't touch |
| Memory leak | Heap memory never freed |
| Double free | `free` on the same pointer twice (UB) |
| Buffer overflow | Writing past a buffer's end |
| Stack | Locals, params, return addresses; auto-managed |
| Heap | `malloc` area; manual `free` |
| BSS / Data | Uninitialized / initialized globals & statics |
| Undefined behaviour | The standard imposes no requirements; anything may happen |
| Sequence point | Point where all side effects are complete |
| Struct padding | Bytes inserted for alignment |
| Union | Members share the same memory |
| Endianness | Byte order in memory (little: LSB at the lowest address) |
| Macro | Text substitution by the preprocessor |
| `static` (local) | Keeps value across calls; zero-initialized |
| `volatile` | Value may change outside program control; don't optimize away |
| `extern` | Declares a variable defined elsewhere |
| `sizeof` | Compile-time operator returning `size_t` |

## B. Pointer declaration decoder ⭐ (read right to left)
| Declaration | Meaning |
|-------------|---------|
| `int *p` | pointer to int |
| `int **pp` | pointer to pointer to int |
| `int *p[3]` | array of 3 pointers to int |
| `int (*p)[3]` | pointer to an array of 3 ints |
| `int *f(int)` | function returning pointer to int |
| `int (*f)(int)` | pointer to a function (int → int) |
| `int (*f[3])(int)` | array of 3 pointers to functions |
| `int *(*f)(int)` | pointer to a function returning `int *` |
| `const int *p` | pointer to const int |
| `int *const p` | const pointer to int |
| `const int *const p` | const pointer to const int |
| `char *argv[]` = `char **argv` | array/pointer of strings |

## C. Sizes & values cheat sheet (64-bit Linux)
| | |
|--|--|
| char / short / int / long / long long | 1 / 2 / 4 / **8** / 8 |
| float / double / long double | 4 / 8 / 16 |
| pointer (any type) | **8** |
| `sizeof('A')` | **4** (C) |
| `sizeof("abc")` / `strlen("abc")` | 4 / 3 |
| `int a[5]`: `sizeof(a)` / `sizeof(&a)` / `sizeof(a+0)` | 20 / 8 / 8 |
| `int *ap[3]` / `int (*pa)[3]` | 24 / 8 |
| Array param `sizeof` | 8 |
| INT range | −2³¹ .. 2³¹−1 |
| UINT_MAX | 4294967295 |
| `~0`, `~5` | −1, −6 |
| `-7/2`, `-7%2` | −3, −1 |
| ASCII `'0'`, `'A'`, `'a'` | 48, 65, 97 |

## D. Rules to apply to any output question ⭐
1. **Types first:** promotions, signed/unsigned mixing (→ unsigned), integer vs float division.
2. **UB scan:** a variable changed twice between sequence points (`i++ + ++i`), uninitialized read, out-of-bounds, NULL/dangling dereference, modifying a string literal, signed overflow, bad shifts.
3. **Unspecified scan:** order of evaluating function arguments / operands.
4. **Array vs pointer:** `sizeof`, `a` vs `&a`, `p + 1` step size.
5. **Precedence:** unary > `* / %` > `+ -` > shifts > relational > `==` > `& ^ |` > `&& ||` > `?:` > `=` > `,`. Postfix `++` > `*`.
6. **Macros:** expand textually, then apply precedence (no brackets → trouble).
7. **Short-circuit:** `&&`/`||` may skip the right side (and its side effects).
8. **Pass by value:** callee changes don't reach the caller unless you pass a pointer.
9. **Strings:** `'\0'` terminator, literal vs array, `==` compares addresses.
10. **Static / global:** zero-init, persist; locals: garbage.
11. **`switch`:** fall-through unless `break`.
12. **`printf`** returns the char count; `scanf` returns the items read; `strcmp` returns 0 on equal.

## E. "Which one…?" quick answers
- Modify the caller's variable → **pass a pointer**
- Modify the caller's pointer → **pointer to pointer**
- Zero-initialized heap memory → **`calloc`**
- Resize a heap block → **`realloc`** (assign to a temp first)
- Overlapping copy → **`memmove`**
- Safe line input → **`fgets`**
- Bounded formatted print → **`snprintf`**
- Share memory between types → **union**
- Reduce struct size → **reorder members (largest first)** or pack
- Persist a local between calls → **`static`**
- Limit a global to the file → **`static` global**
- Use a variable from another file → **`extern`**
- Callback / dispatch table → **function pointer**
- Generic function (`qsort`) → **`void *`**
- Hardware register / signal flag → **`volatile`**
- Constant, scoped, typed value → **`const`** (vs `#define`)
- Related named constants → **`enum`**
- Detect leaks / invalid access → **valgrind / AddressSanitizer**

## F. Top 50 interview questions (answer out loud)
**Pointers**
1. What is a pointer? Size? Does it depend on type?
2. NULL vs void vs wild vs dangling pointers?
3. `*p++` vs `(*p)++` vs `*++p` vs `++*p`?
4. Pointer arithmetic: what does `p + 1` do for different types?
5. Can you subtract/add/compare pointers?
6. Array vs pointer; `a` vs `&a`; `sizeof`?
7. Why is `sizeof(arr)` 8 inside a function?
8. `const int *p` vs `int *const p` vs `const int *const p`?
9. Pointer to pointer: why?
10. Function pointer: declare, assign, call, use case?
11. `int *p[3]` vs `int (*p)[3]`?
12. `void *`: why can't you dereference it?
13. Can a function return a pointer to a local? Alternatives?
14. What is `p->x` vs `(*p).x`?
15. Segfault: causes?
16. Explain `a[i] == i[a]`.

**Memory**
17. `malloc` vs `calloc` vs `realloc` vs `free`?
18. Memory leak, double free, use-after-free, buffer overflow?
19. Stack vs heap vs BSS vs data vs text?
20. What happens if `realloc` fails?
21. How does `free` know the block size?
22. How is a 2-D array stored? Allocate a 2-D array dynamically?
23. Why do locals contain garbage while globals are zero?
24. Stack overflow: cause?

**Strings**
25. `char s[]` vs `char *s` with a literal?
26. `sizeof` vs `strlen`?
27. `strcpy` vs `strncpy` vs `memcpy` vs `memmove`?
28. `strcmp` return values?
29. Why is `gets` unsafe?
30. Write `strlen`, `strcpy`, reverse, palindrome, using pointers.

**Language**
31. Undefined vs unspecified vs implementation-defined behaviour?
32. What are sequence points? Why is `i = i++ + ++i` UB?
33. Short-circuit evaluation?
34. Operator precedence traps (`x & 1 == 0`, `*p++`)?
35. Signed vs unsigned comparison; overflow behaviour?
36. Integer promotion / usual arithmetic conversions?
37. Storage classes: `auto`, `static`, `extern`, `register`?
38. `static` uses (local, global, function)?
39. `volatile`, `restrict`, `const`?
40. Declaration vs definition?
41. Pass by value in C; simulating pass by reference?
42. `printf`/`scanf` return values; common format mistakes?

**Structs, preprocessor, misc**
43. Struct vs union; size of each?
44. Structure padding/alignment; how to minimize?
45. Endianness: how to check?
46. Macro vs function vs `inline`; `SQ(2+3)`?
47. `#include <>` vs `""`; include guards?
48. `typedef` vs `#define`?
49. Bit manipulation: power of 2, count set bits, swap without a temp?
50. C vs C++ differences (e.g. `sizeof('A')`, `void*` conversions)?

## G. Last-minute traps checklist
- [ ] `int *p, q;` → `q` is an `int`
- [ ] `p + 1` moves by `sizeof(*p)`, pointer − pointer = elements
- [ ] `sizeof(array)` ≠ `sizeof(pointer)`; array param = pointer (8)
- [ ] `char s[] = "x"` modifiable; `char *s = "x"` is not (UB)
- [ ] Strings end with `'\0'`: `sizeof("abc") = 4`
- [ ] `strcmp` returns 0 when equal; `==` compares addresses
- [ ] `malloc` = garbage, `calloc` = zero; `free(NULL)` OK, double free ✘
- [ ] Return the address of a local ✘ (use `static`/heap)
- [ ] Locals = garbage; global/static = 0
- [ ] `-1 < 0u` is false; `sizeof(x) - 5 > 0` is true
- [ ] `x & 1 == 0` is wrong (precedence)
- [ ] `i = i++ + ++i`, `printf("%d %d", i, i++)` → UB/unspecified
- [ ] `SQ(2+3)` = 11 without brackets
- [ ] `switch` falls through; `default` can be anywhere
- [ ] `const int *p` ≠ `int *const p`
- [ ] `'A'` is `int` in C (size 4)
- [ ] Struct size includes padding; union = largest member
- [ ] `for (size_t i = n-1; i >= 0; i--)` never ends
- [ ] `printf` returns the character count
