# 11 – Misc Reasoning & Number System (Series, Directions, Blood Relations, Clocks, Calendars)

> **One-line idea:** these are "small topics, big wins" — each has a handful of rules, and a question takes
> under 30 seconds once you know the rule.

---

## 1. Number series

### 1.1 Check in this order
1. **Constant difference** (AP): 3, 7, 11, 15 → +4.
2. **Differences themselves form a pattern**: 2, 6, 12, 20, 30 → +4, +6, +8, +10 → next = 30 + 12 = **42**. (Also n(n+1).)
3. **Constant ratio** (GP): 2, 6, 18, 54 → ×3.
4. **×n ± k pattern**: 3, 7, 15, 31 → ×2 + 1.
5. **Squares / cubes ± something**: 2, 5, 10, 17, 26 → n² + 1. 3, 6, 11, 18, 27 → n² + 2, next = 6² + 2 = **38**.
6. **Fibonacci type** (each term = sum of the previous two): 1, 1, 2, 3, 5, 8 → next **13**.
7. **Alternating series**: odd positions follow one rule, even positions another (e.g., 2, 5, 4, 10, 6, 20…).
8. **Prime numbers**: 2, 3, 5, 7, 11, 13 …
9. **Missing letters (alphabet series)**: convert letters to positions (A = 1 … Z = 26).

### 1.2 Tip
Compute the first-level differences, then second-level differences; if the second level is constant, it's a quadratic sequence.

---

## 2. Directions & distances

- Treat the starting point as (0, 0): North = +y, East = +x, South = −y, West = −x.
- Right turn when facing North → East; right turn when facing East → South, etc. (clockwise order: N → E → S → W).
- Final distance = √(Δx² + Δy²). Use Pythagorean triples: **3-4-5, 5-12-13, 8-15-17, 7-24-25**.
- Final direction: compare Δx and Δy signs (e.g., Δx > 0, Δy > 0 → North-East of the start).

**Example 1:** A walks 3 km north, then 4 km east. Displacement = √(9 + 16) = **5 km**, direction North-East.
**Example 2:** A walks 5 km north, 12 km east → **13 km**.
**Example 3:** A walks 10 m north, turns right and walks 6 m, turns right again and walks 10 m. He is now 6 m **east** of the start (the two 10 m legs cancel) and facing south.

---

## 3. Blood relations

### 3.1 Method
1. Draw a family tree with generations as levels.
2. Use symbols: □ male, ○ female, = for spouse, | for child.
3. Translate each statement step by step; **never skip a step**.

### 3.2 Vocabulary
| Phrase | Relation |
|---|---|
| Mother's brother | Maternal uncle |
| Father's sister | Paternal aunt |
| Mother's mother | Maternal grandmother |
| Son of my uncle | Cousin |
| Wife of my brother | Sister-in-law |
| Brother of my wife | Brother-in-law |
| Father's only son | Myself or brother |

### 3.3 Worked example
"Pointing to a man, a woman says, *He is the son of my mother's only brother*."
Mother's only brother = maternal uncle → his son = **cousin**.

### 3.4 Caution
If the gender of a person isn't stated, the answer may be "cannot be determined".

---

## 4. Clocks

- **Minute hand** moves 6° per minute; **hour hand** moves 0.5° per minute (30° per hour).
- **Angle at h : m** = |30h − 5.5m| (take 360 minus the result if it is more than 180°).
- Hands **coincide** 11 times in 12 hours (22 in a day); **right angle** 22 times in 12 hours (44 in a day); **opposite** 11 times in 12 hours.
- A clock gains/loses minutes → true time = shown time adjusted by the rate.

**Example:** angle at 3:30. Hour hand at 3 × 30 + 15 = 105°, minute hand at 180° → **75°**. (Formula: |90 − 165| = 75.)

---

## 5. Calendars

- **Odd days** = days left over after dividing by 7. Ordinary year (365 days) → 1 odd day. Leap year (366) → 2 odd days.
- Odd days in centuries: 100 years = 5, 200 years = 3, 300 years = 1, 400 years = 0.
- Leap year: divisible by 4; for century years, divisible by 400 (1900 is not leap, 2000 is).
- Day mapping: Sunday = 0, Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6.

**Example 1:** 1 Jan 2001 was Monday. 1 Jan 2002 → 2001 is ordinary → +1 → **Tuesday**.
**Example 2:** today is Saturday; the day after 61 days → 61 mod 7 = 5 → Saturday + 5 = **Thursday**.

---

## 6. Number system quick facts

### 6.1 Divisibility
- 2: last digit even. 3: digit sum divisible by 3. 4: last two digits. 5: last digit 0/5. 6: both 2 & 3. 8: last three digits. 9: digit sum divisible by 9. 11: (sum of odd-place digits) − (sum of even-place digits) divisible by 11.

### 6.2 Unit digit cycles
| Last digit of base | Cycle of unit digits |
|---|---|
| 2 | 2, 4, 8, 6 |
| 3 | 3, 9, 7, 1 |
| 4 | 4, 6 |
| 7 | 7, 9, 3, 1 |
| 8 | 8, 4, 2, 6 |
| 9 | 9, 1 |
| 0, 1, 5, 6 | the same digit |

**Example:** unit digit of 7¹²³ — cycle length 4; 123 mod 4 = 3 → 3rd term of (7, 9, 3, 1) = **3**.

### 6.3 Factors and HCF/LCM
- Number of factors of N = p^a · q^b is (a + 1)(b + 1). **72 = 2³ · 3²** → 4 × 3 = **12 factors**.
- **HCF × LCM = product of the two numbers.**
  Example: HCF 6, LCM 180, one number 30 → other = (6 × 180)/30 = **36**.

### 6.4 Remainders
- Remainder of a product = product of the remainders (reduced).
- Example: 2¹⁰ mod 7: since 2³ = 8 ≡ 1 (mod 7), 2¹⁰ = (2³)³ · 2 ≡ 2 → **2**.

---

## 7. Traps
1. In series, don't stop at the first-level difference.
2. In directions, mark left/right relative to the **current facing**, not the start.
3. In blood relations, don't assume the gender.
4. In clock problems, convert hours to degrees correctly (30° per hour, plus 0.5° per minute).
5. In calendar problems, 1900 is not a leap year.

---

## 8. Practice MCQs

1. Next term: 2, 6, 12, 20, 30, ?
   a) 40  b) 42  c) 44  d) 36
2. Next term: 1, 1, 2, 3, 5, 8, ?
   a) 11  b) 12  c) 13  d) 15
3. A walks 3 km north, then 4 km east. Distance from start?
   a) 5 km  b) 7 km  c) 6 km  d) 4 km
4. Pointing to a man, a woman says "He is the son of my mother's only brother." The man is her ___?
   a) Brother  b) Cousin  c) Uncle  d) Nephew
5. Angle between the hands at 3:30?
   a) 60°  b) 75°  c) 90°  d) 105°
6. Unit digit of 7¹²³?
   a) 7  b) 9  c) 3  d) 1
7. Number of factors of 72?
   a) 8  b) 10  c) 12  d) 14
8. Next term: 3, 6, 11, 18, 27, ?
   a) 36  b) 38  c) 40  d) 42
9. 1 Jan 2001 was Monday. What day was 1 Jan 2003?
   a) Tuesday  b) Wednesday  c) Thursday  d) Friday
10. Angle between the hands at 6:00?
    a) 90°  b) 120°  c) 180°  d) 0°

<details><summary><b>Answers with solutions</b></summary>

1. **b.** n(n+1): 5 × 6 = 30, next 6 × 7 = 42.
2. **c.** 5 + 8 = 13.
3. **a.** √(9 + 16) = 5.
4. **b.** Maternal uncle's son = cousin.
5. **b.** |30·3 − 5.5·30| = |90 − 165| = 75.
6. **c.** 123 mod 4 = 3 → 3.
7. **c.** 2³·3² → 4 × 3 = 12.
8. **b.** n² + 2 pattern (differences 3, 5, 7, 9, 11) → 36 + 2 = 38.
9. **b.** Two ordinary years (2001, 2002) → +2 odd days → Monday + 2 = Wednesday.
10. **c.** |180 − 0| = 180°.
</details>

## 9. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
