# 01 — DBMS Basics & ER Model

## 1. What is a DBMS?
A **Database** is an organized collection of related data. A **DBMS** is software that creates, stores, retrieves, and manages databases (MySQL, PostgreSQL, Oracle, SQL Server, MongoDB).

### DBMS vs File System ⭐
| File system | DBMS |
|-------------|------|
| Data redundancy and inconsistency | Controlled redundancy |
| Hard to query (write custom programs) | Query language (SQL) |
| No concurrency control | Concurrent access with ACID |
| Weak security | Access control, authentication |
| No crash recovery | Backup and recovery |
| Data dependent on the program | **Data independence** |

**Advantages:** less redundancy, integrity, security, concurrency, recovery, data independence. **Disadvantages:** cost, complexity, performance overhead for simple apps.

## 2. Three-Schema Architecture & Data Independence ⭐
| Level | View | Describes |
|-------|------|-----------|
| **External (view)** | User | Part of the DB for each user |
| **Conceptual (logical)** | Community | Whole DB structure: entities, relations, constraints |
| **Internal (physical)** | Storage | Files, indexes, how data is stored |

- **Logical data independence:** change the conceptual schema without changing external views/programs. (Harder.)
- **Physical data independence:** change the internal schema without changing the conceptual schema. (Easier.)
- **Schema** = structure (design, rarely changes). **Instance** = data at a given moment.

## 3. Languages
| | Full form | Commands |
|--|-----------|----------|
| **DDL** | Data Definition | CREATE, ALTER, DROP, TRUNCATE, RENAME |
| **DML** | Data Manipulation | INSERT, UPDATE, DELETE (and often SELECT) |
| **DQL** | Data Query | SELECT |
| **DCL** | Data Control | GRANT, REVOKE |
| **TCL** | Transaction Control | COMMIT, ROLLBACK, SAVEPOINT |

## 4. DBMS Architecture (tiers)
- **1-tier:** app and DB on the same machine. **2-tier:** client ↔ DB server. **3-tier:** client ↔ application server ↔ DB server (web apps; better security and scalability).
- **DBA** duties: schema design, security, backup, tuning.

## 5. Keys ⭐⭐
| Key | Meaning |
|-----|---------|
| **Super key** | Any set of attributes that **uniquely identifies** a tuple (may contain extras) |
| **Candidate key** | **Minimal** super key (no redundant attribute) |
| **Primary key** | The candidate key chosen to identify rows. **Unique, NOT NULL**. One per table |
| **Alternate key** | Candidate keys not chosen as primary |
| **Unique key** | Unique values; **allows NULL** (one NULL in most DBs); many per table |
| **Foreign key** | Attribute referencing the **primary key of another table** (can be NULL, can repeat) |
| **Composite key** | Key made of 2+ attributes |
| **Surrogate key** | Artificial key (auto-increment ID) with no business meaning |
| **Natural key** | Real-world unique attribute (email, SSN) |

**Example:** Student(RollNo, Email, Name, Phone). RollNo and Email are candidate keys. Choose RollNo as the primary key → Email is the alternate key. {RollNo, Name} is a super key but not a candidate key.

**Number of super keys:** if a relation with n attributes has a single candidate key of 1 attribute, super keys = 2ⁿ⁻¹.

## 6. ER (Entity–Relationship) Model ⭐
| Component | Symbol | Meaning |
|-----------|--------|---------|
| **Entity** | Rectangle | Real-world object (Student) |
| **Weak entity** | Double rectangle | No primary key of its own; depends on an owner entity via an **identifying relationship** (Dependent of Employee) |
| **Attribute** | Ellipse | Property |
| **Key attribute** | Underlined | Unique identifier |
| **Multivalued attribute** | Double ellipse | Many values (phone numbers) |
| **Derived attribute** | Dashed ellipse | Computed (age from DOB) |
| **Composite attribute** | Ellipse with sub-ellipses | Name → first + last |
| **Relationship** | Diamond | Association between entities |

### Cardinality
**1:1, 1:N, N:1, M:N.** Example: Student–Course is M:N; Department–Employee is 1:N.
- **Participation:** **total** (double line; every entity must participate) vs **partial**.

### ER → Relational mapping
- Entity → table. Multivalued attribute → **separate table**. M:N relationship → **separate (junction) table** with both foreign keys. 1:N → put the FK on the **N side**. 1:1 → FK on either side (prefer the total-participation side).
- Weak entity table's PK = owner's PK + partial key.
- Min number of tables: M:N needs a new table; 1:N and 1:1 don't.

### Extended ER
- **Generalization** (bottom-up: combine entities into a super-class) vs **Specialization** (top-down). **Aggregation** treats a relationship as an entity. Inheritance: "is-a".

## 7. Common Interview Questions
1. What is a DBMS? DBMS vs file system?
2. What is data independence? Logical vs physical?
3. Primary key vs unique key vs foreign key?
4. Candidate key vs super key?
5. What is a weak entity?
6. How do you convert an M:N relationship to tables?
7. DDL vs DML vs DCL vs TCL?
8. What is a schema vs an instance?
9. Why use surrogate keys?

## MCQ Traps
- **Primary key = unique + NOT NULL; unique key may be NULL.**
- **Foreign key can be NULL and can repeat.**
- **Candidate key = minimal super key.** Every candidate key is a super key, not vice versa.
- **M:N needs a third table.**
- **Weak entity has a partial (discriminator) key**, not a full primary key.
- **TRUNCATE is DDL** (can't roll back in many DBs); DELETE is DML.
- **Logical** data independence is harder than physical.

## Practice MCQs
1. Minimal super key is called → **Candidate key**
2. Multivalued attribute in ER becomes → **A separate table**
3. Which can be NULL? **(a) Primary key (b) Foreign key (c) both (d) none** → **b**
4. GRANT belongs to → **DCL**
5. Changing a storage structure without affecting the conceptual schema → **Physical data independence**
