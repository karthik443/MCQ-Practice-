# 02 — Processes and Threads

## 1. Program vs Process
- **Program:** a passive entity, an executable file on disk.
- **Process:** a **program in execution**, an active entity with its own state and resources.
- One program can create many processes (for example, several Chrome windows or tabs).

## 2. Process Memory Layout
```
High address  +------------------+
              |      Stack       |  local variables, function params, return addresses (grows down)
              |        ↓         |
              |                  |
              |        ↑         |
              |       Heap       |  dynamic memory: malloc/new (grows up)
              +------------------+
              |       BSS        |  uninitialized globals/statics
              |       Data       |  initialized globals/statics
              +------------------+
Low address   |    Text (Code)   |  instructions (read-only)
              +------------------+
```
- Stack overflow: deep recursion. Heap exhaustion or memory leak: missing `free`.

## 3. Process States
```
   new --admitted--> ready --scheduler dispatch--> running --exit--> terminated
                      ^  ^                          |  |
                      |  +------interrupt/timeout---+  |
                      |                                | I/O or event wait
                      +---I/O or event completion--- waiting (blocked)
```
| State | Meaning |
|-------|---------|
| New | Being created |
| Ready | In memory, waiting for the CPU |
| Running | Instructions being executed |
| Waiting / Blocked | Waiting for I/O or an event |
| Terminated | Finished execution |
| **Suspended Ready / Suspended Blocked** | Swapped out to disk by the medium-term scheduler (7-state model) |

**Transitions to remember:** Running → Ready (preemption/timeout), Running → Waiting (I/O request), Waiting → Ready (I/O done). There is **no direct Waiting → Running** transition.

## 4. Process Control Block (PCB)
The data structure the OS keeps **per process** (called `task_struct` in Linux). It contains:
- Process ID (PID), parent PID
- Process state
- **Program counter**
- CPU registers
- CPU scheduling info (priority, queue pointers)
- Memory management info (base/limit registers, page tables)
- Accounting info (CPU time used)
- I/O status (open files list, devices)

## 5. Context Switch
Saving the state (PCB) of the current process and loading the state of the next process.
- **Pure overhead:** the system does no useful work while switching.
- Triggered by interrupts, time-slice expiry, I/O requests, or system calls.
- Cost depends on hardware support. Thread switches are cheaper than process switches (same address space, no TLB flush).

**Context switch vs mode switch:** a mode switch (user ↔ kernel) happens *within* the same process and is cheaper. A context switch changes the running process.

## 6. Schedulers
| Scheduler | Also called | Job | Frequency |
|-----------|-------------|-----|-----------|
| **Long-term** | Job scheduler | Picks jobs from the job pool into memory (ready queue). Controls **degree of multiprogramming** | Infrequent |
| **Short-term** | CPU scheduler | Picks a ready process for the CPU | Very frequent (ms) |
| **Medium-term** | Swapper | Swaps processes out/in (suspend/resume) to reduce load | Medium |

- **Dispatcher:** the module that actually gives the CPU to the selected process (context switch, switch to user mode, jump to PC). The time it takes is **dispatch latency**.
- **Queues:** job queue, ready queue, device (I/O) queues.
- **I/O-bound vs CPU-bound processes:** a good long-term scheduler mixes both.

## 7. Process Creation: `fork()` and `exec()`
- `fork()` creates a **child** that is a copy of the parent. It returns:
  - `0` in the child
  - the child's PID (>0) in the parent
  - `-1` on failure
- `exec()` family replaces the process's memory image with a new program (the PID stays the same).
- `wait()` makes the parent wait for the child to finish.
- `exit()` terminates the process.
- Modern systems use **Copy-on-Write (COW):** parent and child share pages until one of them writes.

```c
int main() {
    pid_t pid = fork();
    if (pid == 0)       printf("Child\n");
    else if (pid > 0) { wait(NULL); printf("Parent\n"); }
    else                printf("Fork failed\n");
}
```

### ⭐ Classic fork question
```c
fork(); fork(); fork();
printf("Hello\n");
```
- Number of processes = **2ⁿ = 8**, so "Hello" prints **8 times**.
- Number of **child processes created = 2ⁿ − 1 = 7**.

```c
if (fork() && fork()) fork();   // && short-circuits → total processes = 4
```
Explanation: the 1st fork gives P and C1. In C1 the 1st fork returned 0, so `&&` stops. P runs the 2nd fork → P, C2. In C2 the 2nd returned 0, so it stops. P runs the 3rd fork → C3. Total = P, C1, C2, C3 = **4**.

```c
if (fork() || fork()) fork();   // total = 5
```

## 8. Zombie and Orphan Processes
- **Zombie:** the child has terminated but the parent hasn't called `wait()` yet. Its PCB entry remains in the process table (state `Z`). Too many zombies exhaust PIDs. Fix: the parent calls `wait()`, or handles `SIGCHLD`.
- **Orphan:** the parent terminated before the child. The child is **adopted by init/systemd (PID 1)**, which reaps it later.
- **Daemon:** a background process with no controlling terminal (sshd, crond).

## 9. Threads
A **thread** is the basic unit of CPU utilization, a "lightweight process".
- **Shared by threads of the same process:** code, data (globals), heap, open files, signals.
- **Private to each thread:** **thread ID, program counter, registers, stack**.

### Process vs Thread
| Process | Thread |
|---------|--------|
| Heavyweight | Lightweight |
| Separate address space | Shares the process's address space |
| Creation and context switch are expensive | Cheap |
| Communication via IPC (slow) | Communicate via shared memory (fast) |
| One crashing doesn't affect others | One thread crashing can kill the whole process |
| Isolated, more secure | Less isolation |

### Benefits of multithreading
Responsiveness (UI stays responsive), resource sharing, economy, and scalability on multicore systems.

### User-level vs Kernel-level threads
| User-Level Threads (ULT) | Kernel-Level Threads (KLT) |
|--------------------------|----------------------------|
| Managed by a user library; the kernel doesn't know about them | Managed by the OS |
| Fast to create and switch | Slower |
| If one thread blocks, the **whole process blocks** | Other threads keep running |
| Can't use multiple CPUs in parallel | True parallelism on multicore |
| e.g. green threads | e.g. Linux pthreads (1:1), Windows threads |

### Multithreading models
- **Many-to-One:** many ULTs → 1 KLT. One block blocks all. No parallelism.
- **One-to-One:** each ULT → one KLT. Parallelism, but thread creation has overhead. Used by **Linux and Windows**.
- **Many-to-Many:** many ULTs → an equal or smaller number of KLTs. Flexible.

**Concurrency vs Parallelism:** concurrency means making progress on several tasks at once (interleaving, possible on 1 core). Parallelism means actually running at the same instant (needs multiple cores).

## 10. Inter-Process Communication (IPC)
Processes are **independent** or **cooperating**. Cooperating processes need IPC.

**Two fundamental models:**
1. **Shared memory:** a region shared by the processes. Fast (no kernel involvement after setup) but needs synchronization.
2. **Message passing:** `send()`/`receive()` via the kernel. Easier and suited to distributed systems, but slower.

**IPC mechanisms:**
| Mechanism | Notes |
|-----------|-------|
| **Pipe** (anonymous) | Unidirectional, between related (parent-child) processes. `ls \| grep txt` |
| **Named pipe (FIFO)** | Has a name in the file system, works between unrelated processes |
| **Message queue** | Messages stored in a kernel queue |
| **Shared memory** | Fastest IPC |
| **Semaphores** | For synchronization |
| **Sockets** | Communication across the network or locally |
| **Signals** | Asynchronous notifications (`SIGKILL`, `SIGINT`, `SIGTERM`) |
| **Memory-mapped files** | `mmap()` |

**SIGKILL (9) vs SIGTERM (15):** SIGTERM asks the process to terminate and can be caught or handled. SIGKILL can't be caught or ignored. `Ctrl+C` sends **SIGINT**.

## 11. Common Interview Questions
1. Difference between a process and a program?
2. Difference between a process and a thread? (use the table)
3. What is a PCB, and what does it contain?
4. What is a context switch, and why is it overhead?
5. What does `fork()` return? How many processes do *n* forks create?
6. What are zombie and orphan processes?
7. What do threads share, and what is private to each?
8. User vs kernel threads?
9. IPC mechanisms? Which is the fastest? (**Shared memory**)
10. Why is a thread context switch faster than a process context switch? (Same address space, no page-table/TLB switch.)

## MCQ Traps
- Threads **don't share the stack or registers**.
- `n` forks → `2ⁿ` total processes, `2ⁿ − 1` new ones.
- An orphan is adopted by **init (PID 1)**.
- The long-term scheduler controls the **degree of multiprogramming**.
- A process moves Waiting → **Ready** (not Running) after I/O completes.
