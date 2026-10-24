# 05 – Permutations & Combinations

> **One-line idea:** *Permutation* = arrangement (order matters). *Combination* = selection (order doesn't).
> Ask yourself: "If I swap two chosen items, is it a different outcome?" Yes → permutation, No → combination.

---

## 1. Foundations

### 1.1 Fundamental counting principle
- Tasks done **one after another** (AND) → **multiply** the choices.
- **Either** one task **or** another (OR) → **add** the choices.

**Example:** 3 shirts and 4 trousers → 3 × 4 = 12 outfits. One shirt **or** one trouser → 3 + 4 = 7 items.

### 1.2 Factorials
n! = n × (n−1) × … × 1, and 0! = 1. (5! = 120, 6! = 720, 7! = 5040)

### 1.3 Permutations and combinations
- `nPr = n!/(n − r)!` – arrange r items out of n.
- `nCr = n!/(r!(n − r)!)` – choose r items out of n.
- Properties: nCr = nC(n−r); nC0 = nCn = 1; nCr + nC(r−1) = (n+1)Cr; nPr = nCr × r!.

**Quick value:** 10C3 = (10 × 9 × 8)/(3 × 2 × 1) = 120; 7C3 = 35; 6C2 = 15; 8C2 = 28.

---

## 2. Patterns

### Pattern A – Arrangements with all distinct items
n distinct items in a row → **n!** ways. 5 people in a row → 120.

### Pattern B – Arrangements with repeated items
`n!/(p! · q! · r! …)` where p, q, r are counts of the repeated items.
- **LEVEL:** 5 letters, L twice, E twice → 5!/(2!·2!) = **30**.
- **BANANA:** 6!/(3!·2!) = **60** (A ×3, N ×2).
- **MISSISSIPPI:** 11!/(4!·4!·2!) = **34,650** (I ×4, S ×4, P ×2).

### Pattern C – Items that must stay together
**Idea:** glue them into one block, arrange the blocks, then multiply by arrangements *inside* the block.
**Example:** arrange the letters of DELHI with the vowels (E, I) together.
Blocks: D, L, H, [EI] → 4! = 24; inside block EI → 2! = 2 → **48**.

### Pattern D – Items that must NOT be together
**Idea:** total − together.
**Example:** 5 people in a row, A and B not adjacent: 5! − (4! × 2!) = 120 − 48 = **72**.

### Pattern E – Circular arrangements
- n distinct people around a round table: **(n − 1)!** (fix one person to remove rotations).
- Bead necklace / garland (can be flipped): (n − 1)!/2.
- Two particular people together: treat as a block → (n − 2)! × 2!.

**Examples:** 5 people → 4! = **24**. 5 people with two specific ones together → 3! × 2! = **12**.

### Pattern F – Committees (selection)
- Choose r from n: nCr.
- **Including a specific person:** choose the rest from the remaining → (n−1)C(r−1).
- **Excluding a specific person:** (n−1)Cr.
- **At least one of a type:** total − (none of that type).
- **Mixed groups:** multiply selections from each group.

**Examples:**
- Committee of 3 from 4 men + 3 women with **at least one woman** = 7C3 − 4C3 = 35 − 4 = **31**.
- Committee of 3 from 7 that **includes a particular person** = 6C2 = **15**.
- 2 men and 1 woman from 4 men, 3 women = 4C2 × 3C1 = 6 × 3 = **18**.

### Pattern G – Forming numbers from digits
**Idea:** fill the **restricted positions first** (leading digit ≠ 0, last digit for even/odd/5-divisible).
- 4-digit numbers, digits 0–9, no repetition: 9 × 9 × 8 × 7 = **4,536**.
- 3-digit **distinct** numbers from {1,2,3,4,5}: 5 × 4 × 3 = **60**.
- Even 3-digit numbers from {1,2,3,4,5}, no repetition: last digit ∈ {2,4} (2 ways) × 4 × 3 = **24**.

### Pattern H – Handshakes, diagonals, lines
- Handshakes among n people = nC2 (6 people → 15).
- Diagonals of an n-gon = nC2 − n = n(n−3)/2 (hexagon → 9).
- Lines from n points (no three collinear) = nC2; triangles = nC3.

### Pattern I – Distribution of identical items
Distribute n identical items among r people (zero allowed) = **(n + r − 1)C(r − 1)**.
**Example:** 10 identical chocolates to 3 children → 12C2 = **66**.
(If each must get at least one: (n − 1)C(r − 1) → 9C2 = 36.)

### Pattern J – Rank of a word in the dictionary
Count the words that come before it, letter by letter.
**Example:** rank of CAT (letters A, C, T): words starting with A → 2! = 2 (ACT, ATC); next C: CAT is the first with C then A → rank = 2 + 1 = **3**.

---

## 3. Traps
1. Forgetting the "internal arrangements" for the glued block.
2. Using nCr when order matters (arrangements of people into *different* positions).
3. For repeated letters, forgetting to divide.
4. In "at least one" – always think complement.
5. Circular arrangement: reflections count as different unless it's a necklace/garland.

---

## 4. Practice MCQs

1. Ways to arrange 5 people in a row?
   a) 24  b) 60  c) 120  d) 720
2. Ways to seat 5 people around a circular table?
   a) 24  b) 120  c) 60  d) 12
3. Distinct arrangements of the letters of LEVEL?
   a) 120  b) 60  c) 30  d) 24
4. Committee of 3 from 4 men and 3 women with at least one woman?
   a) 35  b) 31  c) 30  d) 34
5. Arrangements of the letters of BANANA?
   a) 720  b) 120  c) 60  d) 36
6. Number of 3-digit numbers with distinct digits from {1,2,3,4,5}?
   a) 60  b) 125  c) 120  d) 30
7. 6 persons each shake hands once with every other. Total handshakes?
   a) 12  b) 15  c) 30  d) 36
8. Arrangements of MISSISSIPPI?
   a) 34,650  b) 39,916,800  c) 69,300  d) 17,325
9. Arrange the letters of DELHI so that vowels are together?
   a) 24  b) 48  c) 72  d) 120
10. Number of diagonals in a decagon (10-gon)?
    a) 35  b) 45  c) 25  d) 20

<details><summary><b>Answers with solutions</b></summary>

1. **c.** 5! = 120.
2. **a.** (5 − 1)! = 24.
3. **c.** 5!/(2!·2!) = 30.
4. **b.** 7C3 − 4C3 = 35 − 4 = 31.
5. **c.** 6!/(3!·2!) = 720/12 = 60.
6. **a.** 5 × 4 × 3 = 60.
7. **b.** 6C2 = 15.
8. **a.** 11!/(4!·4!·2!) = 39,916,800/1,152 = 34,650.
9. **b.** 4! × 2! = 48.
10. **a.** 10 × 7/2 = 35.
</details>

## 5. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
