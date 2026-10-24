# 03 — Data Preprocessing & Feature Engineering

"Garbage in, garbage out." This topic is very common in OAs because it is easy to frame as MCQs.

## 1. Types of Data
| Type | Sub-type | Example |
|------|----------|---------|
| **Numerical** | Continuous | height, price |
| | Discrete | number of children |
| **Categorical** | **Nominal** (no order) | colour, city |
| | **Ordinal** (ordered) | low/medium/high, grade |

## 2. Handling Missing Values ⭐
**Types of missingness:**
- **MCAR:** missing completely at random
- **MAR:** missing depends on other observed columns
- **MNAR:** missing depends on the missing value itself (e.g. high earners hide salary)

**Techniques:**
| Method | When |
|--------|------|
| **Drop rows** | Few missing (<5%) and MCAR |
| **Drop column** | Majority (>50–60%) missing |
| **Mean imputation** | Numeric, no outliers, roughly symmetric |
| **Median imputation** | Numeric **with outliers / skew** |
| **Mode imputation** | Categorical |
| **Constant / "Unknown"** | Missing itself carries information |
| **Forward/backward fill** | Time series |
| **kNN / iterative (MICE) imputation** | Better accuracy, costlier |
| **Missing-indicator column** | Keep the information that a value was missing |

**Always compute imputation statistics on the training set only**, then apply them to the test set (avoids leakage).

## 3. Outliers ⭐
- **IQR method:** outlier if x < Q1 − 1.5·IQR or x > Q3 + 1.5·IQR. (Box plot whiskers.)
- **Z-score method:** |z| > 3 (assumes roughly normal data).
- Handling: remove (if an error), **cap / winsorize**, log-transform, or use robust models (trees) and robust scaler.
- Outliers hurt: **mean, linear regression, kNN, k-means, scaling by min-max**.
- Robust to outliers: **median, tree-based models, MAE loss**.

**Example:** Q1 = 10, Q3 = 20 → IQR = 10 → fences: −5 and 35. Value 50 is an outlier.

## 4. Feature Scaling ⭐⭐
| Method | Formula | Range | Notes |
|--------|---------|-------|-------|
| **Min-Max (Normalization)** | (x − min) / (max − min) | [0, 1] | Sensitive to outliers |
| **Standardization (Z-score)** | (x − μ) / σ | mean 0, std 1 | Not bounded; most common |
| **Robust scaler** | (x − median) / IQR | — | Good with outliers |
| **Log / Power transform** | log(x), Box-Cox | — | Reduces right skew |
| **Max-abs scaler** | x / max(|x|) | [−1, 1] | Sparse data |

**Needs scaling (distance / gradient based):** kNN, K-Means, SVM, PCA, linear/logistic regression with gradient descent, neural networks, regularized models.
**Does NOT need scaling:** **Decision Trees, Random Forest, XGBoost/GBM**, Naive Bayes.

**Min-max example:** ages 20, 30, 50 → (30−20)/(50−20) = **0.33**.
**Rule:** `fit` scaler on **train only**; `transform` both train and test.

## 5. Encoding Categorical Variables ⭐
| Method | Use | Watch out |
|--------|-----|-----------|
| **Label encoding** | Target labels; ordinal features | Implies an order. Bad for nominal features in linear/distance models |
| **Ordinal encoding** | Ordered categories (S < M < L) | |
| **One-hot encoding** | Nominal, low cardinality | Increases dimensions. **Dummy variable trap** (drop one column, k−1 dummies) |
| **Binary / hashing** | High cardinality | Collisions (hashing) |
| **Target / mean encoding** | High cardinality | **Leakage risk**, use within CV folds |
| **Frequency encoding** | High cardinality | |
| **Embeddings** | Very high cardinality (deep learning) | |

One-hot of a column with 4 categories → 4 columns (or **3** after avoiding the dummy trap).

## 6. Feature Engineering
- **Creating features:** date → day/month/weekday/is_weekend; ratios (price/area); interactions (x₁·x₂); polynomial features; text length; aggregates (mean spend per user).
- **Binning / discretization:** age → age groups.
- **Transformation:** log for skew, sqrt, Box-Cox.
- **Domain knowledge** is the best source of features.

## 7. Feature Selection vs Extraction ⭐
| | Feature **Selection** | Feature **Extraction** |
|--|-----------------------|------------------------|
| Idea | Keep a **subset** of original features | Create **new** features from combinations |
| Keeps interpretability | Yes | Usually no |
| Examples | Filter, wrapper, embedded | **PCA**, LDA, autoencoders, t-SNE |

**Selection methods:**
- **Filter:** statistics independent of the model: correlation, chi-square, ANOVA F-test, mutual information, variance threshold. *Fast.*
- **Wrapper:** search subsets using model performance: forward selection, backward elimination, **RFE**. *Accurate but expensive.*
- **Embedded:** selection happens during training: **Lasso (L1)**, tree feature importance.

**Multicollinearity:** highly correlated features. Detect with the correlation matrix or **VIF** (VIF > 5–10 is a problem). It destabilizes **linear regression coefficients**; it does not hurt prediction as much and trees are largely unaffected.

## 8. Dimensionality Reduction & the Curse of Dimensionality
- As the number of features grows, data becomes **sparse**, distances become less meaningful, and models overfit.
- Fixes: feature selection, PCA, regularization, more data.

## 9. Imbalanced Data ⭐
When one class is rare (fraud 1%, disease 0.1%), **accuracy is misleading**: predicting "no fraud" always gives 99%.
| Technique | Note |
|-----------|------|
| **Resampling: oversample minority** | Random duplication |
| **SMOTE** | Synthesizes new minority points by interpolating between neighbours |
| **Undersample majority** | Loses information |
| **Class weights** (`class_weight='balanced'`) | Penalize minority errors more |
| **Better metrics** | Precision, Recall, F1, PR-AUC |
| **Threshold tuning** | Move the decision threshold |
| **Ensembles** | Balanced Random Forest, EasyEnsemble |

**Resample only the training set.** Never the validation/test set.

## 10. Train / Validation / Test Split
- Typical: **70/15/15** or **80/20**.
- **Stratified split** keeps the class ratio in every split. Use it for imbalanced data.
- **Time series:** split **chronologically**. Never shuffle.
- **Data leakage:** information from outside the training data sneaks in (scaling on full data, target-derived features, future information). It makes validation scores look unrealistically good.

## 11. Common Interview Questions
1. How do you handle missing values? When mean vs median?
2. Normalization vs standardization? Which algorithms need scaling?
3. How do you deal with categorical variables? What is the dummy variable trap?
4. How do you detect and handle outliers?
5. What is data leakage? Give an example.
6. How do you handle imbalanced data? What is SMOTE?
7. Feature selection vs feature extraction?
8. What is multicollinearity and how do you detect it? (VIF)
9. Why do tree-based models not need scaling?
10. What is the curse of dimensionality?

## MCQ Traps
- **Median** for skewed/outlier data; **mean** for symmetric.
- Scale **after** splitting: `fit` on train only.
- **Trees don't need scaling; kNN/SVM/K-Means/PCA do.**
- Label encoding nominal data introduces a **false ordering**.
- **SMOTE on the training set only.**
- Accuracy is unreliable on imbalanced data.
- Min-max normalization is **sensitive to outliers**.
- **Lasso** performs feature selection; **Ridge** doesn't.

## Practice MCQs
1. Which model does NOT need feature scaling? **(a) kNN (b) SVM (c) Random Forest (d) K-Means** → **c**
2. Salaries have extreme outliers. Best imputation? → **Median**
3. A column has 5 nominal categories. One-hot (no dummy trap) gives → **4 columns**
4. Q1 = 25, Q3 = 45. Upper outlier fence? → 45 + 1.5×20 = **75**
5. Which is an embedded feature-selection method? **(a) chi-square (b) RFE (c) Lasso (d) PCA** → **c**
