# 05 — Transactions & Concurrency Control

## 1. Transaction & ACID ⭐⭐⭐
A **transaction** is a logical unit of work (one or more operations) that must execute fully or not at all. Example: transfer ₹100 from A to B = read A, A −= 100, write A, read B, B += 100, write B.

| Property | Meaning | Ensured by |
|----------|---------|------------|
| **Atomicity** | All or nothing | Recovery manager (undo via log / rollback) |
| **Consistency** | DB moves from one valid state to another (constraints hold) | Application + constraints |
| **Isolation** | Concurrent transactions don't interfere; appear serial | **Concurrency control** (locks, MVCC) |
| **Durability** | Committed changes survive crashes | Write-ahead log, redo, backups |

### Transaction states
**Active → Partially committed → Committed** ; **Active/Partially committed → Failed → Aborted** (rolled back). After abort: restart or kill.

## 2. Concurrency Problems ⭐
| Problem | Description |
|---------|-------------|
| **Dirty read** | Read **uncommitted** data of another transaction that later rolls back |
| **Non-repeatable read** | Same row read twice gives **different values** (another txn updated and committed in between) |
| **Phantom read** | Same query twice returns **different set of rows** (another txn inserted/deleted rows) |
| **Lost update** | Two transactions overwrite each other's update |

### Isolation levels (SQL standard) ⭐⭐
| Level | Dirty read | Non-repeatable | Phantom |
|-------|:--:|:--:|:--:|
| **Read Uncommitted** | Possible | Possible | Possible |
| **Read Committed** | ✗ | Possible | Possible |
| **Repeatable Read** | ✗ | ✗ | Possible |
| **Serializable** | ✗ | ✗ | ✗ |

Higher isolation = more correctness, less concurrency. Defaults: **PostgreSQL / Oracle / SQL Server = Read Committed; MySQL InnoDB = Repeatable Read.**

## 3. Schedules & Serializability ⭐⭐
- **Schedule:** order of operations from multiple transactions. **Serial:** one transaction at a time (always correct). **Serializable:** equivalent to some serial schedule.
- **Conflicting operations:** belong to different transactions, same data item, at least one is a **write** (R–W, W–R, W–W conflict; **R–R does not conflict**).

### Conflict serializability
Build a **precedence (serialization) graph**: a node per transaction; edge Ti → Tj if an operation of Ti conflicts with and precedes one of Tj. **Schedule is conflict serializable iff the graph has NO cycle.** Serial order = topological order.

**Example:** S: R1(A) W2(A) W1(A) → edges T1→T2 (R1–W2) and T2→T1 (W2–W1) → cycle → **not conflict serializable**.

- **View serializability:** weaker (more schedules qualify). **Conflict serializable ⇒ view serializable**, not the reverse (the difference arises through blind writes). Testing view serializability is NP-complete.

### Recoverability ⭐
| Type | Rule |
|------|------|
| **Recoverable** | If Tj reads data written by Ti, **Ti commits before Tj commits** |
| **Cascadeless (ACA)** | Transactions read only **committed** data (no cascading rollback) |
| **Strict** | No read **or write** of a data item until the last writer commits/aborts |
- **Strict ⊂ Cascadeless ⊂ Recoverable.** Irrecoverable schedule: Tj commits after reading Ti's uncommitted write, then Ti aborts.
- **Cascading rollback:** abort of Ti forces aborts of dependent transactions.

## 4. Locking Protocols ⭐
- **Shared lock (S):** read; many allowed. **Exclusive lock (X):** write; only one.
- **Compatibility:** S–S ✔, S–X ✗, X–X ✗.
- **Two-Phase Locking (2PL):** **growing phase** (acquire locks, no release) then **shrinking phase** (release, no new locks). **Guarantees conflict serializability**, but **doesn't prevent deadlock** and may cause cascading rollbacks.
- **Strict 2PL:** hold all **exclusive** locks until commit/abort → avoids cascading rollbacks (strict schedules).
- **Rigorous 2PL:** hold **all** locks until commit.
- **Conservative 2PL:** acquire all locks up front → **deadlock-free**.
- **Lock granularity:** row / page / table / database. Finer = more concurrency, more overhead. **Intention locks (IS, IX)** support multi-granularity locking.

### Timestamp-based protocol
Each transaction gets a timestamp at start. Conflicting operations must execute in timestamp order; otherwise roll back the violating transaction. **Deadlock-free**, but may cause starvation and cascading aborts. **Thomas write rule** ignores outdated writes.

### MVCC (Multi-Version Concurrency Control) ⭐
Keep multiple versions of each row. **Readers don't block writers and writers don't block readers** (readers see a snapshot). Used in PostgreSQL, Oracle, MySQL InnoDB. **Snapshot isolation** prevents dirty/non-repeatable reads but allows **write skew**.

### Optimistic vs pessimistic
- **Pessimistic:** lock first (assume conflicts). **Optimistic (OCC):** read/compute, validate at commit, retry on conflict (version/timestamp column). Good for low-contention workloads.

## 5. Deadlock in DBMS
Transactions wait for each other's locks in a cycle.
- **Detection:** **wait-for graph**, a cycle means deadlock. Victim: roll back one transaction (youngest / least work).
- **Prevention (by timestamps):**
  - **Wait-Die** (non-preemptive): older waits for younger; younger **dies** (aborts) if it requests a lock held by older.
  - **Wound-Wait** (preemptive): older **wounds** (aborts) younger; younger waits for older.
- **Timeout**-based abort is common in practice.
- Avoid by **consistent lock ordering** and short transactions.

## 6. Recovery ⭐
- **Failure types:** transaction failure (logic error), system crash (power loss, memory loss), **disk failure**.
- **Log:** records `<T start>`, `<T, X, old, new>`, `<T commit>`. **Write-Ahead Logging (WAL):** write the log record to disk **before** modifying the data page. Gives atomicity + durability.
- **Undo** (uncommitted txns), **Redo** (committed txns whose changes weren't flushed).
- **Checkpoint:** periodically flush dirty pages and write a marker, so recovery starts from the last checkpoint (don't scan the whole log).
- **Buffer policies:** **Steal** (may write uncommitted pages to disk → need UNDO) and **No-force** (don't force committed pages to disk at commit → need REDO). Steal + No-force = best performance, needs both UNDO + REDO (**ARIES** algorithm: analysis → redo → undo).
- **Shadow paging:** copy-on-write pages, no log needed.
- **Immediate update** (writes before commit; needs UNDO) vs **deferred update** (writes at commit; needs REDO only).
- **Backups:** full, incremental, differential; **replication** for high availability.

## 7. Common Interview Questions
1. What is a transaction? Explain ACID with an example.
2. Isolation levels and the problems each solves?
3. Dirty read vs non-repeatable read vs phantom read?
4. What is serializability? How do you test conflict serializability?
5. What is 2PL? Does it prevent deadlocks? (No.)
6. Strict 2PL and why is it used?
7. How is deadlock detected and handled? Wait-die vs wound-wait?
8. What is MVCC?
9. What is WAL? Undo vs redo? What's a checkpoint?
10. Optimistic vs pessimistic locking?
11. What is a cascading rollback?
12. Commit vs rollback vs savepoint?

## MCQ Traps
- **ACID: Atomicity → rollback/undo; Durability → log/redo; Isolation → locking; Consistency → constraints.**
- **Read–Read is never a conflict.**
- **Precedence graph cycle ⇒ NOT conflict serializable.**
- **2PL ensures serializability but NOT deadlock freedom.**
- **Strict 2PL ⇒ cascadeless.**
- **Phantom** is solved only by **Serializable**.
- **Wait-Die: older waits, younger dies. Wound-Wait: older wounds, younger waits.**
- **Conflict serializable ⇒ view serializable**.
- **WAL: log first, data later.**
- **MVCC: readers don't block writers.**

## Practice MCQs
1. Reading uncommitted data of another transaction is a → **Dirty read**
2. Which isolation level prevents phantom reads? → **Serializable**
3. Schedule with precedence graph T1→T2→T3→T1 → **Not conflict serializable**
4. Which property is enforced by the recovery manager using a log? → **Atomicity & Durability**
5. In wait-die, a younger transaction requesting a lock held by an older one → **Dies (aborts)**
