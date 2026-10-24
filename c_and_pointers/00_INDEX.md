# C & Pointers — Placement Revision Kit

Topic-wise notes for C interviews and MCQ rounds (TCS, Infosys, Wipro, Accenture, Capgemini, Amazon, and similar). Heavy on **"what is the output?"** questions, which is how C is usually tested in online assessments.
Each file has **concepts → examples → common interview questions → MCQ traps → practice MCQs**.

> **Assumptions for all outputs:** 64-bit Linux, GCC. `int` = 4 B, `long` = 8 B, pointer = 8 B, `char` is signed. Answers marked **(UB)** are undefined behaviour, **(unspecified)** or **(impl-defined)** vary by compiler, and exam questions often want you to say exactly that. Every runnable snippet in file 05 was compiled and executed to get its output.

## Files

| # | File | Topics | Priority |
|---|------|--------|----------|
| 01 | [01_C_Basics_and_Operators.md](01_C_Basics_and_Operators.md) | Data types, sizes, type conversion, operators, precedence, printf/scanf, storage classes | ⭐⭐⭐ |
| 02 | [02_Pointers.md](02_Pointers.md) | Pointer basics, arithmetic, `*p++` family, pointer-to-pointer, const, void*, function pointers | ⭐⭐⭐ |
| 03 | [03_Arrays_Strings_and_Dynamic_Memory.md](03_Arrays_Strings_and_Dynamic_Memory.md) | Arrays vs pointers, 2-D arrays, strings, malloc/calloc/realloc/free, leaks, memory layout | ⭐⭐⭐ |
| 04 | [04_Structs_Unions_Preprocessor_and_Misc.md](04_Structs_Unions_Preprocessor_and_Misc.md) | Struct padding, union, enum, bit-fields, macros, recursion, bit tricks, files | ⭐⭐ |
| 05 | [05_Tricky_Output_Questions.md](05_Tricky_Output_Questions.md) | 85 tricky snippets with verified answers and the rule behind each | ⭐⭐⭐ |
| 06 | [06_Quick_Revision_and_Top_Questions.md](06_Quick_Revision_and_Top_Questions.md) | Cheat sheet, pointer declarations decoder, top 50 questions | ⭐⭐⭐ (read last) |

## 1-day plan (≈5–6 hrs)

1. 01 Basics & operators (45 min). **Precedence, type promotion, overflow**
2. 02 Pointers (1 hr). **Draw boxes and arrows** for every example
3. 03 Arrays, strings, dynamic memory (1 hr)
4. 04 Structs, unions, preprocessor (45 min)
5. 05 Tricky outputs (1.5 hr). **Cover the answer, predict, then check.** Note every one you got wrong
6. 06 Quick revision (45 min). Answer every question out loud

> Tip: for output questions, ask in order: **(1)** Is any variable modified twice without a sequence point (UB)? **(2)** What are the types, with promotions and signed/unsigned mixing? **(3)** Is it an array or a pointer (`sizeof` differs)? **(4)** Is there a macro without brackets? **(5)** Is there an operator-precedence trap (`*p++`, `==` vs `=`)?
