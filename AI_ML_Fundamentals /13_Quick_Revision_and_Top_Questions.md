# 13 — Quick Revision (Read this right before the interview / OA)

## A. One-line definitions
| Term | One-liner |
|------|-----------|
| AI / ML / DL | AI ⊃ ML ⊃ DL. Smart machines / learning from data / multi-layer neural nets |
| Supervised | Labeled data, learn X → y (regression, classification) |
| Unsupervised | Unlabeled data, find structure (clustering, PCA) |
| Reinforcement | Agent learns by reward through interaction |
| Parameter / Hyperparameter | Learned by the model / set by you |
| Overfitting | Great on train, poor on test (high variance) |
| Underfitting | Poor on both (high bias) |
| Bias–variance | Simple → high bias; complex → high variance |
| Regularization | Penalty on weights to cut overfitting (L1/L2) |
| Cross-validation | Rotate train/validation folds for a reliable estimate |
| Data leakage | Test/future info leaks into training |
| Gradient descent | Step opposite to the gradient to minimize loss |
| Backpropagation | Chain rule to get gradients for all weights |
| Activation function | Adds non-linearity (ReLU, sigmoid, softmax) |
| Dropout | Randomly drop neurons in training to regularize |
| Batch norm | Normalize layer inputs per batch |
| CNN | Conv layers for images (local patterns, shared weights) |
| RNN / LSTM | Sequence models with memory; LSTM fixes vanishing gradients |
| Transformer | Self-attention, parallel, no recurrence |
| Self-attention | Each token weighs every other token: softmax(QKᵀ/√d)V |
| BERT / GPT | Encoder-only bidirectional / decoder-only autoregressive |
| Embedding | Dense vector representing meaning |
| RAG | Retrieve relevant docs, then let the LLM generate from them |
| Hallucination | Fluent but false LLM output |
| Temperature | Randomness of LLM sampling |
| PCA | Project onto max-variance orthogonal directions |
| K-Means | Partition into k clusters by nearest centroid |
| DBSCAN | Density-based clustering with noise detection |
| Precision | TP / (TP + FP) |
| Recall | TP / (TP + FN) |
| ROC-AUC | TPR vs FPR; 0.5 = random |
| SMOTE | Synthetic oversampling of the minority class |
| Ensemble | Combine models (bagging / boosting / stacking) |
| A* | Search with f = g + h, optimal if h is admissible |
| Q-learning | Off-policy value-based RL |
| GAN | Generator vs discriminator |

## B. Formulas cheat sheet
| What | Formula |
|------|---------|
| Mean / Variance | Σx/n ; Σ(x−μ)²/n (sample: n−1) |
| Z-score | (x − μ) / σ |
| Bayes | P(A\|B) = P(B\|A)P(A)/P(B) |
| Min-max | (x − min)/(max − min) |
| IQR outlier fences | Q1 − 1.5·IQR, Q3 + 1.5·IQR |
| Linear regression | ŷ = w₀ + w₁x₁ + …; w = (XᵀX)⁻¹Xᵀy |
| Gradient descent | w ← w − η·∂J/∂w |
| MSE / RMSE / MAE | mean(e²) / √MSE / mean(\|e\|) |
| R² | 1 − SS_res / SS_tot |
| Adjusted R² | 1 − (1−R²)(n−1)/(n−k−1) |
| Sigmoid | 1/(1+e⁻ᶻ) |
| Softmax | eᶻⁱ / Σeᶻʲ |
| Log loss (binary) | −[y log ŷ + (1−y) log(1−ŷ)] |
| Entropy | −Σ p log₂ p |
| Gini | 1 − Σ p² |
| Info gain | H(parent) − Σ (nᵢ/n) H(childᵢ) |
| Accuracy | (TP+TN)/total |
| Precision / Recall | TP/(TP+FP) / TP/(TP+FN) |
| F1 | 2PR/(P+R) |
| Specificity | TN/(TN+FP) |
| Silhouette | (b − a)/max(a, b) |
| Lift | confidence / support(B) |
| TF-IDF | TF × log(N/df) |
| Cosine similarity | a·b / (\|a\|\|b\|) |
| Attention | softmax(QKᵀ/√dₖ)V |
| Conv output | (W − F + 2P)/S + 1 |
| Dense params | in × out + out |
| Conv params | (F×F×C_in + 1) × C_out |
| Iterations / epoch | N / batch size |
| Q-learning | Q ← Q + α(r + γ maxQ′ − Q) |
| A* | f = g + h |
| Bias–variance | Error = Bias² + Variance + Noise |

## C. "Which one…?" quick answers
- Continuous output → **Regression**; discrete → **Classification**
- Segmenting customers with no labels → **Clustering (K-Means)**
- Reduce dimensionality (unsupervised) → **PCA**; supervised → **LDA**
- Feature selection inside a model → **Lasso (L1)**
- Shrink weights but keep all → **Ridge (L2)**
- Doesn't need scaling → **Decision Tree, Random Forest, XGBoost, Naive Bayes**
- Needs scaling → **kNN, SVM, K-Means, PCA, NN, regularized linear models**
- Reduces variance → **Bagging / Random Forest**; reduces bias → **Boosting**
- Best default on tabular data → **Gradient Boosting (XGBoost / LightGBM)**
- Interpretable model → **Linear/Logistic regression, Decision Tree**
- Text classification baseline → **Naive Bayes / TF-IDF + Logistic Regression**
- Arbitrary-shaped clusters + outliers → **DBSCAN**
- Imbalanced data metric → **F1 / Recall / PR-AUC**, not accuracy
- Medical screening → **Recall**; spam filter → **Precision**
- Images → **CNN**; sequences → **LSTM / Transformer**
- Vanishing gradient fix → **ReLU, ResNet, LSTM, BatchNorm, good init**
- Multi-class output layer → **Softmax**; binary → **Sigmoid**
- Default optimizer → **Adam**
- Language understanding (classification, NER) → **BERT**; generation → **GPT**
- Add fresh/private knowledge to an LLM → **RAG**; change style/behaviour → **fine-tuning**
- Cheap fine-tuning → **LoRA / PEFT**
- Shortest path, unweighted → **BFS**; weighted → **UCS / Dijkstra / A\***
- Game playing → **Minimax + alpha-beta**
- Learning from rewards → **RL (Q-learning / PPO)**
- Cold-start recommenders → **Content-based**
- Time-series split → **chronological, never shuffle**
- Explain a prediction → **SHAP / LIME**

## D. Top 60 interview questions (answer out loud)
**Basics**
1. AI vs ML vs DL?
2. Supervised vs unsupervised vs RL, with examples?
3. Parameters vs hyperparameters?
4. Explain the end-to-end ML pipeline.
5. Generative vs discriminative models?

**Data & preprocessing**
6. How do you handle missing values / outliers?
7. Normalization vs standardization. Which algorithms need scaling?
8. One-hot vs label encoding? The dummy variable trap?
9. What is data leakage?
10. How do you handle class imbalance? SMOTE?
11. Feature selection vs feature extraction?
12. What is multicollinearity? VIF?
13. What is the curse of dimensionality?

**Regression & classification**
14. Linear regression assumptions?
15. Gradient descent and its variants; effect of the learning rate?
16. Ridge vs Lasso?
17. R² vs adjusted R²? MAE vs RMSE?
18. How does logistic regression work? Why log loss?
19. How does kNN work? Choosing k?
20. Why is Naive Bayes naive?
21. How does a decision tree split? Entropy vs Gini?
22. Prevent decision tree overfitting?
23. Bagging vs boosting? Random Forest vs XGBoost?
24. SVM: margin, support vectors, kernel trick, C, gamma?

**Unsupervised**
25. K-Means steps, choosing k, limitations?
26. K-Means vs hierarchical vs DBSCAN?
27. PCA: steps and purpose?
28. Support, confidence, lift?

**Evaluation**
29. Overfitting vs underfitting and fixes?
30. Bias–variance trade-off?
31. k-fold and stratified CV?
32. Confusion matrix, precision, recall, F1?
33. When recall over precision?
34. ROC-AUC meaning?
35. Why is accuracy misleading on imbalanced data?

**Deep learning**
36. How does a neural network learn?
37. Why non-linear activations? ReLU vs sigmoid?
38. Vanishing/exploding gradients?
39. SGD vs Adam?
40. Dropout and batch normalization?
41. How does a CNN work? Pooling?
42. RNN vs LSTM vs GRU?
43. What is transfer learning?
44. Why can't a perceptron solve XOR?

**NLP / LLM**
45. Tokenization, stemming vs lemmatization?
46. TF-IDF vs embeddings?
47. Explain self-attention and the Transformer.
48. BERT vs GPT?
49. Temperature, top-k, top-p?
50. Hallucination and how to reduce it?
51. RAG and RAG vs fine-tuning?
52. LoRA / PEFT?
53. Zero-shot, few-shot, chain-of-thought?

**Classical AI / RL / Misc**
54. Types of agents; PEAS?
55. BFS vs DFS; A* and admissible heuristics?
56. Minimax and alpha-beta pruning?
57. RL: state, action, reward, policy; explore vs exploit?
58. Q-learning update; on-policy vs off-policy?
59. Content-based vs collaborative filtering; cold start?
60. Data drift vs concept drift; how do you deploy and monitor a model?

## E. Project-style questions (prepare your own answers)
- "Walk me through an ML project you built." (Problem → data → preprocessing → model choice → metric → result → what you'd improve.)
- "Why did you choose this model/metric?"
- "How did you handle overfitting / imbalance / missing data?"
- "How would you scale/deploy it?"
- "What would you do with no labeled data?" (Clustering, weak supervision, pre-trained models, labeling budget / active learning.)
- "Design a spam classifier / recommendation system / fraud detection system." (Data, features, model, metric, deployment, monitoring.)

## F. Last-minute traps checklist
- [ ] Recall = TP/(TP+FN); Precision = TP/(TP+FP)
- [ ] Type I = FP, Type II = FN
- [ ] Lasso = L1 = sparsity; Ridge = L2
- [ ] Scale after splitting; fit on train only
- [ ] Trees don't need scaling; kNN/SVM/K-Means/PCA do
- [ ] Bagging ↓ variance; Boosting ↓ bias
- [ ] Dropout off at inference
- [ ] Softmax multi-class, sigmoid binary
- [ ] BERT encoder-only; GPT decoder-only
- [ ] A* needs an admissible heuristic; BFS = queue, DFS = stack
- [ ] Q-learning = off-policy
- [ ] Correlation ≠ causation; independent ≠ mutually exclusive
- [ ] Median for outliers; MAE robust; R² never drops with extra features
- [ ] Time series: no shuffling
