# 50 MCQs — AI/ML Fundamentals (Topics 01–06)

Coverage: 01 Basics (Q1–6) · 02 Math & Stats (Q7–14) · 03 Preprocessing (Q15–23) · 04 Regression (Q24–31) · 05 Classification (Q32–43) · 06 Unsupervised (Q44–50)

Click **Show answer** under each question to reveal the answer and reasoning. Every answer is **(b)** or **(c)**.

---

## Section A — AI/ML Basics (01)

**Q1.** Which statement correctly describes the relationship between AI, ML and DL?
- (a) ML ⊂ DL ⊂ AI
- (b) AI ⊂ ML ⊂ DL
- (c) DL ⊂ ML ⊂ AI
- (d) AI, ML and DL are mutually disjoint fields

<details>
<summary>Show answer</summary>

**Answer: (c) DL ⊂ ML ⊂ AI**

DL is a subset of ML, which is a subset of AI.

</details>

**Q2.** BERT is pre-trained by predicting randomly masked words in a sentence. This learning paradigm is best called:
- (a) Supervised learning with human labels
- (b) Self-supervised learning
- (c) Reinforcement learning
- (d) Clustering

<details>
<summary>Show answer</summary>

**Answer: (b) Self-supervised learning**

Labels (the masked words) come from the data itself → self-supervised.

</details>

**Q3.** A dataset has 4800 samples. It is trained with mini-batch gradient descent, batch size 120, for 5 epochs. How many weight updates (iterations) occur in total?
- (a) 40
- (b) 120
- (c) 200
- (d) 960

<details>
<summary>Show answer</summary>

**Answer: (c) 200**

4800/120 = 40 iterations per epoch × 5 epochs = 200.

</details>

**Q4.** Which of the following is a hyperparameter rather than a learned parameter?
- (a) Weights of a neural network
- (b) The value of *k* in kNN
- (c) Intercept of a linear regression model
- (d) Split thresholds chosen inside a decision tree

<details>
<summary>Show answer</summary>

**Answer: (b) The value of *k* in kNN**

*k* is set before training; weights, intercepts and learned thresholds are parameters.

</details>

**Q5.** Which algorithm is a *lazy learner* (no real training phase, computation deferred to prediction time)?
- (a) Decision Tree
- (b) SVM
- (c) k-Nearest Neighbours
- (d) Logistic Regression

<details>
<summary>Show answer</summary>

**Answer: (c) k-Nearest Neighbours**

kNN just stores the data and computes at prediction time.

</details>

**Q6.** Which of the following is an example of **data leakage**?
- (a) Splitting the data first, then scaling
- (b) Fitting `StandardScaler` on the full dataset before the train/test split
- (c) Using a stratified split for an imbalanced dataset
- (d) Tuning hyperparameters on the validation set

<details>
<summary>Show answer</summary>

**Answer: (b) Fitting `StandardScaler` on the full dataset before the train/test split**

Scaler statistics from the test set leak into training. Always `fit` on train only.

</details>

---

## Section B — Math & Statistics (02)


**Q7.** The sample variance (divide by n − 1) of the data 2, 4, 4, 4, 5, 5, 7, 9 is approximately:
- (a) 4.00
- (b) 4.57
- (c) 5.00
- (d) 3.50

<details>
<summary>Show answer</summary>

**Answer: (b) 4.57**

mean = 5, Σ(x−μ)² = 32, and 32/7 ≈ 4.57 (population variance would be 32/8 = 4).

</details>

**Q8.** For a right-skewed distribution, which ordering holds?
- (a) mean < median < mode
- (b) mean = median = mode
- (c) mean > median > mode
- (d) median > mean > mode

<details>
<summary>Show answer</summary>

**Answer: (c) mean > median > mode**

The long right tail pulls the mean above the median, which is above the mode.

</details>

**Q9.** 2% of transactions are fraudulent. A detector flags 90% of fraudulent transactions and also wrongly flags 10% of legitimate ones. If a transaction is flagged, the probability it is actually fraud is about:
- (a) 90%
- (b) 18%
- (c) 15.5%
- (d) 9.8%

<details>
<summary>Show answer</summary>

**Answer: (c) 15.5%**

P(flag) = 0.9×0.02 + 0.1×0.98 = 0.018 + 0.098 = 0.116. P(fraud | flag) = 0.018/0.116 ≈ 0.155. Low base rate → many false positives.

</details>

**Q10.** A and B are independent with P(A) = 0.5 and P(B) = 0.4. What is P(A ∪ B)?
- (a) 0.9
- (b) 0.7
- (c) 0.2
- (d) 0.45

<details>
<summary>Show answer</summary>

**Answer: (b) 0.7**

P(A∩B) = 0.5×0.4 = 0.2, so P(A∪B) = 0.5 + 0.4 − 0.2 = 0.7. (0.9 forgets the overlap.)

</details>

**Q11.** A drug is declared effective when in reality it has no effect. This is a:
- (a) Type II error
- (b) Correct decision with power 1 − β
- (c) Type I error
- (d) Sampling bias

<details>
<summary>Show answer</summary>

**Answer: (c) Type I error**

Rejecting a true H₀ (false positive) is a Type I error.

</details>

**Q12.** Loss L = w², current w = 5, learning rate η = 0.1. After one gradient descent step, w is:
- (a) 4.5
- (b) 4.0
- (c) 5.5
- (d) 0.0

<details>
<summary>Show answer</summary>

**Answer: (b) 4.0**

Gradient = 2w = 10, so w = 5 − 0.1×10 = 4.0.

</details>

**Q13.** A is a 3×4 matrix and B is a 4×2 matrix. Which statement is true?
- (a) AB is 4×4
- (b) BA is 2×3
- (c) AB is 3×2 and BA is undefined
- (d) AB and BA are both defined and equal

<details>
<summary>Show answer</summary>

**Answer: (c) AB is 3×2 and BA is undefined**

(3×4)(4×2) → 3×2. BA would need 2 = 4, which fails, so it is undefined. Matrix multiplication is not commutative.

</details>

**Q14.** The entropy of a random variable with 4 equally likely outcomes is:
- (a) 1 bit
- (b) 2 bits
- (c) 4 bits
- (d) 0.25 bits

<details>
<summary>Show answer</summary>

**Answer: (b) 2 bits**

H = −4 × (¼ × log₂¼) = 2 bits.

</details>

---

## Section C — Data Preprocessing & Feature Engineering (03)


**Q15.** Q1 = 12 and Q3 = 28. Using the 1.5×IQR rule, the upper outlier fence is:
- (a) 40
- (b) 44
- (c) 52
- (d) 56

<details>
<summary>Show answer</summary>

**Answer: (c) 52**

IQR = 16; upper fence = 28 + 1.5×16 = 52.

</details>

**Q16.** Values: 10, 20, 40, 70. After min-max normalization, the value 40 becomes:
- (a) 0.40
- (b) 0.50
- (c) 0.67
- (d) 0.30

<details>
<summary>Show answer</summary>

**Answer: (b) 0.50**

(40 − 10)/(70 − 10) = 30/60 = 0.5.

</details>

**Q17.** Which model is the *least* affected by feature scaling?
- (a) kNN
- (b) Random Forest
- (c) K-Means
- (d) SVM with RBF kernel

<details>
<summary>Show answer</summary>

**Answer: (b) Random Forest**

Tree ensembles split on thresholds, so monotonic scaling is irrelevant. kNN, K-Means and SVM are distance-based.

</details>

**Q18.** A nominal column has 6 categories. One-hot encoding that avoids the dummy variable trap produces:
- (a) 6 columns
- (b) 7 columns
- (c) 5 columns
- (d) 1 column

<details>
<summary>Show answer</summary>

**Answer: (c) 5 columns**

k − 1 = 5 dummy columns.

</details>

**Q19.** Which is an example of **MNAR** (Missing Not At Random) data?
- (a) A sensor randomly fails and drops readings
- (b) Income is missing more often for younger respondents (age is recorded)
- (c) High earners deliberately leave the salary field blank
- (d) Rows are deleted at random during export

<details>
<summary>Show answer</summary>

**Answer: (c) High earners deliberately leave the salary field blank**

The missingness depends on the unobserved value itself. (b) is MAR; (a) and (d) are MCAR.

</details>

**Q20.** SMOTE should be applied to:
- (a) The entire dataset before splitting
- (b) The training set only
- (c) The test set only
- (d) The validation and test sets

<details>
<summary>Show answer</summary>

**Answer: (b) The training set only**

Resample only the training data. Oversampling before the split leaks synthetic copies into validation/test.

</details>

**Q21.** Which of the following is an **embedded** feature-selection technique?
- (a) Pearson correlation filter
- (b) PCA
- (c) L1 (Lasso) regularization
- (d) Forward selection

<details>
<summary>Show answer</summary>

**Answer: (c) L1 (Lasso) regularization**

Lasso selects features during model training. (a) is a filter, (d) is a wrapper, and (b) is feature extraction.

</details>

**Q22.** Fraud is 1% of the data. A model predicts "not fraud" for every sample. Its accuracy and fraud-recall are:
- (a) 1% accuracy, 100% recall
- (b) 99% accuracy, 0% recall
- (c) 99% accuracy, 99% recall
- (d) 50% accuracy, 50% recall

<details>
<summary>Show answer</summary>

**Answer: (b) 99% accuracy, 0% recall**

It gets all 99% of negatives right and catches none of the positives (recall 0). Accuracy misleads on imbalanced data.

</details>

**Q23.** Regarding the Variance Inflation Factor (VIF):
- (a) VIF = 1 indicates severe multicollinearity
- (b) VIF is used to detect outliers
- (c) VIF > 10 suggests serious multicollinearity
- (d) A high VIF improves coefficient stability

<details>
<summary>Show answer</summary>

**Answer: (c) VIF > 10 suggests serious multicollinearity**

VIF = 1 means no collinearity; VIF > 5–10 signals a problem.

</details>

---

## Section D — Regression (04)


**Q24.** Training points are (1, 3), (2, 5), (3, 7). The fitted simple linear regression predicts which value at x = 4?
- (a) 8
- (b) 9
- (c) 10
- (d) 11

<details>
<summary>Show answer</summary>

**Answer: (b) 9**

The points lie exactly on y = 2x + 1, so at x = 4, y = 9.

</details>

**Q25.** Which statement about L1 vs L2 regularization is correct?
- (a) L2 produces sparse models by zeroing weights
- (b) L1 can set some weights exactly to zero, while L2 only shrinks them
- (c) Both force weights exactly to zero
- (d) Neither shrinks the weights

<details>
<summary>Show answer</summary>

**Answer: (b) L1 can set some weights exactly to zero, while L2 only shrinks them**

The L1 diamond constraint has corners on the axes (sparsity); the L2 circle only shrinks.

</details>

**Q26.** You add a completely irrelevant feature to a linear regression model. Which is true?
- (a) Both R² and adjusted R² must decrease
- (b) R² decreases, adjusted R² increases
- (c) R² does not decrease, but adjusted R² may decrease
- (d) Both always increase

<details>
<summary>Show answer</summary>

**Answer: (c) R² does not decrease, but adjusted R² may decrease**

R² never decreases when adding features; adjusted R² penalizes useless ones.

</details>

**Q27.** In gradient descent, a learning rate that is too large will most likely:
- (a) Reach the exact minimum faster
- (b) Converge very slowly
- (c) Overshoot, oscillate or even diverge
- (d) Get stuck only in local minima

<details>
<summary>Show answer</summary>

**Answer: (c) Overshoot, oscillate or even diverge**

The step overshoots the minimum and may oscillate or diverge.

</details>

**Q28.** Prediction errors are +2, −2, +4, −4. The RMSE is approximately:
- (a) 3.00
- (b) 3.16
- (c) 10.0
- (d) 2.50

<details>
<summary>Show answer</summary>

**Answer: (b) 3.16**

MSE = (4 + 4 + 16 + 16)/4 = 10, so RMSE = √10 ≈ 3.16. (MAE is 3, and RMSE ≥ MAE.)

</details>

**Q29.** A residual-vs-fitted plot shows a funnel shape (spread grows with fitted value). This indicates:
- (a) Multicollinearity
- (b) Non-linearity
- (c) Heteroscedasticity
- (d) Autocorrelation

<details>
<summary>Show answer</summary>

**Answer: (c) Heteroscedasticity**

A funnel means non-constant error variance, i.e. heteroscedasticity.

</details>

**Q30.** In Ridge regression, increasing λ typically results in:
- (a) Lower bias, higher variance
- (b) Higher bias, lower variance
- (c) Lower bias, lower variance
- (d) No change in either

<details>
<summary>Show answer</summary>

**Answer: (b) Higher bias, lower variance**

More regularization → simpler model → bias ↑, variance ↓.

</details>

**Q31.** Training data has x in [0, 10]. At x = 20, which regressor **cannot** extrapolate beyond the training range?
- (a) Linear regression
- (b) Decision tree regressor
- (c) Lasso regression
- (d) Elastic Net

<details>
<summary>Show answer</summary>

**Answer: (b) Decision tree regressor**

Trees predict averages of the leaves seen in training, so they flatten out of range. Linear models extrapolate.

</details>

---

## Section E — Classification Algorithms (05)


**Q32.** Why is MSE not preferred as the loss for logistic regression?
- (a) MSE cannot be computed on probabilities
- (b) MSE is slower than log loss in every case
- (c) With a sigmoid output, MSE is non-convex (local minima), whereas log loss is convex
- (d) MSE produces negative values

<details>
<summary>Show answer</summary>

**Answer: (c) With a sigmoid output, MSE is non-convex (local minima), whereas log loss is convex**

Sigmoid + squared error gives a non-convex cost surface; cross-entropy is convex.

</details>

**Q33.** In kNN, setting k = 1 leads to:
- (a) High bias and low variance
- (b) 100% training accuracy and a high risk of overfitting
- (c) Underfitting with a very smooth boundary
- (d) A model that ignores the nearest point

<details>
<summary>Show answer</summary>

**Answer: (b) 100% training accuracy and a high risk of overfitting**

Each point is its own nearest neighbour → 100% training accuracy, low bias, high variance.

</details>

**Q34.** Out of 20 emails, 12 are spam and 8 are ham. The word "offer" appears in 9 of the 12 spam and 2 of the 8 ham emails. P(spam | "offer") is approximately:
- (a) 0.75
- (b) 0.45
- (c) 0.82
- (d) 0.60

<details>
<summary>Show answer</summary>

**Answer: (c) 0.82**

Spam: 0.75 × 0.6 = 0.45. Ham: 0.25 × 0.4 = 0.10. P = 0.45/0.55 ≈ 0.82.

</details>

**Q35.** Laplace (add-one) smoothing in Naive Bayes is used to:
- (a) Speed up training
- (b) Avoid zero probabilities for word–class combinations unseen in training
- (c) Remove the conditional independence assumption
- (d) Normalize numeric features

<details>
<summary>Show answer</summary>

**Answer: (b) Avoid zero probabilities for word–class combinations unseen in training**

Adding 1 to the counts prevents a single unseen word from zeroing out the whole product.

</details>

**Q36.** A parent node has 4 positive and 4 negative samples (entropy = 1). A split gives left = (3+, 1−) and right = (1+, 3−), each with entropy ≈ 0.811. The information gain is approximately:
- (a) 0.811
- (b) 0.500
- (c) 0.189
- (d) 1.000

<details>
<summary>Show answer</summary>

**Answer: (c) 0.189**

IG = 1 − (½×0.811 + ½×0.811) = 1 − 0.811 = 0.189.

</details>

**Q37.** Which statement correctly compares bagging and boosting?
- (a) Bagging is sequential and mainly reduces bias; boosting is parallel
- (b) Bagging trains models in parallel on bootstrap samples and mainly reduces variance; boosting trains sequentially and mainly reduces bias
- (c) Both only reduce variance
- (d) Both are strictly sequential

<details>
<summary>Show answer</summary>

**Answer: (b) Bagging trains models in parallel on bootstrap samples and mainly reduces variance; boosting trains sequentially and mainly reduces bias**

Bagging (e.g. Random Forest) is parallel and cuts variance; boosting is sequential and cuts bias.

</details>

**Q38.** In a Random Forest, roughly what fraction of the training samples is out-of-bag (left out) for a given tree?
- (a) 5%
- (b) 63%
- (c) 37%
- (d) 50%

<details>
<summary>Show answer</summary>

**Answer: (c) 37%**

P(a sample is never picked) = (1 − 1/n)ⁿ → 1/e ≈ 0.368.

</details>

**Q39.** In a trained SVM, you delete a training point that is **not** a support vector and retrain. The decision boundary:
- (a) Shifts noticeably
- (b) Rotates by 90°
- (c) Stays unchanged
- (d) Becomes a soft margin

<details>
<summary>Show answer</summary>

**Answer: (c) Stays unchanged**

Only support vectors define the hyperplane.

</details>

**Q40.** An RBF-kernel SVM is trained with a very large C and a very large γ. The model will most likely:
- (a) Underfit
- (b) Overfit
- (c) Be an ideal fit
- (d) Fail to train

<details>
<summary>Show answer</summary>

**Answer: (b) Overfit**

Large C (little tolerance for violations) plus large γ (very narrow influence) memorizes the training data.

</details>

**Q41.** In Gradient Boosting, each new tree is trained to predict:
- (a) A bootstrap sample of the original labels
- (b) A random subset of the features
- (c) The residuals (negative gradient) of the current ensemble
- (d) Only the samples that were classified correctly

<details>
<summary>Show answer</summary>

**Answer: (c) The residuals (negative gradient) of the current ensemble**

Gradient boosting fits each new tree to the negative gradient (residuals) of the loss.

</details>

**Q42.** For a 5-class problem, how many binary classifiers does One-vs-One (OvO) need?
- (a) 5
- (b) 10
- (c) 20
- (d) 4

<details>
<summary>Show answer</summary>

**Answer: (b) 10**

k(k − 1)/2 = 5×4/2 = 10.

</details>

**Q43.** Which change would most likely **increase** overfitting in a decision tree?
- (a) Cost-complexity pruning
- (b) Removing the `max_depth` limit
- (c) Raising `min_samples_split`
- (d) Raising `min_samples_leaf`

<details>
<summary>Show answer</summary>

**Answer: (b) Removing the `max_depth` limit**

An unrestricted depth lets the tree memorize the training set. The other options are pruning or regularizing controls.

</details>

---

## Section F — Unsupervised Learning (06)


**Q44.** K-Means with k = 2 on points 2, 4, 10, 12 with initial centroids 2 and 12. After the first assign-and-update step, the new centroids are:
- (a) 2 and 12
- (b) 3 and 10
- (c) 3 and 11
- (d) 4 and 10

<details>
<summary>Show answer</summary>

**Answer: (c) 3 and 11**

Assign {2, 4} → C1 and {10, 12} → C2. New centroids are (2+4)/2 = 3 and (10+12)/2 = 11.

</details>

**Q45.** In DBSCAN, a point that has fewer than minPts neighbours within ε **and** is not within ε of any core point is a:
- (a) Core point
- (b) Noise point
- (c) Border point
- (d) Centroid

<details>
<summary>Show answer</summary>

**Answer: (b) Noise point**

Neither core nor within ε of a core point → noise (outlier).

</details>

**Q46.** Out of 200 transactions: A appears in 80, B in 50, and both in 30. The lift of A → B is:
- (a) 0.375
- (b) 1.0
- (c) 1.5
- (d) 0.75

<details>
<summary>Show answer</summary>

**Answer: (c) 1.5**

Confidence = 30/80 = 0.375; support(B) = 50/200 = 0.25; lift = 0.375/0.25 = 1.5 (> 1: positive association).

</details>

**Q47.** Which statement about PCA is correct?
- (a) It is supervised and maximizes class separability
- (b) It is unsupervised and linear, and its principal components are orthogonal directions of maximum variance
- (c) Its principal components are correlated with each other
- (d) It is a non-linear method meant only for visualization

<details>
<summary>Show answer</summary>

**Answer: (b) It is unsupervised and linear, and its principal components are orthogonal directions of maximum variance**

PCA is unsupervised and linear, with orthogonal PCs along maximum-variance directions. LDA is the supervised one.

</details>

**Q48.** A data point has a silhouette score of −0.4. This most likely means:
- (a) It is perfectly clustered
- (b) It lies exactly on the boundary between two clusters
- (c) It has probably been assigned to the wrong cluster
- (d) It is a DBSCAN noise point

<details>
<summary>Show answer</summary>

**Answer: (c) It has probably been assigned to the wrong cluster**

A negative silhouette means the point is closer to another cluster than to its own. 0 is on the boundary, and 1 is ideal.

</details>

**Q49.** The covariance matrix has eigenvalues 5, 3, 1, 1. What fraction of the variance do the first two principal components explain?
- (a) 50%
- (b) 80%
- (c) 60%
- (d) 90%

<details>
<summary>Show answer</summary>

**Answer: (b) 80%**

(5 + 3)/(5 + 3 + 1 + 1) = 8/10 = 80%.

</details>

**Q50.** Which statement about K-Means is true?
- (a) It always finds the global optimum
- (b) Its result is independent of initialization
- (c) It converges, but possibly to a local optimum, so k-means++ and multiple restarts are used
- (d) It handles non-convex clusters such as moons and rings well

<details>
<summary>Show answer</summary>

**Answer: (c) It converges, but possibly to a local optimum, so k-means++ and multiple restarts are used**

K-Means always converges but only to a local optimum, which is why k-means++ and multiple runs are used. It fails on non-convex shapes.

</details>
