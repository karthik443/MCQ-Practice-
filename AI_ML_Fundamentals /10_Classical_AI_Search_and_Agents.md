# 10 — Classical AI: Agents, Search & Games

Frequent in campus exams and "AI fundamentals" MCQ rounds.

## 1. Intelligent Agents ⭐
**Agent** = perceives the environment through **sensors** and acts through **actuators**. **Rational agent** = takes the action expected to maximize its **performance measure**.

**PEAS** description: **P**erformance measure, **E**nvironment, **A**ctuators, **S**ensors.
Example (self-driving car): P = safety, time, comfort; E = roads, traffic; A = steering, brake; S = camera, LiDAR, GPS.

### Agent types (increasing sophistication) ⭐
1. **Simple reflex:** condition–action rules on the current percept only. (Thermostat.)
2. **Model-based reflex:** keeps an **internal state** of the world.
3. **Goal-based:** chooses actions to achieve a goal (uses search/planning).
4. **Utility-based:** maximizes a **utility** (handles trade-offs, "how happy").
5. **Learning agent:** improves with experience (critic, learning element, performance element, problem generator).

### Environment properties ⭐
| Property | Options |
|----------|---------|
| Observability | **Fully** (chess) vs **partially** (poker, driving) |
| Determinism | **Deterministic** vs **stochastic** |
| Episodic vs sequential | Sequential: current action affects future (chess) |
| Static vs dynamic | Dynamic: changes while the agent thinks (driving) |
| Discrete vs continuous | Chess discrete, driving continuous |
| Single vs multi-agent | |

Chess: fully observable, deterministic, sequential, static, discrete, multi-agent.

## 2. Problem Formulation
A search problem = **initial state, actions, transition model, goal test, path cost**. Example: 8-puzzle (9!/2 = 181,440 reachable states), route finding.

## 3. Uninformed (Blind) Search ⭐⭐
b = branching factor, d = depth of the shallowest goal, m = max depth, l = depth limit.
| Algorithm | Data structure | Complete? | Optimal? | Time | Space |
|-----------|----------------|:--:|:--:|------|-------|
| **BFS** | **Queue (FIFO)** | Yes | Yes (**uniform step cost**) | O(bᵈ) | O(bᵈ) |
| **DFS** | **Stack (LIFO)** / recursion | No (infinite/loops) | No | O(bᵐ) | **O(b·m)** |
| **Uniform Cost Search (UCS)** | Priority queue by g(n) | Yes | **Yes** | O(b^(1+C*/ε)) | same |
| **Depth-Limited** | Stack | No | No | O(bˡ) | O(b·l) |
| **Iterative Deepening (IDDFS)** | Stack | Yes | Yes (uniform cost) | O(bᵈ) | **O(b·d)** |
| **Bidirectional** | two queues | Yes | Yes | O(b^(d/2)) | O(b^(d/2)) |

- **BFS:** shortest path in unweighted graphs; heavy memory. **DFS:** low memory; can go down an infinite path. **IDDFS** combines BFS's completeness/optimality with DFS's memory. **Dijkstra = UCS.**
- Graph search keeps an **explored set** to avoid cycles.

## 4. Informed (Heuristic) Search ⭐⭐
**Heuristic h(n):** estimated cost from n to the goal. **g(n):** cost so far.
| Algorithm | Evaluation f(n) | Complete | Optimal |
|-----------|-----------------|:--:|:--:|
| **Greedy Best-First** | h(n) | No (can loop) | **No** |
| **A\*** | **g(n) + h(n)** | Yes | **Yes, if h is admissible** (tree search) / **consistent** (graph search) |
| **IDA\*** | iterative deepening on f | Yes | Yes (with admissible h) |
| **Hill climbing** | local move improving h | No | No |
| **Simulated annealing** | hill climbing + random downhill moves with decreasing "temperature" | | Can escape local optima |
| **Genetic algorithm** | selection, crossover, mutation of a population | | |

- **Admissible heuristic:** **never overestimates** the true cost (h(n) ≤ h*(n)). **Consistent (monotone):** h(n) ≤ c(n, n′) + h(n′). **Consistent ⇒ admissible.**
- **A\*** with h = 0 → **UCS / Dijkstra**.
- 8-puzzle heuristics: **misplaced tiles**, **Manhattan distance** (dominates misplaced tiles; both admissible).
- **Dominance:** if h₂(n) ≥ h₁(n) for all n (both admissible), h₂ is better (expands fewer nodes).
- **Hill climbing problems:** local maxima, plateaus, ridges.

**A\* worked example:** S→A (cost 1), S→B (cost 4), A→G (cost 5), B→G (cost 1). h(S)=5, h(A)=4, h(B)=1, h(G)=0.
- f(A) = 1+4 = 5, f(B) = 4+1 = 5. Expand A: G via A gives g = 6. Expand B: G via B gives g = 5. Optimal path **S→B→G, cost 5**.

## 5. Adversarial Search (Games) ⭐⭐
### Minimax
Two players: **MAX** (maximizes score) and **MIN** (minimizes). Explore the game tree to depth, evaluate leaves, **back up** max at MAX levels and min at MIN levels. Assumes an optimal opponent. Time O(bᵐ), space O(b·m) (DFS).

**Example:** MAX root with two MIN children; leaves: left (3, 5), right (2, 9). MIN values: left = 3, right = 2. MAX picks max(3, 2) = **3**.

### Alpha–Beta Pruning ⭐
- Maintains **α** (best for MAX so far, lower bound) and **β** (best for MIN so far, upper bound). **Prune when α ≥ β.**
- Gives the **same result as minimax**, but skips branches.
- Best-case ordering: time **O(b^(m/2))**, so the search goes **twice as deep** in the same time. Worst case: no pruning = O(bᵐ).
- In the example above: after left MIN = 3 (α = 3), right's first leaf 2 ≤ 3, so **9 is pruned**.

**Others:** **Expectiminimax** (chance nodes), **Monte Carlo Tree Search (MCTS)** (AlphaGo).

## 6. Constraint Satisfaction Problems (CSP)
Variables, domains, constraints. Examples: **Sudoku, map colouring, N-Queens, scheduling**.
- Solved by **backtracking** + **forward checking**, **arc consistency (AC-3)**, heuristics: **MRV** (choose the most constrained variable), **degree heuristic**, **LCV** (least constraining value).

## 7. Knowledge Representation & Logic
- **Propositional logic:** statements true/false; connectives ∧ ∨ ¬ → ↔. **Limited expressiveness.**
- **First-Order Logic (FOL):** objects, predicates, **quantifiers ∀ ∃**. More expressive.
- **Inference:** **Modus Ponens** (P, P→Q ⊢ Q), **resolution**, forward/backward chaining.
- **Knowledge-based agents**, **expert systems** (knowledge base + inference engine).
- **Turing Test:** a machine is intelligent if a human judge can't tell it from a human. **Chinese Room** (Searle) argues against "understanding".
- **Probabilistic reasoning:** **Bayesian networks** (DAG of conditional dependencies), **Hidden Markov Models (HMM)**.

## 8. Common Interview Questions
1. What is a rational agent? Types of agents?
2. What is PEAS? Give an example.
3. BFS vs DFS: when to use which? Data structures?
4. What makes a heuristic admissible? Why must A* use one?
5. A* vs Greedy best-first vs UCS?
6. Explain minimax and alpha-beta pruning. Does pruning change the answer? (No.)
7. What is hill climbing and its drawbacks?
8. Explain IDDFS and why it's useful.
9. Propositional vs first-order logic?
10. What is the Turing Test?
11. What is a CSP? Example?

## MCQ Traps
- **BFS → Queue; DFS → Stack.**
- **DFS isn't complete or optimal**; BFS is optimal only for **uniform/unit** step costs.
- **A\*: f = g + h; needs an admissible heuristic for optimality.**
- **Greedy best-first isn't optimal** (uses only h).
- **Alpha–beta gives the same value as minimax.**
- **Consistent ⇒ admissible** (not the reverse).
- **UCS = Dijkstra; A\* with h = 0 = UCS.**
- IDDFS: **space O(bd)**, complete, optimal for unit costs.
- Best-case alpha–beta: **O(b^(m/2))**.
- A utility-based agent deals with **preferences/trade-offs**; a goal-based agent only binary achieved/not.

## Practice MCQs
1. Which search uses a FIFO queue? → **BFS**
2. A heuristic that never overestimates is → **admissible**
3. α–β pruning occurs when → **α ≥ β**
4. Thermostat is which agent type? → **Simple reflex**
5. Which search is complete, optimal (unit cost) with low memory? → **Iterative deepening DFS**
