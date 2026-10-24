# 05 — Classification Algorithms

## 1. Logistic Regression ⭐⭐
- A **classification** algorithm. Output = **probability** via the **sigmoid**: σ(z) = 1 / (1 + e⁻ᶻ), z = wᵀx + b.
- Sigmoid output is in (0, 1). σ(0) = 0.5. Default threshold = 0.5.
- **Loss: Binary cross-entropy (log loss):** −[y log ŷ + (1−y) log(1−ŷ)]. (MSE is non-convex for logistic regression.)
- Decision boundary is **linear**. Coefficients are interpretable as **log-odds**: log(p/(1−p)) = wᵀx + b.
- **Multi-class:** One-vs-Rest, or **Softmax (multinomial)** regression. Softmax outputs sum to 1.
- Assumes no heavy multicollinearity; benefits from scaling; regularized (L1/L2) by default in sklearn.

**Example:** z = 0 → p = 0.5. z = 2 → p ≈ 0.88. z = −2 → p ≈ 0.12.

## 2. k-Nearest Neighbours (kNN) ⭐
- **Lazy, non-parametric.** Predict by **majority vote** (classification) or **average** (regression) of the k closest points.
- **Distances:** Euclidean (default), Manhattan, Minkowski, cosine, Hamming (categorical).
- **Choosing k:** small k → low bias, high variance (**overfit**, noisy). Large k → smoother, **underfit**. Use **odd k** for binary to avoid ties. Tune with cross-validation.
- **Needs feature scaling.** Suffers from the **curse of dimensionality**.
- Training O(1), **prediction O(n·d)**, so slow for big data. Must store all data.
- k = 1 → training accuracy 100% (each point is its own neighbour) → overfit.

## 3. Naive Bayes ⭐
- Applies **Bayes' theorem** with the **"naive" assumption that features are conditionally independent given the class.**
- P(C | x₁..xₙ) ∝ P(C) · Π P(xᵢ | C). Pick the class with the highest posterior.
- **Variants:** **Gaussian** (continuous), **Multinomial** (word counts, text), **Bernoulli** (binary features).
- **Laplace (add-one) smoothing** avoids zero-probability when a word was never seen in a class.
- Pros: very fast, works with little data, great for **text / spam**, handles high dimensions.
- Cons: independence assumption rarely true; poor probability calibration.
- It is **generative**.

**Worked example:** 10 emails: 6 spam, 4 ham. "free" appears in 4 of 6 spam, 1 of 4 ham. P(spam | free) = (4/6·6/10) / (4/6·6/10 + 1/4·4/10) = 0.4 / (0.4 + 0.1) = **0.8**.

## 4. Decision Tree ⭐⭐
- Tree of if-else splits. Internal node = feature test, leaf = class / value.
- **Splitting criteria:**
  - **Entropy / Information Gain** (ID3, C4.5): IG = H(parent) − Σ (nᵢ/n) H(childᵢ)
  - **Gini impurity** (CART): G = 1 − Σ pᵢ²
  - Regression trees: minimize variance / MSE.
- **Gini:** pure node = **0**; max for 2 classes = **0.5**. **Entropy:** pure = 0, max for 2 classes = **1**.
- **Algorithms:** ID3 (categorical, IG), C4.5 (handles continuous, gain ratio, pruning), **CART** (binary splits, Gini, classification + regression; used in sklearn).
- Greedy algorithm, so it finds a locally optimal split at each step.
- **Overfits easily** (a fully grown tree memorizes the training data). Control with **pruning** (pre: max_depth, min_samples_split, min_samples_leaf; post: cost-complexity).
- Pros: interpretable, no scaling, handles numeric + categorical, non-linear. Cons: unstable (small data change → different tree), overfits, biased to high-cardinality features.

**Worked example (entropy):** 9 positive, 5 negative → H = −(9/14)log₂(9/14) − (5/14)log₂(5/14) ≈ **0.940**.
**Gini example:** 50/50 → 1 − (0.25 + 0.25) = **0.5**.

## 5. Ensemble Learning ⭐⭐
Combine many weak/base models to get a strong one.
| | **Bagging** | **Boosting** | **Stacking** |
|--|-------------|--------------|--------------|
| Training | **Parallel**, independent models on bootstrap samples | **Sequential**, each fixes previous errors | Meta-model learns from base predictions |
| Reduces | **Variance** | **Bias** (and variance) | Both |
| Weak learner | Deep (high-variance) trees | Shallow trees / stumps | Mixed |
| Examples | **Random Forest** | **AdaBoost, Gradient Boosting, XGBoost, LightGBM, CatBoost** | |
| Overfitting risk | Low | Higher (needs tuning) | |

### Random Forest
- Many decision trees on **bootstrap samples** (bagging) **+ random subset of features at each split**. Final: **majority vote** / average.
- Reduces variance, robust to overfitting and outliers, gives **feature importance**, has **OOB (out-of-bag) error** (~37% of samples left out per tree) as a free validation estimate.
- Less interpretable than a single tree; slower; no scaling needed.

### Boosting
- **AdaBoost:** re-weights misclassified samples, then combines learners with weights.
- **Gradient Boosting:** each new tree fits the **residuals (negative gradient)** of the current model.
- **XGBoost:** regularized, fast, handles missing values; dominates tabular data competitions. **LightGBM** is leaf-wise and very fast. **CatBoost** handles categorical features natively.
- Key hyperparameters: n_estimators, learning_rate (shrinkage), max_depth, subsample.

## 6. Support Vector Machine (SVM) ⭐⭐
- Finds the hyperplane that **maximizes the margin** between classes. Margin = 2/‖w‖.
- **Support vectors:** the points closest to the boundary. **Only they define the hyperplane.** Removing other points doesn't change it.
- **Soft margin & C:** large **C** → small margin, fewer violations (**overfit**); small C → wider margin, more tolerance (**underfit**).
- **Kernel trick:** implicitly map data to a higher dimension so it becomes linearly separable, without computing the mapping.
  - **Linear, Polynomial, RBF (Gaussian; default)**, Sigmoid.
  - RBF **gamma**: large γ → narrow influence → **overfit**; small γ → underfit.
- **Needs feature scaling.** Works well in high dimensions and small/medium data. Slow on very large datasets (O(n²)–O(n³)). Not probabilistic by default.
- Hinge loss: max(0, 1 − y·f(x)).

## 7. Algorithm Comparison ⭐
| Algorithm | Type | Scaling needed | Interpretable | Handles non-linear | Notes |
|-----------|------|:--:|:--:|:--:|-------|
| Logistic Reg | Discriminative, parametric | Yes | High | No (linear) | Probabilities, fast baseline |
| kNN | Lazy, non-param | **Yes** | Medium | Yes | Slow predict |
| Naive Bayes | Generative | No | High | Limited | Text, fast |
| Decision Tree | Non-param | No | **Very high** | Yes | Overfits |
| Random Forest | Bagging | No | Low | Yes | Robust default |
| XGBoost | Boosting | No | Low | Yes | Best on tabular |
| SVM | Margin-based | **Yes** | Low | Yes (kernel) | Small/medium data |

## 8. Multi-class Strategies
- **One-vs-Rest (OvR):** k binary classifiers (class i vs all others).
- **One-vs-One (OvO):** k(k−1)/2 classifiers. (SVM in sklearn uses OvO.)
- **Softmax** for a natively multi-class output (NNs, multinomial logistic regression).

## 9. Common Interview Questions
1. How does logistic regression work? Why "regression" in the name?
2. Why is MSE not used for logistic regression?
3. How do you choose k in kNN? Effect of k?
4. Why is Naive Bayes "naive"? What is Laplace smoothing?
5. Entropy vs Gini? How does a decision tree choose a split?
6. How do you prevent decision tree overfitting?
7. Bagging vs boosting? Random Forest vs Gradient Boosting?
8. Why does Random Forest add random feature selection?
9. What is the kernel trick? What do C and gamma do?
10. What are support vectors?
11. When would you choose SVM over Random Forest?
12. Which algorithm for a small dataset with many features? (SVM / Naive Bayes / regularized LR)

## MCQ Traps
- **Logistic regression = classification; output via sigmoid; loss = log loss.**
- **kNN needs scaling; trees do not.**
- **Large k → underfitting; k = 1 → overfitting.**
- **Bagging ↓ variance; boosting ↓ bias.**
- Random Forest = bagging + **random feature subsets**.
- Max Gini (binary) = **0.5**; max entropy (binary) = **1**.
- SVM: **only support vectors** matter. Higher C = **less** regularization.
- Naive Bayes: features **independent given the class**.
- Boosting is **sequential** and can't be parallelized across trees; bagging can.

## Practice MCQs
1. sigmoid(0) = ? → **0.5**
2. Gini impurity of a node with 3 A and 1 B → 1 − (0.5625 + 0.0625) = **0.375**
3. Which reduces variance? **(a) Boosting (b) Bagging (c) Pruning only (d) None** → **b**
4. RBF kernel with very large gamma likely → **overfits**
5. Which technique avoids zero probabilities in Naive Bayes? → **Laplace smoothing**
