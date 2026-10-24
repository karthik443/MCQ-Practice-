# 03 — Arrays, Strings & Dynamic Memory

## 1. Arrays ⭐
Contiguous block of same-type elements. **Indexing starts at 0; C does NO bounds checking.**
```c
int a[5] = {1, 2};            // a = {1, 2, 0, 0, 0}  (rest zero-filled)
int b[] = {1, 2, 3};          // size inferred = 3
int c[5] = {0};               // all zeros
int d[3] = {1, 2, 3, 4};      // too many initializers: error/warning
```
- **Partial initialization zero-fills the rest.** Without any initializer, a **local** array has **garbage**; a **global/static** array is **zero**.
- `sizeof(a)/sizeof(a[0])` = number of elements (works only where `a` is a real array, **not** a function parameter).
- **Out-of-bounds access = UB** (may silently corrupt memory, crash, or appear to work).
- **Arrays can't be copied with `=`** or compared with `==` (compares addresses). Use `memcpy` / loops / `memcmp`.
- **Variable-length arrays (VLA, C99):** `int a[n];` (stack-allocated, size at runtime; avoid for large n).
- **Designated initializers (C99):** `int a[5] = {[2] = 10};`.
- **`a[i]` ≡ `*(a + i)` ≡ `i[a]`.**
- **Passed as pointers**; the callee can modify the caller's array (no copy).
- **2-D arrays are stored row-major** (row after row). `int m[2][3]`: 6 contiguous ints; `m[1][2]` is the last. Only the **first** dimension may be omitted in declarations/params.

## 2. Strings ⭐⭐⭐
A C "string" is a **`char` array terminated by `'\0'`** (null character, value 0). There is no string type.
```c
char s1[] = "hello";     // array of 6 chars (incl. '\0'); MODIFIABLE copy
char *s2  = "hello";     // pointer to a string LITERAL (read-only memory); modifying = UB
char s3[10] = "hi";      // 'h','i','\0', then zeros
char s4[5] = "hello";    // no room for '\0' → NOT a valid string
```
- **`sizeof("hello") = 6`**, `strlen("hello") = 5`. **`sizeof(s2)` = 8** (pointer), `sizeof(s1)` = 6.
- **`char s[] = "abc"; s[0] = 'X';` ✔** vs **`char *p = "abc"; p[0] = 'X';` ✘ UB (segfault typically).** Use `const char *` for literals.
- **Two identical literals** may share storage (implementation-defined): comparing `char *` with `==` compares **addresses, not contents**. Two separate char arrays with the same text: `c1 == c2` is **false**; `strcmp(c1, c2) == 0` is **true**.
- Embedded `'\0'`: `strlen("a\nb\0c")` = **3**, `sizeof` = **6**.
- **`'a'` is a char/int; `"a"` is a 2-byte string (`'a','\0'`).** `'ab'` is a multi-char constant (don't).
- **`char` arithmetic:** `'a' + 1` = 98 (int); `(char)('a'+1)` = `'b'`; `'5' - '0'` = 5 (digit → number); `'a' - 'A'` = 32.
- **Printing:** `printf("%s", s)` reads until `'\0'` (no terminator → runs on, UB). `s + 1` is the string from index 1: `"hello" + 1` → `"ello"`.

### `<string.h>` functions ⭐⭐
| Function | Does | Notes |
|----------|------|-------|
| `strlen(s)` | Length **excluding** `'\0'` | O(n); returns `size_t` |
| `strcpy(d, s)` | Copy incl. `'\0'` | **No bounds check → overflow**. `strncpy` may **not** null-terminate |
| `strcat(d, s)` | Append `s` to `d` | `d` must have room and be terminated |
| `strcmp(a, b)` | `<0`, `0`, `>0` | **Returns 0 when equal** (so `if (strcmp(a,b))` means *different*) |
| `strncmp`, `strncpy`, `strncat` | Bounded versions | |
| `strchr(s, c)` / `strrchr` | First / last occurrence → pointer or NULL | |
| `strstr(s, sub)` | Substring search → pointer or NULL | |
| `strtok(s, delim)` | Tokenize; **modifies** `s`, **not thread-safe**, `s` must be modifiable | |
| `memcpy(d, s, n)` | Copy bytes | **Overlap = UB** |
| `memmove(d, s, n)` | Copy bytes, **overlap-safe** | `memmove(ov+2, ov, 4)` on `"abcdef"` → `"ababcd"` |
| `memset(p, v, n)` | Fill bytes with `v` | `memset(a, 0, sizeof a)`; don't use for non-0/-1 int values |
| `memcmp` | Compare bytes | |
| `atoi`, `atof`, `strtol` | String → number | `strtol` reports errors |
| `sprintf`, `snprintf` | Format into a buffer | `snprintf` is safe |
| `toupper`, `tolower`, `isalpha`, `isdigit`, `isspace` | `<ctype.h>` | |
- **`strcpy` into a too-small buffer = buffer overflow** (security bug). **`gets` is unsafe and removed; use `fgets(buf, size, stdin)`** (keeps the `'\n'`).
- **`scanf("%s")`** stops at whitespace; to read a line: `fgets` or `scanf("%[^\n]", s)`.
- **`strcmp` compares character by character** (lexicographic) and isn't the same as comparing addresses.

### Classic string code (be able to write these)
```c
int  my_strlen(const char *s){ int n=0; while(s[n]) n++; return n; }
void my_strcpy(char *d, const char *s){ while((*d++ = *s++)); }
void reverse(char *s){ int i=0,j=strlen(s)-1; while(i<j){ char t=s[i]; s[i++]=s[j]; s[j--]=t; } }
int  is_palindrome(const char *s){ int i=0,j=strlen(s)-1; while(i<j) if(s[i++]!=s[j--]) return 0; return 1; }
```
- Also: count vowels, anagram check (frequency array `int cnt[256]`), first non-repeating char, remove duplicates, word count.

### Array of strings
```c
char *words[3] = {"one", "two", "three"};   // array of 3 pointers → sizeof = 24
words[1][0]  // 't'
char names[3][10];                           // 2-D char array: 30 bytes, each row up to 9 chars + '\0'
```
- **Array of pointers** (ragged, points to literals) vs **2-D char array** (fixed-width, modifiable).

## 3. Memory Layout of a C Program ⭐⭐
From high to low addresses:
| Segment | Contents | Notes |
|---------|----------|-------|
| **Stack** | Local variables, function parameters, return addresses | Grows **downward**; auto-managed; limited (~8 MB); **stack overflow** on deep recursion |
| *(free space)* | | |
| **Heap** | `malloc`/`calloc`/`realloc` memory | Grows **upward**; **manual** `free`; fragmentation/leaks |
| **BSS** | **Uninitialized** globals/statics (zeroed) | Not stored in the executable |
| **Data** | **Initialized** globals/statics | |
| **Text (code)** | Program instructions; string literals / constants (read-only) | Read-only, shareable |

- `int g;` → BSS. `int g = 5;` → data. `static int s;` → BSS. `const char *p = "hi"` → `p` in data/stack, `"hi"` in read-only text.
- **Stack vs heap:** stack = fast, automatic, fixed lifetime; heap = flexible size/lifetime, slower, manual.

## 4. Dynamic Memory Allocation ⭐⭐⭐ (`<stdlib.h>`)
| Function | Does | Initialized? |
|----------|------|:--:|
| `malloc(n)` | Allocate `n` **bytes** | **No (garbage)** |
| `calloc(count, size)` | Allocate `count × size` bytes | **Yes, zeroed** |
| `realloc(p, new)` | Resize a block (may **move** it; copies contents) | New part uninitialized |
| `free(p)` | Release | |
```c
int *a = malloc(5 * sizeof(int));        // or malloc(5 * sizeof *a)
if (a == NULL) { /* out of memory */ }
for (int i = 0; i < 5; i++) a[i] = i;
a = realloc(a, 10 * sizeof *a);          // DANGER: if realloc fails → NULL, old block leaks
free(a);
a = NULL;                                // avoid a dangling pointer
```
- **Always check for `NULL`.** **`malloc(0)`** may return NULL or a unique pointer.
- **`realloc` safe idiom:** `tmp = realloc(a, n); if (tmp) a = tmp;`. `realloc(NULL, n)` ≡ `malloc(n)`; `realloc(p, 0)` may free.
- **`free(NULL)` is safe (no-op).** **Double free = UB.** **Freeing a non-heap or interior pointer = UB.** **Use after free = UB.**
- **Cast of `malloc`:** not needed in C (needed in C++).
- **Memory leak:** allocated memory not freed before losing the pointer. Long-running programs eventually run out of memory.
- **Heap overflow:** writing past the allocated size. **Uninitialized read:** reading `malloc` memory.
- **`sizeof *p` idiom** keeps the size correct when the type changes.
- **`malloc` vs `calloc`:** `calloc` zero-initializes and takes two args; `malloc` is faster, uninitialized.
- **2-D dynamic array:**
```c
int **m = malloc(r * sizeof(int*));                  // array of row pointers
for (int i = 0; i < r; i++) m[i] = malloc(c * sizeof(int));
/* free each row, then free(m) */
// or one block: int *m = malloc(r*c*sizeof(int)); m[i*c + j]
```
- **How does `free` know the size?** The allocator stores metadata just before the block.
- **Memory alignment**: `malloc` returns memory aligned for any type.
- **Fragmentation**: free memory split into small unusable pieces.
- **`alloca`** allocates on the stack (non-standard).
- **Dangling pointer example:** `int *p = malloc(4); int *q = p; free(p); *q = 1;` ← `q` dangles too (aliasing).

## 5. Linked List Essentials (frequent C question)
```c
typedef struct Node { int data; struct Node *next; } Node;
Node *push(Node *head, int v){ Node *n = malloc(sizeof *n); n->data=v; n->next=head; return n; }
void print(Node *h){ for(; h; h = h->next) printf("%d ", h->data); }
Node *reverse(Node *h){ Node *prev=NULL; while(h){ Node *nx=h->next; h->next=prev; prev=h; h=nx; } return prev; }
```
- To change the **head** inside a function, pass `Node **head` (or return the new head).
- **Detect a cycle:** Floyd's (slow/fast pointers). **Find the middle:** slow/fast. **Delete a node** carefully (update `next`, `free`).
- A **self-referential struct** must use a **pointer** to itself (`struct Node *next`), not the struct itself.

## 6. Common Interview Questions
1. `char s[] = "abc"` vs `char *s = "abc"`: differences? Which can be modified?
2. `sizeof` vs `strlen`?
3. `malloc` vs `calloc`? What does `realloc` do if it can't extend in place?
4. What is a memory leak? How do you detect it? (`valgrind`)
5. What is a dangling pointer? How do you prevent it?
6. Stack vs heap? Memory layout of a C program (segments)?
7. Why can't you assign arrays (`a = b`)? How do you copy one?
8. What happens on an out-of-bounds array access?
9. `strcpy` vs `strncpy` vs `memcpy` vs `memmove`?
10. Why is `gets` dangerous? 
11. How is a 2-D array stored? How to allocate a 2-D array dynamically?
12. What does `strcmp` return? Why is `s1 == s2` wrong for strings?
13. Reverse a string / check a palindrome / count vowels in place.
14. BSS vs data segment?
15. How does `free` know how much to free?
16. What is a buffer overflow? How do you avoid it?

## MCQ Traps
- **Strings end with `'\0'`; `sizeof("abc") = 4`, `strlen("abc") = 3`.**
- **`char *p = "x"; p[0] = 'y';` is UB. `char a[] = "x"; a[0] = 'y';` is fine.**
- **`==` on strings compares addresses.**
- **`strcmp` returns 0 for equal strings.**
- **`malloc` doesn't zero memory; `calloc` does.**
- **Local arrays are uninitialized; global arrays are zero.**
- **`{1,2}` into `int a[5]` gives `1,2,0,0,0`.**
- **`memcpy` overlap = UB; `memmove` is safe.**
- **Stack grows down; heap grows up.**
- **`free(NULL)` is safe; double free isn't.**
- **`sizeof` of a pointer parameter is 8, not the array size.**
- **`strncpy` may not null-terminate.**

## Practice MCQs
1. `char s[10] = "hi"; printf("%zu %zu", sizeof(s), strlen(s));` → **10 2**
2. `printf("%s", "abc" + 2);` → **`c`**
3. Memory from `calloc` is → **Zero-initialized**
4. Which segment holds uninitialized global variables? → **BSS**
5. `int a[5] = {1,2}; printf("%d", a[4]);` → **0**
