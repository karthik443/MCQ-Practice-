# 05 — Tricky Output Questions

**How to use:** pick an option, then expand **Answer** to check. (Use the Markdown preview so the `<details>` blocks collapse.)
All outputs were **compiled and run** with GCC 13 on 64-bit Linux. **(UB)** = undefined behaviour, **(unspecified)** / **(impl-defined)** = depends on the compiler; in an exam, say so.

Assume `#include <stdio.h>`, `<string.h>`, `<stdlib.h>` where needed.

---
# A. Data types & conversions

**1.** What is the output of the following code?

```c
printf("%zu %zu %zu %zu %zu %zu %zu", sizeof(char), sizeof(short), sizeof(int),
       sizeof(long), sizeof(long long), sizeof(double), sizeof(void*));
```

- **A)** `1 2 4 4 8 8 8`
- **B)** `1 2 4 8 8 8 8`
- **C)** `1 4 4 8 8 8 8`
- **D)** `1 2 4 8 8 8 4`

<details><summary>Answer</summary>

**B** — `1 2 4 8 8 8 8`

`1 2 4 8 8 8 8` (64-bit Linux). `long` is 4 on Windows; a pointer is 8 regardless of its type (4 on 32-bit).
</details>

**2.** What is the output of the following code?

```c
char c = 200;
printf("%d", c);
```

- **A)** `56`
- **B)** `200`
- **C)** `-56`
- **D)** `-200`

<details><summary>Answer</summary>

**C** — `-56`

`-56` (impl-defined: `char` is signed on x86; 200 − 256 = −56). With `unsigned char` → `200`.
</details>

**3.** What is the output of the following code?

```c
unsigned int u = -1;
printf("%u", u);
```

- **A)** `65535`
- **B)** `-1`
- **C)** `4294967295`
- **D)** `2147483647`

<details><summary>Answer</summary>

**C** — `4294967295`

`4294967295` (2³² − 1). Conversion to unsigned is modulo 2ⁿ.
</details>

**4.** What does this code print?

```c
if (-1 < (unsigned)0) printf("true"); else printf("false");
```

- **A)** true
- **B)** Undefined behaviour
- **C)** Compilation error
- **D)** false

<details><summary>Answer</summary>

**D** — false

`false`. `-1` is converted to `unsigned` → 4294967295, which is not < 0.
</details>

**5.** What is the output of the following code?

```c
if (sizeof(int) - 5 > 0) printf("yes"); else printf("no");
```

- **A)** Compilation error
- **B)** no
- **C)** yes
- **D)** Undefined behaviour

<details><summary>Answer</summary>

**C** — yes

`yes`. `sizeof(int) - 5` is `size_t` (unsigned): 4 − 5 wraps to a huge positive number.
</details>

**6.** What is the output of the following code?

```c
printf("%d %zu", 'A', sizeof('A'));
```

- **A)** `65 4`
- **B)** `A 1`
- **C)** `A 4`
- **D)** `65 1`

<details><summary>Answer</summary>

**A** — `65 4`

`65 4`. In C, `'A'` has type `int` (in C++ it's `char`, so 1).
</details>

**7.** What is the output of the following code?

```c
printf("%d %d %d %d", -7/2, -7%2, 7/-2, 7%-2);
```

- **A)** `-4 -1 -3 1`
- **B)** `-3 -1 -3 1`
- **C)** `-4 1 -4 -1`
- **D)** `-3 1 -3 -1`

<details><summary>Answer</summary>

**B** — `-3 -1 -3 1`

`-3 -1 -3 1`. Division truncates toward zero; `%` takes the sign of the **dividend**.
</details>

**8.** What is the output of the following code?

```c
double d = 10/4;
printf("%.1f %.1f", d, 10/4.0);
```

- **A)** `2.5 2.5`
- **B)** `2.0 2.5`
- **C)** `2.0 2.0`
- **D)** `2.5 2.0`

<details><summary>Answer</summary>

**B** — `2.0 2.5`

`2.0 2.5`. `10/4` is integer division (2) and only then converted.
</details>

**9.** What is the output of the following code?

```c
printf("%d", 5/2*2.0 == 4.0);
```

- **A)** `2`
- **B)** `0`
- **C)** Compilation error
- **D)** `1`

<details><summary>Answer</summary>

**D** — `1`

`1`. `5/2 = 2` (int), then `2*2.0 = 4.0`.
</details>

**10.** What is the output of the following code?

```c
int i = 3.9 + 1.9;
printf("%d", i);
```

- **A)** `5`
- **B)** `4`
- **C)** `5.8`
- **D)** `6`

<details><summary>Answer</summary>

**A** — `5`

`5`. `3.9 + 1.9 = 5.8` → truncated (not rounded).
</details>

**11.** What is the output of the following code?

```c
printf("%d", (char)300);
```

- **A)** `300`
- **B)** `44`
- **C)** `127`
- **D)** `-44`

<details><summary>Answer</summary>

**B** — `44`

`44` (300 mod 256).
</details>

**12.** What is the output of the following code?

```c
unsigned char a = 255; a++;
signed char   b = 127; b++;
printf("%d %d", a, b);
```

- **A)** `256 128`
- **B)** `0 128`
- **C)** `0 -128`
- **D)** `255 127`

<details><summary>Answer</summary>

**C** — `0 -128`

`0 -128`. Unsigned wrap is well-defined. The signed result is impl-defined (signed overflow in general is UB).
</details>

**13.** What is the output of the following code?

```c
printf("%d %d", 0.1 + 0.2 == 0.3, 0.1f == 0.1);
```

- **A)** `0 0`
- **B)** `1 0`
- **C)** `0 1`
- **D)** `1 1`

<details><summary>Answer</summary>

**A** — `0 0`

`0 0`. Binary floating point can't represent 0.1 exactly; `0.1f` (float) ≠ `0.1` (double).
</details>

**14.** What is the output of the following code?

```c
printf("%d %zu", 1 ? 'a' : 0, sizeof(1 ? 'a' : 0));
```

- **A)** `97 4`
- **B)** `a 1`
- **C)** `97 1`
- **D)** `a 4`

<details><summary>Answer</summary>

**A** — `97 4`

`97 4`. Both branches are `int`, so the result is an `int`.
</details>

**15.** What is the output of the following code?

```c
printf("%d %d", 010, 0x1F);
```

- **A)** `10 15`
- **B)** `10 31`
- **C)** `8 31`
- **D)** `8 15`

<details><summary>Answer</summary>

**C** — `8 31`

`8 31`. A leading `0` makes an octal literal.
</details>

---
# B. Operators, precedence & evaluation order

**16.** What is the output of the following code?

```c
printf("%d", printf("Hello"));
```

- **A)** `5Hello`
- **B)** `Hello0`
- **C)** `Hello5`
- **D)** `Hello6`

<details><summary>Answer</summary>

**C** — `Hello5`

`Hello5`. The inner `printf` prints `Hello` and returns 5 (characters printed).
</details>

**17.** What is the output of the following code?

```c
int k = 0;
if (k++ && k++) {}
printf("%d", k);
```

- **A)** `2`
- **B)** `1`
- **C)** `3`
- **D)** `0`

<details><summary>Answer</summary>

**B** — `1`

`1`. `k++` yields 0 (false), so the second `k++` is **never evaluated**.
</details>

**18.** What is the output of the following code?

```c
int k = 1;
if (k++ || k++) {}
printf("%d", k);
```

- **A)** `0`
- **B)** `3`
- **C)** `1`
- **D)** `2`

<details><summary>Answer</summary>

**D** — `2`

`2`. `k++` yields 1 (true) → the right side is skipped.
</details>

**19.** What is the output of the following code?

```c
printf("%d %d", 5 > 3 > 1, 1 < 2 < 3);
```

- **A)** `0 1`
- **B)** `1 0`
- **C)** `1 1`
- **D)** `0 0`

<details><summary>Answer</summary>

**A** — `0 1`

`0 1`. `(5>3)>1` → `1>1` → 0. `(1<2)<3` → `1<3` → 1.
</details>

**20.** What is the output of the following code?

```c
printf("%d", !5 + !0 + !!7);
```

- **A)** `3`
- **B)** `2`
- **C)** `1`
- **D)** `0`

<details><summary>Answer</summary>

**B** — `2`

`2`. `!5 = 0`, `!0 = 1`, `!!7 = 1` → 0 + 1 + 1.
</details>

**21.** What is the output of the following code?

```c
int z = (1, 2, 3);
printf("%d", z);
```

- **A)** Compilation error
- **B)** `3`
- **C)** `2`
- **D)** `1`

<details><summary>Answer</summary>

**B** — `3`

`3`. The comma operator evaluates left to right and yields the last value.
</details>

**22.** What is the output of the following code?

```c
int q = 5;
int r = q++ * 2;
printf("%d %d", r, q);
```

- **A)** `12 6`
- **B)** `10 5`
- **C)** `10 6`
- **D)** `12 5`

<details><summary>Answer</summary>

**C** — `10 6`

`10 6`. The old value (5) is used, then `q` becomes 6.
</details>

**23.** What is the output of the following code?

```c
int i = 5;
printf("%zu %d", sizeof(i++), i);
```

- **A)** `4 5`
- **B)** `1 5`
- **C)** `4 6`
- **D)** `5 6`

<details><summary>Answer</summary>

**A** — `4 5`

`4 5`. The operand of `sizeof` is not executed.
</details>

**24.** What is the output of the following code?

```c
printf("%d %d %d %d %d", ~0, ~5, 1<<3, -8>>1, 7&3);
```

- **A)** `-1 -6 8 -4 3`
- **B)** `-1 -6 8 4 3`
- **C)** `-1 -5 8 -4 3`
- **D)** `0 -5 8 4 3`

<details><summary>Answer</summary>

**A** — `-1 -6 8 -4 3`

`-1 -6 8 -4 3`. `~x = -x-1`; `-8>>1` is arithmetic shift on GCC (impl-defined).
</details>

**25.** What is the output of the following code?

```c
int x = 4;
if (x & 1 == 0) printf("even"); else printf("odd");
```

- **A)** Compilation error
- **B)** `odd`
- **C)** `even`
- **D)** Nothing is printed

<details><summary>Answer</summary>

**B** — `odd`

`odd` (wrong!). `1 == 0` is evaluated first (→ 0), so `x & 0` = 0 → false. Correct code: `(x & 1) == 0`.
</details>

**26.** What is the output of the following code?

```c
int w = 0;
if (w = 5) printf("assign %d", w);
```

- **A)** `assign 5`
- **B)** Nothing is printed
- **C)** Compilation error
- **D)** `assign 0`

<details><summary>Answer</summary>

**A** — `assign 5`

`assign 5`. The assignment expression's value (5) is true.
</details>

**27.** What is the output of the following code?

```c
switch (2) { case 1: printf("1"); case 2: printf("2"); case 3: printf("3"); break; default: printf("d"); }
```

- **A)** `2`
- **B)** `23`
- **C)** `123`
- **D)** `23d`

<details><summary>Answer</summary>

**B** — `23`

`23`. Execution falls through `case 3` until `break`.
</details>

**28.** What is the output of the following code?

```c
switch (5) { default: printf("d"); case 1: printf("1"); }
```

- **A)** `1`
- **B)** Nothing is printed
- **C)** `d1`
- **D)** `d`

<details><summary>Answer</summary>

**C** — `d1`

`d1`. No match → `default`, then it falls into `case 1`.
</details>

**29.** What is the output of the following code?

```c
int n = 5;
while (n-- > 0) printf("%d", n);
```

- **A)** `43210`
- **B)** `4321`
- **C)** `54321`
- **D)** `543210`

<details><summary>Answer</summary>

**A** — `43210`

`43210`. The test uses the old `n`; the body sees the decremented value. After the loop `n == -1`.
</details>

**30.** What is the output of the following code?

```c
for (int i = 0; i < 3; i++);
    printf("x");
```

- **A)** Nothing is printed
- **B)** `x`
- **C)** `xxx`
- **D)** Compilation error

<details><summary>Answer</summary>

**B** — `x`

`x` (once). The `;` makes the loop body empty.
</details>

**31.** What is the output of the following code?

```c
int i = 5;
i = i++ + ++i;
printf("%d", i);
```

- **A)** `12`
- **B)** `11`
- **C)** Undefined behaviour, no guaranteed output
- **D)** `13`

<details><summary>Answer</summary>

**C** — Undefined behaviour, no guaranteed output

**(UB)**, with no correct answer. `i` is modified twice without a sequence point. Compilers may print different values.
</details>

**32.** What is the output of the following code?

```c
int counter(void){ static int c = 0; return ++c; }
printf("%d %d %d", counter(), counter(), counter());
```

- **A)** Compilation error
- **B)** Always `1 2 3`, left to right
- **C)** Always `3 2 1`, right to left
- **D)** Unspecified: GCC prints `3 2 1`, other compilers may print `1 2 3`

<details><summary>Answer</summary>

**D** — Unspecified: GCC prints `3 2 1`, other compilers may print `1 2 3`

**(unspecified)**. GCC prints `3 2 1` (right to left); other compilers may print `1 2 3`. The C standard doesn't fix the order in which arguments are evaluated.
</details>

---
# C. Arrays & pointers

**33.** What is the output of the following code?

```c
int a[5] = {1,2,3,4,5};
printf("%zu %zu %ld %ld", sizeof(a), sizeof(&a), (long)((&a+1)-&a), (long)(*(&a+1)-a));
```

- **A)** `20 4 1 5`
- **B)** `5 8 1 5`
- **C)** `20 8 20 5`
- **D)** `20 8 1 5`

<details><summary>Answer</summary>

**D** — `20 8 1 5`

`20 8 1 5`. `&a` is a pointer to the whole array (8 bytes; `&a + 1` jumps 20 bytes = 1 array). `*(&a+1) - a` = number of elements (5).
</details>

**34.** What is the output of the following code?

```c
int a[] = {1,2,3,4,5}; int *p = a;
printf("%d ", *p++);
printf("%d %d", *p, a[0]);
```

- **A)** `1 1 1`
- **B)** `1 2 1`
- **C)** `2 3 2`
- **D)** `2 2 1`

<details><summary>Answer</summary>

**B** — `1 2 1`

`1 2 1`. `*p++` yields `a[0]`, then `p` moves to `a[1]`.
</details>

**35.** What is the output of the following code?

```c
int a[] = {1,2,3}; int *p = a;
int v = (*p)++;
printf("%d %d %d", v, a[0], *p);
```

- **A)** `1 1 1`
- **B)** `1 2 3`
- **C)** `2 2 3`
- **D)** `1 2 2`

<details><summary>Answer</summary>

**D** — `1 2 2`

`1 2 2`. The pointed value is incremented; `p` still points at `a[0]` (now 2).
</details>

**36.** What is the output of the following code?

```c
int a[] = {1,2,3}; int *p = a;
printf("%d ", *++p);   // step 1
p = a;
++*p;
printf("%d", a[0]);    // step 2
```

- **A)** `2 2`
- **B)** `2 1`
- **C)** `1 2`
- **D)** `1 1`

<details><summary>Answer</summary>

**A** — `2 2`

`2 2`. `*++p` moves first, then reads `a[1]`. `++*p` increments `a[0]` to 2.
</details>

**37.** What is the output of the following code?

```c
int a[] = {1,2,3,4};
printf("%d %d", a[2], 2[a]);
```

- **A)** `2 3`
- **B)** Compilation error
- **C)** `3 3`
- **D)** `3 2`

<details><summary>Answer</summary>

**C** — `3 3`

`3 3`. `a[i]` ≡ `*(a+i)` ≡ `*(i+a)` ≡ `i[a]`.
</details>

**38.** What is the output of the following code?

```c
char *s = "hello"; char s2[] = "hello";
printf("%zu %zu %zu %zu", sizeof(s), sizeof(s2), strlen(s), strlen(s2));
```

- **A)** `8 6 5 5`
- **B)** `5 5 5 5`
- **C)** `8 5 5 5`
- **D)** `6 6 5 5`

<details><summary>Answer</summary>

**A** — `8 6 5 5`

`8 6 5 5`. `s` is a pointer (8); `s2` has 6 bytes incl. `'\0'`.
</details>

**39.** What is the output of the following code?

```c
int m[2][3] = {{1,2,3},{4,5,6}};
printf("%d %d %zu %zu", *(*(m+1)+2), m[1][2], sizeof(m), sizeof(m[0]));
```

- **A)** `6 6 24 3`
- **B)** `6 6 24 12`
- **C)** `3 6 24 12`
- **D)** `6 6 6 3`

<details><summary>Answer</summary>

**B** — `6 6 24 12`

`6 6 24 12`. `m+1` steps a whole row (12 bytes).
</details>

**40.** What is the output of the following code?

```c
int *ap[3]; int (*pa)[3];
printf("%zu %zu", sizeof(ap), sizeof(pa));
```

- **A)** `24 8`
- **B)** `8 8`
- **C)** `24 24`
- **D)** `12 8`

<details><summary>Answer</summary>

**A** — `24 8`

`24 8`. `ap` is 3 pointers; `pa` is a single pointer.
</details>

**41.** What is the output of the following code?

```c
int *x1, y1;
printf("%zu %zu", sizeof(x1), sizeof(y1));
```

- **A)** `8 8`
- **B)** `4 8`
- **C)** `4 4`
- **D)** `8 4`

<details><summary>Answer</summary>

**D** — `8 4`

`8 4`. `y1` is a plain `int`.
</details>

**42.** What is the output of the following code?

```c
int a[5] = {1,2,3,4,5};
printf("%d %ld", (int)(&a[4] - &a[1]), (long)((char*)(a+3) - (char*)a));
```

- **A)** `3 3`
- **B)** `3 12`
- **C)** `12 12`
- **D)** `12 3`

<details><summary>Answer</summary>

**B** — `3 12`

`3 12`. Pointer difference is in **elements**; the `char*` difference is in **bytes**.
</details>

**43.** What is the output of the following code?

```c
int len(int arr[]) { return sizeof(arr)/sizeof(arr[0]); }
int a[4] = {1,2,3,4};
printf("%d %zu", len(a), sizeof(a)/sizeof(a[0]));
```

- **A)** `4 2`
- **B)** `2 2`
- **C)** `4 4`
- **D)** `2 4`

<details><summary>Answer</summary>

**D** — `2 4`

`2 4`. Inside `len`, `arr` is an `int *` → 8/4 = 2.
</details>

**44.** What is the output of the following code?

```c
void swap(int *a, int *b){ int t=*a; *a=*b; *b=t; }
void noswap(int a, int b){ int t=a; a=b; b=t; }
int p=1, q=2; swap(&p,&q); printf("%d %d ", p, q);
p=1; q=2; noswap(p,q); printf("%d %d", p, q);
```

- **A)** `2 1 2 1`
- **B)** `1 2 2 1`
- **C)** `2 1 1 2`
- **D)** `1 2 1 2`

<details><summary>Answer</summary>

**C** — `2 1 1 2`

`2 1 1 2`. C is pass-by-value.
</details>

**45.** What is the output of the following code?

```c
void setp(int **pp){ static int v = 42; *pp = &v; }
int *ptr; setp(&ptr); printf("%d", *ptr);
```

- **A)** `0`
- **B)** `42`
- **C)** Segmentation fault
- **D)** Garbage value

<details><summary>Answer</summary>

**B** — `42`

`42`. A pointer-to-pointer lets the callee change the caller's pointer.
</details>

**46.** What is the output of the following code?

```c
char str[] = "abc"; char *t = str;
while (*t) putchar(*t++ + 1);
```

- **A)** `abc`
- **B)** `bcde`
- **C)** `b`
- **D)** `bcd`

<details><summary>Answer</summary>

**D** — `bcd`

`bcd`. Each character is incremented by 1 before printing.
</details>

**47.** What is the output of the following code?

```c
char c1[] = "ab", c2[] = "ab";
printf("%d %d", c1 == c2, strcmp(c1, c2) == 0);
```

- **A)** `0 0`
- **B)** `1 1`
- **C)** `1 0`
- **D)** `0 1`

<details><summary>Answer</summary>

**D** — `0 1`

`0 1`. Different arrays → different addresses; contents equal.
</details>

**48.** What is the output of the following code?

```c
const char *pc = "hello";
printf("%c %s", *(pc + 4), "abc" + 1);
```

- **A)** `o bc`
- **B)** `l bc`
- **C)** `o c`
- **D)** `o abc`

<details><summary>Answer</summary>

**A** — `o bc`

`o bc`.
</details>

**49.** What is the output of the following code?

```c
char *words[3] = {"one","two","three"};
printf("%s %c %zu", words[2], words[1][0], sizeof(words));
```

- **A)** `three t 24`
- **B)** `three o 24`
- **C)** `three t 3`
- **D)** `two t 24`

<details><summary>Answer</summary>

**A** — `three t 24`

`three t 24`. Three 8-byte pointers.
</details>

**50.** What is the output of the following code?

```c
int add(int a,int b){return a+b;}  int sub(int a,int b){return a-b;}
int (*fp[2])(int,int) = {add, sub};
printf("%d %d", fp[0](5,3), (*fp[1])(5,3));
```

- **A)** `15 2`
- **B)** `8 2`
- **C)** `2 8`
- **D)** `8 8`

<details><summary>Answer</summary>

**B** — `8 2`

`8 2`.
</details>

**51.** What is the output of the following code?

```c
int v = 5; int *p1 = &v; int **p2 = &p1;
**p2 = 9;
printf("%d", v);
```

- **A)** The address of v
- **B)** `9`
- **C)** `5`
- **D)** Compilation error

<details><summary>Answer</summary>

**B** — `9`

`9`.
</details>

**52.** What is the output of the following code?

```c
typedef struct Node { int val; struct Node *next; } Node;
Node n3={3,NULL}, n2={2,&n3}, n1={1,&n2};
int sum=0; for (Node *t=&n1; t; t=t->next) sum += t->val;
printf("%d %d", sum, n1.next->next->val);
```

- **A)** `6 2`
- **B)** `6 1`
- **C)** `6 3`
- **D)** `3 3`

<details><summary>Answer</summary>

**C** — `6 3`

`6 3`.
</details>

**53.** What is the output of the following code?

```c
int a[] = {3,4}; void *vp = a;
printf("%d", *(int*)vp);
```

- **A)** `3`
- **B)** `4`
- **C)** Compilation error
- **D)** An address

<details><summary>Answer</summary>

**A** — `3`

`3`. A `void *` must be cast before dereferencing.
</details>

**54.** Which of the lines marked (a), (b), (c) are compile errors?

```c
int x = 1, y = 2;
const int *p1 = &x;   *p1 = 5;   // (a)
int *const p2 = &x;   p2 = &y;   // (b)
int *const p3 = &x;   *p3 = 5;   // (c)
```

- **A)** Only (a) is an error
- **B)** All three are errors
- **C)** (a) and (b) are errors; (c) is fine
- **D)** (b) and (c) are errors; (a) is fine

<details><summary>Answer</summary>

**C** — (a) and (b) are errors; (c) is fine

(a) **error**: data through `p1` is read-only. (b) **error**: `p2` itself is constant. (c) **OK**.
</details>

**55.** Which statement about (a), (b) and (c) is correct?

```c
int *p = NULL; *p = 1;                        // (a)
int *q = malloc(4); free(q); *q = 1;          // (b)
int *bad(void){ int x = 5; return &x; }       // (c)
```

- **A)** (a) segmentation fault; (b) UB (use-after-free); (c) UB (address of a dead local)
- **B)** (a) UB; (b) fine; (c) fine because x is an int
- **C)** (a) compile error; (b) segmentation fault always; (c) fine
- **D)** (a) sets *p to 1; (b) safe, freed memory is zeroed; (c) always returns 5

<details><summary>Answer</summary>

**A** — (a) segmentation fault; (b) UB (use-after-free); (c) UB (address of a dead local)

(a) **segmentation fault**. (b) **UB** (use-after-free), it may seem to work. (c) **UB**: returns the address of a dead local. Fix with `static` or `malloc`.
</details>

**56.** What is the output of the following code?

```c
int *retstatic(void){ static int x = 7; return &x; }
printf("%d", *retstatic());
```

- **A)** Garbage value
- **B)** Segmentation fault
- **C)** `7`
- **D)** `0`

<details><summary>Answer</summary>

**C** — `7`

`7`. Static storage outlives the call.
</details>

---
# D. Strings & memory

**57.** What is the output of the following code?

```c
printf("%d %zu", (int)strlen("a\nb\0c"), sizeof("a\nb\0c"));
```

- **A)** `3 6`
- **B)** `5 5`
- **C)** `3 5`
- **D)** `5 6`

<details><summary>Answer</summary>

**A** — `3 6`

`3 6`. `strlen` stops at the first `'\0'`; `sizeof` counts all 6 bytes (`a \n b \0 c \0`).
</details>

**58.** What is the output of the following code?

```c
printf("%zu %zu", sizeof("abc"), strlen("abc"));
```

- **A)** `3 3`
- **B)** `4 4`
- **C)** `4 3`
- **D)** `3 4`

<details><summary>Answer</summary>

**C** — `4 3`

`4 3`.
</details>

**59.** What happens when this code runs?

```c
char s[] = "hello"; s[0] = 'J'; printf("%s ", s);
char *p = "hello";  p[0] = 'J';
```

- **A)** Prints `Jello`; the second write is UB (string literal is read-only)
- **B)** Prints `Jello`; both writes are fine
- **C)** Prints `hello`; the second write works fine
- **D)** Compilation error on the `char *p` line

<details><summary>Answer</summary>

**A** — Prints `Jello`; the second write is UB (string literal is read-only)

First prints `Jello`. The second write is **UB** (string literal in read-only memory, typically a segfault).
</details>

**60.** What is the output of the following code?

```c
printf("%d %d %d", strcmp("a","b")<0, strcmp("b","a")>0, strcmp("a","a"));
```

- **A)** `1 1 1`
- **B)** `1 1 0`
- **C)** `0 0 1`
- **D)** `-1 1 0`

<details><summary>Answer</summary>

**B** — `1 1 0`

`1 1 0`. `strcmp` returns **0 when equal**.
</details>

**61.** What is the output of the following code?

```c
char ov[] = "abcdef";
memmove(ov+2, ov, 4);
printf("%s", ov);
```

- **A)** `abcdcd`
- **B)** `ababab`
- **C)** `ababcd`
- **D)** `abcdef`

<details><summary>Answer</summary>

**C** — `ababcd`

`ababcd`. `memmove` copies as if through a temp buffer (`memcpy` here would be UB).
</details>

**62.** What is the output of the following code?

```c
int *c = calloc(3, sizeof(int));
printf("%d%d%d ", c[0],c[1],c[2]);
int *h = malloc(3*sizeof(int)); h[0]=1; h[1]=2; h[2]=3;
h = realloc(h, 5*sizeof(int)); h[3]=4;
printf("%d %d", h[2], h[3]);
```

- **A)** `123 3 4`
- **B)** `000 0 4`
- **C)** Garbage 3 4
- **D)** `000 3 4`

<details><summary>Answer</summary>

**D** — `000 3 4`

`000 3 4`. `calloc` zeroes; `realloc` preserves existing contents.
</details>

**63.** What is the output of the following code?

```c
int a[5] = {1,2};
printf("%d %d %d", a[1], a[2], a[4]);
```

- **A)** `2 1 1`
- **B)** `2 0 0`
- **C)** `2 2 2`
- **D)** 2 followed by garbage values

<details><summary>Answer</summary>

**B** — `2 0 0`

`2 0 0`. Remaining elements are zero.
</details>

**64.** What is the output of the following code?

```c
int g;
int counter(void){ static int c = 0; return ++c; }
int main(){ counter(); counter(); printf("%d %d", counter(), g); }
```

- **A)** `3 0`
- **B)** 3 followed by a garbage value
- **C)** `0 0`
- **D)** `1 0`

<details><summary>Answer</summary>

**A** — `3 0`

`3 0`. The static keeps its value; globals are zero-initialized.
</details>

**65.** What does this program print?

```c
int main(){ int x; printf("%d", x); }
```

- **A)** Compilation error
- **B)** `0`
- **C)** A garbage (indeterminate) value; reading it is UB
- **D)** `-1`

<details><summary>Answer</summary>

**C** — A garbage (indeterminate) value; reading it is UB

**Garbage value** (indeterminate; reading it is UB). Globals and statics would be 0.
</details>

**66.** What is the output of the following code?

```c
printf("%.2f|%5d|%-5d|%05d", 3.14159, 42, 42, 42);
```

- **A)** `3.14|   42|42   |00042`
- **B)** `3.14159|   42|42   |42`
- **C)** `3.14|42   |   42|00042`
- **D)** `3.1|   42|42   |00042`

<details><summary>Answer</summary>

**A** — `3.14|   42|42   |00042`

`3.14|   42|42   |00042`.
</details>

**67.** What is the output of the following code?

```c
char ch = 'A'; ch += 2;
printf("%c %d %d", ch, ch, 'a' + 'b' - 'a');
```

- **A)** `C 66 98`
- **B)** `A 65 98`
- **C)** `C 67 98`
- **D)** `C 67 97`

<details><summary>Answer</summary>

**C** — `C 67 98`

`C 67 98`.
</details>

**68.** What is the output of the following code?

```c
printf("%d", 10 % 3 * 2 + 4 / 2);
```

- **A)** `6`
- **B)** `2`
- **C)** `3`
- **D)** `4`

<details><summary>Answer</summary>

**D** — `4`

`4`. `%` and `*` are left-to-right: (10%3)*2 = 2; 4/2 = 2; sum 4.
</details>

---
# E. Structs, unions, macros & misc

**69.** What is the output of the following code?

```c
struct S1 { char c; int i; char d; };
struct S2 { int i; char c; char d; };
struct S3 { char c; double d; char e; };
struct S4 { char a; char b; char c; };
printf("%zu %zu %zu %zu", sizeof(struct S1), sizeof(struct S2), sizeof(struct S3), sizeof(struct S4));
```

- **A)** `6 8 16 3`
- **B)** `12 8 16 3`
- **C)** `12 6 24 3`
- **D)** `12 8 24 3`

<details><summary>Answer</summary>

**D** — `12 8 24 3`

`12 8 24 3`. Members are aligned to their size; the total is a multiple of the largest alignment.
</details>

**70.** What is the output of the following code?

```c
union U { int i; char c[4]; float f; };
union U u; u.i = 0x41424344;
printf("%zu %c %c", sizeof(u), u.c[0], u.c[3]);
```

- **A)** `8 D A`
- **B)** `12 D A`
- **C)** `4 D A`
- **D)** `4 A D`

<details><summary>Answer</summary>

**C** — `4 D A`

`4 D A`. Shared memory; little-endian stores the lowest byte `0x44` ('D') first.
</details>

**71.** What is the output of the following code?

```c
int one = 1;
printf("%s", *(char*)&one ? "little" : "big");
```

- **A)** Compilation error
- **B)** `big`
- **C)** Undefined behaviour
- **D)** `little`

<details><summary>Answer</summary>

**D** — `little`

`little` on x86/ARM.
</details>

**72.** What is the output of the following code?

```c
struct B { unsigned a:3; unsigned b:5; };
printf("%zu", sizeof(struct B));
```

- **A)** `8`
- **B)** `1`
- **C)** `2`
- **D)** `4`

<details><summary>Answer</summary>

**D** — `4`

`4`. 8 bits are used, but the storage unit is an `unsigned` (4 bytes).
</details>

**73.** What is the output of the following code?

```c
#define SQ(x) x*x
printf("%d", SQ(2+3));
```

- **A)** `10`
- **B)** Compilation error
- **C)** `11`
- **D)** `25`

<details><summary>Answer</summary>

**C** — `11`

`11`. It expands to `2+3*2+3`. With `((x)*(x))` you'd get 25.
</details>

**74.** What is the output of the following code?

```c
#define SQ(x) x*x
printf("%d", 10/SQ(2));
```

- **A)** `2`
- **B)** `40`
- **C)** `25`
- **D)** `10`

<details><summary>Answer</summary>

**D** — `10`

`10`. It expands to `10/2*2` = (10/2)*2.
</details>

**75.** What is the output of the following code?

```c
#define SQ2(x) ((x)*(x))
int i = 3;
printf("%d", SQ2(i++));
```

- **A)** `16`
- **B)** Undefined behaviour
- **C)** `12`
- **D)** `9`

<details><summary>Answer</summary>

**B** — Undefined behaviour

**(UB)**. `i++` appears twice in the expansion, with no sequence point between them.
</details>

**76.** What is the output of the following code?

```c
#define MAX(a,b) ((a)>(b)?(a):(b))
printf("%d", MAX(3, 4) + 1);
```

- **A)** `5`
- **B)** `6`
- **C)** `7`
- **D)** `4`

<details><summary>Answer</summary>

**A** — `5`

`5`.
</details>

**77.** What is the output of the following code?

```c
enum E { A, B = 5, C, D = 2, F };
printf("%d %d %d %d %d", A, B, C, D, F);
```

- **A)** `0 1 2 3 4`
- **B)** `1 5 6 2 3`
- **C)** `0 5 6 2 3`
- **D)** `0 5 6 2 7`

<details><summary>Answer</summary>

**C** — `0 5 6 2 3`

`0 5 6 2 3`. Each value continues from the previous + 1 unless set.
</details>

**78.** After these declarations, which statement about `b` and `d` is correct?

```c
#define PINT int*
typedef int* TINT;
PINT a, b;     // sizeof(b)?
TINT c, d;     // sizeof(d)?
```

- **A)** `b` is an int (4 bytes), `d` is a pointer (8 bytes)
- **B)** Both `b` and `d` are ints (4 bytes)
- **C)** Both `b` and `d` are pointers (8 bytes)
- **D)** `b` is a pointer (8 bytes), `d` is an int (4 bytes)

<details><summary>Answer</summary>

**A** — `b` is an int (4 bytes), `d` is a pointer (8 bytes)

`b` is an **int** (4 bytes), because it expands to `int *a, b;`. `d` is a **pointer** (8 bytes).
</details>

**79.** What is the output of the following code?

```c
int x = 5, y = 9;
x ^= y; y ^= x; x ^= y;
printf("%d %d", x, y);
```

- **A)** `14 14`
- **B)** `9 5`
- **C)** `5 9`
- **D)** `0 0`

<details><summary>Answer</summary>

**B** — `9 5`

`9 5`. **Trap:** `swap(&a, &a)` with XOR sets the variable to 0.
</details>

**80.** What is the output of the following code?

```c
int fact(int n){ return n<=1 ? 1 : n*fact(n-1); }
int fib(int n){ return n<2 ? n : fib(n-1)+fib(n-2); }
void pr(int n){ if(n==0) return; pr(n-1); printf("%d ", n); }
printf("%d %d ", fact(5), fib(10)); pr(4);
```

- **A)** `24 55 1 2 3 4`
- **B)** `120 89 1 2 3 4`
- **C)** `120 55 4 3 2 1`
- **D)** `120 55 1 2 3 4`

<details><summary>Answer</summary>

**D** — `120 55 1 2 3 4`

`120 55 1 2 3 4`. `pr` prints **after** the recursive call, so it counts up.
</details>

**81.** What is the output of the following code?

```c
int big = 2147483647;
unsigned ub = big; ub++;
printf("%u", ub);
```

- **A)** `2147483648`
- **B)** `2147483647`
- **C)** `-2147483648`
- **D)** `0`

<details><summary>Answer</summary>

**A** — `2147483648`

`2147483648`. No overflow for `unsigned` here (2³¹ fits in 32 bits).
</details>

**82.** What happens when this loop runs?

```c
int a[3] = {1,2,3};
for (size_t i = 2; i >= 0; i--) printf("%d", a[i]);
```

- **A)** Infinite loop / out-of-bounds access (UB)
- **B)** Compilation error
- **C)** `321`
- **D)** `123`

<details><summary>Answer</summary>

**A** — Infinite loop / out-of-bounds access (UB)

**Infinite loop / crash.** `i >= 0` is always true for an unsigned type; after `i = 0`, `i--` wraps to a huge value → out-of-bounds (UB).
</details>

**83.** What is the output of the following code?

```c
for (int j = 0; j < 3; j++) { if (j == 1) continue; printf("%d", j); }
```

- **A)** `01`
- **B)** `02`
- **C)** `012`
- **D)** `12`

<details><summary>Answer</summary>

**B** — `02`

`02`.
</details>

**84.** What is the output of the following code?

```c
printf("%zu %zu", sizeof(int[10]), sizeof(char[10]));
```

- **A)** `40 40`
- **B)** `8 10`
- **C)** `10 10`
- **D)** `40 10`

<details><summary>Answer</summary>

**D** — `40 10`

`40 10`.
</details>

**85.** What is the output of the following code?

```c
char buf[10] = "hi";
printf("%zu %zu", sizeof(buf), strlen(buf));
```

- **A)** `10 3`
- **B)** `2 2`
- **C)** `10 10`
- **D)** `10 2`

<details><summary>Answer</summary>

**D** — `10 2`

`10 2`.
</details>

---
# Spot the bug

**86.** What is wrong with this code?

```c
char *s = malloc(strlen(t)); strcpy(s, t);
```

- **A)** ``malloc` must be cast to `char *` in C`
- **B)** `Allocates one byte too few (no room for `'\0'`), so `strcpy` overflows the heap block`
- **C)** ``s` is never freed, so it leaks`
- **D)** ``strcpy` cannot be used on `malloc`'d memory`

<details><summary>Answer</summary>

**B** — `Allocates one byte too few (no room for `'\0'`), so `strcpy` overflows the heap block`

Needs `strlen(t) + 1` for the terminating `'\0'` → heap overflow.
</details>

**87.** What is wrong with this code?

```c
int *p = malloc(10);
...
p = malloc(20);
```

- **A)** ``p` must be cast to `void *` first`
- **B)** ``malloc(20)` fails because `malloc(10)` was not freed`
- **C)** `Calling `malloc` twice on one pointer is undefined behaviour`
- **D)** `The first block is leaked`

<details><summary>Answer</summary>

**D** — `The first block is leaked`

The address of the first block is lost, so it can never be freed.
</details>

**88.** What is wrong with this code?

```c
free(p);
free(p);
```

- **A)** `Memory leak`
- **B)** `Double free (undefined behaviour)`
- **C)** `Compilation error`
- **D)** `Harmless, because `free` sets `p` to NULL`

<details><summary>Answer</summary>

**B** — `Double free (undefined behaviour)`

`free` does not reset `p`; freeing twice corrupts the heap. Set `p = NULL` after freeing.
</details>

**89.** What is wrong with this code?

```c
int a[5];
for (i = 0; i <= 5; i++) a[i] = i;
```

- **A)** `The loop never terminates`
- **B)** `Off-by-one: writes `a[5]`, out of bounds (UB)`
- **C)** ``a[i] = i` is not allowed for `int` arrays`
- **D)** ``a` must be initialised before it is assigned`

<details><summary>Answer</summary>

**B** — `Off-by-one: writes `a[5]`, out of bounds (UB)`

Valid indices are 0–4; `<=` writes one element past the end.
</details>

**90.** What is wrong with this code?

```c
if (p = NULL)
```

- **A)** ``NULL` cannot be used inside an `if``
- **B)** `A pointer cannot be compared with `NULL``
- **C)** `Missing cast of `NULL` to `int``
- **D)** `Assignment `=` used instead of comparison `==``

<details><summary>Answer</summary>

**D** — `Assignment `=` used instead of comparison `==``

It assigns NULL to `p` and the condition is always false.
</details>

**91.** What is wrong with this code?

```c
scanf("%d", n);
```

- **A)** ``n` must be declared as `int **``
- **B)** ``scanf` needs a trailing `\n` in the format`
- **C)** `Missing `&`: the address of `n` must be passed`
- **D)** ``%d` should be `%i``

<details><summary>Answer</summary>

**C** — `Missing `&`: the address of `n` must be passed`

`scanf` needs a pointer to store the value (`&n`).
</details>

**92.** What is wrong with this code?

```c
char s[5] = "hello";
```

- **A)** `The array size must be 7`
- **B)** `It must be declared as `char *s``
- **C)** `A `char` array cannot be initialised with a string`
- **D)** `No room for the `'\0'` terminator`

<details><summary>Answer</summary>

**D** — `No room for the `'\0'` terminator`

"hello" needs 6 bytes (5 chars + `'\0'`).
</details>

**93.** What is wrong with this code?

```c
int f() { int a[3]; return a; }
```

- **A)** `Arrays cannot be declared inside functions`
- **B)** ``a` is uninitialised so it returns 0`
- **C)** `Returns the address of a local array (and the return type is wrong)`
- **D)** `Missing `static`, so it fails to compile`

<details><summary>Answer</summary>

**C** — `Returns the address of a local array (and the return type is wrong)`

Returns the address of a dead local (dangling pointer), and `int` is the wrong type.
</details>

**94.** What is wrong with this code?

```c
while (!feof(fp)) fgets(buf, sizeof buf, fp);
```

- **A)** ``fgets` requires the file to be opened in binary mode`
- **B)** ``feof` cannot be used with `fgets``
- **C)** `The last line is processed twice; check the return value of `fgets` instead`
- **D)** `It always loops forever`

<details><summary>Answer</summary>

**C** — `The last line is processed twice; check the return value of `fgets` instead`

`feof` becomes true only after a read fails; test `fgets(...) != NULL` instead.
</details>

**95.** What is wrong with this code?

```c
gets(buf);
```

- **A)** `It returns `int`, not `char *``
- **B)** `It needs `&buf``
- **C)** ``gets` cannot read spaces`
- **D)** `No bounds checking (buffer overflow); removed from the C standard`

<details><summary>Answer</summary>

**D** — `No bounds checking (buffer overflow); removed from the C standard`

`gets` cannot limit input length; use `fgets`.
</details>

**96.** What is wrong with this code?

```c
void f(int **pp){ pp = malloc(4); }
```

- **A)** `An `int **` cannot be passed to a function`
- **B)** ``malloc(4)` should be `malloc(8)``
- **C)** `Assigns to the local copy of `pp`; it should be `*pp = malloc(...)``
- **D)** ``pp` must be checked against NULL first`

<details><summary>Answer</summary>

**C** — `Assigns to the local copy of `pp`; it should be `*pp = malloc(...)``

The caller's pointer is unchanged, and the memory leaks.
</details>

**97.** What is wrong with this code?

```c
printf("%d", 3.14);
```

- **A)** ``3.14` needs an `f` suffix`
- **B)** `Nothing wrong; it safely prints 3`
- **C)** ``printf` needs a second argument`
- **D)** `Wrong format specifier for a `double` (UB)`

<details><summary>Answer</summary>

**D** — `Wrong format specifier for a `double` (UB)`

`%d` expects an `int`; use `%f`.
</details>

**98.** What is wrong with this code?

```c
int x;
int *p = &x;
free(p);
```

- **A)** `Memory leak of `x``
- **B)** `Freeing a non-heap pointer (UB)`
- **C)** ``p` is a dangling pointer`
- **D)** ``free` needs `p` cast to `void *``

<details><summary>Answer</summary>

**B** — `Freeing a non-heap pointer (UB)`

Only pointers returned by `malloc`/`calloc`/`realloc` may be freed.
</details>

**99.** What is wrong with this code?

```c
char *s = "abc";
s[0] = 'x';
```

- **A)** `Modifying a string literal (UB)`
- **B)** ``'x'` must be written as `"x"``
- **C)** `Compile error: missing a cast`
- **D)** ``s` is not initialised`

<details><summary>Answer</summary>

**A** — `Modifying a string literal (UB)`

String literals live in read-only memory. Use `char s[] = "abc";`.
</details>

**100.** What is wrong with this code?

```c
if (strcmp(a, b)) puts("same");
```

- **A)** ``puts` needs a format string`
- **B)** ``strcmp` cannot be used inside an `if``
- **C)** ``strcmp` returns 1 for equal strings`
- **D)** ``strcmp` returns 0 for equal strings, so the logic is inverted`

<details><summary>Answer</summary>

**D** — ``strcmp` returns 0 for equal strings, so the logic is inverted`

It prints "same" when the strings are **different**.
</details>

---
## Common Interview Questions (from this file)
1. Explain undefined, unspecified, and implementation-defined behaviour with examples.
2. Why is `printf("%d %d", i++, i++)` a problem?
3. Why does `SQ(2+3)` give 11? How do you fix it?
4. Why is `sizeof(arr)` 8 inside a function?
5. Why does `-1 < 0u` return false?
6. Why can't you modify a string literal?
7. What is the output of `*p++` vs `(*p)++`?
8. How do you find bugs like leaks, double free, invalid reads? (`valgrind`, `-fsanitize=address`, `gdb`.)
