# 05 — Deadlocks

## 1. Definition
A **deadlock** is a situation where a set of processes are blocked because each holds a resource and waits for a resource held by another process in the set. None of them can ever proceed.

**Real-life example:** a traffic gridlock at a 4-way junction.
**Code example:** Thread A locks M1 then waits for M2. Thread B locks M2 then waits for M1.

## 2. Necessary Conditions (Coffman Conditions) ⭐
A deadlock can occur only if **all four** hold **simultaneously**:
1. **Mutual Exclusion:** at least one resource is non-shareable.
2. **Hold and Wait:** a process holds at least one resource while waiting for others.
3. **No Preemption:** resources can't be forcibly taken away. They are released voluntarily.
4. **Circular Wait:** a circular chain P0 → P1 → … → Pn → P0, where each waits for the next one's resource.

Break any one of them and deadlock is impossible.

## 3. Resource Allocation Graph (RAG)
- **Nodes:** processes (circles) and resources (squares, with dots for instances).
- **Request edge:** P → R. **Assignment edge:** R → P.
- **No cycle → no deadlock.**
- **Cycle + single instance per resource → deadlock (definitely).**
- **Cycle + multiple instances → deadlock *possible*, not guaranteed.**
- **Wait-for graph:** collapse the resource nodes (single-instance case). A cycle means deadlock.

## 4. Methods for Handling Deadlocks
1. **Prevention:** make sure at least one Coffman condition can never hold.
2. **Avoidance:** use extra information (max needs) to never enter an unsafe state (Banker's).
3. **Detection & Recovery:** let deadlocks happen, detect them, then recover.
4. **Ignorance (Ostrich Algorithm):** pretend deadlocks never happen. **Used by most OSes (Windows, Linux)** because deadlocks are rare and prevention is costly.

## 5. Deadlock Prevention
| Condition | How to break it | Drawback |
|-----------|-----------------|----------|
| Mutual Exclusion | Make resources shareable (e.g. read-only files, spooling for printers) | Not possible for many resources |
| Hold and Wait | Request **all resources at once** before starting, or release all before requesting new ones | Low utilization, starvation |
| No Preemption | If a request is denied, release held resources, or preempt from the waiting process | Only works for resources whose state can be saved (CPU, memory) |
| Circular Wait | **Impose a total ordering** on resource types. Request only in increasing order | Most practical. Ordering can be inconvenient |

## 6. Deadlock Avoidance
- **Safe state:** a **safe sequence** exists in which every process can obtain its maximum needs and finish.
- **Safe ⇒ no deadlock. Unsafe ⇒ deadlock *may* occur** (not every unsafe state is a deadlock).
- Single instance per resource: **resource-allocation graph algorithm** with claim edges.
- Multiple instances: **Banker's Algorithm**.

### Banker's Algorithm ⭐
**Data structures** (n processes, m resource types):
- `Available[m]`
- `Max[n][m]`
- `Allocation[n][m]`
- `Need[n][m] = Max − Allocation`

**Safety algorithm:**
1. `Work = Available`, `Finish[i] = false` for all i.
2. Find i with `Finish[i] == false` and `Need[i] ≤ Work`. If none exists, go to step 4.
3. `Work = Work + Allocation[i]`, `Finish[i] = true`. Go to step 2.
4. If every `Finish[i] == true`, the state is **safe**.

**Resource-request algorithm** (process Pi requests `Request[i]`):
1. If `Request > Need` → error (it exceeded its max claim).
2. If `Request > Available` → wait.
3. Pretend to allocate: `Available −= Req`, `Allocation += Req`, `Need −= Req`. Run the safety algorithm. If safe, grant. Otherwise roll back and make Pi wait.

### Worked Example
Total resources: A = 10, B = 5, C = 7

| Process | Allocation (A B C) | Max (A B C) | Need = Max − Alloc |
|---------|-------------------|-------------|--------------------|
| P0 | 0 1 0 | 7 5 3 | 7 4 3 |
| P1 | 2 0 0 | 3 2 2 | 1 2 2 |
| P2 | 3 0 2 | 9 0 2 | 6 0 0 |
| P3 | 2 1 1 | 2 2 2 | 0 1 1 |
| P4 | 0 0 2 | 4 3 3 | 4 3 1 |

Total allocated = (7, 2, 5) → **Available = (10,5,7) − (7,2,5) = (3, 3, 2)**

| Step | Pick | Need ≤ Work? | New Work |
|------|------|--------------|----------|
| 1 | P1 | (1,2,2) ≤ (3,3,2) ✅ | (5,3,2) |
| 2 | P3 | (0,1,1) ≤ (5,3,2) ✅ | (7,4,3) |
| 3 | P4 | (4,3,1) ≤ (7,4,3) ✅ | (7,4,5) |
| 4 | P0 | (7,4,3) ≤ (7,4,5) ✅ | (7,5,5) |
| 5 | P2 | (6,0,0) ≤ (7,5,5) ✅ | (10,5,7) |

**Safe sequence: <P1, P3, P4, P0, P2>** → the system is in a **safe state**. (A safe sequence need not be unique. <P1, P3, P4, P2, P0> is also valid.)

**Drawbacks of Banker's:** needs max needs in advance, a fixed number of processes and resources, and O(m·n²) time. Rarely used in real OSes.

## 7. Deadlock Detection & Recovery
**Detection:**
- Single instance: look for a cycle in the **wait-for graph**.
- Multiple instances: a Banker's-like detection algorithm that uses the current **Request** matrix instead of Need.

**Recovery:**
1. **Process termination:** abort all deadlocked processes, or abort **one at a time** until the cycle breaks. Choose the victim by priority, work done, resources held, and so on.
2. **Resource preemption:** select a victim, **roll back** it to a safe checkpoint, and avoid **starvation** (don't pick the same victim every time; include the rollback count in the cost).

## 8. Important Formula ⭐ (very common MCQ)
There are **n processes**, and each needs at most **k** instances of a resource. The **minimum number of resources R that guarantees no deadlock** is:

**R ≥ n(k − 1) + 1**

*Why:* worst case, each process holds k−1 and waits. One extra instance lets one of them finish.

- Example: 3 processes, each needs 2 → R ≥ 3(1) + 1 = **4**.
- Example: 6 resources, each process needs 3 → max processes without deadlock: n(2) + 1 ≤ 6 → **n ≤ 2** (so 3 processes *can* deadlock).

Generalized: if process i needs at most kᵢ, then deadlock-free if **R ≥ Σ(kᵢ − 1) + 1**.

## 9. Deadlock vs Starvation vs Livelock
| Deadlock | Starvation | Livelock |
|----------|------------|----------|
| Processes block forever waiting for each other | A process waits indefinitely while others progress | Processes are active but make no progress |
| Circular wait | Low priority, unfair scheduling | Keep reacting to each other |
| Everyone involved is stuck | Only the victim is stuck | CPU is busy, no useful work |
| Fix: prevention, avoidance, detection | Fix: **aging** | Fix: randomized back-off |

## 10. Common Interview Questions
1. What is deadlock? Give a real example.
2. What are the four necessary conditions?
3. How do you prevent deadlock? Which condition is the most practical to break? (**Circular wait**, via resource ordering)
4. Safe vs unsafe state? Is every unsafe state a deadlock? (**No**)
5. Explain the Banker's algorithm with an example.
6. How does an OS recover from deadlock?
7. What does Linux or Windows do about deadlocks? (**Ostrich approach**)
8. Deadlock vs starvation?
9. How would you avoid deadlock in a multithreaded program? (Lock ordering, `tryLock` with timeout, holding locks for less time, avoiding nested locks.)

## MCQ Traps
- A cycle in the RAG is **necessary but not sufficient** for multi-instance resources.
- Unsafe ≠ deadlocked.
- Banker's = **avoidance**, not prevention.
- Requesting all resources at once breaks **hold and wait**.
- Use the formula **n(k−1)+1**.
