# 09 — Disk Scheduling & I/O Systems

## 1. Disk Structure (HDD)
- **Platters** → **surfaces** → **tracks** (concentric circles) → **sectors** (smallest unit, usually 512 B / 4 KB).
- **Cylinder:** the set of tracks at the same arm position across all platters.
- A **read/write head** for each surface sits on an arm, and all arms move together.
- **Disk capacity** = surfaces × tracks per surface × sectors per track × bytes per sector.

### Disk Access Time ⭐
```
Access time = Seek time + Rotational latency + Transfer time (+ controller overhead)
```
- **Seek time:** move the head to the correct track (usually the largest component).
- **Rotational latency:** wait for the sector to rotate under the head. **Average = ½ rotation time**.
- **Transfer time:** the time to read the data.

**Example:** 7200 RPM → one rotation = 60/7200 s = **8.33 ms** → average rotational latency = **4.17 ms**.

**SSD:** no moving parts, so there's no seek or rotation. Faster random access, but it has a limited number of write cycles (wear levelling). Disk scheduling matters much less. Linux often uses the `none`/`mq-deadline` scheduler for SSDs.

## 2. Disk Scheduling Algorithms ⭐
**Goal:** minimize **total head movement** (seek time).

**Standard example:** Cylinders 0–199. Head at **53**, moving toward **higher** cylinders.
Request queue: **98, 183, 37, 122, 14, 124, 65, 67**

### 2.1 FCFS
Serve the requests in arrival order.
53 → 98 → 183 → 37 → 122 → 14 → 124 → 65 → 67
= 45 + 85 + 146 + 85 + 108 + 110 + 59 + 2 = **640 cylinders**
- Fair and simple, but causes large, wild swings of the head.

### 2.2 SSTF (Shortest Seek Time First)
Always go to the closest pending request.
53 → 65 → 67 → 37 → 14 → 98 → 122 → 124 → 183
= 12 + 2 + 30 + 23 + 84 + 24 + 2 + 59 = **236 cylinders**
- Much better than FCFS, but it can cause **starvation** of far-away requests. It's not optimal either.

### 2.3 SCAN (Elevator Algorithm)
The head moves in one direction to the **end of the disk**, serving requests, then reverses.
53 → 65 → 67 → 98 → 122 → 124 → 183 → **199** → 37 → 14
= (199 − 53) + (199 − 14) = 146 + 185 = **331 cylinders**
(If the head were moving toward 0 instead: 53 → 37 → 14 → **0** → 65 … 183 = 53 + 183 = **236**.)

### 2.4 C-SCAN (Circular SCAN)
Moves to the end, **jumps back to the start (cylinder 0) without serving**, then continues in the same direction. This gives a **more uniform wait time**.
53 → 65 → 67 → 98 → 122 → 124 → 183 → **199** → *(jump)* **0** → 14 → 37
= 146 + 199 (return) + 37 = **382 cylinders** (or **183** if the question says not to count the return jump)

### 2.5 LOOK
Like SCAN, but the head goes only as far as the **last request** in each direction (not to the disk end).
53 → 65 → 67 → 98 → 122 → 124 → **183** → 37 → 14
= (183 − 53) + (183 − 14) = 130 + 169 = **299 cylinders**

### 2.6 C-LOOK
Like C-SCAN, but it jumps from the last request to the **lowest pending request** (not to 0).
53 → … → **183** → *(jump)* **14** → 37
= 130 + 169 (jump) + 23 = **322 cylinders** (or **153** if the jump isn't counted)

### Summary
| Algorithm | Total movement | Starvation? | Notes |
|-----------|----------------|-------------|-------|
| FCFS | 640 | No | Simple, poor performance |
| SSTF | 236 | **Yes** | Good for light load |
| SCAN | 331 | No | Good for heavy load |
| C-SCAN | 382 (183) | No | Most uniform wait time |
| LOOK | 299 | No | Practical SCAN |
| C-LOOK | 322 (153) | No | Practical C-SCAN |

⚠️ **Always check the MCQ** for the head direction, the disk range, and whether the return jump counts.

## 3. RAID (Redundant Array of Independent Disks) ⭐
| Level | Technique | Min disks | Fault tolerance | Note |
|-------|-----------|-----------|-----------------|------|
| **RAID 0** | **Striping** | 2 | ❌ None | Fastest, full capacity, one failure loses everything |
| **RAID 1** | **Mirroring** | 2 | ✅ 1 disk | 50% capacity, fast reads |
| RAID 2 | Bit-level striping + Hamming ECC | – | ✅ | Obsolete |
| RAID 3 | Byte-level striping + dedicated parity | 3 | ✅ 1 | Rare |
| RAID 4 | Block-level striping + **dedicated parity disk** | 3 | ✅ 1 | The parity disk is a bottleneck |
| **RAID 5** | Block striping + **distributed parity** | 3 | ✅ 1 disk | Popular. Capacity = (n−1) disks |
| **RAID 6** | Block striping + **double distributed parity** | 4 | ✅ 2 disks | Capacity = (n−2) disks |
| **RAID 10 (1+0)** | Mirror, then stripe | 4 | ✅ (1 per mirror pair) | Fast + safe, 50% capacity |

## 4. I/O Systems
### I/O techniques
| Technique | How it works | CPU involvement |
|-----------|--------------|-----------------|
| **Programmed I/O (polling)** | The CPU busy-waits, checking device status | Very high (wasteful) |
| **Interrupt-driven I/O** | The device interrupts the CPU when ready | Medium (an interrupt per word/byte) |
| **DMA (Direct Memory Access)** ⭐ | The DMA controller moves a **whole block** between device and memory. The CPU is interrupted **once**, at the end | Low. Best for bulk transfers |

- **Cycle stealing:** the DMA controller takes the memory bus for a cycle, which slightly slows the CPU.

### Kernel I/O subsystem services
- **Scheduling:** ordering I/O requests.
- **Buffering:** handles speed mismatch and transfer-size mismatch between devices. Single, **double buffering**, or circular buffers.
- **Caching:** keeps copies of data in faster storage.
- **Spooling:** holds output for a device that can't accept interleaved streams (printer).
- **Device reservation:** exclusive access.
- **Error handling.**

### Device types
- **Block devices:** disks (read/write/seek in blocks).
- **Character devices:** keyboard, mouse, serial port (a stream of bytes).
- **Network devices:** sockets.

### Blocking vs Non-blocking vs Asynchronous I/O
- **Blocking:** the process is suspended until the I/O completes.
- **Non-blocking:** returns immediately with whatever data is available.
- **Asynchronous:** returns immediately, and the process is notified later when the I/O is done.

**Device driver:** OS software that knows how to talk to a specific device controller. It gives the kernel a uniform interface.

## 5. Common Interview Questions
1. What are the components of disk access time?
2. Explain SCAN vs C-SCAN, and LOOK vs C-LOOK.
3. Which disk scheduling algorithm can cause starvation? (**SSTF**)
4. Solve total head movement for a given queue.
5. What is DMA, and why is it used?
6. Polling vs interrupts?
7. RAID 0 vs 1 vs 5? Which RAID level would you use for a database? (RAID 10 for performance + redundancy, RAID 5/6 for capacity.)
8. Buffering vs caching vs spooling?
9. HDD vs SSD?

## MCQ Traps
- SCAN is also called the **elevator algorithm**.
- C-SCAN gives a **more uniform** wait time than SCAN.
- LOOK/C-LOOK don't go to the disk ends.
- RAID 0 has **no redundancy**. It isn't really "redundant".
- Average rotational latency = **half** a rotation.
