# 01 – Percentages

> **One-line idea:** "percent" means "per hundred". Almost every percentage problem becomes easy if you
> **assume a convenient base (usually 100)** and track what happens to it.

---

## 1. Foundations

### 1.1 What a percentage really is
`x% of y = (x/100) × y`. It is just a fraction with denominator 100.
A useful symmetry: **x% of y = y% of x** (e.g., 8% of 50 = 50% of 8 = 4). Use it to pick the easier direction.

### 1.2 Converting between fraction ↔ percent (memorise)
| Fraction | % | Fraction | % |
|---|---|---|---|
| 1/2 | 50 | 1/8 | 12.5 |
| 1/3 | 33.33 | 1/9 | 11.11 |
| 1/4 | 25 | 1/10 | 10 |
| 1/5 | 20 | 1/11 | 9.09 |
| 1/6 | 16.67 | 1/12 | 8.33 |
| 1/7 | 14.28 | 1/16 | 6.25 |

Why it matters: "a number increased by 12.5%" instantly means "multiply by 9/8".

### 1.3 The multiplier method (the single most useful trick)
- Increase by a% → multiply by **(1 + a/100)**. (Up 20% → ×1.2)
- Decrease by a% → multiply by **(1 − a/100)**. (Down 20% → ×0.8)

Final value = Original × multiplier(s). To find the *percentage change* afterwards: `(final − original)/original × 100`.

---

## 2. Concepts & Patterns

### Pattern A – Successive percentage changes
**Idea:** the second change applies to the *new* value, not the original, so percentages do **not** simply add.

**Formula:** net % change = `a + b + (a·b)/100` (use negative numbers for decreases).

**Worked example:** a price rises 20% then falls 20%.
- Assume price = 200. After +20% → 240. After −20% of 240 (= 48) → 192.
- Net change = (192 − 200)/200 = **−4%**.
- By formula: 20 + (−20) + (20 × −20)/100 = −4. ✔

**Trap:** "up 20 then down 20 = no change" is wrong. Any equal up-then-down results in a *loss*.

### Pattern B – "A is more than B" vs "B is less than A"
**Idea:** the base changes, so the percentages are different.

- A is a% more than B → B is `a/(100+a) × 100 %` less than A.
- A is a% less than B → B is `a/(100−a) × 100 %` more than A.

**Worked example:** A's salary is 25% more than B's.
- Take B = 100 → A = 125.
- B is 25 less than A, and the base is A (125): 25/125 = **20% less**.

### Pattern C – Price rises, consumption must fall (expenditure constant)
**Idea:** expenditure = price × quantity. To keep it constant, quantity must fall by the "reciprocal" amount.

- Price up by a% → cut consumption by `a/(100+a) × 100 %`.
- Price down by a% → increase consumption by `a/(100−a) × 100 %`.

**Worked example:** sugar price rises 25%. Old price 100, quantity 1 → expenditure 100. New price 125, so quantity must be 100/125 = 0.8 → **cut of 20%**.

### Pattern D – Area/volume when lengths change
**Idea:** area depends on length², so a change in length is applied twice.

- Side/radius up by r% → area up by `2r + r²/100 %`.
- Rectangle with length up a%, breadth up b% → area up by `a + b + ab/100 %` (same as successive change).

**Worked example:** side of a square +10%. Area = 1.1 × 1.1 = 1.21 → **+21%**.

### Pattern E – Pass/fail marks
**Idea:** "pass mark" is a fixed number. Equate it from both sides.

`pass% × Total = marks obtained + marks short`  (or `− marks by which he passed`)

**Worked example:** pass mark is 40%; a student scores 130 and fails by 30.
- Pass mark = 130 + 30 = 160. 0.4 × T = 160 → **T = 400**.

### Pattern F – Chain percentages
**Idea:** convert each percentage to a decimal and multiply along the chain.

**Worked example:** x is 20% of y; y is 50% of z → x = 0.2 × 0.5 × z = 0.1z → **10% of z**.

### Pattern G – Population / depreciation (compounding)
**Idea:** repeated growth is a repeated multiplier.

- Grows r% per year for n years: `P × (1 + r/100)^n`.
- Depreciates r% per year: `P × (1 − r/100)^n`.

**Worked example:** 10,000 population, +10%/yr, 2 years → 10,000 × 1.1 × 1.1 = **12,100**.

### Pattern H – Elections / votes
**Idea:** work in the order: total → valid → each candidate → margin.

**Worked example:** 10,000 votes, 20% invalid, winner got 55% of valid votes.
- Valid = 8,000. Winner = 4,400, loser = 3,600. **Margin = 800.**

---

## 3. Common traps (read before every test)
1. Percent change is always relative to the **original** (the "from" value).
2. "% points" vs "%": going from 20% to 25% is +5 percentage points but **+25 %**.
3. In "A is more than B" questions, check which one is the base in the question's last line.
4. Don't add successive percentages; multiply multipliers.

---

## 4. Practice MCQs (try in ≤ 1 min each)

1. A price rises 20% then falls 20%. Net change?
   a) 0  b) −4%  c) +4%  d) −2%
2. A's salary is 25% more than B's. B's salary is what % less than A's?
   a) 25%  b) 20%  c) 16.67%  d) 33.33%
3. A population of 10,000 grows 10% per year. After 2 years it is?
   a) 12,000  b) 12,100  c) 11,000  d) 12,200
4. A student needs 40% to pass, gets 130 marks and fails by 30. Maximum marks?
   a) 350  b) 400  c) 450  d) 500
5. Side of a square increases by 10%. Area increases by?
   a) 10%  b) 20%  c) 21%  d) 22%
6. x is 20% of y and y is 50% of z. x is what % of z?
   a) 10%  b) 15%  c) 25%  d) 70%
7. Sugar price rises 25%. By what % should consumption fall so expenditure stays same?
   a) 25%  b) 20%  c) 15%  d) 30%
8. In an exam, 30% fail in Maths, 20% fail in English and 10% fail in both. What % pass both?
   a) 50%  b) 60%  c) 70%  d) 40%
9. A number is increased by 20% and then decreased by 20%; the result is 960. Original number?
   a) 1,000  b) 1,050  c) 1,000.5  d) 960
10. The length of a rectangle is increased by 20% and the breadth decreased by 20%. Change in area?
    a) 0  b) −4%  c) +4%  d) −2%

<details><summary><b>Answers with solutions</b></summary>

1. **b.** 1.2 × 0.8 = 0.96 → −4%.
2. **b.** B = 100, A = 125 → 25/125 = 20%.
3. **b.** 10,000 × 1.21 = 12,100.
4. **b.** Pass mark = 160 = 0.4T → T = 400.
5. **c.** 1.1² = 1.21.
6. **a.** 0.2 × 0.5 = 0.1.
7. **b.** 25/125 = 20%.
8. **b.** Fail in at least one = 30 + 20 − 10 = 40% → pass both = 60%.
9. **a.** Result = 0.96 × N = 960 → N = 1,000.
10. **b.** 1.2 × 0.8 = 0.96 → −4%.
</details>

## 5. Mistakes box (fill after practice)
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
