# 06 – Probability

> **One-line idea:** probability = (number of ways you *want*) ÷ (total number of equally likely ways).
> For anything with "at least one", compute the **complement** (the opposite case) and subtract from 1.

---

## 1. Foundations

### 1.1 Definition and range
`P(E) = favourable outcomes / total outcomes`, with 0 ≤ P ≤ 1.
- Impossible event: 0. Sure event: 1.
- **P(not E) = 1 − P(E).**

### 1.2 Combining events
- **Union (OR):** P(A ∪ B) = P(A) + P(B) − P(A ∩ B).
  If A and B are *mutually exclusive* (can't happen together), P(A ∩ B) = 0.
- **Intersection (AND), independent events:** P(A ∩ B) = P(A) × P(B).
  Independent = one outcome doesn't affect the other (coin tosses, drawing *with* replacement).
- **Conditional:** P(A | B) = P(A ∩ B) / P(B)  — "probability of A given that B has happened".

### 1.3 Standard sample spaces (memorise)
- **Coin:** n tosses → 2ⁿ outcomes. P(exactly k heads) = nCk / 2ⁿ.
- **Dice:** two dice → 36 outcomes. Number of ways to get sums 2…12: **1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1**.
  (Sum 7 is most likely: 6/36 = 1/6.)
- **Cards:** 52 cards, 4 suits (13 each), 26 red, 26 black, 12 face cards (J, Q, K), 4 aces.

---

## 2. Patterns

### Pattern A – Coins and dice
**Example 1:** P(at least one head in 3 tosses) = 1 − P(no head) = 1 − 1/8 = **7/8**.
**Example 2:** two dice, P(sum = 7) = 6/36 = **1/6**.
**Example 3:** two dice, P(sum ≥ 10) = (3 + 2 + 1)/36 = 6/36 = **1/6**.

### Pattern B – Drawing without replacement (two ways to compute)
**Example:** bag has 3 red, 5 blue. Two balls drawn without replacement.
- P(both red), *step method*: 3/8 × 2/7 = 6/56 = **3/28**.
- *Combination method*: 3C2 / 8C2 = 3/28. ✔
- P(one red, one blue) = (3C1 × 5C1)/8C2 = 15/28.

**With replacement** the probabilities don't change between draws: P(both red) = (3/8)² = 9/64.

### Pattern C – Cards
**Example:** two cards drawn without replacement; P(both aces) = 4/52 × 3/51 = 12/2652 = **1/221**.
P(one card is a heart) = 13/52 = 1/4. P(face card) = 12/52 = 3/13.

### Pattern D – Independent events
**Example:** P(A) = 0.4, P(B) = 0.5, independent.
P(A ∩ B) = 0.2; P(A ∪ B) = 0.4 + 0.5 − 0.2 = **0.7**; P(neither) = 0.6 × 0.5 = 0.3.

### Pattern E – Selecting a number from a range
**Example:** pick a number from 1 to 20, P(multiple of 3 or 5):
multiples of 3: 6, of 5: 4, of both (15): 1 → 6 + 4 − 1 = 9 → **9/20**.

### Pattern F – Conditional probability
**Example:** a family has two children, at least one is a girl. P(both girls)?
Sample space (given at least one girl): GG, GB, BG → 3 outcomes; favourable: GG → **1/3**.

### Pattern G – Bayes' theorem (defective items)
`P(A|B) = P(B|A)·P(A) / P(B)`.
**Example:** Machine A produces 60% of items (2% defective); Machine B produces 40% (5% defective). A defective item is found – P(it came from A)?
- Defective from A = 0.6 × 0.02 = 0.012; from B = 0.4 × 0.05 = 0.020. Total = 0.032.
- P(A | defective) = 0.012/0.032 = 12/32 = **3/8**.

### Pattern H – "At least one" (complement)
P(at least one success in n independent trials) = 1 − (P(failure))ⁿ.
**Example:** each of 3 shooters hits with probability 1/2 → P(at least one hit) = 1 − 1/8 = 7/8.

---

## 3. Traps
1. "With replacement" vs "without" – the denominator shrinks in the second case.
2. Don't multiply probabilities of mutually exclusive events; add them (OR) or they can't both happen (AND = 0).
3. "At least one" almost always means "1 − none".
4. Check that each outcome in your sample space is equally likely (sum of two dice is not equally likely, but the 36 ordered pairs are).

---

## 4. Practice MCQs

1. Two dice rolled. P(sum = 7)?
   a) 1/12  b) 1/6  c) 1/9  d) 5/36
2. Two cards drawn without replacement from 52. P(both aces)?
   a) 1/169  b) 1/221  c) 1/13  d) 2/221
3. P(at least one head) in 3 tosses?
   a) 1/8  b) 3/8  c) 7/8  d) 1/2
4. Bag: 3 red, 5 blue. Two drawn without replacement. P(both red)?
   a) 3/28  b) 9/64  c) 3/8  d) 1/4
5. P(A) = 0.4, P(B) = 0.5, independent. P(A ∪ B)?
   a) 0.9  b) 0.7  c) 0.2  d) 0.45
6. A number is chosen from 1–20. P(multiple of 3 or 5)?
   a) 9/20  b) 1/2  c) 2/5  d) 11/20
7. Machine A: 60% items, 2% defective. Machine B: 40%, 5% defective. A random item is defective. P(from A)?
   a) 3/8  b) 3/5  c) 5/8  d) 1/2
8. Three coins tossed. P(exactly two heads)?
   a) 1/8  b) 3/8  c) 1/2  d) 5/8
9. Bag: 3 red, 5 blue. Two balls drawn without replacement. P(one red and one blue)?
   a) 15/56  b) 15/28  c) 3/8  d) 5/8
10. A card is drawn from a pack. P(it's a king or a heart)?
    a) 4/13  b) 17/52  c) 15/52  d) 1/4

<details><summary><b>Answers with solutions</b></summary>

1. **b.** 6/36.
2. **b.** 4/52 × 3/51 = 1/221.
3. **c.** 1 − 1/8.
4. **a.** 3/8 × 2/7 = 6/56 = 3/28.
5. **b.** 0.4 + 0.5 − 0.2.
6. **a.** 6 + 4 − 1 = 9 of 20.
7. **a.** 0.012/0.032 = 3/8.
8. **b.** 3C2/8 = 3/8.
9. **b.** (3 × 5)/28 = 15/28.
10. **a.** King (4) + hearts (13) − king of hearts (1) = 16/52 = 4/13.
</details>

## 5. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
