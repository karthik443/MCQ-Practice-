# 08 – Syllogisms & Venn Diagrams

> **One-line idea:** a syllogism gives two statements; you decide which conclusions are **definitely true
> in every possible Venn diagram** consistent with the statements. If a conclusion is only true in *some*
> diagrams, it does **not** follow.

---

## 1. The four statement types

| Type | Statement | Meaning | Venn picture |
|---|---|---|---|
| **A** (universal +) | All A are B | Every A is also a B | A circle fully inside B |
| **E** (universal −) | No A is B | A and B share nothing | Two separate circles |
| **I** (particular +) | Some A are B | At least one thing is both | Circles overlap |
| **O** (particular −) | Some A are not B | At least one A lies outside B | Part of A outside B |

Important details:
- "Some" means **at least one** (possibly all) – never "not all".
- "Some A are not B" can be true while "All A are B" is false, but it does **not** imply "Some A are B".

---

## 2. Converting statements

| Statement | Valid conversion |
|---|---|
| All A are B | **Some B are A** (not "All B are A") |
| No A is B | **No B is A** |
| Some A are B | **Some B are A** |
| Some A are not B | *(no conversion possible)* |

Why "All A are B → Some B are A"? Since every A is a B, at least those A's are B's (provided A isn't empty).

---

## 3. Combining two statements (A–B and B–C → A–C)

| Premise 1 | Premise 2 | Valid conclusion | Reason |
|---|---|---|---|
| All A are B | All B are C | **All A are C** | A ⊂ B ⊂ C |
| All A are B | Some B are C | **None** | The "some B" might not include any A |
| Some A are B | All B are C | **Some A are C** | The A's that are B are inside C |
| All A are B | No B is C | **No A is C** | A inside B, B disjoint from C |
| No A is B | All B are C | **Some C are not A** | B's are in C but outside A |
| Some A are B | No B is C | **Some A are not C** | Those A's are in B, B disjoint from C |
| Some A are B | Some B are C | **None** | Two "some" never link |
| No A is B | No B is C | **None** | Two negatives never link |
| Some A are not B | anything | usually **None** | O-type is too weak |

**Memory aid:** 
- Two particulars (I/O) → nothing. 
- Two negatives → nothing. 
- Middle term must be "covered" by an "All" statement for the link to be certain.

---

## 4. Special question types

### 4.1 "Either I or II follows"
If two conclusions are **complementary** (together they cover every possibility) and *neither alone is definite*, then **either I or II** follows. Typical pairs:
- "Some A are B" / "No A is B"
- "All A are B" / "Some A are not B"

### 4.2 Possibility statements ("Some A may be B")
True if there exists *any* valid diagram where it holds. It is false only if the premises directly contradict it (e.g., "No A is B" makes "Some A may be B" false).

### 4.3 Real-world flavoured syllogisms
Ignore common sense! Use only the given statements. Example: "All cats are dogs. Some dogs are birds." → "Some cats are birds" **does not follow** (the birds among dogs may not include any cats).

---

## 5. Venn diagrams for sets (counting)

### 5.1 Two sets
`n(A ∪ B) = n(A) + n(B) − n(A ∩ B)`.
- Only A = n(A) − n(A ∩ B).
- Neither = Total − n(A ∪ B).

**Example:** class of 60: 35 like tea, 30 like coffee, 10 like both. Union = 35 + 30 − 10 = 55 → neither = **5**.

### 5.2 Three sets
`n(A ∪ B ∪ C) = n(A) + n(B) + n(C) − n(A∩B) − n(B∩C) − n(A∩C) + n(A∩B∩C)`.

**Example:** 100 students: Maths 50, Physics 40, Chemistry 30; M∩P = 15, P∩C = 10, M∩C = 8; all three = 5.
- Union = 50 + 40 + 30 − 15 − 10 − 8 + 5 = **92**; none = 8.
- Only Maths = 50 − 15 − 8 + 5 = **32**. (Subtract both pairs but add back the triple, since it was subtracted twice.)

### 5.3 "Choose the right Venn diagram" questions
For three items, decide the relationship for each pair:
- **Subset** (one is a type of the other): e.g., Dog and Cat are both inside Animal; Dog and Cat don't overlap → two separate circles inside a big circle.
- **Overlap** (some members common): Doctors and Teachers (a person can be both).
- **Disjoint**: Pen and Pencil are not the same item → separate circles.

---

## 6. Traps
1. Using general knowledge instead of the statements.
2. Treating "Some" as "Some but not all".
3. Concluding from two "Some"s or two "No"s.
4. Forgetting that conversions of "All" give only "Some".
5. In 3-set counting, forgetting to add the triple intersection back.

---

## 7. Practice MCQs

1. Statements: All A are B. All B are C. Conclusions: I. All A are C. II. All C are A.
   a) only I follows  b) only II  c) both  d) neither
2. Statements: Some A are B. No B is C. Conclusions: I. Some A are not C. II. No A is C.
   a) only I  b) only II  c) both  d) neither
3. Statements: All cats are dogs. Some dogs are birds. Conclusion: Some cats are birds.
   a) follows  b) does not follow  c) may follow only  d) cannot say
4. In a class of 60, 35 like tea, 30 like coffee, 10 like both. How many like neither?
   a) 5  b) 10  c) 15  d) 20
5. Statements: No A is B. All B are C. Conclusion: Some C are not A.
   a) follows  b) does not follow  c) either-or  d) none
6. Everyone in a group plays at least one game: 40 play cricket, 30 football, 20 both. Group size?
   a) 50  b) 70  c) 90  d) 60
7. Statements: Some A are B. All B are C. Conclusion: Some A are C.
   a) follows  b) does not follow  c) cannot say  d) either-or
8. Statements: All A are B. Some B are C. Conclusion: Some A are C.
   a) follows  b) does not follow  c) always true  d) none
9. Statements: No pen is a book. No book is a bag. Conclusion: No pen is a bag.
   a) follows  b) does not follow  c) either-or  d) cannot say
10. In a survey of 100: 60 use phone A, 50 use phone B, 20 use neither. How many use both?
    a) 20  b) 30  c) 40  d) 10

<details><summary><b>Answers with solutions</b></summary>

1. **a.** A ⊂ B ⊂ C gives I; II is the reverse and doesn't follow.
2. **a.** The A's inside B are outside C → "Some A are not C". "No A is C" is too strong (other A's unknown).
3. **b.** Two statements with "All…Some" in that order → no link.
4. **a.** 35 + 30 − 10 = 55 → 5 neither.
5. **a.** Rule: E + A → "Some C are not A".
6. **a.** 40 + 30 − 20 = 50.
7. **a.** Some A are B; all B are in C → those A are in C.
8. **b.** "All A are B, Some B are C" → nothing definite.
9. **b.** Two negatives give no conclusion; pen and bag may or may not overlap.
10. **b.** Used at least one = 80. 60 + 50 − both = 80 → both = 30.
</details>

## 8. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
