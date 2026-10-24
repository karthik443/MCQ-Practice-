# 03 – Time & Work (including Pipes & Cisterns)

> **One-line idea:** think in **"work per day"** (rate). Rates add when people work together, and the
> time taken = total work ÷ combined rate. The **LCM trick** turns fractions into whole numbers.

---

## 1. Foundations

### 1.1 Rate of work
If A finishes a job in `a` days, A's rate = **1/a of the job per day**.
Work done = rate × time. Job finished when work done = 1 (or the total units).

### 1.2 Two people together
`1/t = 1/a + 1/b  →  t = ab/(a + b)`
**Example:** A = 10 days, B = 15 days → t = 150/25 = **6 days**.

### 1.3 Finding the second person's time
If together take t days and A alone takes a days: `1/b = 1/t − 1/a`.
**Example:** together 8, A alone 12 → 1/8 − 1/12 = 1/24 → **B takes 24 days**.

### 1.4 The LCM (units) method – use this almost always
1. Take **total work = LCM of all the days** (call it units).
2. Each person's daily output = total units ÷ their days.
3. Add outputs for together-work. Days = total ÷ combined output.

**Example:** A = 12 days, B = 18 days. LCM = 36 units. A = 3/day, B = 2/day → together 5/day → 36/5 = **7.2 days**.

### 1.5 Efficiency
Efficiency ∝ 1/time. If A is **twice as efficient** as B, A takes **half** the time.
**Example:** A twice as efficient as B and together they finish in 12 days. Rates 2 : 1, combined 3 units/day → total 36 units. A alone = 36/2 = **18 days**, B alone = 36 days.

---

## 2. Patterns

### Pattern A – Together, one leaves/joins midway
**Example:** A (10 days) and B (15 days) start together; A leaves after 4 days. Total days?
- LCM 30: A = 3/day, B = 2/day. In 4 days: 5 × 4 = 20 units.
- Remaining 10 units by B at 2/day = 5 days. **Total = 9 days.**

### Pattern B – Alternate-day work
**Idea:** compute work for one full cycle (A day, B day), find how many cycles fit, handle the remainder.
**Example:** A (10 days) and B (15 days) work on alternate days starting with A.
- LCM 30: A = 3, B = 2 → 5 units per 2-day cycle. 30/5 = 6 cycles = **12 days**.
- *If it doesn't divide evenly*, the last partial cycle may finish early (A alone may complete the remainder in less than a full day).

### Pattern C – Work and wages
**Idea:** wages are divided in the ratio of **work done**, i.e., (rate × days worked).
**Example:** A (10 days) and B (15 days) finish a job together for ₹1,000. Rates 3:2 (from LCM units) → A gets ₹600, B gets ₹400.

### Pattern D – Men, days, hours (chain rule)
`(M1 × D1 × H1) / W1 = (M2 × D2 × H2) / W2`
**Example:** 10 men working 8 hours/day finish a job in 12 days. How many days will 15 men working 8 hours/day need?
Man-hours = 10 × 8 × 12 = 960. New rate = 15 × 8 = 120/day → **8 days**.
(Fewer days when more men – inverse proportion.)

### Pattern E – Pipes and cisterns (identical logic)
- Inlet pipe = positive work, outlet/leak = negative work.
- **Example:** A fills in 12 h, B fills in 15 h, C empties in 20 h. LCM 60: +5 + 4 − 3 = 6 units/h → 60/6 = **10 hours**.
- **Leak example:** a pipe alone fills the tank in 6 h, but a leak could empty a full tank in 8 h. Net rate = 1/6 − 1/8 = 1/24 → the tank fills in **24 h**.

### Pattern F – Group changes (more efficiency of a group)
`If m men and w women … ` → convert everything to a single unit (e.g., 1 woman = 2 men) and then use man-days.

---

## 3. Traps
1. Never add *times*; add *rates*.
2. A person who "leaves" at the end doesn't contribute to the last days – check who is working in which period.
3. In alternate-day problems, check whether the job ends during A's day or B's day.
4. "Fills tank in X hours **with** a leak" – leak is negative; the **net** rate is positive.

---

## 4. Practice MCQs

1. A finishes in 10 days, B in 15 days. Together?
   a) 5  b) 6  c) 7.5  d) 8
2. A and B together take 8 days; A alone 12 days. B alone?
   a) 20  b) 24  c) 18  d) 30
3. A pipe fills a tank in 6 h; a leak empties it in 8 h. Time to fill with leak?
   a) 12 h  b) 14 h  c) 24 h  d) 48 h
4. 12 men finish a job in 10 days. 15 men would take?
   a) 7  b) 8  c) 9  d) 12
5. A takes 20 days, B 30 days. A works 5 days alone, then B joins. Total days?
   a) 12  b) 13  c) 14  d) 15
6. A is twice as efficient as B. Together they take 12 days. A alone?
   a) 18  b) 24  c) 36  d) 20
7. A, B and C can do a job in 10, 15 and 30 days. All start; A leaves 2 days before the end. Total days?
   a) 4  b) 5  c) 6  d) 7
8. Two pipes fill a tank in 12 and 16 minutes. A third pipe empties it in 24 minutes. All opened together – time to fill?
   a) 9.6  b) 10.4  c) 12  d) 14.4
9. 6 men can do a job in 12 days. After 4 days, 6 more men join. Total days to complete?
   a) 6  b) 8  c) 9  d) 10
10. A can do a job in 20 days; B is 25% more efficient than A. B alone takes?
    a) 15  b) 16  c) 18  d) 25

<details><summary><b>Answers with solutions</b></summary>

1. **b.** 150/25 = 6.
2. **b.** 1/8 − 1/12 = 1/24.
3. **c.** 1/6 − 1/8 = 1/24.
4. **b.** 120 man-days ÷ 15.
5. **c.** A does 5/20 = 1/4 in 5 days. Remaining 3/4 at 1/20 + 1/30 = 1/12 per day → 9 days. Total 5 + 9 = 14.
6. **a.** 36 units, A = 2/day → 18 days.
7. **c.** LCM 30: A = 3, B = 2, C = 1 units/day. Let total days = t; A works t − 2 days: 3(t − 2) + 2t + t = 30 → 6t = 36 → t = 6. Check: 12 + 12 + 6 = 30 ✔.
8. **a.** LCM 48: 4 + 3 − 2 = 5/min → 48/5 = 9.6.
9. **b.** Total 6 × 12 = 72 man-days. First 4 days: 24 done. Remaining 48 by 12 men = 4 days. Total 4 + 4 = 8.
10. **b.** Efficiency 125% → time = 20/1.25 = 16.
</details>

## 5. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
