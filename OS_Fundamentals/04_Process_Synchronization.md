# 04 — Process Synchronization

## 1. Why do we need it?
When cooperating processes or threads access **shared data concurrently**, the result can depend on the order of execution. That situation is a **race condition**.

**Example:** `count++` is really 3 machine instructions:
```
reg = count      // load
reg = reg + 1    // increment
count = reg      // store
```
If two threads interleave, both may read 5 and both write 6. One increment is **lost**.

## 2. Critical Section Problem
- **Critical Section (CS):** the part of the code that accesses shared resources.
- Structure:
```
do {
    entry section
        CRITICAL SECTION
    exit section
        remainder section
} while (true);
```

### Requirements of a correct solution ⭐
1. **Mutual Exclusion:** at most one process is in the CS at a time.
2. **Progress:** if no process is in the CS, the choice of who enters next can't be postponed indefinitely, and only processes that want to enter take part in the decision.
3. **Bounded Waiting:** there is a limit on how many times others can enter the CS after a process has requested entry. This rules out starvation.

(Also expected: no assumptions about speed or number of CPUs.)

## 3. Software Solutions
### Strict Alternation (turn variable)
```c
while (turn != i);   // busy wait
/* CS */
turn = j;
```
✅ Mutual exclusion. ❌ **Progress** fails: a process can't enter twice in a row even if the other doesn't want to.

### Peterson's Solution (2 processes) ⭐
```c
// shared: bool flag[2]; int turn;
flag[i] = true;          // I want to enter
turn = j;                // but you go first
while (flag[j] && turn == j);  // wait
/* CRITICAL SECTION */
flag[i] = false;
```
✅ Satisfies **all three** requirements. It only works for 2 processes and may fail on modern CPUs because of instruction reordering unless memory barriers are used.

### Bakery Algorithm
Lamport's solution for **n processes**. Each process takes a number, like a token at a bakery, and the smallest number goes first (ties broken by PID).

## 4. Hardware Solutions
- **Disabling interrupts:** works on a uniprocessor. Not feasible on multiprocessors, and dangerous to hand to users.
- **Atomic instructions:**
  - **Test-and-Set (TSL)**
    ```c
    bool TestAndSet(bool *target) { bool rv = *target; *target = true; return rv; } // atomic
    while (TestAndSet(&lock)); /* CS */ lock = false;
    ```
    Mutual exclusion ✅, bounded waiting ❌ (in the simple form).
  - **Compare-and-Swap (CAS):** `if (*value == expected) *value = new_value;` atomically. Used in lock-free data structures.

## 5. Mutex Locks
- A **mutex** (mutual exclusion lock) has `acquire()` and `release()`.
- **Ownership:** only the thread that locked it can unlock it.
- **Spinlock:** a mutex that **busy-waits**. Good when the wait is short and the system is multiprocessor (it avoids a context switch). Wastes CPU otherwise.

## 6. Semaphores ⭐
A **semaphore S** is an integer variable accessed only through two **atomic** operations:
```c
wait(S)   / P(S) / down(S):   while (S <= 0);  S--;     // busy-wait version
signal(S) / V(S) / up(S):     S++;
```
**Blocking implementation (no busy waiting):**
```c
wait(S)   { S.value--; if (S.value < 0) { add to S.list; block(); } }
signal(S) { S.value++; if (S.value <= 0) { remove P from S.list; wakeup(P); } }
```
- A negative value means **|value| processes are waiting**.

### Types
| Binary semaphore | Counting semaphore |
|------------------|--------------------|
| Values 0 or 1 | Any non-negative integer |
| Used for mutual exclusion | Controls access to a resource with **N instances** |

### Mutex vs Semaphore ⭐ (very common question)
| Mutex | Semaphore |
|-------|-----------|
| Locking mechanism | Signalling mechanism |
| Has ownership: only the owner unlocks | No ownership: any process can signal |
| Only 0/1 | Binary or counting |
| One thread in the CS | Up to N threads (counting) |
| Example: a single bathroom key | Example: a parking lot with N spaces |

### Semaphore problems
- **Deadlock:** P0: `wait(S); wait(Q);` P1: `wait(Q); wait(S);` → each holds one and waits for the other.
- **Starvation**, e.g. with a LIFO wait queue.
- **Priority inversion:** a low-priority task holds a lock needed by a high-priority task, while a medium-priority task preempts the low one. The high-priority task effectively waits for the medium one. **Solution: priority inheritance** (the low task temporarily inherits the high priority). A famous case is the **Mars Pathfinder** bug.

## 7. Classic Synchronization Problems ⭐

### 7.1 Producer–Consumer (Bounded Buffer)
Buffer of size N. Semaphores: `mutex = 1`, `empty = N`, `full = 0`.
```c
// Producer                    // Consumer
do {                           do {
  produce item;                  wait(full);
  wait(empty);                   wait(mutex);
  wait(mutex);                   remove item from buffer;
  add item to buffer;            signal(mutex);
  signal(mutex);                 signal(empty);
  signal(full);                  consume item;
} while (1);                   } while (1);
```
⚠️ **Order matters:** if the producer does `wait(mutex)` before `wait(empty)` and the buffer is full, it holds the mutex while blocked, and you get a **deadlock**.

### 7.2 Readers–Writers
- Many readers may read together. A writer needs exclusive access.
- Semaphores: `rw_mutex = 1`, `mutex = 1`, `read_count = 0`.
```c
// Writer                     // Reader
wait(rw_mutex);               wait(mutex);
  write;                        read_count++;
signal(rw_mutex);               if (read_count == 1) wait(rw_mutex);  // first reader locks writers out
                              signal(mutex);
                                read;
                              wait(mutex);
                                read_count--;
                                if (read_count == 0) signal(rw_mutex); // last reader lets writers in
                              signal(mutex);
```
- The **first readers-writers problem** favours readers, so writers may starve. The second variant favours writers, so readers may starve.

### 7.3 Dining Philosophers
5 philosophers, 5 chopsticks. Each needs both left and right to eat.
```c
do {
  wait(chopstick[i]);
  wait(chopstick[(i+1) % 5]);
    eat;
  signal(chopstick[i]);
  signal(chopstick[(i+1) % 5]);
    think;
} while (1);
```
❌ **Deadlock** if all pick up their left chopstick at the same time.
**Solutions:**
1. Allow at most **4** philosophers at the table.
2. Pick up both chopsticks only if both are available (inside a critical section / monitor).
3. **Asymmetric:** odd philosophers pick left then right, even ones pick right then left. This breaks circular wait.

### 7.4 Sleeping Barber
A barber, one barber chair, N waiting chairs. Customers leave if all the chairs are full. Semaphores: `customers`, `barber`, `mutex`, plus a `waiting` count.

## 8. Monitors
- A **high-level synchronization construct** (language level). Only one process can be active inside the monitor at a time.
- **Condition variables:** `x.wait()` suspends the caller. `x.signal()` resumes one waiting process (it does nothing if none are waiting, unlike a semaphore's signal, which always increments).
- Examples: Java `synchronized` methods with `wait()`/`notify()`, and C++ `std::condition_variable`.

## 9. Other Terms
- **Busy waiting:** looping while waiting, which wastes CPU.
- **Atomic operation:** runs completely without interruption.
- **Livelock:** processes keep changing state in response to each other but make no progress (two people stepping aside in a corridor).
- **Reentrant code:** can be safely executed by multiple threads at once (no shared mutable state).
- **Thread-safe:** works correctly under concurrent access.

## 10. Common Interview Questions
1. What is a race condition? Give an example.
2. What is a critical section, and what are its three requirements?
3. Explain Peterson's solution.
4. Mutex vs semaphore?
5. Binary vs counting semaphore?
6. Solve producer-consumer with semaphores. Why does the order of `wait` calls matter?
7. How do you avoid deadlock in dining philosophers?
8. What is priority inversion, and how is it solved?
9. Spinlock vs mutex: when would you use a spinlock?
10. What is a monitor?

## MCQ Traps
- Peterson's satisfies **ME, progress, and bounded waiting**. Strict alternation fails **progress**.
- For a counting semaphore with initial value `S` after `x` P ops and `y` V ops: **final = S − x + y**.
- A semaphore with value **−3** means **3 processes are blocked**.
- A binary semaphore **≈** a mutex, but without ownership.
- The TSL-based lock doesn't guarantee **bounded waiting**.
