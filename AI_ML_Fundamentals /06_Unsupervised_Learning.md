# 06 — Unsupervised Learning

Finding structure in **unlabeled** data.

## 1. K-Means Clustering ⭐⭐
**Algorithm:**
1. Choose k; initialize k centroids (random / **k-means++**).
2. **Assign** each point to the nearest centroid.
3. **Update** each centroid = mean of its points.
4. Repeat 2–3 until assignments stop changing (convergence).

**Objective:** minimize **WCSS / inertia** = Σ ‖x − centroid‖².

**Worked example:** points 1, 2, 9, 10; initial centroids 1 and 10.
- Assign: {1, 2} → C1, {9, 10} → C2. Update: C1 = 1.5, C2 = 9.5. Reassign: no change → **converged**.

**Choosing k:**
- **Elbow method:** plot WCSS vs k, pick the "elbow".
- **Silhouette score:** s = (b − a) / max(a, b), range [−1, 1], higher is better. (a = mean intra-cluster distance, b = mean distance to the nearest other cluster.)

**Properties & limits:**
- Must specify **k** in advance. Sensitive to **initialization** (use k-means++, multiple runs) and **outliers**.
- Assumes **spherical, similar-size** clusters. Fails on non-convex shapes (moons, rings).
- **Needs scaling.** Only numeric data (use **K-Modes** for categorical, **K-Prototypes** for mixed).
- Converges to a **local** optimum. Complexity O(n·k·d·iterations).
- Hard assignment. **GMM (Gaussian Mixture Model)** gives soft probabilistic assignment via the EM algorithm.

## 2. Hierarchical Clustering ⭐
- **Agglomerative (bottom-up):** start with each point as a cluster, merge the closest pair repeatedly. **Divisive (top-down):** start with one cluster and split.
- Output: **dendrogram**. Cut at a height to get k clusters.
- **Linkage:** **single** (min distance; chaining effect), **complete** (max distance; compact clusters), **average**, **Ward** (minimizes variance increase).
- No need to pre-specify k. Deterministic. But **O(n²)–O(n³)**, so not for big data, and merges are irreversible.

## 3. DBSCAN ⭐⭐
**Density-based.** Parameters: **ε (eps)** radius, **minPts**.
- **Core point:** ≥ minPts points within ε.
- **Border point:** within ε of a core point but not core itself.
- **Noise (outlier):** neither.
- Pros: finds **arbitrary-shaped** clusters, **detects outliers**, **no need to specify k**.
- Cons: struggles with **varying densities**, sensitive to eps/minPts, poor in high dimensions.

| | K-Means | Hierarchical | DBSCAN |
|--|---------|-------------|--------|
| Needs k | Yes | No (cut dendrogram) | No |
| Shapes | Spherical | Depends on linkage | **Arbitrary** |
| Outliers | Sensitive | Sensitive | **Identifies as noise** |
| Scalability | **Best** | Poor | Good |

## 4. Principal Component Analysis (PCA) ⭐⭐
**Dimensionality reduction** by projecting data onto orthogonal directions of **maximum variance**.
- Steps: **standardize** → covariance matrix → **eigenvectors / eigenvalues** → sort by eigenvalue → pick top-k → project.
- **PC1** captures the most variance; PCs are **orthogonal (uncorrelated)**.
- **Explained variance ratio** = λᵢ / Σλ. Keep components covering ~95% (scree plot).
- **Unsupervised** (ignores labels). **Linear** method. **Needs scaling.** Loses interpretability.
- Uses: visualization (2-D/3-D), noise reduction, speeding up models, removing multicollinearity.
- Number of PCs ≤ min(n_samples, n_features).

| PCA | LDA |
|-----|-----|
| Unsupervised | **Supervised** |
| Maximizes **variance** | Maximizes **class separability** |

- **t-SNE / UMAP:** non-linear, for **visualization** only (2-D), not for feature engineering in pipelines.
- **Autoencoder:** neural-network non-linear dimensionality reduction.

## 5. Association Rule Mining (Market Basket) ⭐
Rule: **A → B** ("if a customer buys A, they likely buy B").
- **Support(A→B)** = P(A ∩ B) = count(A,B) / N
- **Confidence(A→B)** = P(B | A) = support(A,B) / support(A)
- **Lift(A→B)** = confidence / support(B). **Lift > 1:** positive association; **= 1:** independent; **< 1:** negative.
- **Apriori principle:** all subsets of a frequent itemset must be frequent (used to prune). **FP-Growth** is faster (no candidate generation).

**Example:** 100 transactions; bread 40, butter 30, both 20. Support = 0.2; Confidence(bread→butter) = 20/40 = **0.5**; Lift = 0.5 / 0.3 = **1.67**.

## 6. Anomaly Detection
- **Statistical** (Z-score, IQR), **Isolation Forest** (outliers are isolated in fewer splits), **One-class SVM**, **DBSCAN noise**, **autoencoder reconstruction error**, **Local Outlier Factor**.

## 7. Clustering Evaluation
- **Internal (no labels):** Silhouette, Davies–Bouldin (lower is better), Calinski–Harabasz (higher is better), inertia.
- **External (with ground truth):** Adjusted Rand Index, NMI, purity.

## 8. Common Interview Questions
1. Explain K-Means. How do you choose k?
2. Limitations of K-Means? How does k-means++ help?
3. K-Means vs hierarchical vs DBSCAN?
4. What does a silhouette score of −0.5 mean? (Point probably in the wrong cluster.)
5. What is PCA? Explain the steps. Why scale first?
6. PCA vs LDA?
7. Support, confidence, lift?
8. What is the curse of dimensionality and how does PCA help?
9. How do you detect anomalies without labels?
10. Does K-Means always converge? To a global optimum? (Converges; not global.)

## MCQ Traps
- **K-Means = partitional, centroid-based, needs k, local optimum.**
- **DBSCAN detects noise; no k needed.**
- PCA is **unsupervised**, **linear**, and picks directions of **max variance**.
- PCA components are **orthogonal**.
- **Always scale before K-Means and PCA.**
- **Lift = 1 means independence.**
- **t-SNE is for visualization**, not a general preprocessing step.
- **Elbow** uses inertia; **silhouette** ranges −1 to 1.

## Practice MCQs
1. Which clustering handles arbitrary shapes and noise? **(a) K-Means (b) DBSCAN (c) GMM (d) PCA** → **b**
2. Confidence(A→B) = 0.6, support(B) = 0.3. Lift? → **2**
3. PCA picks directions that maximize → **variance**
4. K-Means objective → **minimize within-cluster sum of squares**
5. Agglomerative clustering is shown as a → **dendrogram**
