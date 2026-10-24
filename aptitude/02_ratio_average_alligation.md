# 02 – Ratio, Proportion, Average, Mixtures & Alligation

> **One-line idea:** a ratio is a *comparison*, an average is an *equal share*, and alligation is a shortcut
> for *weighted averages of two groups*. They are the same topic wearing different clothes.

---

## 1. Ratio & Proportion

### 1.1 Basics
- Ratio a:b = a/b. Multiplying or dividing both terms by the same number keeps it unchanged.
- Proportion: a:b = c:d ⇔ **a × d = b × c** (cross-multiplication).
- Compound ratio of a:b and c:d = ac : bd.

### 1.2 Dividing a quantity in a ratio
Add the ratio parts → each part = Total / sum → multiply by each term.
**Example:** divide ₹780 in 2:3:7. Parts = 12, one part = 65 → ₹130, ₹195, ₹455.

### 1.3 Combining two ratios into one (three-term ratio)
**Idea:** make the *common* quantity equal in both ratios using LCM.
**Example:** a:b = 2:3 and b:c = 4:5.
- b is 3 in the first and 4 in the second → LCM = 12.
- First ratio ×4 → 8:12. Second ratio ×3 → 12:15.
- So **a:b:c = 8:12:15**.

### 1.4 Ratio after adding/removing a quantity
**Idea:** the quantity that doesn't change is the anchor.
**Example:** a 40 L mixture of milk:water = 3:1. How much water to add to make 1:1?
- Milk = 30 L (unchanged), water = 10 L. For 1:1 water must be 30 → add **20 L**.

### 1.5 Ratio of ages / fixed-difference problems
Use variables as 2x, 3x … and apply "after t years" to each term separately (see file 07).

---

## 2. Averages

### 2.1 Core ideas
- Average = Sum ÷ Number of items. Therefore **Sum = Average × Number**.
- Average of the first n natural numbers = (n + 1)/2. Sum = n(n+1)/2.
- Average of an AP = (first + last)/2.

### 2.2 Changing one member
**Idea:** the whole change in the *sum* equals (new avg − old avg) × n.
**Example 1 (removal):** average of 5 numbers is 20 → sum 100. After removing one, avg of 4 is 18 → sum 72. Removed number = **28**.
**Example 2 (replacement):** 10 persons, avg age rises by 2 when a 50-year-old is replaced by a new person. Total age rises by 2 × 10 = 20 → new person is **70**.

### 2.3 Weighted average
`(n1·a1 + n2·a2) / (n1 + n2)`
**Example:** class A has 30 students with average 60, class B has 20 with average 70.
(1800 + 1400)/50 = **64**.

### 2.4 Overlapping groups
**Example:** avg of 11 numbers = 50. avg of first 6 = 49, last 6 = 52. The 6th is counted in both groups:
6th = (6 × 49 + 6 × 52) − 11 × 50 = 294 + 312 − 550 = **56**.

### 2.5 Median and mode
- Median: sort, take the middle (average the two middle ones if count is even).
- Mode: most frequent value.
- Relation (moderately skewed data): Mode ≈ 3·Median − 2·Mean.

---

## 3. Mixtures & Alligation

### 3.1 What alligation does
When two items with values/prices/concentrations **cheaper (c)** and **dearer (d)** are mixed to give a **mean (m)**:

```
cheaper c         dearer d
        \         /
          mean m
        /         \
   (d − m)       (m − c)
```
**Ratio of quantities cheaper : dearer = (d − m) : (m − c).**

*Why it works:* the total "excess above c" of the dearer part must balance the "shortfall below d" of the cheaper part.

**Example:** rice ₹20/kg and ₹30/kg mixed to get ₹24/kg.
Cheaper : dearer = (30 − 24) : (24 − 20) = 6 : 4 = **3 : 2**.

### 3.2 Concentration version
Same table works for percentages of milk/alcohol/salt in solutions.
**Example:** mix 30% and 50% solutions to get 40%: ratio = (50−40):(40−30) = 1:1.

### 3.3 Replacement (repeated removal)
Container with V litres of pure liquid. Remove x litres and replace with water, repeat n times.
`Pure liquid left = V × (1 − x/V)^n`.
**Example:** 40 L milk, remove 4 L and replace with water, do it twice.
Milk left = 40 × (0.9)² = **32.4 L**.

### 3.4 Profit using mixing
Mean price is the cost price of the mixture; sell price decides the profit%.

---

## 4. Traps
1. In ratio-combining, the middle term must be equalised – not the first.
2. In average problems, count the items correctly (a number counted in two groups).
3. In alligation, put the **mean in the middle** and subtract *diagonally*. Always check the answer is positive.
4. Don't use the replacement formula for "add" operations – only for remove-and-replace.

---

## 5. Practice MCQs

1. Divide ₹780 in ratio 2:3:7. Largest share?
   a) 455  b) 390  c) 260  d) 325
2. Average of 5 numbers is 20. One is removed and the average becomes 18. The removed number?
   a) 24  b) 26  c) 28  d) 30
3. Rice at ₹20/kg is mixed with rice at ₹30/kg to get ₹24/kg. Ratio (cheaper : dearer)?
   a) 2:3  b) 3:2  c) 1:2  d) 3:1
4. 40 L milk-water mixture has ratio 3:1. How much water to add to make it 1:1?
   a) 10 L  b) 20 L  c) 30 L  d) 15 L
5. If a:b = 2:3 and b:c = 4:5, then a:b:c =
   a) 2:3:5  b) 8:12:15  c) 6:9:10  d) 4:6:5
6. Average of 11 numbers is 50; first 6 avg 49; last 6 avg 52. The 6th number is?
   a) 56  b) 52  c) 60  d) 48
7. Avg weight of 8 persons rises by 2.5 kg when a person of 65 kg is replaced. Weight of new person?
   a) 75  b) 80  c) 85  d) 90
8. Mix 3 L of 20% acid solution with 2 L of 45% acid solution. Concentration of mixture?
   a) 30%  b) 32%  c) 35%  d) 28%
9. Ages of A and B are in the ratio 3:5. After 6 years the ratio becomes 2:3. Present age of A?
   a) 12  b) 18  c) 24  d) 9
10. Average of first 20 natural numbers?
    a) 10  b) 10.5  c) 11  d) 20.5

<details><summary><b>Answers with solutions</b></summary>

1. **a.** 780/12 = 65; 7 × 65 = 455.
2. **c.** 100 − 72 = 28.
3. **b.** (30−24):(24−20) = 6:4.
4. **b.** Milk 30, water 10 → water must become 30.
5. **b.** LCM of 3 and 4 = 12.
6. **a.** 294 + 312 − 550 = 56.
7. **c.** Rise in total = 2.5 × 8 = 20 → new = 65 + 20 = 85.
8. **a.** (3 × 20 + 2 × 45)/5 = (60 + 90)/5 = 30%.
9. **b.** (3x + 6)/(5x + 6) = 2/3 → 9x + 18 = 10x + 12 → x = 6 → A = 18.
10. **b.** (20 + 1)/2 = 10.5.
</details>

## 6. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
