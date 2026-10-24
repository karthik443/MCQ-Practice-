# 07 — NoSQL & Advanced Topics

## 1. SQL vs NoSQL ⭐⭐
| | **SQL (relational)** | **NoSQL** |
|--|----------------------|-----------|
| Schema | Fixed, predefined | **Flexible / schema-less** |
| Data model | Tables, rows | Document, key-value, column-family, graph |
| Scaling | Mostly **vertical** (scale up); horizontal is harder | Built for **horizontal** (scale out) |
| Consistency | **ACID** | Often **BASE** (eventual consistency) |
| Joins | Strong support | Limited / denormalized |
| Query | SQL | DB-specific APIs |
| Best for | Structured data, transactions (banking), complex queries | Big data, high-velocity, unstructured, flexible, real-time |
| Examples | MySQL, PostgreSQL, Oracle, SQL Server | MongoDB, Redis, Cassandra, Neo4j, DynamoDB |

### Types of NoSQL ⭐
| Type | Model | Example | Use cases |
|------|-------|---------|-----------|
| **Key–Value** | key → value | **Redis**, DynamoDB | Caching, sessions, leaderboards |
| **Document** | JSON/BSON documents | **MongoDB**, CouchDB | Catalogs, CMS, user profiles |
| **Column-family** | Wide columns | **Cassandra**, HBase | Time series, massive writes, analytics |
| **Graph** | Nodes + edges | **Neo4j** | Social networks, recommendations, fraud rings |

MongoDB terms: database → **collection** (table) → **document** (row); `_id` is the primary key; embedded documents vs references.

## 2. BASE vs ACID
- **B**asically **A**vailable, **S**oft state, **E**ventually consistent. Trades immediate consistency for availability/scale.

## 3. CAP Theorem ⭐⭐
A distributed data store can guarantee **at most two** of:
- **C**onsistency: every read sees the latest write.
- **A**vailability: every request gets a (non-error) response.
- **P**artition tolerance: the system keeps working despite network splits.

Since **partitions are unavoidable in distributed systems**, the real choice is **CP vs AP** during a partition.
- **CP:** MongoDB (default), HBase, Redis cluster, ZooKeeper (consistent, may refuse requests).
- **AP:** Cassandra, DynamoDB, CouchDB (available, may serve stale data).
- Traditional single-node RDBMS = **CA** (no partitions to tolerate).
- **PACELC:** extends CAP: else (no partition), trade **latency vs consistency**.

## 4. Replication & Sharding ⭐
### Replication
Copies of data on multiple nodes → **high availability, fault tolerance, read scaling**.
- **Master–slave (primary–replica):** writes to the primary, reads from replicas. Replica lag = stale reads.
- **Multi-master:** writes at several nodes (conflict resolution needed).
- **Synchronous** (consistent, slower) vs **asynchronous** (fast, may lose recent writes on failover).

### Sharding (horizontal partitioning across servers)
Split data across machines by a **shard key** to scale **writes and storage**.
- **Range-based** (simple; hotspots), **hash-based** (even distribution; range queries harder), **directory-based**.
- **Consistent hashing** reduces data movement when nodes join/leave.
- Challenges: **cross-shard joins/transactions**, rebalancing, choosing a good shard key (high cardinality, even distribution).
- **Replication = copies (availability); sharding = split (scale).** Real systems use both.

## 5. Views, Stored Procedures, Functions, Triggers ⭐
| | Description |
|--|-------------|
| **View** | Virtual table from a query; hides complexity, adds security. Usually **read-only** if it uses joins/aggregates. **Materialized view** stores the results (refresh needed) |
| **Stored procedure** | Precompiled SQL + logic stored in the DB; can have **IN/OUT** params, can modify data; called with `CALL`. Reduces network traffic; reusable, secure |
| **Function (UDF)** | **Returns a value**; can be used inside SELECT |
| **Trigger** | Auto-executes on **INSERT / UPDATE / DELETE** (BEFORE / AFTER). For auditing, validation, derived data. Overuse hurts performance and is hard to debug |
| **Cursor** | Row-by-row processing of a result set (slow; prefer set-based SQL) |

**Procedure vs function:** a function must return a value and can be used in expressions; a procedure may return 0+ values and can't be used in a SELECT.

## 6. Data Warehousing & OLTP vs OLAP ⭐
| | **OLTP** | **OLAP** |
|--|----------|----------|
| Purpose | Day-to-day transactions | Analysis, reporting |
| Queries | Short, simple, many writes | Complex, read-heavy aggregates |
| Schema | **Normalized** | **Denormalized** (star/snowflake) |
| Data | Current | Historical |
| Example | Banking, orders | Sales dashboards, BI |

- **Data warehouse:** central store of integrated historical data. **ETL:** Extract, Transform, Load. **Data lake:** raw data of any format. **Data mart:** subset for a team.
- **Star schema:** central **fact table** (measures) + **dimension tables** (denormalized). **Snowflake:** normalized dimensions.
- **OLAP operations:** roll-up, drill-down, slice, dice, pivot.

## 7. Security & Other Concepts
- **Authentication vs authorization.** **GRANT/REVOKE.** **Roles.** Encrypt data at rest/in transit.
- **SQL injection:** attacker injects SQL via user input (`' OR '1'='1`). **Prevention:** **parameterized queries / prepared statements**, input validation, least privilege, ORM, escaping.
- **Connection pooling:** reuse DB connections (saves the cost of creating them).
- **ORM:** maps objects to tables (Hibernate, SQLAlchemy, Sequelize).
- **Stored vs calculated data; soft delete** (`is_deleted` flag).
- **Two-phase commit (2PC):** distributed transaction commit (prepare → commit), a blocking protocol.
- **Distributed DB:** data spread across sites; **homogeneous vs heterogeneous**.
- **Database locks vs latches:** locks for logical data (transactions); latches for internal memory structures.
- **ACID vs CAP "consistency":** ACID's C = valid state via constraints; CAP's C = all nodes see the same data (linearizability).

## 8. Common Interview Questions
1. SQL vs NoSQL: when do you choose which?
2. Types of NoSQL databases with examples?
3. Explain CAP theorem. Is MongoDB CP or AP?
4. ACID vs BASE?
5. Replication vs sharding?
6. What is a view? Materialized view?
7. Stored procedure vs function vs trigger?
8. OLTP vs OLAP? Star schema?
9. What is SQL injection and how do you prevent it?
10. What is eventual consistency?
11. Why is horizontal scaling easier with NoSQL?
12. What is a data warehouse / ETL?

## MCQ Traps
- **CAP: choose 2 of 3, but P is mandatory in distributed systems → CP or AP.**
- **Redis = key-value; MongoDB = document; Cassandra = column-family; Neo4j = graph.**
- **NoSQL = "Not Only SQL", typically BASE, horizontally scalable.**
- **Sharding = scale; replication = availability.**
- **OLTP = normalized; OLAP = denormalized.**
- **Prepared statements prevent SQL injection.**
- **A function returns a value; a procedure needn't.**
- **Triggers fire automatically on DML events.**

## Practice MCQs
1. Best DB for a social-network relationship graph → **Graph (Neo4j)**
2. Cassandra in CAP → **AP**
3. Splitting data across servers by a key → **Sharding**
4. Which prevents SQL injection? → **Parameterized queries**
5. Fact tables appear in → **Star schema (data warehouse)**
