# 07 — Virtual Memory

## 1. What is Virtual Memory?
A technique that lets a process execute **even if it's not entirely in main memory**. Logical memory is separated from physical memory, so:
- programs can be **larger than physical RAM**
- more processes fit in memory → **higher degree of multiprogramming** and CPU utilization
- less I/O is needed to load or swap programs
- memory can be shared easily (shared libraries, `fork()` with COW)

It's implemented with **demand paging** (most common) or demand segmentation.

## 2. Demand Paging
- A page is loaded into memory **only when it's needed** (a lazy swapper, called the **pager**).
- **Valid–invalid bit** in the PTE: valid = in memory. Invalid = not in memory, or not part of the address space.
- **Pure demand paging:** start with *no* pages in memory. Every first access causes a fault.
- **Locality of reference** is what makes it work:
  - **Temporal:** recently used items are likely to be used again (loops).
  - **Spatial:** nearby items are likely to be used (arrays).

## 3. Page Fault ⭐
A **page fault** happens when a process accesses a page that is not in memory (invalid bit), which causes a **trap** to the OS.

**Steps in handling a page fault:**
1. Check an internal table (in the PCB): was the reference valid? If invalid → terminate (segfault).
2. If valid but not in memory → find a **free frame** (or run page replacement if none is free).
3. Schedule a **disk read** to bring the page into the frame. The process is blocked meanwhile.
4. When the read completes → update the page table (set the valid bit, frame number).
5. **Restart the instruction** that caused the fault.

**Effective Access Time with page faults:**
```
EAT = (1 − p) × memory_access_time + p × page_fault_service_time
```
**Example:** memory access = 200 ns, fault service = 8 ms, p = 1/1000
EAT = 0.999 × 200 + 0.001 × 8,000,000 ≈ **8.2 µs**, a **40× slowdown**! This is why the page-fault rate must be kept very low.

**Copy-on-Write (COW):** after `fork()`, parent and child share pages marked read-only. The page is copied only when one of them writes to it.

## 4. Page Replacement
When no frame is free, choose a **victim page** to evict. If the victim is **dirty (modified bit = 1)**, it must first be written back to disk. Clean pages can simply be overwritten.

**Goal:** the lowest page-fault rate.

### Reference string used below (3 frames)
`7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1` (20 references)

### 4.1 FIFO
Replace the page that has been in memory the **longest**.

| Ref | 7 | 0 | 1 | 2 | 0 | 3 | 0 | 4 | 2 | 3 | 0 | 3 | 2 | 1 | 2 | 0 | 1 | 7 | 0 | 1 |
|-----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| F1 | 7 | 7 | 7 | 2 | 2 | 2 | 2 | 4 | 4 | 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 7 | 7 | 7 |
| F2 |   | 0 | 0 | 0 | 0 | 3 | 3 | 3 | 2 | 2 | 2 | 2 | 2 | 1 | 1 | 1 | 1 | 1 | 0 | 0 |
| F3 |   |   | 1 | 1 | 1 | 1 | 0 | 0 | 0 | 3 | 3 | 3 | 3 | 3 | 2 | 2 | 2 | 2 | 2 | 1 |
| Fault? | F | F | F | F | H | F | F | F | F | F | F | H | H | F | F | H | H | F | F | F |

(F = page fault, H = hit)

**FIFO page faults = 15** (hits = 5)

- Simple, but can replace heavily used pages.
- Suffers from **Belady's anomaly**.

### 4.2 Optimal (OPT / MIN)
Replace the page that **won't be used for the longest time in the future**.
- **Page faults = 9** for the string above (the minimum possible).
- **Can't be implemented** (it needs knowledge of the future). It's used as a **benchmark**.

### 4.3 LRU (Least Recently Used)
Replace the page that **hasn't been used for the longest time** (past as an approximation of the future).
- **Page faults = 12** for the string above.
- Implementation: **counters/timestamps** or a **stack** (doubly linked list + hashmap, the classic LRU cache interview problem!). Needs hardware support, so it's expensive.
- **No Belady's anomaly** (it's a stack algorithm).

**Summary for this string (3 frames): OPT 9 < LRU 12 < FIFO 15**

### 4.4 LRU approximations
- **Reference bit:** set by hardware on access.
- **Second-chance (Clock) algorithm:** FIFO + reference bit. If the bit is 1, clear it and move on (give a second chance). If 0, replace. A circular queue with a "clock hand".
- **Enhanced second chance:** uses the (reference, modify) pair. (0,0) is the best victim, then (0,1), (1,0), (1,1).

### 4.5 Counting-based
- **LFU (Least Frequently Used):** replace the page with the smallest count.
- **MFU (Most Frequently Used):** replace the page with the largest count (the argument is that a page with a small count was probably just brought in).

## 5. Belady's Anomaly ⭐
**Increasing the number of frames increases the number of page faults.** It occurs in **FIFO** (and FIFO-based algorithms), **not** in LRU or Optimal (stack algorithms).

**Classic example:** reference string `1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5`
- FIFO with **3 frames → 9 faults**
- FIFO with **4 frames → 10 faults** 😲

## 6. Frame Allocation
- **Equal allocation:** m frames / n processes.
- **Proportional allocation:** aᵢ = (sᵢ / S) × m (based on process size).
- **Global replacement:** a process can take a frame from any process. Higher throughput, less predictable. Most common.
- **Local replacement:** a process chooses only from its own frames.

## 7. Thrashing ⭐
**Thrashing** is when a process spends **more time paging than executing**, because it doesn't have enough frames to hold its working set.

**Why it happens:** CPU utilization drops → the OS sees low utilization → **raises the degree of multiprogramming** → each process gets even fewer frames → more faults → utilization drops further. It's a vicious cycle.

```
CPU
util  |        ___
      |      /     \
      |    /         \     ← thrashing
      |  /             \
      |/_________________\__
             degree of multiprogramming →
```

**Solutions:**
1. **Working-set model:** working set W(t, Δ) = the set of pages referenced in the last Δ references. If Σ WSSᵢ > total frames → **suspend a process**.
2. **Page-Fault Frequency (PFF):** set upper and lower bounds on the fault rate. Above the upper bound, give the process more frames. Below the lower bound, take frames away.
3. Use local replacement, reduce multiprogramming, add more RAM.

## 8. Other Concepts
- **Memory-mapped files:** map a file into the virtual address space (`mmap`). File I/O becomes memory access.
- **Kernel memory allocation:** the **buddy system** (splits memory into power-of-2 blocks, easy coalescing, internal fragmentation) and the **slab allocator** (caches of pre-initialized objects, no fragmentation).
- **Prepaging:** bring in likely-needed pages ahead of time.
- **Page size trade-offs:** large pages → smaller page tables, less I/O overhead, more internal fragmentation. Small pages → better locality and resolution.
- **TLB reach** = TLB entries × page size.
- **Page locking / pinning:** keep pages (e.g. I/O buffers) from being paged out.

## 9. Common Interview Questions
1. What is virtual memory, and what are its advantages?
2. What is demand paging?
3. What is a page fault? Walk through the steps to handle it.
4. Compare FIFO, LRU, and Optimal. Solve a reference string.
5. What is Belady's anomaly, and which algorithms suffer from it?
6. What is thrashing? What causes it, and how is it prevented?
7. What is the working-set model?
8. How would you implement LRU? (HashMap + doubly linked list, O(1) get/put.)
9. What is copy-on-write?
10. What is the dirty bit used for? (It avoids writing clean pages back to disk.)

## MCQ Traps
- Belady's anomaly → **FIFO only** (among the common algorithms).
- Optimal gives the minimum faults but **isn't implementable**.
- Thrashing → **high paging activity, low CPU utilization**.
- The first reference to a page in pure demand paging is **always a fault** (a compulsory miss).
- Minimum number of faults = the number of **distinct pages** in the reference string (when frames ≥ distinct pages).
- **Page hit ratio** = hits / total references.
