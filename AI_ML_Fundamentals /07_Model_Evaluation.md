# 07 — Model Evaluation

## 1. Overfitting vs Underfitting ⭐⭐
| | **Underfitting** | **Overfitting** |
|--|------------------|-----------------|
| Training error | High | **Low** |
| Test error | High | **High** (gap is large) |
| Cause | Model too simple, too few features, too much regularization | Model too complex, too little data, noisy data, trained too long |
| Bias / Variance | **High bias**, low variance | Low bias, **high variance** |
| Fix | More complex model, more features, less regularization, train longer | **More data, regularization (L1/L2), dropout, early stopping, pruning, simpler model, cross-validation, data augmentation, ensembling** |

## 2. Bias–Variance Trade-off ⭐⭐
- **Bias:** error from wrong/oversimplified assumptions (systematic error).
- **Variance:** error from sensitivity to the training set (model changes a lot with different data).
- **Expected error = Bias² + Variance + Irreducible noise.**
- Increasing complexity: **bias ↓, variance ↑**. Goal = the sweet spot.
- Examples: linear regression on curved data = high bias. A deep unpruned tree / kNN with k = 1 = high variance.
- **Bagging ↓ variance. Boosting ↓ bias.**

## 3. Data Splitting & Cross-Validation ⭐
- **Hold-out:** single train/test split. Quick but high-variance estimate.
- **k-Fold CV:** split into k folds. Train on k−1, validate on 1, repeat k times, **average** the scores. Typical k = 5 or 10. Uses all data for both training and validation.
- **Stratified k-Fold:** preserves class ratios. **Use for classification / imbalanced data.**
- **Leave-One-Out (LOOCV):** k = n. Low bias but **expensive**, high variance.
- **Time-series split (walk-forward):** train on the past, test on the future. **Never shuffle.**
- **Nested CV:** inner loop tunes hyperparameters, outer loop estimates performance.
- k-fold trains **k models**. Larger k → lower bias, more computation.

## 4. Hyperparameter Tuning
- **Grid search:** try all combinations (exhaustive, expensive).
- **Random search:** sample combinations (often better for the same budget).
- **Bayesian optimization** (Optuna, Hyperopt): smarter search using past results.
- Always tune with **validation/CV**, never on the test set.

## 5. Classification Metrics ⭐⭐⭐
### Confusion Matrix
|  | **Predicted +** | **Predicted −** |
|--|:-:|:-:|
| **Actual +** | **TP** | **FN** (Type II) |
| **Actual −** | **FP** (Type I) | **TN** |

| Metric | Formula | Meaning |
|--------|---------|---------|
| **Accuracy** | (TP + TN) / total | Overall correct. **Misleading if imbalanced** |
| **Precision** | TP / (TP + FP) | Of predicted positives, how many were right. **Cost of false alarms** |
| **Recall (Sensitivity, TPR)** | TP / (TP + FN) | Of actual positives, how many were found. **Cost of misses** |
| **Specificity (TNR)** | TN / (TN + FP) | Of actual negatives, how many correctly rejected |
| **FPR** | FP / (FP + TN) = 1 − Specificity | |
| **F1-score** | 2PR / (P + R) | **Harmonic mean** of precision and recall |
| **Fβ** | (1+β²)PR / (β²P + R) | β > 1 favours recall |

**Worked example:** TP = 40, FP = 10, FN = 20, TN = 130 (total 200).
- Accuracy = 170/200 = **0.85**
- Precision = 40/50 = **0.80**
- Recall = 40/60 = **0.667**
- F1 = 2(0.8)(0.667)/(1.467) ≈ **0.727**
- Specificity = 130/140 = **0.929**

### Which metric to prioritize ⭐
| Situation | Prioritize |
|-----------|-----------|
| **Cancer / disease screening, fraud detection** (missing a positive is costly) | **Recall** |
| **Spam filter** (flagging a good email as spam is costly) | **Precision** |
| Imbalanced + need a balance | **F1** |
| Balanced classes | Accuracy |

**Precision–recall trade-off:** raising the threshold → precision ↑, recall ↓. Lowering → recall ↑, precision ↓.

### ROC & AUC ⭐
- **ROC curve:** TPR (recall) vs FPR at all thresholds. **AUC** = area under it.
- AUC = 1 perfect; **0.5 = random guessing**; < 0.5 worse than random (invert the predictions).
- AUC is **threshold-independent** and measures ranking quality. For **heavily imbalanced** data, prefer the **Precision–Recall curve (PR-AUC)**.
- **Log loss:** penalizes confident wrong probabilities.

### Multi-class averaging
- **Macro:** average per-class metric equally. **Micro:** pool all TP/FP/FN. **Weighted:** average weighted by class support.

**Trap:** F1 is the **harmonic** mean, not the arithmetic. If P = 1, R = 0 → F1 = **0**.

## 6. Regression Metrics (recap)
MAE, MSE, RMSE, R², Adjusted R². (See file 04.)

## 7. Learning Curves & Diagnosis
- **Training error low, validation error high, big gap** → overfitting → more data / regularize.
- **Both high and close** → underfitting → bigger model.
- **Early stopping:** stop training when validation loss starts rising.

## 8. Common Interview Questions
1. What are overfitting and underfitting? How to fix each?
2. Explain the bias–variance trade-off.
3. Precision vs recall? Give an example where recall matters more.
4. Why is accuracy bad for imbalanced data?
5. What is F1 and why harmonic mean?
6. Explain ROC-AUC. What does AUC = 0.5 mean?
7. What is k-fold CV and why use it? Stratified?
8. Train/validation/test roles?
9. How do you choose the classification threshold?
10. What is data leakage and how does CV handle it? (It doesn't automatically; preprocess within folds with a Pipeline.)

## MCQ Traps
- **Precision = TP/(TP+FP); Recall = TP/(TP+FN).** Learn these cold.
- **Type I = FP, Type II = FN.**
- AUC = 0.5 → **random**.
- **Disease detection → recall; spam → precision.**
- **High train accuracy + low test accuracy = overfitting.**
- **More data helps variance (overfitting) more than bias.**
- F1 = **harmonic** mean.
- Accuracy paradox with imbalanced classes.
- LOOCV = k-fold with **k = n**.

## Practice MCQs
1. TP = 30, FP = 10, FN = 10, TN = 50. Precision? → 30/40 = **0.75**
2. Same data, recall? → 30/40 = **0.75**
3. A model has 99% training and 70% test accuracy → **overfitting (high variance)**
4. Which metric best for detecting rare fraud? **(a) Accuracy (b) Recall / PR-AUC (c) R² (d) MSE** → **b**
5. A 10-fold CV trains how many models? → **10**
