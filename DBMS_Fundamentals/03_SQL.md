# 03 — SQL

Most asked DBMS topic. Practise by typing the queries.

## Sample tables used below
```
Employee(emp_id, name, salary, dept_id, manager_id)
Department(dept_id, dept_name)
```

## 1. Basics
```sql
CREATE TABLE Employee (
  emp_id INT PRIMARY KEY,
  name VARCHAR(50) NOT NULL,
  salary DECIMAL(10,2) CHECK (salary > 0),
  dept_id INT,
  FOREIGN KEY (dept_id) REFERENCES Department(dept_id) ON DELETE SET NULL
);
ALTER TABLE Employee ADD COLUMN email VARCHAR(100);
INSERT INTO Employee VALUES (1, 'Asha', 50000, 10, NULL);
UPDATE Employee SET salary = salary * 1.1 WHERE dept_id = 10;
DELETE FROM Employee WHERE emp_id = 1;
```
**Constraints:** PRIMARY KEY, FOREIGN KEY, UNIQUE, NOT NULL, CHECK, DEFAULT.

### DELETE vs TRUNCATE vs DROP ⭐
| | DELETE | TRUNCATE | DROP |
|--|--------|----------|------|
| Type | DML | DDL | DDL |
| Removes | Rows (with WHERE) | **All rows** | Table structure + data |
| WHERE clause | Yes | No | No |
| Rollback | Yes | Usually no | No |
| Speed | Slower (row-by-row logging) | Faster | |
| Resets auto-increment | No | Yes | |
| Triggers | Fire | Don't | |

## 2. Query Clause Order ⭐
**Written:** SELECT → FROM → WHERE → GROUP BY → HAVING → ORDER BY → LIMIT
**Executed:** **FROM → WHERE → GROUP BY → HAVING → SELECT → ORDER BY → LIMIT**
(So you can't use a SELECT alias in WHERE, but you can in ORDER BY.)

```sql
SELECT dept_id, COUNT(*) AS cnt, AVG(salary) AS avg_sal
FROM Employee
WHERE salary > 20000
GROUP BY dept_id
HAVING COUNT(*) > 2
ORDER BY avg_sal DESC
LIMIT 5;
```
- **WHERE** filters **rows before** grouping (no aggregates). **HAVING** filters **groups after** aggregation.
- **Aggregates:** COUNT, SUM, AVG, MIN, MAX. **COUNT(\*)** counts all rows; **COUNT(col)** ignores NULLs; **COUNT(DISTINCT col)**. Other aggregates ignore NULLs.
- Every non-aggregated column in SELECT must be in GROUP BY.

## 3. Operators & NULL ⭐
- `LIKE`: `%` = any characters, `_` = exactly one. `'A%'`, `'%son'`, `'_a%'`.
- `IN`, `BETWEEN a AND b` (**inclusive**), `IS NULL` / `IS NOT NULL`, `DISTINCT`.
- **NULL is unknown**: `NULL = NULL` is **not true** (it's NULL/unknown). Use `IS NULL`. Any comparison or arithmetic with NULL gives NULL.
- Three-valued logic: TRUE, FALSE, UNKNOWN. `WHERE` keeps only TRUE rows.
- `NOT IN` with a NULL in the list returns **no rows** (trap!). Prefer `NOT EXISTS`.
- `COALESCE(a, b, c)` returns the first non-NULL. `IFNULL / NVL`.
- In ORDER BY, NULL placement depends on the DB.

## 4. Joins ⭐⭐⭐
| Join | Returns |
|------|---------|
| **INNER JOIN** | Only matching rows in both |
| **LEFT (OUTER) JOIN** | All left rows + matches (NULLs for non-matching right) |
| **RIGHT (OUTER) JOIN** | All right rows + matches |
| **FULL (OUTER) JOIN** | All rows from both (NULLs where no match) |
| **CROSS JOIN** | Cartesian product (m × n) |
| **SELF JOIN** | A table joined with itself (aliases) |
| **NATURAL JOIN** | Join on all same-named columns |

```sql
-- employees with dept name
SELECT e.name, d.dept_name
FROM Employee e JOIN Department d ON e.dept_id = d.dept_id;

-- departments with no employees
SELECT d.dept_name FROM Department d
LEFT JOIN Employee e ON d.dept_id = e.dept_id
WHERE e.emp_id IS NULL;

-- employee and their manager (self join)
SELECT e.name AS emp, m.name AS manager
FROM Employee e LEFT JOIN Employee m ON e.manager_id = m.emp_id;
```
**Row counts:** A has 3 rows, B has 4. CROSS JOIN = 12. INNER ≤ 12. LEFT ≥ 3. FULL ≥ max(3,4).

## 5. Subqueries
```sql
-- above-average salary
SELECT name FROM Employee WHERE salary > (SELECT AVG(salary) FROM Employee);

-- IN / EXISTS
SELECT name FROM Employee WHERE dept_id IN (SELECT dept_id FROM Department WHERE dept_name='IT');
SELECT d.dept_name FROM Department d WHERE EXISTS (SELECT 1 FROM Employee e WHERE e.dept_id = d.dept_id);
```
- **Correlated subquery:** references the outer query; runs once per outer row.
- **IN vs EXISTS:** EXISTS stops at the first match (good for large inner sets); `NOT EXISTS` is NULL-safe.
- `ANY`, `ALL`: `salary > ALL (subquery)` = greater than the max.
- Derived table: subquery in FROM. **CTE:** `WITH t AS (...) SELECT ...` (readable, supports recursion).

## 6. Set Operations
`UNION` (removes duplicates), `UNION ALL` (keeps duplicates, faster), `INTERSECT`, `EXCEPT / MINUS`. Need the same number and compatible types of columns.

## 7. Window Functions ⭐ (frequent in modern interviews)
```sql
SELECT name, dept_id, salary,
  ROW_NUMBER() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS rn,
  RANK()       OVER (PARTITION BY dept_id ORDER BY salary DESC) AS rnk,
  DENSE_RANK() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS drnk,
  SUM(salary)  OVER (PARTITION BY dept_id) AS dept_total,
  LAG(salary)  OVER (ORDER BY emp_id) AS prev_sal
FROM Employee;
```
| Salaries | ROW_NUMBER | RANK | DENSE_RANK |
|----------|-----------|------|-----------|
| 100, 90, 90, 80 | 1,2,3,4 | 1,2,2,**4** | 1,2,2,**3** |

- Window functions **don't collapse rows** (unlike GROUP BY). `LAG/LEAD` look at previous/next rows. `NTILE(n)` buckets.

## 8. Classic Interview Queries ⭐⭐⭐
```sql
-- 2nd highest salary (3 ways)
SELECT MAX(salary) FROM Employee WHERE salary < (SELECT MAX(salary) FROM Employee);
SELECT DISTINCT salary FROM Employee ORDER BY salary DESC LIMIT 1 OFFSET 1;
SELECT salary FROM (SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) r FROM Employee) t WHERE r = 2;

-- Nth highest: DENSE_RANK() = N. Top earner per dept: rank within PARTITION BY dept_id.

-- Duplicate emails
SELECT email, COUNT(*) FROM Employee GROUP BY email HAVING COUNT(*) > 1;

-- Delete duplicates (keep lowest id)
DELETE FROM Employee WHERE emp_id NOT IN
 (SELECT MIN(emp_id) FROM Employee GROUP BY email);   -- (MySQL needs a derived-table wrapper)

-- Employees earning more than their manager
SELECT e.name FROM Employee e JOIN Employee m ON e.manager_id = m.emp_id WHERE e.salary > m.salary;

-- Dept with max headcount
SELECT dept_id FROM Employee GROUP BY dept_id ORDER BY COUNT(*) DESC LIMIT 1;

-- Employees with no department
SELECT name FROM Employee WHERE dept_id IS NULL;
```

## 9. Views, Indexes, Transactions (short)
- **View:** saved query, a virtual table. Simplifies and secures. A **materialized view** stores the result physically.
- **Index:** speeds up reads, slows down writes (file 06).
- `BEGIN; ... COMMIT; / ROLLBACK;` `SAVEPOINT`.

## 10. SQL Functions
- String: `UPPER, LOWER, LENGTH, SUBSTRING, CONCAT, TRIM, REPLACE`.
- Date: `NOW(), CURDATE(), DATEDIFF, YEAR()`.
- Numeric: `ROUND, CEIL, FLOOR, MOD`.
- `CASE WHEN salary > 50000 THEN 'High' ELSE 'Low' END`.

## 11. Common Interview Questions
1. WHERE vs HAVING?
2. DELETE vs TRUNCATE vs DROP?
3. Types of joins? Explain with an example.
4. INNER vs LEFT JOIN? Self join use-case?
5. Find the 2nd/Nth highest salary.
6. Find duplicates and delete them.
7. UNION vs UNION ALL?
8. RANK vs DENSE_RANK vs ROW_NUMBER?
9. What happens when you compare with NULL? COUNT(*) vs COUNT(col)?
10. IN vs EXISTS? Correlated subquery?
11. What is a view? Why use it?
12. PRIMARY KEY vs UNIQUE?
13. What is a CTE?

## MCQ Traps
- **Execution order: FROM → WHERE → GROUP BY → HAVING → SELECT → ORDER BY.**
- **`= NULL` never works. Use `IS NULL`.**
- **COUNT(\*) counts NULLs; COUNT(col) doesn't.**
- **BETWEEN is inclusive.**
- **UNION removes duplicates; UNION ALL doesn't.**
- **NOT IN + NULL → empty result.**
- **Aggregates aren't allowed in WHERE.**
- **LEFT JOIN + `WHERE right.col IS NULL` = anti-join (non-matching rows).**
- **LEFT JOIN with a WHERE filter on the right table turns it into an inner join.**
- TRUNCATE has no WHERE.

## Practice MCQs
1. Table A has 5 rows, B has 4. Rows in `A CROSS JOIN B` → **20**
2. Salaries 100, 90, 90, 80. DENSE_RANK of 80 → **3**
3. `SELECT COUNT(*)` on a table with 10 rows, 3 NULLs in col x; `COUNT(x)` → **7**
4. Which filters groups? → **HAVING**
5. `LIKE '_a%'` matches → **Strings whose 2nd character is 'a'**
