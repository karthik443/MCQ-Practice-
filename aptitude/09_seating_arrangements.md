# 09 – Seating Arrangements (and Ordering Puzzles)

> **One-line idea:** draw a skeleton, place **certain** clues first, combine the rest into chains, and keep
> multiple cases alive until a clue kills them. Never guess – deduce.

---

## 1. Universal method (use for every puzzle)

1. **Read all clues once** and mark which ones are *definite* (extreme end, exactly opposite, fixed position) and which are *relative* (A is left of B).
2. **Draw the skeleton**: n boxes in a row, or n points on a circle numbered clockwise 1…n.
3. **Place definite clues first.**
4. **Chain relative clues**: "A left of B" + "B left of C" → A B C (not necessarily adjacent unless "immediate").
5. **Use negative clues last** to cross out options.
6. If two cases remain, carry both forward; the next clue usually kills one.
7. Answer the questions *only* from the final arrangement; if two cases remain, answer only what is true in both.

---

## 2. Vocabulary that causes mistakes
| Phrase | Meaning |
|---|---|
| Immediate left/right | Directly adjacent |
| Second to the left | One person between |
| Between A and B | Somewhere in between (not necessarily adjacent) unless "exactly between" |
| Extreme end | First or last position |
| Opposite | In a circle of n: position + n/2 (for even n) |
| Neighbour | Adjacent person |

---

## 3. Orientation rules
- **Row facing North:** left = left side of the page, right = right side.
- **Row facing South:** reversed — the person's left is the page's right.
- **Two rows facing each other:** one row faces North, the other South → their left/right are opposite.
- **Circle facing the centre:** a person's **left is clockwise**, right is anticlockwise (seen from above).
- **Circle facing outward:** left is anticlockwise, right is clockwise.
- **Mixed facing circles:** convert each person's "left/right" into clockwise/anticlockwise separately.

---

## 4. Types of puzzles

### Type 1 – Single row (5–8 people)
Place extremes first; then adjacency chains.

### Type 2 – Two parallel rows
Each person in one row faces someone in the other row; the "facing" clue links the rows.

### Type 3 – Circular
Fix one person at position 1 (this removes rotation symmetry), then place others using clockwise numbering.

### Type 4 – Square / rectangular table
Corners and middle-of-sides positions have different "facing" directions. Keep a diagram with directions.

### Type 5 – Floors, days, months (ordering)
Same logic as a row: positions are floors/days; "immediately above" = adjacent.

### Type 6 – Attribute matching (person – colour – city)
Use a grid; tick yes, cross no, and fill rows/columns by elimination.

---

## 5. Worked puzzles

### Puzzle 1 – Row
Five friends P, Q, R, S, T sit in a row facing north.
- P is at the extreme left.
- T is at the extreme right.
- R sits immediately left of T.
- S sits immediately right of P.

Solution: P ? ? ? T → R immediately left of T → P ? ? R T → S immediately right of P → P S ? R T → Q fills the gap → **P S Q R T**.

Q1. Who sits in the middle? → **Q**.
Q2. Who is second from the right? → **R**.
Q3. How many people sit between P and R? → S and Q = **2**.

### Puzzle 2 – Circle (facing centre)
Six people A–F sit around a table facing the centre.
- A sits opposite D.
- B sits immediately to the right of A.
- C sits immediately to the left of A.
- E sits between D and B.
- E is not adjacent to C.

Solution (positions numbered clockwise 1–6):
- A = 1 → D opposite = 4.
- Facing centre: right = anticlockwise → B = 6. Left = clockwise → C = 2.
- E between D(4) and B(6) → E = 5. F takes the last seat = 3. Check: E (5) is not adjacent to C (2). ✔
- Clockwise order: **A, C, F, D, E, B**.

Q1. Who sits opposite B? → position 3 = **F**.
Q2. Who is second to the left of A? → left = clockwise, second = position 3 = **F**.
Q3. Who sits between E and A (shorter side)? → **B**.

### Puzzle 3 – Attribute matching
Three people Asha, Bala, Chitra each own one pet (cat, dog, fish).
- Asha does not own the dog.
- Chitra owns neither the cat nor the fish.
- Bala does not own the cat.

Solution: Chitra → dog (only option). Bala not cat → Bala = fish. Asha = cat.
Q1. Who owns the cat? **Asha**. Q2. Who owns the fish? **Bala**.

---

## 6. Traps
1. Mixing up clockwise/anticlockwise with left/right when people face the centre vs. outside.
2. Treating "between" as "adjacent".
3. Not carrying two cases forward and committing to a wrong one.
4. Answering from one case when two are still possible.

---

## 7. Practice MCQs

**Set 1:** Six people A–F sit in a row facing north.
- F is at the extreme right.
- B is at the other extreme end.
- A sits immediately right of B.
- D sits immediately left of F.
- C sits third from the right end.

1. Who sits at the 3rd and 4th positions (counting from the left)?
   a) A and E  b) E and C  c) C and D  d) A and C
2. Who sits immediately right of E?
   a) A  b) C  c) D  d) F
3. How many persons sit between B and D?
   a) 2  b) 3  c) 4  d) 1

**Set 2:** Four friends W, X, Y, Z sit one on each side of a square table, facing the centre.
W sits opposite Y, and X is on the immediate right of W.

4. Who is on the immediate left of W?
   a) X  b) Y  c) Z  d) cannot say
5. Who is on the immediate right of Y?
   a) W  b) X  c) Z  d) cannot say

<details><summary><b>Answers with solutions</b></summary>

Set 1 arrangement: F at position 6, B at 1, A at 2, D at 5, C third from right = position 4, E fills position 3 → **B A E C D F**.

1. **b.** Positions 3 and 4 are E and C.
2. **b.** Right of E (position 3) is position 4 = C.
3. **b.** Between B (1) and D (5): A, E, C = 3.
4. **c.** Seat W at the bottom facing up (towards the centre). Their right is east → X; their left is west → Z. Y sits at the top facing down.
5. **c.** Y faces down, so Y's right is west → Z.
</details>

## 8. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
