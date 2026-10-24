# 04 – Time, Speed & Distance (Trains, Boats & Streams, Relative Speed)

> **One-line idea:** everything comes from **Distance = Speed × Time**. Most problems are about *which two
> of the three quantities stay the same* between two situations.

---

## 1. Foundations

### 1.1 Unit conversion
- km/h → m/s: **multiply by 5/18**. (54 km/h = 15 m/s)
- m/s → km/h: **multiply by 18/5**. (20 m/s = 72 km/h)
Always convert so that distance and time units match (metres with seconds, km with hours).

### 1.2 Proportionality (the quickest solver)
- Same distance → speed and time are **inversely** proportional. Speed ratio a:b → time ratio b:a.
- Same speed → distance ∝ time.
- Same time → distance ∝ speed.

**Example:** a man walks at 3/4 of his usual speed and arrives 20 minutes late. Time ratio = 4/3 → he takes 1/3 *more* time → usual time × 1/3 = 20 min → **usual time = 60 min**.

### 1.3 Average speed
- Same distance at two speeds s1, s2: **avg = 2·s1·s2/(s1 + s2)** (a *harmonic* mean – never the simple average).
- Same time at two speeds: avg = (s1 + s2)/2.
- General: total distance ÷ total time.

**Example:** 60 km/h up, 40 km/h back → 2·60·40/100 = **48 km/h**.

### 1.4 Relative speed
- Two objects moving in **opposite** directions: relative speed = s1 + s2.
- Same direction: relative speed = |s1 − s2|.
- Time to meet/overtake = gap distance ÷ relative speed.

---

## 2. Trains

### 2.1 Cases
| Situation | Distance covered | Time |
|---|---|---|
| Crossing a pole / standing person | Train length L | L / speed |
| Crossing a platform/bridge (length P) | L + P | (L + P) / speed |
| Crossing another train (opposite) | L1 + L2 | (L1 + L2) / (s1 + s2) |
| Overtaking another train (same direction) | L1 + L2 | (L1 + L2) / (s1 − s2) |
| Overtaking a moving man | L | L / (s_train − s_man) |

### 2.2 Worked examples
1. A 150 m train at 54 km/h crosses a pole: 54 km/h = 15 m/s → 150/15 = **10 s**.
2. Trains 100 m and 150 m moving opposite at 36 and 54 km/h: relative = 90 km/h = 25 m/s; distance 250 m → **10 s**.
3. A 200 m train crosses a 300 m platform in 25 s: distance 500 m → speed 20 m/s = **72 km/h**.
4. A 150 m train at 60 km/h passes a man running at 6 km/h in the same direction: relative = 54 km/h = 15 m/s → **10 s**.

---

## 3. Boats & Streams

- Let boat in still water = **b**, stream = **s**.
- Downstream speed (with the current) = **b + s**; upstream = **b − s**.
- Given D (downstream) and U (upstream): **b = (D + U)/2, s = (D − U)/2**.

**Example 1:** D = 15, U = 9 → b = 12, s = 3.

**Example 2 (round trip):** boat 5 km/h in still water, river 1 km/h, destination 6 km away.
Down: 6/6 = 1 h. Up: 6/4 = 1.5 h → **2.5 h** total. (Don't use the still-water speed alone for the round trip – the stream helps one way and hurts the other, and the losses don't cancel.)

---

## 4. Patterns

### Pattern A – Late/early arrival at two speeds
Use `distance/s1 − distance/s2 = time difference`.
**Example:** at 30 km/h he's 1 h late; at 40 km/h he's 1 h early → total diff 2 h.
d/30 − d/40 = 2 → d/120 = 2 → **d = 240 km**.

### Pattern B – Meeting problems
Two people start at opposite ends of a route of length D: time to meet = D/(s1 + s2).
Meeting point from A = s1 × time.

### Pattern C – Circular track
- Same direction: they meet when the faster gains one full lap: time = Track / (s1 − s2).
- Opposite direction: time = Track / (s1 + s2).
**Example:** track 400 m, speeds 4 and 6 m/s. Same direction: 400/2 = **200 s**. Opposite: 400/10 = **40 s**.

### Pattern D – Change of speed mid-way
Break the journey into parts and add the times. Use total distance / total time for the average.

### Pattern E – Races and head starts
"A beats B by 20 m in a 100 m race" → when A runs 100 m, B runs 80 m → speeds A : B = 100 : 80 = 5 : 4.

---

## 5. Traps
1. Forgetting to add the length of the platform/bridge.
2. Using the simple average for average speed over equal distances.
3. Mixing units (km/h with metres) – convert first.
4. Boat problems: "speed of boat" means still-water speed unless told otherwise.

---

## 6. Practice MCQs

1. A 150 m train at 54 km/h crosses a pole in?
   a) 8 s  b) 10 s  c) 12 s  d) 15 s
2. Going at 60 km/h and returning at 40 km/h on the same route. Average speed?
   a) 50  b) 48  c) 45  d) 52
3. Boat downstream 15 km/h, upstream 9 km/h. Speed of boat and stream?
   a) 12, 3  b) 13, 2  c) 11, 4  d) 10, 5
4. Trains of 100 m and 150 m run opposite at 36 and 54 km/h. Time to cross?
   a) 8 s  b) 10 s  c) 12 s  d) 15 s
5. At 30 km/h a man is 1 h late; at 40 km/h he is 1 h early. Distance?
   a) 120 km  b) 200 km  c) 240 km  d) 300 km
6. A 200 m train crosses a 300 m platform in 25 s. Its speed?
   a) 20 m/s  b) 72 km/h  c) both a and b  d) 25 m/s
7. A man walks at 5/6 of his usual speed and takes 12 minutes extra. Usual time?
   a) 48 min  b) 60 min  c) 72 min  d) 80 min
8. Two cars start 300 km apart and travel toward each other at 50 and 70 km/h. When do they meet?
   a) 2 h  b) 2.5 h  c) 3 h  d) 3.5 h
9. A boat takes 4 h to go 24 km downstream and 6 h to return. Speed of the stream?
   a) 1 km/h  b) 2 km/h  c) 3 km/h  d) 5 km/h
10. A can run 100 m in 20 s, B in 25 s. By how many metres does A beat B?
    a) 15  b) 20  c) 25  d) 10

<details><summary><b>Answers with solutions</b></summary>

1. **b.** 15 m/s → 150/15 = 10.
2. **b.** 2·60·40/100 = 48.
3. **a.** b = 12, s = 3.
4. **b.** 250/25 = 10.
5. **c.** d/120 = 2 → 240.
6. **c.** 500/25 = 20 m/s = 72 km/h.
7. **b.** Time ratio 6/5 → extra = 1/5 of usual = 12 → usual = 60.
8. **b.** Relative speed 50 + 70 = 120 km/h → 300/120 = 2.5 h.
9. **a.** D = 24/4 = 6, U = 24/6 = 4 → s = (6 − 4)/2 = 1.
10. **b.** A runs 100 m in 20 s. B in 20 s runs 80 m (speed 4 m/s) → A wins by **20 m**.
</details>

## 7. Mistakes box
| Question # | What went wrong | Rule to remember |
|---|---|---|
| | | |
