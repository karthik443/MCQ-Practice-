# 04 — Normalization & Functional Dependencies

## 1. Why Normalize? ⭐
Reduce **redundancy** and avoid **anomalies**:
- **Insertion anomaly:** can't add data without other data (can't add a department with no employees).
- **Deletion anomaly:** deleting one fact loses another (delete the last employee → lose the department).
- **Update anomaly:** must change many rows (change a department name everywhere → inconsistency).

Normalization = decomposing relations into smaller ones. Good decomposition is **lossless** and **dependency-preserving**.

## 2. Functional Dependency (FD) ⭐
**X → Y**: if two tuples agree on X, they must agree on Y. (X determines Y.)
- **Trivial:** Y ⊆ X (e.g. {A,B} → A). **Non-trivial:** Y ⊄ X.
- **Armstrong's axioms:**
  - **Reflexivity:** if Y ⊆ X then X → Y
  - **Augmentation:** X → Y ⇒ XZ → YZ
  - **Transitivity:** X → Y, Y → Z ⇒ X → Z
- **Derived rules:** Union (X→Y, X→Z ⇒ X→YZ), Decomposition (X→YZ ⇒ X→Y, X→Z), Pseudo-transitivity.
- **Types:** full FD (Y depends on all of X), **partial** (Y depends on part of a composite key), **transitive** (non-key → non-key).

## 3. Attribute Closure & Keys ⭐⭐⭐
**Closure X⁺** = all attributes determined by X.

**Algorithm:** start with X⁺ = X. Repeat: for each FD A → B where A ⊆ X⁺, add B. Stop when nothing changes.

**Example:** R(A,B,C,D,E), FDs: A→B, B→C, CD→E.
- A⁺ = {A, B, C}. (AD)⁺ = {A, B, C, D, E} = all → AD is a **candidate key** (A alone isn't; D alone isn't).
- **Key finding shortcut:** attributes that **never appear on any RHS** must be in every candidate key. Here A and D never appear on the RHS. Check (AD)⁺ = all ✔ → the only candidate key is **AD**.

- **Prime attribute:** part of some candidate key. **Non-prime:** not part of any.
- **X is a candidate key** iff X⁺ = all attributes and no proper subset of X has that property.
- **Checking whether an FD X→Y follows from F:** compute X⁺ and see whether Y ⊆ X⁺.
- **Minimal (canonical) cover:** remove extraneous attributes and redundant FDs, RHS single attribute.

## 4. Normal Forms ⭐⭐⭐
| NF | Rule | Removes |
|----|------|---------|
| **1NF** | All attributes **atomic** (no multivalued or repeating groups) | Multivalued attributes |
| **2NF** | 1NF + **no partial dependency** (no non-prime attribute depends on part of a candidate key) | Partial dependencies |
| **3NF** | 2NF + **no transitive dependency**. For every X → Y: **X is a super key OR Y is a prime attribute** | Transitive dependencies |
| **BCNF** | For every non-trivial X → Y: **X is a super key** | Anomalies from non-key determinants |
| **4NF** | BCNF + no non-trivial **multivalued dependencies** | MVDs |
| **5NF** | No join dependency not implied by candidate keys | |

- **Hierarchy:** BCNF ⊂ 3NF ⊂ 2NF ⊂ 1NF. **Every BCNF relation is in 3NF.**
- **If a table has only single-attribute candidate keys, it's automatically in 2NF** (partial dependency needs a composite key).
- **Every 2-attribute relation is in BCNF.**
- **3NF always achievable** with lossless + dependency-preserving decomposition. **BCNF is always lossless, but may not preserve dependencies.**

### Example walkthrough
Student_Course(StudentID, CourseID, StudentName, Instructor, InstructorOffice)
- Key: (StudentID, CourseID). StudentName depends on StudentID only → **partial dependency** → violates 2NF.
- Decompose: Student(StudentID, StudentName); Enrollment(StudentID, CourseID, Instructor, ...) etc.
- Instructor → InstructorOffice (non-key → non-key) is **transitive** → violates 3NF. Split into Instructor(Instructor, Office).

### Quick check recipe for MCQs
1. Find all candidate keys (closure).
2. List prime attributes.
3. For each FD X→Y: if X is a super key → OK for BCNF. Else if Y is prime → OK for 3NF only. Else check for partial (X ⊂ a key, Y non-prime → violates 2NF) or transitive (violates 3NF).
4. **Highest NF = the weakest condition that holds for all FDs.**

**Example:** R(A,B,C), FDs: AB→C, C→B. Keys: AB and AC (AC⁺ = A,C,B). All attributes are prime → **3NF** ✔. C→B: C is not a super key → **not BCNF**. Answer: **3NF**.

## 5. Decomposition Properties ⭐
- **Lossless-join:** joining the decomposed tables gives exactly the original (no spurious tuples). For R → R1, R2: **R1 ∩ R2 → R1 or R1 ∩ R2 → R2** (the common attributes must be a key of one of them).
- **Dependency-preserving:** all original FDs can be enforced in the decomposed tables without joins.
- A decomposition that loses data is a **lossy** decomposition.

## 6. Denormalization
Deliberately adding redundancy to **speed up reads** (fewer joins), used in data warehouses/reporting and read-heavy systems. Cost: more storage, update anomalies, extra care for consistency.

## 7. Common Interview Questions
1. What is normalization? Why do we need it?
2. Explain 1NF, 2NF, 3NF, BCNF with an example.
3. 3NF vs BCNF?
4. What are anomalies?
5. What is a functional dependency? Partial and transitive dependency?
6. What is attribute closure? How do you find the candidate keys?
7. What is a lossless decomposition?
8. What is denormalization and when would you use it?
9. Is it always good to normalize up to BCNF? (No. Performance/dependency trade-offs.)

## MCQ Traps
- **BCNF is stricter than 3NF.** Every BCNF is in 3NF, not the reverse.
- **3NF allows X → Y if Y is prime; BCNF doesn't.**
- **2NF violations need a composite key** and a **partial** dependency.
- **BCNF may not preserve dependencies; 3NF always can.**
- **Attributes never on the RHS belong to every candidate key.**
- **1NF = atomic values.**
- Transitivity: X → Y and Y → Z ⇒ X → Z.
- **More normalization = more tables = more joins.**

## Practice MCQs
1. R(A,B,C,D), FDs: A→B, B→C, C→D. Candidate key → **A** (A⁺ = ABCD)
2. R(A,B,C), FDs: A→B, B→C. Highest normal form → Key A; B→C has a non-prime RHS and non-key LHS (transitive) → **2NF**
3. Which removes partial dependency? → **2NF**
4. Every relation with two attributes is at least in → **BCNF**
5. Lossless decomposition needs R1 ∩ R2 to be → **a key (determine all of R1 or R2)**
