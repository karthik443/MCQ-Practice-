# 02 — Math & Statistics Essentials

Only what placements actually test. No proofs.

## 1. Descriptive Statistics
| Measure | Formula / note |
|---------|----------------|
| **Mean** | Σx / n. Sensitive to outliers |
| **Median** | Middle value. **Robust to outliers** |
| **Mode** | Most frequent value |
| **Variance** | σ² = Σ(x − μ)² / n (sample variance divides by **n − 1**) |
| **Std. deviation** | σ = √variance (same units as data) |
| **Range / IQR** | max − min / Q3 − Q1 |
| **Skewness** | Right-skewed: **mean > median > mode**. Left-skewed: mean < median < mode |
| **Covariance** | How two variables vary together. Sign tells direction, magnitude is scale-dependent |
| **Correlation (Pearson r)** | Cov(X,Y) / (σx σy), range **[−1, +1]**, unit-free. Measures **linear** relation only |

**Correlation ≠ causation.** r = 0 means no *linear* relation, not independence.

**Example:** data = 2, 4, 4, 4, 5, 5, 7, 9 → mean 5, variance (population) = 4, σ = 2.

## 2. Probability Basics ⭐
- P(A) ∈ [0, 1]. P(Aᶜ) = 1 − P(A).
- **Union:** P(A ∪ B) = P(A) + P(B) − P(A ∩ B)
- **Conditional:** P(A | B) = P(A ∩ B) / P(B)
- **Independent events:** P(A ∩ B) = P(A)·P(B)
- **Mutually exclusive:** P(A ∩ B) = 0 (so **mutually exclusive events with non-zero probability are NOT independent**)
- **Chain rule:** P(A ∩ B) = P(A | B)·P(B)
- **Total probability:** P(B) = Σ P(B | Aᵢ) P(Aᵢ)

### Bayes' Theorem ⭐⭐ (asked everywhere)
**P(A | B) = P(B | A) · P(A) / P(B)**

Terms: **Posterior** = Likelihood × Prior / Evidence.

**Worked example:** A disease affects 1% of people. The test has 99% sensitivity (true positive) and 5% false-positive rate. A person tests positive. P(disease)?
- P(D) = 0.01, P(+|D) = 0.99, P(+|¬D) = 0.05
- P(+) = 0.99×0.01 + 0.05×0.99 = 0.0099 + 0.0495 = 0.0594
- P(D|+) = 0.0099 / 0.0594 ≈ **0.167 (16.7%)**

Lesson: with a low **base rate**, even an accurate test gives many false positives.

## 3. Random Variables & Distributions
| Distribution | Type | Use | Key facts |
|--------------|------|-----|-----------|
| **Bernoulli** | Discrete | One trial, success p | mean p, var p(1−p) |
| **Binomial** | Discrete | # successes in n trials | mean np, var np(1−p) |
| **Poisson** | Discrete | Count of events in an interval | mean = variance = λ |
| **Uniform** | Both | All outcomes equally likely | |
| **Normal (Gaussian)** | Continuous | Natural phenomena, errors | Bell curve, symmetric, mean = median = mode |
| **Exponential** | Continuous | Time between events | Memoryless |

### Normal distribution: the 68–95–99.7 rule ⭐
- μ ± 1σ → **68%**
- μ ± 2σ → **95%**
- μ ± 3σ → **99.7%**
- **Z-score** = (x − μ) / σ. Standardizes to mean 0, std 1.

**Central Limit Theorem (CLT):** the distribution of the **sample mean** approaches a normal distribution as sample size grows (n ≳ 30), **regardless of the population distribution**.

**Expected value:** E[X] = Σ x·P(x). Linear: E[aX + b] = aE[X] + b.

## 4. Inferential Statistics
- **Null hypothesis (H₀):** no effect. **Alternative (H₁):** there is an effect.
- **p-value:** probability of seeing results at least this extreme **if H₀ is true**. If **p < α** (commonly 0.05), reject H₀.
- **Type I error (α):** reject a true H₀ → **false positive**.
- **Type II error (β):** fail to reject a false H₀ → **false negative**.
- **Power** = 1 − β.
- **Confidence interval:** range likely to contain the true parameter.
- Common tests: **t-test** (compare means), **chi-square** (categorical association), **ANOVA** (3+ group means).

## 5. Information Theory (for decision trees and loss)
- **Entropy:** H = −Σ pᵢ log₂ pᵢ. Max for a uniform distribution, **0 for a pure set**.
  - 50/50 binary split → H = **1 bit**. 100/0 → H = 0.
- **Information gain** = H(parent) − weighted H(children).
- **Cross-entropy:** −Σ y log(ŷ). Standard **classification loss**.
- **KL divergence:** how one distribution differs from another (not symmetric).

## 6. Linear Algebra Essentials
- **Vector:** 1-D array. **Matrix:** 2-D. **Tensor:** n-D.
- **Dot product:** a·b = Σ aᵢbᵢ = |a||b|cosθ. The basis of neurons and similarity.
- **Matrix multiplication:** (m×n)·(n×p) → (m×p). **Not commutative** (AB ≠ BA in general).
- **Transpose:** rows ↔ columns. (AB)ᵀ = BᵀAᵀ.
- **Identity:** AI = A. **Inverse:** AA⁻¹ = I (exists only for square, non-singular matrices, det ≠ 0).
- **Eigenvector:** direction unchanged by a transformation: **Av = λv**. λ is the eigenvalue. **PCA uses eigenvectors of the covariance matrix.**
- **L1 norm:** Σ|xᵢ| (Manhattan). **L2 norm:** √Σxᵢ² (Euclidean).
- **Cosine similarity:** (a·b) / (|a||b|), range [−1, 1]. Used for text/embeddings.
- **SVD:** A = UΣVᵀ. Used in PCA, recommenders, LSA.
- **Rank:** number of linearly independent rows/columns.

## 7. Calculus Essentials
- **Derivative:** slope / rate of change. **Gradient:** vector of partial derivatives.
- **Gradient descent:** w ← w − η · ∂L/∂w (move **opposite** to the gradient). η = learning rate.
- **Chain rule:** d/dx f(g(x)) = f′(g(x))·g′(x). **The mathematical basis of backpropagation.**
- **Convex function:** one global minimum. Linear regression with MSE is convex; neural network loss is **non-convex** (local minima, saddle points).

**Quick gradient step:** L = w², w = 4, η = 0.1 → gradient = 2w = 8 → w_new = 4 − 0.1×8 = **3.2**.

## 8. Common Interview Questions
1. State Bayes' theorem and give a use in ML (Naive Bayes).
2. What is the p-value? What do you do if p < 0.05?
3. Type I vs Type II error?
4. Covariance vs correlation?
5. What is the Central Limit Theorem and why does it matter?
6. What does a Z-score tell you?
7. Why is the gradient negative in gradient descent?
8. What is an eigenvector? Where is it used in ML? (PCA)
9. What is entropy? What does entropy = 0 mean?
10. Mean vs median: which do you use with outliers?

## MCQ Traps
- **Sample variance divides by n − 1** (Bessel's correction); population divides by n.
- **Correlation is bounded [−1, 1]; covariance is not.**
- **Independent ≠ mutually exclusive.**
- Right-skewed: **mean > median**.
- **Type I = false positive; Type II = false negative.**
- **Poisson: mean = variance.**
- Matrix multiplication is **not commutative**.

## Practice MCQs
1. P(A)=0.4, P(B)=0.5, independent. P(A∩B)? → **0.2**
2. Height ~ N(170, 10²). What % lie between 160 and 180? → **≈68%**
3. Which measure is robust to outliers? **(a) mean (b) median (c) variance (d) range** → **b**
4. Entropy of a pure node = ? → **0**
5. Gradient descent update with gradient +5, η = 0.2, w = 3 → **2.0**
