# 06 — Indexing, Storage & Query Processing

## 1. Storage Basics
- Data is stored on disk in **blocks/pages** (typically 4–16 KB). Disk I/O is the bottleneck, so DB design minimizes block accesses.
- **Blocking factor** = ⌊block size / record size⌋ (records per block). **Number of blocks** = ⌈records / blocking factor⌉.
- **Heap file:** unordered. **Sorted (sequential) file:** ordered by a key. **Hashed file:** placed by a hash of the key.
- **Buffer pool:** memory cache of pages; replacement policies like LRU.

**Example:** block = 1024 B, record = 100 B → bf = 10. 1000 records → 100 blocks. Linear search = up to 100 block accesses; binary search on sorted data ≈ ⌈log₂ 100⌉ = 7.

## 2. Indexing ⭐⭐
An **index** is a data structure (like a book's index) that finds rows **without scanning the whole table**.

**Pros:** much faster reads (SELECT, WHERE, JOIN, ORDER BY). **Cons:** extra storage; **slower INSERT/UPDATE/DELETE** (the index must be updated).

### Types of indexes
| Type | Description |
|------|-------------|
| **Primary (clustering) index** | On the **ordering key** of a sorted file. Data is physically sorted by it. **One per table** |
| **Clustered index** | Determines the **physical order** of rows. **Only one per table.** (InnoDB: the primary key.) Range queries are fast |
| **Non-clustered (secondary) index** | Separate structure with pointers to rows. **Many per table** |
| **Dense index** | An entry for **every record** |
| **Sparse index** | An entry for **some records** (one per block); requires sorted data |
| **Unique index** | Enforces uniqueness |
| **Composite (multi-column) index** | On several columns. **Leftmost-prefix rule**: index (A,B,C) helps queries on A, (A,B), (A,B,C), not B alone |
| **Covering index** | Contains all columns a query needs, so there's no table lookup |
| **Full-text / spatial / bitmap** | Special use cases. Bitmap = low-cardinality columns (gender) |

- **Primary index** has sparse entries typically; **secondary index must be dense**.
- **Index size:** if a dense index entry = 12 B, block = 1024 B → ~85 entries per block.

### When to index / not to
- **Index:** columns used in WHERE, JOIN, ORDER BY, GROUP BY; **high cardinality** (many distinct values).
- **Avoid:** tiny tables, **low-cardinality** columns, columns updated constantly, too many indexes on write-heavy tables.
- Indexes may be skipped when: a function is applied to the column (`WHERE YEAR(date)=2024`), **leading wildcard** `LIKE '%abc'`, implicit type conversion, `OR` conditions, or the query returns a large part of the table.

## 3. B-Tree & B+ Tree ⭐⭐
Self-balancing **multiway** search trees, designed for disk (high fan-out → very shallow, all leaves at the same level). Search/insert/delete = **O(log n)** block accesses.

| | **B-Tree** | **B+ Tree** |
|--|-----------|------------|
| Data pointers | In **all** nodes | **Only in leaves** |
| Internal nodes | Keys + data | **Keys only** (more keys per node → higher fan-out, shorter tree) |
| Leaf linking | No | **Leaves linked as a linked list** → fast **range queries** and sequential scans |
| Search cost | Can end early | Always goes to a leaf (predictable) |
| Used in | Rare | **Most DBMS indexes** |

**Order/properties (order m):** each node has at most **m children**, at most **m − 1 keys**. Non-root nodes have at least ⌈m/2⌉ children. Root has ≥ 2 children (if not a leaf). **Node split** on overflow (propagates upward); **merge/redistribute** on underflow.

**Height:** ≈ log_m(N). Example: fan-out 100, 1 million records → height ≈ 3.

## 4. Hashing
- **Static hashing:** h(key) → bucket. **Equality lookups O(1)**. **No range queries**, no ordering. Overflow/collisions → chaining or open addressing.
- **Dynamic hashing:** **extendible hashing** and **linear hashing**: buckets grow without rehashing everything.
- Choose **B+ tree** for range queries/sorting; **hash** for exact-match lookups.

## 5. Query Processing & Optimization ⭐
Pipeline: **Parse → validate → relational algebra tree → optimize → execution plan → execute.**
- **Heuristic optimization:** push **selections down** (filter early), push **projections down**, apply the **most restrictive selection first**, avoid Cartesian products.
- **Cost-based optimization:** estimates the cost from **table statistics** (row counts, histograms) and picks the cheapest plan.
- **`EXPLAIN`** shows the plan (full table scan vs index scan).

### Join algorithms
| Algorithm | Idea | Best for |
|-----------|------|----------|
| **Nested loop join** | For each row of outer, scan inner | Small tables; indexed inner |
| **Block nested loop** | Uses memory blocks to cut passes | |
| **Sort-merge join** | Sort both, merge | Sorted inputs, non-equality ranges |
| **Hash join** | Build a hash table on the smaller table, probe | Large, unsorted equi-joins |

- **Full table scan** vs **index scan**. **Index scan isn't always faster** (if the query retrieves a large fraction).
- **External merge sort** for data larger than memory.

## 6. Performance Tips
- Select only needed columns (avoid `SELECT *`).
- Index foreign keys and filter columns. Use `LIMIT`.
- Avoid functions on indexed columns; avoid leading-wildcard LIKE.
- Prefer `JOIN`s / `EXISTS` over nested correlated subqueries where appropriate.
- Use **pagination**, **caching**, **partitioning**, **denormalization** for reads.
- **N+1 query problem** in ORMs: one query for the list + N queries for details. Fix with joins / eager loading.

## 7. Partitioning
- **Horizontal:** split **rows** across partitions (by range/hash/list, e.g. by date). **Vertical:** split **columns**.
- (**Sharding** = horizontal partitioning across different servers. See file 07.)

## 8. Common Interview Questions
1. What is an index? Pros and cons?
2. Clustered vs non-clustered index?
3. Why B+ tree and not binary tree / hash for DB indexes?
4. B-tree vs B+ tree?
5. Dense vs sparse index?
6. What is a composite index? The leftmost-prefix rule?
7. When will an index not be used?
8. What is a covering index?
9. How does the query optimizer work? What is EXPLAIN?
10. Hash index vs B+ tree?
11. How do you speed up a slow query?
12. What is partitioning vs sharding?

## MCQ Traps
- **Only ONE clustered index per table; many non-clustered.**
- **B+ tree: data only in leaves, leaves linked; best for range queries.**
- **Hash indexes can't do range queries.**
- **Indexes speed up reads but slow down writes.**
- **Secondary index is dense; primary can be sparse.**
- **`LIKE '%x'` can't use a normal index; `LIKE 'x%'` can.**
- **Low-cardinality columns are poor B-tree index candidates.**
- **Selection pushdown** is a key heuristic optimization.

## Practice MCQs
1. Which is used for range queries? → **B+ tree**
2. Number of clustered indexes per table → **1**
3. Block 512 B, record 64 B → records per block → **8**
4. A sparse index requires the file to be → **Sorted**
5. Which index type for a gender column (2 values)? → **Bitmap (or none)**
