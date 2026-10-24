# 12 – Calendar & Clocks (Angles, Time-at-Angle, Mirror Image, Day-of-Date)

> **One-line idea:** both topics are *cyclic*. A calendar cycles every 7 days (so we only keep the
> **remainder after dividing by 7**), and a clock hand cycles every 360° (so we only keep the **angle
> between the hands**). Learn the two or three base facts and everything else is substitution.

---

# PART A – CLOCKS

## A.1 Base facts (derive everything from these)

| Fact | Value | Why |
|---|---|---|
| Minute hand speed | **6° per minute** | 360° in 60 min |
| Hour hand speed | **0.5° per minute** (30° per hour) | 360° in 12 h |
| Relative speed of minute hand over hour hand | **5.5° per minute** | 6 − 0.5 |
| Minute hand moves 12× faster than hour hand | | 6 ÷ 0.5 |
| Each minute mark | 6° apart | 360/60 |
| Each hour mark | 30° apart | 360/12 |

## A.2 Angle between the hands at h : m

**Position of each hand measured clockwise from 12:**
- Hour hand = **30h + 0.5m** degrees
- Minute hand = **6m** degrees

**Angle = |30h − 5.5m|**. If the result is greater than 180°, subtract it from 360° (the question wants the smaller angle unless it says "reflex").

### Worked examples
| Time | Hour hand | Minute hand | Difference | Answer |
|---|---|---|---|---|
| 3:30 | 90 + 15 = 105° | 180° | 75° | **75°** |
| 9:15 | 270 + 7.5 = 277.5° | 90° | 187.5° → 360 − 187.5 | **172.5°** |
| 7:20 | 210 + 10 = 220° | 120° | 100° | **100°** |
| 12:20 | 0 + 10 = 10° | 120° | 110° | **110°** |
| 6:00 | 180° | 0° | 180° | **180°** |
| 3:00 | 90° | 0° | 90° | **90°** |

> Treat 12 as 0 in the formula (so at 12:20, h = 0).

### Fast mental trick
Angle at h:m = |30h − 5.5m|. For whole-minute times that are multiples of 10, 5.5m is easy:
m = 10 → 55, m = 20 → 110, m = 30 → 165, m = 40 → 220, m = 50 → 275.

---

## A.3 Time when the hands make a given angle (the "time at angle" type)

**Problem form:** "At what time between *h* and *h+1* o'clock will the hands be at angle θ?"

**Derivation:** at *m* minutes past h, the minute hand is at 6m and the hour hand at 30h + 0.5m.
Set the difference equal to ±θ:

```
5.5 m − 30h = ± θ
        m = (30h ± θ) / 5.5  =  2(30h ± θ) / 11    (minutes past h)
```
Accept only the answers with **0 ≤ m < 60** (these may give 0, 1 or 2 valid times).

### A.3.1 Hands coincide (θ = 0)
`m = 60h / 11` minutes past h.

| Between | Minutes past h | Time |
|---|---|---|
| 12 and 1 | 0 | 12:00 |
| 1 and 2 | 5 5/11 | 1:05 5/11 |
| 2 and 3 | 10 10/11 | 2:10 10/11 |
| 3 and 4 | 16 4/11 | 3:16 4/11 |
| 4 and 5 | 21 9/11 | 4:21 9/11 |
| 5 and 6 | 27 3/11 | 5:27 3/11 |
| 6 and 7 | 32 8/11 | 6:32 8/11 |
| 7 and 8 | 38 2/11 | 7:38 2/11 |
| 8 and 9 | 43 7/11 | 8:43 7/11 |
| 9 and 10 | 49 1/11 | 9:49 1/11 |
| 10 and 11 | 54 6/11 | 10:54 6/11 |
| 11 and 12 | 60 → | 12:00 |

Successive coincidences are **720/11 = 65 5/11 minutes** apart.

### A.3.2 Hands opposite / in a straight line (θ = 180°)
`m = (30h ± 180)/5.5` → keep the value in [0, 60).
- **Between 3 and 4:** (90 + 180)/5.5 = 270/5.5 = **49 1/11** → 3:49 1/11.
- **Between 7 and 8:** (210 − 180)/5.5 = 30/5.5 = **5 5/11** → 7:05 5/11.
  (The "+" option gives 390/5.5 = 70.9, which is more than 60 → rejected.)

### A.3.3 Hands at right angle (θ = 90°)
Both signs usually work, giving two times in each hour.
- **Between 4 and 5:** (120 − 90)/5.5 = 5 5/11 and (120 + 90)/5.5 = 38 2/11 → **4:05 5/11 and 4:38 2/11**.
- **Between 3 and 4:** (90 − 90)/5.5 = 0 → exactly **3:00**, and (90 + 90)/5.5 = 32 8/11 → 3:32 8/11.

### A.3.4 Hands at any other angle (e.g., 30°, 60°, 120°)
Same formula. Example: between 5 and 6, angle 60°:
(150 − 60)/5.5 = 16 4/11 and (150 + 60)/5.5 = 38 2/11 → **5:16 4/11 and 5:38 2/11**.

### A.3.5 "After how many minutes from now?" type
Use relative motion: the minute hand gains 5.5° per minute on the hour hand.
**Example:** at 4:00 the minute hand is 120° behind the hour hand. To coincide it must gain 120° → 120/5.5 = **21 9/11 minutes**.

---

## A.4 Counting how often things happen

| Event | In 12 hours | In 24 hours |
|---|---|---|
| Hands coincide | **11** | **22** |
| Hands opposite (180°) | **11** | **22** |
| Hands at right angle (90°) | **22** | **44** |
| Hands at any given angle θ (0 < θ < 180) | 22 | 44 |

**Why 11, not 12?** Between 11 and 1 only one coincidence occurs (at 12:00), so 12 hours give 11.

---

## A.5 Mirror image & water image

- **Mirror image of time T** (a clock held in front of a mirror) = **11:60 − T**.
  Example: 3:20 → 11:60 − 3:20 = **8:40**. Example: 4:10 → 7:50.
- On the hour it simplifies to 12:00 − T. Example: 3:00 → 9:00; 6:00 → 6:00 (11:60 − 6:00 = 5:60 = 6:00).
- **Water image** (reflection in water, i.e., flipped top-to-bottom) = **5:60 − T**; if the result is negative, add 12 hours.
  Example: 4:20 → 5:60 − 4:20 = 1:40. Example: 3:00 → 3:00 (the 3 o'clock position doesn't move when flipped vertically).

---

## A.6 Faulty clocks (gain/loss)

**Method:** a correct clock's hands coincide every 720/11 = 65 5/11 minutes **of its own time**.
If a clock's hands coincide every *x* **true** minutes, the faulty clock is showing 65 5/11 of its own minutes in *x* true minutes:
- x < 65 5/11 → the clock runs **fast** (gains).
- x > 65 5/11 → the clock runs **slow** (loses).

**Example:** the hands of a clock coincide every 65 minutes (true time). A correct clock needs 65 5/11 min. So the faulty clock shows 65 5/11 minutes in only 65 true minutes → **it gains** 5/11 min per 65 true minutes.
Gain in 24 h = (5/11)/65 × 1440 = 7200/715 = **10 10/143 minutes**.

> Quick rule: **if hands meet every 65 min (< 65 5/11) the clock is fast; if every 66 min (> 65 5/11) it is slow.**

**Other gain/loss problems:** "A clock gains 2 minutes per hour; it is set correct at 6 AM; what does it show at 6 PM?" → 12 h × 2 = 24 min gained → shows 6:24 PM when the true time is 6:00 PM.

---

# PART B – CALENDAR

## B.1 Vocabulary
- **Odd days** = remainder when the number of days is divided by 7.
- Map days to numbers: **Sun = 0, Mon = 1, Tue = 2, Wed = 3, Thu = 4, Fri = 5, Sat = 6**.
  The day of the week is `(known day + odd days) mod 7`.

## B.2 Leap year rules
- Divisible by 4 → leap year (2024 ✔, 2023 ✘).
- **Century years** (1700, 1800, 1900, 2100) are leap years only if divisible by **400**.
  → 1900 ✘, 2000 ✔, 2100 ✘.
- Leap year has 366 days = 52 weeks + **2 odd days**; ordinary year has 365 = 52 weeks + **1 odd day**.

## B.3 Odd days table (memorise)

**Years**
| Period | Odd days |
|---|---|
| Ordinary year | 1 |
| Leap year | 2 |
| 100 years | **5** (76 ordinary + 24 leap = 76 + 48 = 124 = 17 weeks + 5) |
| 200 years | **3** |
| 300 years | **1** |
| 400 years | **0** (calendar repeats every 400 years) |

**Months (ordinary year)**
| Month | Days | Odd days | | Month | Days | Odd days |
|---|---|---|---|---|---|---|
| Jan | 31 | 3 | | Jul | 31 | 3 |
| Feb | 28 (29) | 0 (1) | | Aug | 31 | 3 |
| Mar | 31 | 3 | | Sep | 30 | 2 |
| Apr | 30 | 2 | | Oct | 31 | 3 |
| May | 31 | 3 | | Nov | 30 | 2 |
| Jun | 30 | 2 | | Dec | 31 | 3 |

## B.4 Finding the day of any date – step by step

1. Count the **completed years** before the year in question (year − 1) and split: centuries + remaining years.
2. Odd days from centuries (use the table above; 1600 = 0, 1700 → 5, 1800 → 3, 1900 → 1, 2000 → 0 …).
3. Odd days from remaining years = (number of years) + (number of leap years among them), then mod 7.
4. Add the days from 1 Jan up to the given date (count months using days, add the date), then mod 7.
5. Add all odd days and mod 7 → map to the weekday (0 = Sunday).

### Worked example 1 – 15 August 1947
- Completed years = 1946 = 1900 + 46.
- 1900 years → 1600 (0) + 300 (1) = **1** odd day.
- 46 years: 11 leap years (4, 8, …, 44) → 46 + 11 = 57 → 57 mod 7 = **1**.
- Days up to 15 Aug 1947: Jan–Jul = 31 + 28 + 31 + 30 + 31 + 30 + 31 = 212; + 15 = 227 → 227 mod 7 = **3**.
- Total = 1 + 1 + 3 = 5 → **Friday**. ✔

### Worked example 2 – 26 January 1950
- 1949 = 1900 + 49 → 1 odd day; 49 years has 12 leap years → 49 + 12 = 61 → 61 mod 7 = 5.
- 26 days → 26 mod 7 = 5.
- Total = 1 + 5 + 5 = 11 mod 7 = 4 → **Thursday**. ✔

## B.5 Shortcuts you will use more often

### B.5.1 Day shift between two dates
Count the days between them, mod 7, then add (or subtract) from the known day.
**Example:** 5 March 2023 was a Sunday. Day on 5 January 2023?
Jan 5 → Feb 5 = 31 days; Feb 5 → Mar 5 = 28 days; total 59 → 59 mod 7 = 3 → Sunday − 3 = **Thursday**.

### B.5.2 Same date, next year
Day moves forward by **1** if there is no 29 Feb in between, by **2** if there is.
**Example:** 1 Jan 2001 was Monday → 1 Jan 2002 Tuesday; 1 Jan 2005 → +1 +1 +1 +2 (2004 is leap) = +5 → **Saturday**.

### B.5.3 Day after N days
Compute N mod 7 and move forward by that.
**Example:** today is Saturday, what day after 61 days? 61 mod 7 = 5 → Saturday + 5 = **Thursday**.

### B.5.4 Counting weekdays in a month
- A 28-day month has exactly four of each weekday.
- Extra days (29th, 30th, 31st) have **5 occurrences** each.
- 31-day month starting on Wednesday → Wed, Thu, Fri occur five times; the 31st is a Friday and the next month begins on **Saturday**.
- Leap-year February starting on a Thursday: Thursdays on 1, 8, 15, 22, 29 → 5 Thursdays.

### B.5.5 Calendar repeat (same calendar in a different year)
Add the odd days of each year in sequence; the calendar repeats when the sum is a multiple of 7 (with the same leap status).
- **2017 → 2023:** 1 + 1 + 1 + 2 + 1 + 1 = 7 ✔ (2017 and 2023 are both ordinary years starting on a Sunday).
- For leap years the repeat gap is usually **28 years** (e.g., 1996 and 2024).
- Ordinary-year repeat gap is typically 6, 11, or 12 years.

### B.5.6 Number of Sundays in a year
52 weeks → 52 Sundays, plus 1 extra day (ordinary) or 2 (leap). Chance of a 53rd Sunday: ordinary year 1/7, leap year 2/7.

### B.5.7 Age and date problems
"Born on 29 Feb 2000 – how many birthdays by 2024?" Count how many 29 Febs exist: 2000, 2004, …, 2024 = 7. (Be careful with 1900/2100.)

---

## Traps (clocks)
1. Using 12 as 12 in the formula instead of 0 – then 12:20 gives a wrong angle.
2. Forgetting the **smaller** angle rule (answer > 180° must be subtracted from 360°).
3. Forgetting that the hour hand moves between hour marks (the 0.5°/min term).
4. In time-at-angle questions, **discard m ≥ 60** and keep both roots otherwise.
5. Mirror image: it's **11:60 − T** (not 12:00 − T) unless the time is exactly on the hour.

## Traps (calendar)
1. Counting the **current** year in the completed years.
2. Treating 1900 or 2100 as a leap year.
3. Forgetting that 29 Feb must lie *between* the two dates for the +2 shift.
4. Forgetting the 400-year reset: 2000 counts as 0 odd days for the 400-year block.

---

## Practice MCQs – Clocks

1. Angle between the hands at 9:15?
   a) 172.5°  b) 187.5°  c) 180°  d) 165°
2. Angle between the hands at 7:20?
   a) 90°  b) 100°  c) 110°  d) 120°
3. At what time between 4 and 5 do the hands coincide?
   a) 4:20  b) 4:21 9/11  c) 4:22  d) 4:24
4. At what times between 4 and 5 are the hands at right angles?
   a) 4:05 5/11 and 4:38 2/11  b) 4:10 and 4:40  c) 4:15 and 4:45  d) 4:00 and 4:30
5. Between 3 and 4, when are the hands opposite each other?
   a) 3:45  b) 3:49 1/11  c) 3:50  d) 3:48 2/11
6. Mirror image of 3:20 is?
   a) 8:40  b) 9:40  c) 8:20  d) 9:20
7. How many times do the hands coincide in a day (24 h)?
   a) 11  b) 12  c) 22  d) 24
8. Hands of a clock coincide every 65 minutes of true time. In a day, the clock?
   a) gains 10 10/143 min  b) loses 10 10/143 min  c) is correct  d) gains 5 min
9. Angle between the hands at 12:20?
   a) 100°  b) 110°  c) 120°  d) 90°
10. At what time between 7 and 8 are the hands in a straight line?
    a) 7:05 5/11  b) 7:10  c) 7:32 8/11  d) 7:38 2/11
11. At 3:00 how many minutes until the hands first coincide?
    a) 16 4/11  b) 15  c) 16  d) 16 6/11
12. How many degrees does the minute hand move in 12 minutes?
    a) 60°  b) 72°  c) 84°  d) 90°

## Practice MCQs – Calendar

13. What day of the week was 15 August 1947?
    a) Thursday  b) Friday  c) Saturday  d) Sunday
14. 1 January 2001 was a Monday. 1 January 2005 was a?
    a) Thursday  b) Friday  c) Saturday  d) Sunday
15. Which of these is a leap year?
    a) 1900  b) 2100  c) 2000  d) 2023
16. Odd days in 200 years?
    a) 1  b) 3  c) 5  d) 0
17. A month with 31 days starts on Wednesday. On which day does the 31st fall?
    a) Thursday  b) Friday  c) Saturday  d) Sunday
18. 5 March 2023 was a Sunday. The day on 5 January 2023?
    a) Tuesday  b) Wednesday  c) Thursday  d) Friday
19. Today is Wednesday. The day after 100 days?
    a) Thursday  b) Friday  c) Saturday  d) Sunday
20. Same calendar as 2017 repeats in?
    a) 2022  b) 2023  c) 2024  d) 2025

<details><summary><b>Answers with solutions</b></summary>

**Clocks**
1. **a.** Hour = 277.5°, minute = 90° → 187.5° → 360 − 187.5 = 172.5°.
2. **b.** Hour = 220°, minute = 120° → 100°.
3. **b.** m = 60h/11 = 240/11 = 21 9/11.
4. **a.** (120 ∓ 90)/5.5 = 5 5/11 and 38 2/11.
5. **b.** (90 + 180)/5.5 = 49 1/11.
6. **a.** 11:60 − 3:20 = 8:40.
7. **c.** 11 in 12 h → 22 in 24 h.
8. **a.** Correct clock needs 65 5/11 min; this one meets in only 65 → it runs fast and gains (5/11)/65 × 1440 = 10 10/143 min.
9. **b.** Hour = 10°, minute = 120° → 110°.
10. **a.** (210 − 180)/5.5 = 5 5/11 (the "+" root exceeds 60).
11. **a.** At 3:00 the minute hand is 90° behind the hour hand: 90/5.5 = 16 4/11.
12. **b.** 12 × 6 = 72°.

**Calendar**
13. **b.** Friday (full working in B.4).
14. **c.** 2001, 2002, 2003 → +1 each; 2004 leap → +2; total +5 → Monday + 5 = Saturday.
15. **c.** 2000 is divisible by 400. 1900 and 2100 are not; 2023 isn't divisible by 4.
16. **b.** 200 years = 5 + 5 = 10 → 10 mod 7 = 3.
17. **b.** 28 days complete 4 weeks; 29th = Wed, 30th = Thu, 31st = Fri.
18. **c.** 59 days between → 59 mod 7 = 3 → Sunday − 3 = Thursday.
19. **b.** 100 mod 7 = 2 → Wednesday + 2 = Friday.
20. **b.** Odd days 2017 to 2022: 1 + 1 + 1 + 2 (2020 leap) + 1 + 1 = 7 → 2023.
</details>

## Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
