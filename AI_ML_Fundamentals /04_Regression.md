# 04 — Regression

Regression predicts a **continuous** value.

## 1. Simple & Multiple Linear Regression ⭐
- **Simple:** ŷ = w₀ + w₁x (one feature). **Multiple:** ŷ = w₀ + w₁x₁ + … + wₙxₙ.
- w₀ = intercept (bias), wᵢ = slope/coefficient. A coefficient is the change in y per unit change in xᵢ, **holding others constant**.
- **Goal:** minimize the sum of squared errors (**Ordinary Least Squares, OLS**).
- **Loss (MSE):** (1/n) Σ (yᵢ − ŷᵢ)².
- **Closed form (Normal Equation):** w = (XᵀX)⁻¹ Xᵀy. Costly for many features (O(n³)); fails if XᵀX is singular (multicollinearity).

**Simple regression formulas:** w₁ = Σ(x−x̄)(y−ȳ) / Σ(x−x̄)², w₀ = ȳ − w₁x̄.

**Worked example:** points (1,2), (2,4), (3,6). x̄ = 2, ȳ = 4 → w₁ = [(−1)(−2)+0+(1)(2)] / [1+0+1] = 4/2 = **2**, w₀ = 4 − 2×2 = **0**. So y = 2x. Predict x = 5 → **10**.

### Assumptions of Linear Regression ⭐ (LINE + no multicollinearity)
1. **Linearity** between X and y
2. **Independence** of errors (no autocorrelation)
3. **Normality** of residuals
4. **Equal variance (Homoscedasticity)** of residuals
5. **No (severe) multicollinearity** among features

Violation of constant variance = **heteroscedasticity**.

## 2. Gradient Descent ⭐⭐
Iteratively minimize the cost: **w ← w − η · ∂J/∂w**

For MSE with ŷ = wx + b: ∂J/∂w = −(2/n) Σ x(y − ŷ), ∂J/∂b = −(2/n) Σ (y − ŷ).

| Variant | Data per update | Pros / cons |
|---------|-----------------|-------------|
| **Batch GD** | All N samples | Stable, smooth. Slow on large data |
| **Stochastic GD (SGD)** | 1 sample | Fast, noisy, can escape local minima |
| **Mini-batch GD** | B samples (32, 64, 128…) | **Best trade-off, most used** |

**Learning rate η:**
- Too **small** → slow convergence.
- Too **large** → overshoots, oscillates, or **diverges**.
- Scale features so GD converges faster.

**One step by hand:** y = 2x target, data (x=1, y=2), w = 0, b = 0, η = 0.1. ŷ = 0; error = y − ŷ = 2; ∂J/∂w = −2·x·error = −4 (with J = (y−ŷ)², one sample) → w = 0 − 0.1(−4) = **0.4**.

**Normal Equation vs Gradient Descent:** Normal eq: no η, no iterations, but slow for large feature counts. GD: works for huge data, needs η and scaling.

## 3. Polynomial Regression
- Adds powers of features (x, x², x³) to model **non-linear** relationships.
- It is still **linear in the parameters**, hence "linear regression".
- Higher degree → **overfitting**.

## 4. Regularization ⭐⭐
Adds a penalty on weights to **reduce overfitting** (reduce variance).
| | **Ridge (L2)** | **Lasso (L1)** | **Elastic Net** |
|--|----------------|----------------|-----------------|
| Penalty | λ Σ wᵢ² | λ Σ \|wᵢ\| | Mix of both |
| Effect | **Shrinks** weights toward 0 (never exactly 0) | Drives some weights **exactly to 0** | Both |
| Feature selection | No | **Yes** | Yes |
| Good for | Multicollinearity, many small effects | Sparse models, feature selection | Correlated features + selection |

- **λ (alpha)** = regularization strength. λ = 0 → plain OLS. λ → ∞ → weights → 0 (underfit).
- Increasing λ: **bias ↑, variance ↓**.
- **Geometry:** L1 constraint is a diamond (corners on axes → sparse); L2 is a circle.
- Don't regularize the intercept. **Scale features** before regularization.

## 5. Regression Metrics ⭐
| Metric | Formula | Notes |
|--------|---------|-------|
| **MAE** | (1/n) Σ\|y − ŷ\| | Same units, **robust to outliers** |
| **MSE** | (1/n) Σ(y − ŷ)² | Penalizes large errors heavily |
| **RMSE** | √MSE | Same units as y, sensitive to outliers |
| **R² (coefficient of determination)** | 1 − SS_res / SS_tot | Fraction of variance explained. Can be **negative** for a bad model |
| **Adjusted R²** | 1 − (1−R²)(n−1)/(n−k−1) | Penalizes useless features. Use for multiple regression |

- **R² never decreases when you add features** (even junk). **Adjusted R²** can decrease.
- R² = 1 → perfect fit; R² = 0 → as good as predicting the mean.

**Example:** errors = 2, −3, 1 → MAE = 2, MSE = (4+9+1)/3 = 4.67, RMSE ≈ 2.16.

## 6. Residuals & Diagnostics
- **Residual** = actual − predicted.
- Residual vs fitted plot should look like **random scatter**. A funnel shape = heteroscedasticity; a curve = non-linearity.
- **Influential points / outliers:** Cook's distance.

## 7. Other Regression Models (one-liners)
- **Logistic regression:** classification, not regression (see 05).
- **Decision tree / Random Forest / XGBoost regressors:** non-linear, handle interactions, no scaling needed.
- **SVR:** support vector regression with an ε-tube.
- **kNN regressor:** average of the k nearest neighbours.
- **Tree-based models cannot extrapolate** beyond the range seen in training; linear models can.

## 8. Common Interview Questions
1. Explain linear regression and its assumptions.
2. How does gradient descent work? What if the learning rate is too high?
3. Batch vs SGD vs mini-batch?
4. Ridge vs Lasso? Which does feature selection?
5. What is R²? Why use adjusted R²?
6. MAE vs RMSE: when would you prefer each?
7. What is multicollinearity and how does it affect regression?
8. How to check whether a linear model is suitable? (Residual plots)
9. Is polynomial regression a linear model?
10. Normal equation vs gradient descent?

## MCQ Traps
- **L1 = Lasso = sparsity; L2 = Ridge = shrinkage.**
- **R² always increases (or stays) with more features; adjusted R² doesn't.**
- Polynomial regression is **linear in parameters**.
- Linear regression minimizes **squared** vertical distances (OLS).
- **Higher λ = more regularization = higher bias, lower variance.**
- RMSE ≥ MAE always, and is more outlier-sensitive.
- GD moves **against** the gradient.
- Logistic regression is for **classification**.

## Practice MCQs
1. Which regularization can make coefficients exactly zero? **(a) L2 (b) L1 (c) Dropout (d) None** → **b**
2. If R² = 0 the model is as good as → **predicting the mean of y**
3. Learning rate too large causes → **divergence / oscillation**
4. Which metric is most robust to outliers? **(a) MSE (b) RMSE (c) MAE (d) R²** → **c**
5. A funnel-shaped residual plot indicates → **heteroscedasticity**
