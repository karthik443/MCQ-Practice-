# 03 — CPU Scheduling

## 1. Basics
- **CPU scheduling** decides which process in the ready queue gets the CPU next.
- A process alternates between a **CPU burst** and an **I/O burst**.
- **Preemptive:** the OS can take the CPU away (on timer interrupt or when a higher-priority process arrives).
- **Non-preemptive:** the process keeps the CPU until it terminates or blocks for I/O.

**When scheduling happens:**
1. Running → Waiting (I/O): non-preemptive
2. Running → Ready (interrupt): preemptive
3. Waiting → Ready (I/O done): preemptive
4. Process terminates: non-preemptive

## 2. Scheduling Criteria & Formulas ⭐
| Term | Formula / meaning | Goal |
|------|-------------------|------|
| **Arrival Time (AT)** | When the process enters the ready queue | – |
| **Burst Time (BT)** | CPU time required | – |
| **Completion Time (CT)** | When the process finishes | – |
| **Turnaround Time (TAT)** | **TAT = CT − AT** | Minimize |
| **Waiting Time (WT)** | **WT = TAT − BT** | Minimize |
| **Response Time (RT)** | **RT = first time it gets CPU − AT** | Minimize (interactive) |
| **Throughput** | Processes completed per unit time | Maximize |
| **CPU Utilization** | % time the CPU is busy | Maximize |

## 3. Algorithms at a Glance
| Algorithm | Preemptive? | Selection | Pros | Cons |
|-----------|-------------|-----------|------|------|
| **FCFS** | No | Earliest arrival | Simple, no starvation | **Convoy effect**, high avg WT |
| **SJF** | No | Smallest BT | **Optimal avg WT** (non-preemptive) | Needs BT in advance, starvation of long jobs |
| **SRTF** (preemptive SJF) | Yes | Smallest remaining time | Optimal avg WT overall | Starvation, many context switches |
| **Priority** | Both | Highest priority | Important jobs first | **Starvation** → fix with **aging** |
| **Round Robin** | Yes | FCFS + time quantum | Fair, good response time, no starvation | Performance depends on quantum |
| **HRRN** | No | Highest response ratio | No starvation, favours short jobs | Needs BT |
| **Multilevel Queue** | Both | Fixed queues by type | Different policies per class | Starvation of lower queues, inflexible |
| **Multilevel Feedback Queue** | Yes | Processes move between queues | Most flexible, approximates SJF | Most complex |

## 4. Worked Example (use the same data for all)
| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 5 |
| P2 | 1 | 3 |
| P3 | 2 | 1 |
| P4 | 3 | 2 |
| P5 | 4 | 3 |

### 4.1 FCFS
Gantt: `| P1 0-5 | P2 5-8 | P3 8-9 | P4 9-11 | P5 11-14 |`

| P | CT | TAT = CT−AT | WT = TAT−BT |
|---|----|-----|----|
| P1 | 5 | 5 | 0 |
| P2 | 8 | 7 | 4 |
| P3 | 9 | 7 | 6 |
| P4 | 11 | 8 | 6 |
| P5 | 14 | 10 | 7 |

**Avg TAT = 37/5 = 7.4, Avg WT = 23/5 = 4.6**

**Convoy effect:** short processes wait behind one long CPU-bound process, which lowers CPU and device utilization.

### 4.2 SJF (non-preemptive)
At t=0 only P1 is present, so it runs to completion. At t=5, pick the shortest: P3(1) → P4(2) → P2(3) → P5(3). The P2/P5 tie is broken by arrival time.

Gantt: `| P1 0-5 | P3 5-6 | P4 6-8 | P2 8-11 | P5 11-14 |`

| P | CT | TAT | WT |
|---|----|-----|----|
| P1 | 5 | 5 | 0 |
| P2 | 11 | 10 | 7 |
| P3 | 6 | 4 | 3 |
| P4 | 8 | 5 | 3 |
| P5 | 14 | 10 | 7 |

**Avg TAT = 34/5 = 6.8, Avg WT = 20/5 = 4.0**

### 4.3 SRTF (preemptive SJF)
- t=0: P1 runs (rem 5)
- t=1: P2 arrives (3) < P1 rem (4) → **preempt**, P2 runs
- t=2: P3 arrives (1) < P2 rem (2) → preempt, P3 runs, finishes at 3
- t=3: P1(4), P2(2), P4(2) → tie → P2 (earlier arrival) runs, finishes at 5
- t=5: P1(4), P4(2), P5(3) → P4 5-7 → P5 7-10 → P1 10-14

Gantt: `| P1 0-1 | P2 1-2 | P3 2-3 | P2 3-5 | P4 5-7 | P5 7-10 | P1 10-14 |`

| P | CT | TAT | WT | RT |
|---|----|-----|----|----|
| P1 | 14 | 14 | 9 | 0 |
| P2 | 5 | 4 | 1 | 0 |
| P3 | 3 | 1 | 0 | 0 |
| P4 | 7 | 4 | 2 | 2 |
| P5 | 10 | 6 | 3 | 3 |

**Avg TAT = 29/5 = 5.8, Avg WT = 15/5 = 3.0** (the lowest, as expected)

### 4.4 Round Robin (Time Quantum = 2)
Convention: when a process arrives at the same instant another is preempted, the **new arrival enters the queue first**.

- 0-2 P1 (rem 3). Arrived: P2, P3. Queue: P2, P3, P1
- 2-4 P2 (rem 1). Arrived: P4, P5. Queue: P3, P1, P4, P5, P2
- 4-5 P3 done. Queue: P1, P4, P5, P2
- 5-7 P1 (rem 1). Queue: P4, P5, P2, P1
- 7-9 P4 done. Queue: P5, P2, P1
- 9-11 P5 (rem 1). Queue: P2, P1, P5
- 11-12 P2 done → 12-13 P1 done → 13-14 P5 done

Gantt: `| P1 0-2 | P2 2-4 | P3 4-5 | P1 5-7 | P4 7-9 | P5 9-11 | P2 11-12 | P1 12-13 | P5 13-14 |`

| P | CT | TAT | WT | RT |
|---|----|-----|----|----|
| P1 | 13 | 13 | 8 | 0 |
| P2 | 12 | 11 | 8 | 1 |
| P3 | 5 | 3 | 2 | 2 |
| P4 | 9 | 6 | 4 | 4 |
| P5 | 14 | 10 | 7 | 5 |

**Avg TAT = 43/5 = 8.6, Avg WT = 29/5 = 5.8.** RR has worse WT/TAT here but **better response time** for everyone. That's its purpose.

**Choosing the time quantum:**
- Too **large** → RR degrades to **FCFS**.
- Too **small** → too many context switches (overhead).
- Rule of thumb: ~80% of CPU bursts should be shorter than the quantum.

### 4.5 Priority Scheduling (non-preemptive, lower number = higher priority)
| Process | AT | BT | Priority |
|---------|----|----|----------|
| P1 | 0 | 4 | 2 |
| P2 | 1 | 3 | 3 |
| P3 | 2 | 1 | 4 |
| P4 | 3 | 5 | 5 |
| P5 | 4 | 2 | 1 |

Gantt: `| P1 0-4 | P5 4-6 | P2 6-9 | P3 9-10 | P4 10-15 |`

CT: P1=4, P2=9, P3=10, P4=15, P5=6 → TAT: 4, 8, 8, 12, 2 → WT: 0, 5, 7, 7, 0
**Avg TAT = 34/5 = 6.8, Avg WT = 19/5 = 3.8**

- **Starvation / indefinite blocking:** a low-priority process may never run.
- **Aging:** gradually raise the priority of processes that have waited a long time. This is the solution.
- Preemptive priority: if a newly arrived process has higher priority, it preempts the running one.

### 4.6 HRRN (Highest Response Ratio Next)
**Response Ratio = (Waiting Time + Burst Time) / Burst Time**
- Non-preemptive. Favours short jobs, but long waiting jobs gain a higher ratio, so there is **no starvation**.

## 5. Multilevel Queue (MLQ)
- The ready queue is split into separate queues, e.g. **system → interactive → batch**, each with its own algorithm (e.g. RR for foreground, FCFS for background).
- Processes are **permanently assigned** to one queue.
- Scheduling between queues: fixed priority (can starve lower queues) or a time-slice split (e.g. 80% foreground / 20% background).

## 6. Multilevel Feedback Queue (MLFQ)
- Processes **can move between queues**.
- Example: Q0 (RR, q=8) → Q1 (RR, q=16) → Q2 (FCFS).
- A new process enters Q0. If it doesn't finish within its quantum, it drops to a lower queue.
- CPU-bound jobs sink and I/O-bound/interactive jobs stay high. **Aging** moves long-waiting jobs back up.
- Defined by: number of queues, algorithm per queue, and rules for upgrading, demoting, and choosing the entry queue.
- It's the most general scheme, and the most complex.

## 7. Other Points
- **Linux CFS (Completely Fair Scheduler)** uses a **red-black tree** keyed by virtual runtime and picks the task with the smallest vruntime. (Linux 6.6+ replaced CFS with EEVDF, but CFS is the usual interview answer.)
- **Multiprocessor scheduling:** processor affinity (soft/hard), load balancing (push/pull migration).
- **Real-time scheduling:** Rate Monotonic (static priority, shorter period = higher priority), EDF (Earliest Deadline First, dynamic).
- **Starvation vs deadlock:** starvation means waiting indefinitely while others progress. Deadlock means nobody in the set progresses.

## 8. Common Interview Questions
1. Preemptive vs non-preemptive scheduling?
2. Which algorithm gives the minimum average waiting time? **SJF (SRTF for preemptive).**
3. Why is SJF not practical? BT isn't known in advance. It's predicted using **exponential averaging**: τₙ₊₁ = α·tₙ + (1−α)·τₙ
4. What is the convoy effect?
5. What is starvation, and how does aging solve it?
6. What happens if the RR time quantum is very large or very small?
7. Which algorithm suits time-sharing systems? **Round Robin.**
8. Explain MLFQ.
9. What is the dispatcher, and what is dispatch latency?

## MCQ Traps
- **FCFS** is always **non-preemptive** and has **no starvation**.
- **SJF & priority** can cause **starvation**. **RR** cannot.
- RR with a very large quantum = **FCFS**.
- **SRTF** is the preemptive version of SJF.
- In MCQs, always check whether a **lower number means higher priority**.
- If the question includes a **context-switch overhead**, add it between process switches.
