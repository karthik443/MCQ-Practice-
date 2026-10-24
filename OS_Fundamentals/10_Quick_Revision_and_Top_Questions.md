# 10 — Quick Revision (Read this right before the interview)

## A. One-line definitions
| Term | One-liner |
|------|-----------|
| OS | Software that manages hardware and provides services to programs |
| Kernel | Core of the OS, runs in privileged mode |
| System call | The interface through which a user program requests an OS service (via a trap) |
| Process | A program in execution |
| Thread | Lightweight unit of execution inside a process. Shares code, data, and heap; has its own stack and registers |
| PCB | Data structure holding all the info about a process |
| Context switch | Save the state of one process, load another's. Pure overhead |
| Zombie | Finished child whose parent hasn't called `wait()` |
| Orphan | Child whose parent died. Adopted by init (PID 1) |
| Race condition | The result depends on the timing or order of concurrent access |
| Critical section | Code that accesses shared resources |
| Mutex | Lock with ownership, one holder at a time |
| Semaphore | Integer with atomic wait/signal. Binary or counting |
| Monitor | High-level construct. One process inside at a time, plus condition variables |
| Deadlock | Processes wait on each other forever in a cycle |
| Starvation | A process waits indefinitely while others progress. Fixed by aging |
| Paging | Non-contiguous allocation using fixed-size pages and frames |
| Segmentation | Variable-size logical segments (code, stack, and so on) |
| TLB | Hardware cache for page-table entries |
| Virtual memory | Run programs larger than RAM by keeping only the needed parts in memory |
| Page fault | Accessed page isn't in RAM, so there's a trap to the OS |
| Thrashing | More time spent paging than executing |
| Belady's anomaly | More frames → more faults (FIFO) |
| Inode | Unix structure with file metadata and block pointers (no file name) |
| DMA | Device ↔ memory transfer without the CPU handling each byte |
| Spooling | Queue jobs on disk for a slow device (printer) |

## B. Formulas cheat sheet
| What | Formula |
|------|---------|
| Turnaround time | TAT = CT − AT |
| Waiting time | WT = TAT − BT |
| Response time | RT = first CPU time − AT |
| SJF prediction | τₙ₊₁ = α·tₙ + (1 − α)·τₙ |
| HRRN ratio | (WT + BT) / BT |
| fork count | n forks → 2ⁿ processes, 2ⁿ − 1 children |
| Deadlock-free resources | R ≥ n(k − 1) + 1 |
| Semaphore final value | S − (#P ops) + (#V ops) |
| Paging address | page = addr / page_size, offset = addr mod page_size |
| Physical address | frame × page_size + offset |
| Page-table size | (#pages) × (PTE size) |
| TLB EAT | h(t + m) + (1 − h)(t + 2m) |
| Page-fault EAT | (1 − p)·m + p·(fault service time) |
| Avg rotational latency | ½ × (60 / RPM) seconds |
| Disk access time | seek + rotational latency + transfer |
| Inode max file size | (direct + P + P² + P³) × block size, where P = block size / pointer size |

## C. "Which one…?" quick answers
- Minimum average waiting time → **SJF / SRTF**
- Best for time-sharing → **Round Robin**
- Convoy effect → **FCFS**
- Starvation possible → **SJF, SRTF, Priority, SSTF, MLQ**
- Starvation fix → **Aging**
- Belady's anomaly → **FIFO**
- Optimal page replacement → **OPT** (not implementable)
- Fastest IPC → **Shared memory**
- Elevator algorithm → **SCAN**
- Uniform wait time (disk) → **C-SCAN**
- Deadlock avoidance → **Banker's algorithm**
- Deadlock handling in Linux/Windows → **Ostrich (ignore)**
- Most practical prevention → **Break circular wait (resource ordering)**
- Paging causes → **internal** fragmentation
- Segmentation / variable partitioning cause → **external** fragmentation
- Fix external fragmentation → **Compaction / paging**
- Controls degree of multiprogramming → **Long-term scheduler**
- Swapping is done by → **Medium-term scheduler**
- Translates logical → physical addresses → **MMU**
- Priority inversion fix → **Priority inheritance**
- Linux scheduler → **CFS (red-black tree)**, replaced by **EEVDF** in kernel 6.6+
- Linux threading model → **One-to-one**
- Kernel type of Linux → **Monolithic** (with loadable modules)

## D. Top 60 Interview Questions (answer each out loud)

### Basics
1. What is an OS? What are its main functions?
2. Types of OS: batch, multiprogramming, time-sharing, RTOS, distributed.
3. Kernel vs shell vs OS.
4. Monolithic vs microkernel vs hybrid kernel.
5. User mode vs kernel mode, and why we need them.
6. What is a system call? Give 5 examples.
7. What happens when you boot a computer?
8. What is an interrupt? Hardware vs software interrupt.
9. What is a virtual machine? Type 1 vs Type 2 hypervisor. VM vs container.
10. 32-bit vs 64-bit OS.

### Processes & Threads
11. Program vs process.
12. Process states and transitions.
13. What is a PCB?
14. Context switch: what is saved, and why is it overhead?
15. Process vs thread (at least 5 differences).
16. What do threads share, and what is private?
17. User-level vs kernel-level threads.
18. Multithreading models.
19. `fork()` return values, and how many times "Hello" prints.
20. `fork()` vs `exec()`.
21. Zombie vs orphan process.
22. IPC mechanisms. Shared memory vs message passing.
23. Concurrency vs parallelism.
24. Long, short, and medium-term schedulers.

### CPU Scheduling
25. Preemptive vs non-preemptive.
26. Explain FCFS, SJF, SRTF, RR, and priority.
27. Which gives the minimum waiting time? Why is it impractical?
28. Convoy effect.
29. Starvation and aging.
30. Effect of the time quantum in RR.
31. Multilevel feedback queue.

### Synchronization
32. Race condition, with an example.
33. Critical-section requirements.
34. Peterson's solution.
35. Mutex vs semaphore. ⭐⭐
36. Binary vs counting semaphore.
37. Producer-consumer using semaphores.
38. Readers-writers problem.
39. Dining philosophers and how to avoid deadlock.
40. Spinlock: when is it good?
41. Priority inversion.
42. What is a monitor?

### Deadlock
43. Define deadlock, with an example.
44. Four necessary conditions.
45. Prevention vs avoidance vs detection.
46. Banker's algorithm, with an example.
47. Safe vs unsafe state.
48. Deadlock vs starvation vs livelock.

### Memory
49. Logical vs physical address. The role of the MMU.
50. Internal vs external fragmentation.
51. Paging: how does address translation work?
52. TLB and effective access time.
53. Paging vs segmentation.
54. What is virtual memory? Its advantages?
55. Demand paging and page-fault handling steps.
56. FIFO vs LRU vs Optimal. Belady's anomaly.
57. Thrashing: cause and solution.
58. Implement an LRU cache (coding).

### Files & Disk
59. Inode, hard link vs soft link, and file allocation methods.
60. Disk scheduling algorithms, DMA, and RAID levels.

## E. Scenario questions interviewers love
- **"Your system becomes very slow when you open many apps. Why?"** → Thrashing: not enough RAM, so there's heavy paging. Close apps or add RAM. The OS can reduce multiprogramming.
- **"Two threads increment a counter 1,000,000 times each, and the result is less than 2,000,000. Why? How do you fix it?"** → Race condition, because `count++` isn't atomic. Fix it with a mutex or an atomic variable.
- **"How does Chrome isolate tabs?"** → A separate process per tab (site isolation). One tab crashing doesn't kill the others. This trades memory for security and stability.
- **"What happens when you run `./a.out`?"** → The shell `fork()`s → the child `exec()`s → the loader maps the ELF into memory (text, data, BSS, heap, stack) → pages load through demand paging (page faults) → `main()` runs → `exit()` → the parent `wait()`s and reaps the child.
- **"Why is a thread switch faster than a process switch?"** → Same address space, so the page table doesn't change, and there's no TLB flush or cache pollution.
- **"How would you detect a deadlock in a running Java or C++ program?"** → Thread dump (`jstack`) or gdb, look for a cycle among threads waiting on locks. Prevent it with lock ordering or `tryLock` with a timeout.

## F. Useful Linux commands (sometimes asked)
| Command | Purpose |
|---------|---------|
| `ps aux`, `top`, `htop` | View processes |
| `kill -9 PID`, `kill -15 PID` | SIGKILL / SIGTERM |
| `nice`, `renice` | Change priority (−20 highest … 19 lowest) |
| `free -h`, `vmstat` | Memory usage / paging stats |
| `df -h`, `du -sh` | Disk usage |
| `ls -i` | Show inode numbers |
| `ln`, `ln -s` | Hard / soft link |
| `chmod`, `chown` | Permissions / ownership |
| `lsof` | List open files |
| `strace` | Trace system calls |
| `jobs`, `bg`, `fg`, `&`, `nohup` | Job control |

---
**Final tip:** for each topic, remember *definition → example → trade-off*. If you can draw the process state diagram, a Gantt chart, a paging translation diagram, and a RAG on a whiteboard, you're well prepared. All the best! 🚀
