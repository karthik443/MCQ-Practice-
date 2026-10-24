# 01 — OS Basics

## 1. What is an Operating System?
An **Operating System (OS)** is system software that sits between hardware and users/applications. It **manages resources** (CPU, memory, I/O, files) and **provides services** to programs.

**Two views:**
- **Resource manager / allocator**: decides who gets the CPU, memory, and devices, and when.
- **Extended machine / abstraction**: hides hardware complexity (for example, you call `read()` instead of programming the disk controller).

**Goals:** convenience, efficiency, the ability to evolve, protection and security.

**Examples:** Windows, Linux, macOS, Android, iOS, Unix.

## 2. Functions of an OS
| Function | What it does |
|----------|--------------|
| Process management | Create/delete processes, scheduling, synchronization, IPC, deadlock handling |
| Memory management | Allocate/deallocate memory, track usage, virtual memory |
| File management | Create/delete files and directories, map files to storage |
| I/O / device management | Device drivers, buffering, caching, spooling |
| Secondary storage management | Free-space management, disk scheduling |
| Security & protection | Authentication, access control |
| User interface | CLI (shell), GUI |
| Networking | Protocol stacks, sockets |

## 3. Types of Operating Systems
| Type | Idea | Example / Note |
|------|------|----------------|
| **Batch OS** | Similar jobs grouped and run without user interaction | Early IBM mainframes. CPU idles during I/O. |
| **Multiprogramming** | Several programs in memory. When one waits for I/O, the CPU switches to another | Goal: **maximize CPU utilization** |
| **Multitasking / Time-sharing** | Multiprogramming + very fast switching (time slices) for interactivity | Goal: **minimize response time**. Unix. |
| **Multiprocessing** | 2+ CPUs share memory and bus | Symmetric (SMP) vs Asymmetric (AMP) |
| **Distributed OS** | Many independent computers appear as one system | Loosely coupled |
| **Network OS** | Machines share resources over a network, each keeps its own OS | Windows Server, Novell NetWare |
| **Real-Time OS (RTOS)** | Hard deadlines | **Hard RTOS** (airbag, pacemaker: a missed deadline means failure), **Soft RTOS** (video streaming: a miss degrades quality). VxWorks, FreeRTOS |
| **Embedded OS** | Runs on dedicated devices | Washing machines, routers |
| **Mobile OS** | Touch, battery-aware | Android, iOS |

**Multiprogramming vs Multitasking vs Multiprocessing vs Multithreading**
- *Multiprogramming*: many programs in memory, 1 CPU, switch **on I/O wait**.
- *Multitasking*: many programs, 1 CPU, switch **on time quantum** (preemptive).
- *Multiprocessing*: **many CPUs** running processes truly in parallel.
- *Multithreading*: many threads **inside one process**.

## 4. Kernel
The **kernel** is the core of the OS. It is always in memory and runs in privileged mode.

| Kernel type | Description | Pros | Cons | Example |
|-------------|-------------|------|------|---------|
| **Monolithic** | All services (FS, drivers, memory, scheduling) in kernel space | Fast (no message passing) | Large; one bug can crash everything | Linux, older Unix |
| **Microkernel** | Only minimal services (IPC, basic scheduling, memory) in kernel; the rest run in user space as servers | Reliable, secure, extensible | Slower (IPC overhead) | Minix, QNX, L4 |
| **Hybrid** | Mix of both | Balance | Complex | Windows NT, macOS (XNU) |
| **Exokernel** | Very small kernel that lets apps manage hardware directly | Flexible | Hard to program | Research |

**Shell vs Kernel:** the shell is a user-space program that interprets commands (bash). The kernel does the actual work.

## 5. User Mode vs Kernel Mode (Dual-Mode Operation)
- A **mode bit** in hardware: **0 = kernel**, **1 = user**.
- **Privileged instructions** (I/O, setting timer, changing mode bit, disabling interrupts) run only in kernel mode.
- The user → kernel switch happens through a **system call, interrupt, or trap/exception**.
- **Why?** Protection: a buggy or malicious user program can't damage the OS or other programs.

## 6. System Calls
A **system call** is the programmatic interface through which a user program requests an OS service. It works via a **trap** (software interrupt) into kernel mode.

Flow: `printf()` (library) → `write()` system call → trap → kernel handler → return to user mode.

**Types of system calls:**
| Category | Linux examples |
|----------|----------------|
| Process control | `fork()`, `exec()`, `exit()`, `wait()`, `kill()` |
| File management | `open()`, `read()`, `write()`, `close()`, `lseek()` |
| Device management | `ioctl()`, `read()`, `write()` |
| Information maintenance | `getpid()`, `alarm()`, `sleep()`, `time()` |
| Communication | `pipe()`, `shmget()`, `mmap()`, `socket()` |
| Protection | `chmod()`, `chown()`, `umask()` |

**Parameter passing** to system calls: registers, a block/table in memory (address in a register), or the stack.

**API vs system call:** an API (such as POSIX or the Win32 API) is a library function that *may* invoke one or more system calls.

## 7. Interrupts
- An **interrupt** is a signal to the CPU that an event needs attention.
- **Hardware interrupt:** from devices (keyboard, disk done, timer).
- **Software interrupt / trap:** from a program (system call, divide-by-zero, page fault).
- **ISR (Interrupt Service Routine):** the handler. Its address is found through the **Interrupt Vector Table**.
- **Polling vs interrupts:** with polling the CPU repeatedly checks the device (wasteful). With interrupts the device notifies the CPU (efficient).

## 8. Booting Process
1. Power on → CPU executes firmware (**BIOS/UEFI**) from ROM.
2. **POST** (Power-On Self Test) checks hardware.
3. BIOS finds the boot device and loads the **bootloader** (MBR: first 512 bytes. UEFI: GPT/EFI partition).
4. Bootloader (GRUB, Windows Boot Manager) loads the **kernel** into memory.
5. Kernel initializes drivers and memory, mounts the root FS, and starts the first process (`init`/`systemd`, PID 1).
6. Services start → login screen.

**Bootstrap program:** the initial program, stored in ROM/EEPROM, that loads the OS.

## 9. Other Must-Know Terms
- **Spooling** (Simultaneous Peripheral Operations On-Line): buffer jobs on disk for a slow device (for example, a printer queue).
- **Buffering:** temporary storage while transferring data between devices of different speeds.
- **Caching:** keep a copy of frequently used data in faster storage.
- **Virtual Machine / Hypervisor:** runs multiple OSes on one machine. **Type 1 (bare-metal):** VMware ESXi, Hyper-V, Xen. **Type 2 (hosted):** VirtualBox, VMware Workstation.
- **Containers vs VMs:** containers share the host kernel (lightweight, e.g. Docker). VMs each have a full guest OS.
- **32-bit vs 64-bit OS:** a 32-bit OS can address at most 2³² = **4 GB** of memory.
- **POSIX:** a standard API for Unix-like OSes.

## 10. Common Interview Questions
1. **What is an OS? Why do we need it?** Resource manager + abstraction. Without it, every program would have to manage hardware itself.
2. **Kernel vs OS?** The kernel is the core part. The OS = kernel + system utilities + UI + libraries.
3. **Monolithic vs microkernel?** See the table above. Linux is monolithic but supports loadable kernel modules.
4. **What happens when you type a command in the shell?** Shell parses it → `fork()` → the child calls `exec()` to load the program → the parent `wait()`s → output → the prompt returns.
5. **Why dual mode?** Protection of the OS from user programs.
6. **What is a system call? Give examples.**
7. **Difference between multiprogramming and multitasking?**
8. **What is an RTOS? Hard vs soft?**
9. **What happens when you power on a computer?** The boot sequence above.

## MCQ Traps
- Mode bit **0 = kernel**, **1 = user**.
- **Multiprogramming** increases **CPU utilization**. **Time-sharing** reduces **response time**.
- The first process in Linux is **init/systemd with PID 1** (PID 0 is the scheduler/swapper/idle process).
- Setting the timer, clearing memory, turning off interrupts, and I/O instructions are **privileged**. **Reading the clock** and **switching from user to kernel mode via a trap** are *not* privileged.
