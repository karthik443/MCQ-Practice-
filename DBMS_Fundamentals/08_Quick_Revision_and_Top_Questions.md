# 08 — Quick Revision (Read this right before the interview)

## A. One-line definitions
| Term | One-liner |
|------|-----------|
| DBMS | Software to create, store, query, and manage databases |
| Data independence | Change one schema level without affecting the next higher level |
| Primary key | Unique + NOT NULL identifier, one per table |
| Candidate key | Minimal super key |
| Foreign key | Attribute referencing another table's primary key |
| Weak entity | Entity with no full key; depends on an owner |
| Referential integrity | FK must be NULL or match an existing PK |
| Normalization | Decompose tables to remove redundancy and anomalies |
| Functional dependency | X → Y: X determines Y |
| 1NF / 2NF / 3NF / BCNF | Atomic / no partial dep. / no transitive dep. / every determinant is a super key |
| Transaction | Logical unit of work, all-or-nothing |
| ACID | Atomicity, Consistency, Isolation, Durability |
| Dirty read | Reading uncommitted data |
| Serializable | Equivalent to some serial execution |
| 2PL | Grow (acquire) then shrink (release) locks |
| Deadlock | Transactions wait on each other in a cycle |
| MVCC | Multiple row versions so readers don't block writers |
| WAL | Log before data write |
| Index | Structure for fast lookup; speeds reads, slows writes |
| Clustered index | Determines the physical row order (one per table) |
| B+ tree | Balanced tree, data in linked leaves, range-query friendly |
| View | Virtual table from a query |
| Trigger | Auto-run code on INSERT/UPDATE/DELETE |
| Sharding | Split data across servers |
| Replication | Copy data across servers |
| CAP | Consistency, Availability, Partition tolerance: pick 2 (CP or AP) |
| OLTP / OLAP | Transactions / analytics |
| SQL injection | Malicious SQL via user input; use parameterized queries |

## B. Formulas & rules cheat sheet
| What | Rule |
|------|------|
| R × S | degree = d₁ + d₂; tuples = m × n |
| R ∪ S tuples | between max(m,n) and m+n |
| R ∩ S tuples | between 0 and min(m,n) |
| Super keys (1 candidate key of 1 attr, n attrs) | 2ⁿ⁻¹ |
| Blocking factor | ⌊block size / record size⌋ |
| Number of blocks | ⌈records / blocking factor⌉ |
| Binary search cost | ⌈log₂ blocks⌉ |
| Attribute closure | Repeatedly add RHS of FDs whose LHS ⊆ closure |
| Candidate key | X⁺ = all attrs, X minimal |
| Lossless join | R1 ∩ R2 → R1 or R2 |
| Conflict serializable | Precedence graph has no cycle |
| Cross join | rows = m × n |
| ROW_NUMBER vs RANK vs DENSE_RANK | 1,2,3,4 / 1,2,2,4 / 1,2,2,3 |
| B+ tree height | ≈ log_fanout(N) |

## C. "Which one…?" quick answers
- Unique but can be NULL → **Unique key**
- Many-to-many in ER → **Separate junction table**
- Remove rows, keep structure, fast → **TRUNCATE** (DDL); conditional removal → **DELETE**
- Filter groups → **HAVING**; filter rows → **WHERE**
- Keep unmatched left rows → **LEFT JOIN**
- Combine without duplicates → **UNION**; keep duplicates → **UNION ALL**
- Hierarchy (employee–manager) → **Self join**
- Nth highest salary → **DENSE_RANK() = N** (or LIMIT/OFFSET)
- Partial dependency → **2NF** fix; transitive → **3NF** fix; non-key determinant → **BCNF** fix
- Highest NF always lossless + dependency-preserving → **3NF**
- Prevents dirty reads → **Read Committed**; prevents phantoms → **Serializable**
- Guarantees serializability → **2PL**; avoids cascading rollback → **Strict 2PL**
- Deadlock prevention (timestamps) → **Wait-Die / Wound-Wait**
- Range queries → **B+ tree**; equality only → **Hash**
- Schema-flexible, horizontally scalable → **NoSQL**
- Caching / sessions → **Redis**; documents → **MongoDB**; relationships → **Neo4j**
- Complex analytics → **OLAP / data warehouse (star schema)**
- Prevent SQL injection → **Prepared statements**

## D. Top 50 interview questions (answer out loud)
**Basics & model**
1. DBMS vs file system?
2. Three-schema architecture and data independence?
3. Types of keys: primary, candidate, super, foreign, unique?
4. ER model: weak entity, cardinality, participation?
5. Integrity constraints? Referential actions?
6. DDL vs DML vs DCL vs TCL?
7. Relational algebra operators? Selection vs projection?

**SQL**
8. WHERE vs HAVING?
9. DELETE vs TRUNCATE vs DROP?
10. All join types with examples?
11. 2nd/Nth highest salary?
12. Find and delete duplicate rows?
13. UNION vs UNION ALL?
14. RANK vs DENSE_RANK vs ROW_NUMBER?
15. NULL handling; COUNT(*) vs COUNT(col)?
16. IN vs EXISTS; correlated subquery?
17. What is a view / CTE?
18. Order of execution of a SQL query?

**Normalization**
19. Why normalize? Anomalies?
20. 1NF, 2NF, 3NF, BCNF with examples?
21. 3NF vs BCNF?
22. Functional dependency, closure, candidate key finding?
23. Lossless and dependency-preserving decomposition?
24. Denormalization: when and why?

**Transactions**
25. ACID with an example?
26. Isolation levels and anomalies?
27. Dirty vs non-repeatable vs phantom?
28. Conflict serializability; precedence graph?
29. 2PL and strict 2PL?
30. Deadlock: detection, wait-die, wound-wait?
31. MVCC?
32. WAL, checkpoint, undo/redo?
33. Optimistic vs pessimistic locking?

**Indexing & performance**
34. What is an index? Trade-offs?
35. Clustered vs non-clustered?
36. B-tree vs B+ tree; why B+ trees?
37. Hash index vs B+ tree?
38. Composite index and leftmost-prefix rule?
39. When is an index not used?
40. How do you optimize a slow query? EXPLAIN?
41. Join algorithms (nested loop, hash, sort-merge)?

**NoSQL & advanced**
42. SQL vs NoSQL?
43. Types of NoSQL with examples?
44. CAP theorem; CP vs AP?
45. ACID vs BASE; eventual consistency?
46. Replication vs sharding?
47. Stored procedure vs function vs trigger?
48. OLTP vs OLAP; star schema?
49. SQL injection and prevention?
50. Design a schema for a library / e-commerce / hospital system. (Entities, keys, relationships, normalization, indexes.)

## E. Last-minute traps checklist
- [ ] PK = unique + NOT NULL; FK may be NULL
- [ ] Degree = columns; cardinality = rows
- [ ] Execution order: FROM → WHERE → GROUP BY → HAVING → SELECT → ORDER BY
- [ ] `= NULL` is wrong; use `IS NULL`; NOT IN + NULL → no rows
- [ ] COUNT(*) counts NULLs; COUNT(col) doesn't
- [ ] BCNF ⊂ 3NF ⊂ 2NF ⊂ 1NF
- [ ] Attributes not on any RHS are in every candidate key
- [ ] Precedence graph cycle ⇒ not conflict serializable
- [ ] 2PL ⇒ serializable, but not deadlock-free
- [ ] Only Serializable stops phantoms
- [ ] One clustered index per table
- [ ] B+ tree for ranges; hash for equality
- [ ] Wait-Die: older waits; Wound-Wait: older wounds
- [ ] CAP: P is unavoidable, so CP or AP
- [ ] Sharding ≠ replication
