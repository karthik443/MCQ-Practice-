# 02 — Relational Model & Relational Algebra

## 1. Relational Model Terms
| Formal | Informal |
|--------|----------|
| **Relation** | Table |
| **Tuple** | Row / record |
| **Attribute** | Column / field |
| **Domain** | Set of allowed values for an attribute |
| **Degree (arity)** | Number of **attributes** (columns) |
| **Cardinality** | Number of **tuples** (rows) |

Properties: no duplicate tuples (a relation is a **set**), tuple order is irrelevant, attribute order is irrelevant, values are **atomic**.

## 2. Integrity Constraints ⭐
| Constraint | Rule |
|------------|------|
| **Domain** | Values must be of the right type/range (CHECK, data type) |
| **Entity integrity** | **Primary key can't be NULL** |
| **Key** | Key values must be unique |
| **Referential integrity** | A foreign key value must be **NULL or exist in the referenced table** |

### Referential actions on DELETE/UPDATE of the parent
- **RESTRICT / NO ACTION:** reject the operation.
- **CASCADE:** apply to child rows too (delete the parent → delete children).
- **SET NULL:** set the child's FK to NULL.
- **SET DEFAULT:** set the child's FK to its default.

**Violations:** INSERT can violate domain, key, entity, and referential constraints. **DELETE** can violate only referential integrity. **UPDATE** can violate any.

## 3. Relational Algebra ⭐ (procedural query language)
| Operator | Symbol | Meaning |
|----------|:-:|---------|
| **Selection** | σ | Filters **rows**: σ_age>20(Student) |
| **Projection** | π | Picks **columns** (removes duplicates): π_name(Student) |
| **Union** | ∪ | Rows in either (union-compatible) |
| **Intersection** | ∩ | Rows in both |
| **Set difference** | − | In R but not in S |
| **Cartesian product** | × | Every pair: |R|·|S| tuples |
| **Rename** | ρ | Rename relation/attributes |
| **Natural join** | ⋈ | Cartesian product + select equal common attributes + remove duplicate columns |
| **Theta/Equi join** | ⋈θ | Join with a condition |
| **Division** | ÷ | "For all" queries (students who took **all** courses) |
| **Outer joins** | ⟕ ⟖ ⟗ | Keep unmatched rows |

- **Union-compatible:** same number of attributes with the same domains.
- **Fundamental operators:** σ, π, ∪, −, ×, ρ. Others (∩, ⋈, ÷) derive from them.
- **Selection is commutative** (σ_c1(σ_c2(R)) = σ_c2(σ_c1(R))). Projection removes duplicates.

### Size rules ⭐ (R has m tuples, S has n)
| Operation | Min | Max |
|-----------|-----|-----|
| R × S | m·n | m·n |
| R ∪ S | max(m, n) | m + n |
| R ∩ S | 0 | min(m, n) |
| R − S | 0 | m |
| R ⋈ S (natural) | 0 | m·n |
| σ(R) | 0 | m |
| π(R) | 1 (if m ≥ 1) | m |

**Cartesian product:** degree = deg(R) + deg(S); cardinality = m × n.

**Example:** R(3 attrs, 4 tuples) × S(2 attrs, 5 tuples) → 5 attributes, 20 tuples.

## 4. Relational Calculus (brief)
- **Tuple Relational Calculus (TRC):** {t | P(t)}. **Domain Relational Calculus (DRC).** **Declarative** (what, not how). Safe expressions are equivalent in power to relational algebra. SQL is based on both.

## 5. Common Interview Questions
1. What are the integrity constraints?
2. Degree vs cardinality of a relation?
3. What is referential integrity? What happens on deleting a parent row?
4. Selection vs projection?
5. What is a natural join? Equi-join vs natural join?
6. What is the division operator used for?
7. What is union compatibility?
8. Why is relational algebra called procedural and SQL declarative?

## MCQ Traps
- **Degree = columns; cardinality = rows.**
- **σ = rows (WHERE); π = columns (SELECT).**
- **Projection removes duplicates in algebra**, but SQL SELECT doesn't unless DISTINCT is used.
- **Natural join on relations with no common attribute = Cartesian product.**
- **DELETE can only violate referential integrity.**
- **R ∪ S / R ∩ S / R − S need union compatibility.**

## Practice MCQs
1. R has 10 tuples, S has 5. Max tuples in R ∪ S? → **15**
2. Operator to pick specific columns → **Projection (π)**
3. A table has 4 columns and 6 rows. Its degree is → **4**
4. Which operator answers "find students enrolled in ALL courses"? → **Division**
5. Min tuples in R ∩ S → **0**
