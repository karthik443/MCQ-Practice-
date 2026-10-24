# 60 MCQs — AI/ML Fundamentals (Topics 07–12)

Coverage: 07 Model Evaluation (Q1–10) · 08 Neural Networks & DL (Q11–22) · 09 NLP/Transformers/LLMs (Q23–33) · 10 Classical AI (Q34–42) · 11 RL & Advanced (Q43–51) · 12 Python & ML Libraries (Q52–60)

Difficulty: medium. Many questions need a short calculation or a code trace. Click **Show answer** under each question to reveal the answer and reasoning. Every answer is **(b)** or **(c)**.

---

## Section A — Model Evaluation (07)

**Q1.** A classifier produces TP = 45, FP = 15, FN = 5, TN = 135. What is its F1-score?

- (a) 0.825 (arithmetic mean of precision and recall)
- (b) 0.750
- (c) 0.818
- (d) 0.900

<details>
<summary>Show answer</summary>

**Answer: (c) 0.818**

Precision = 45/60 = 0.75, recall = 45/50 = 0.90. F1 = 2TP/(2TP+FP+FN) = 90/110 = 0.818. F1 is the *harmonic* mean, so it is below the arithmetic mean (0.825).

</details>

**Q2.** Class A: TP = 90, FP = 10, FN = 10. Class B: TP = 5, FP = 5, FN = 15. What is the **macro-averaged** precision?

- (a) 0.864
- (b) 0.70
- (c) 0.80
- (d) 0.95

<details>
<summary>Show answer</summary>

**Answer: (b) 0.70**

Precision(A) = 90/100 = 0.9, Precision(B) = 5/10 = 0.5, macro = (0.9 + 0.5)/2 = 0.70. Micro precision would pool counts: 95/110 = 0.864, which is dominated by the large class.

</details>

**Q3.** A binary classifier gets an AUC of 0.3 on a held-out set. The best interpretation is:

- (a) It is a weak but useful model, since 0.3 > 0
- (b) It ranks worse than random, so inverting its predictions would give AUC ≈ 0.7
- (c) It is well calibrated but has low accuracy
- (d) The data must be imbalanced; AUC is undefined below 0.5

<details>
<summary>Show answer</summary>

**Answer: (b) It ranks worse than random, so inverting its predictions would give AUC ≈ 0.7**

AUC < 0.5 means the ranking is systematically reversed. Flipping the scores gives 1 − 0.3 = 0.7. AUC is defined on [0, 1] regardless of class balance.

</details>

**Q4.** `GridSearchCV` is run with 3 values of `C`, 4 values of `gamma` and `cv=5` (default `refit=True`). How many times is a model fitted in total?

- (a) 60
- (b) 12
- (c) 61
- (d) 15

<details>
<summary>Show answer</summary>

**Answer: (c) 61**

3 × 4 = 12 combinations × 5 folds = 60 fits, plus 1 final refit of the best parameters on the full training data = 61.

</details>

**Q5.** A model has training error 24% and validation error 26%. Which action is MOST likely to help?

- (a) Collect 10× more training data
- (b) Increase model capacity (more layers or features) or reduce regularization
- (c) Add dropout and stronger L2 regularization
- (d) Apply early stopping sooner

<details>
<summary>Show answer</summary>

**Answer: (b) Increase model capacity (more layers or features) or reduce regularization**

Both errors are high and close together → high bias (underfitting). More data, dropout, L2 and early stopping all attack variance and would not fix it.

</details>

**Q6.** A dataset has 100 samples and 20,000 features. You pick the 50 features most correlated with the label using the *entire* dataset, then run 10-fold CV on those 50 features. The reported CV score will be:

- (a) Pessimistically biased, because only 50 features are kept
- (b) Unbiased, since CV was used
- (c) Optimistically biased, because feature selection saw the validation folds
- (d) Unbiased but high variance

<details>
<summary>Show answer</summary>

**Answer: (c) Optimistically biased, because feature selection saw the validation folds**

Selecting features on all the data leaks label information into every validation fold. Feature selection must happen inside each training fold, for example in a Pipeline.

</details>

**Q7.** Scores and true labels: (0.9, +), (0.8, −), (0.6, +), (0.4, +), (0.3, −). Using the threshold 0.35, precision and recall are:

- (a) Precision = 1.0, Recall = 0.75
- (b) Precision = 0.60, Recall = 1.0
- (c) Precision = 0.75, Recall = 1.0
- (d) Precision = 0.75, Recall = 0.67

<details>
<summary>Show answer</summary>

**Answer: (c) Precision = 0.75, Recall = 1.0**

Scores ≥ 0.35 are 0.9, 0.8, 0.6, 0.4 → labels +, −, +, +. So TP = 3, FP = 1, FN = 0. Precision = 3/4, recall = 3/3.

</details>

**Q8.** For a single sample with true label y = 1, the model predicts P(y=1) = 0.2. The binary cross-entropy (natural log) is approximately:

- (a) 0.22
- (b) 1.61
- (c) 0.80
- (d) 0.20

<details>
<summary>Show answer</summary>

**Answer: (b) 1.61**

Loss = −ln(0.2) = 1.609. Confident wrong predictions are penalised heavily, which is why log loss is sensitive to calibration.

</details>

**Q9.** A dataset has 1000 samples with 10% positives. Using 5-fold *stratified* CV, how many positive samples are in each validation fold?

- (a) 10
- (b) 50
- (c) 20
- (d) Varies between 15 and 25

<details>
<summary>Show answer</summary>

**Answer: (c) 20**

100 positives / 5 folds = 20 per fold, with 200 samples per fold. Stratification preserves the 10% ratio in every fold.

</details>

**Q10.** Only 0.1% of transactions are fraud. Why is PR-AUC usually preferred over ROC-AUC here?

- (a) PR-AUC is threshold-dependent and ROC-AUC is not
- (b) ROC-AUC can look high because the huge number of true negatives keeps FPR tiny, while PR-AUC focuses on the rare positive class
- (c) ROC-AUC cannot be computed for imbalanced data
- (d) PR-AUC uses TN, which makes it more informative

<details>
<summary>Show answer</summary>

**Answer: (b) ROC-AUC can look high because the huge number of true negatives keeps FPR tiny, while PR-AUC focuses on the rare positive class**

FPR = FP/(FP+TN) stays small when TN is huge, hiding many false alarms. Precision (TP/(TP+FP)) does not use TN, so it exposes them. Both curves sweep all thresholds.

</details>

---

## Section B — Neural Networks & Deep Learning (08)

**Q11.** A CNN has `Conv2D(3×3, 3→32)` followed by `Conv2D(3×3, 32→64)`, each with bias. How many parameters does the **second** layer have?

- (a) 18,432
- (b) 18,496
- (c) 9,248
- (d) 896

<details>
<summary>Show answer</summary>

**Answer: (b) 18,496**

(3 × 3 × 32 + 1) × 64 = 289 × 64 = 18,496. (18,432 forgets the biases; 9,248 is a 32→32 layer; 896 is the *first* layer: (3×3×3 + 1) × 32.)

</details>

**Q12.** Input is 224×224. A conv layer uses a 7×7 kernel, stride 2, padding 3. The output spatial size is:

- (a) 111 × 111
- (b) 113 × 113
- (c) 112 × 112
- (d) 224 × 224

<details>
<summary>Show answer</summary>

**Answer: (c) 112 × 112**

(224 − 7 + 2·3)/2 + 1 = 223/2 + 1 = 111.5 → floor → 111 + 1 = 112.

</details>

**Q13.** Compared with a single 7×7 convolution (C channels in and out), three stacked 3×3 convolutions:

- (a) Have a 9×9 receptive field with the same parameters
- (b) Have a 3×3 receptive field but more parameters
- (c) Have the same 7×7 receptive field, fewer parameters (27C² vs 49C²) and more non-linearities
- (d) Have the same receptive field but more parameters (81C²)

<details>
<summary>Show answer</summary>

**Answer: (c) Have the same 7×7 receptive field, fewer parameters (27C² vs 49C²) and more non-linearities**

Each extra 3×3 layer adds 2 to the receptive field: 3 → 5 → 7. Parameters 3·9C² = 27C² < 49C², and a ReLU between layers adds non-linearity. This is the VGG idea.

</details>

**Q14.** Logits are [2, 1, 0]. The softmax probability of the first class is approximately:

- (a) 0.500
- (b) 0.665
- (c) 0.333
- (d) 0.790

<details>
<summary>Show answer</summary>

**Answer: (b) 0.665**

e² = 7.389, e¹ = 2.718, e⁰ = 1. Sum = 11.107. 7.389/11.107 = 0.665.

</details>

**Q15.** With *inverted dropout* using drop probability 0.4, surviving activations during training are multiplied by:

- (a) 0.6, so activations are scaled down at inference
- (b) 1/0.6 ≈ 1.67, so no rescaling is needed at inference
- (c) 1/0.4 = 2.5
- (d) 1.0; weights are multiplied by 0.6 at test time

<details>
<summary>Show answer</summary>

**Answer: (b) 1/0.6 ≈ 1.67, so no rescaling is needed at inference**

Inverted dropout divides by the keep-probability (1 − 0.4 = 0.6) at training time, so the expected activation is unchanged and inference uses the plain network.

</details>

**Q16.** The sigmoid derivative is at most 0.25. For a 10-layer sigmoid network, the upper bound on the gradient factor contributed by the activations alone is about:

- (a) 10⁻² (0.25 × 10)
- (b) 2.5 (0.25 × 10)
- (c) 10⁻⁶ (0.25¹⁰ ≈ 9.5 × 10⁻⁷)
- (d) 10⁻¹⁰

<details>
<summary>Show answer</summary>

**Answer: (c) 10⁻⁶ (0.25¹⁰ ≈ 9.5 × 10⁻⁷)**

Backprop multiplies one derivative per layer: 0.25¹⁰ ≈ 9.5×10⁻⁷. This exponential shrinkage is the vanishing gradient problem.

</details>

**Q17.** Which statement about Batch Normalization is correct?

- (a) At inference it recomputes the mean and variance of each test batch
- (b) It has no learnable parameters
- (c) At inference it uses running estimates of mean and variance accumulated during training
- (d) It works identically for batch size 1 and batch size 256

<details>
<summary>Show answer</summary>

**Answer: (c) At inference it uses running estimates of mean and variance accumulated during training**

BN has learnable γ and β. Test-time behaviour must be deterministic and independent of batch composition, so running averages are used. Small batches make batch statistics noisy; that is why LayerNorm is used in Transformers.

</details>

**Q18.** In Adam with β₁ = 0.9, the first gradient is g₁ = 4 and m₀ = 0. The bias-corrected first-moment estimate m̂₁ is:

- (a) 0.4
- (b) 4.0
- (c) 3.6
- (d) 0.04

<details>
<summary>Show answer</summary>

**Answer: (b) 4.0**

m₁ = 0.9·0 + 0.1·4 = 0.4. Bias correction divides by (1 − β₁¹) = 0.1 → 4.0. Without it, early estimates are biased toward zero.

</details>

**Q19.** An LSTM layer has 10 input features and 20 hidden units (one bias vector per gate). Its number of parameters is:

- (a) 2,400
- (b) 620
- (c) 2,480
- (d) 1,860

<details>
<summary>Show answer</summary>

**Answer: (c) 2,480**

4 gates × [20 × (10 + 20) + 20] = 4 × 620 = 2,480. 2,400 drops the biases; 620 is a single gate; 1,860 is 3 gates (a GRU-sized count).

</details>

**Q20.** A neuron computes ŷ = σ(wx + b) with x = 2, w = 0.5, b = 0, target t = 1 and loss L = ½(ŷ − t)². What is ∂L/∂w approximately?

- (a) −0.053
- (b) −0.106
- (c) −0.269
- (d) +0.106

<details>
<summary>Show answer</summary>

**Answer: (b) −0.106**

z = 1 → ŷ = σ(1) = 0.731. ∂L/∂w = (ŷ − t)·ŷ(1 − ŷ)·x = (−0.269)(0.1966)(2) = −0.106. Dropping x gives −0.053.

</details>

**Q21.** A model must assign any subset of 5 independent tags (e.g. 'sports', 'politics') to an article. The best output layer and loss are:

- (a) 5 softmax units with categorical cross-entropy
- (b) 5 sigmoid units with binary cross-entropy
- (c) 1 softmax unit with MSE
- (d) 5 linear units with hinge loss

<details>
<summary>Show answer</summary>

**Answer: (b) 5 sigmoid units with binary cross-entropy**

Multi-label tasks need independent probabilities per class. Softmax forces the probabilities to sum to 1, which suits single-label multi-class problems.

</details>

**Q22.** Input to a block is 32×32×16. It goes through `MaxPool(2×2, stride 2)`, then `Flatten`, then `Dense(10)`. The Dense layer has how many parameters?

- (a) 163,850
- (b) 40,960
- (c) 40,970
- (d) 10

<details>
<summary>Show answer</summary>

**Answer: (c) 40,970**

Pool → 16×16×16 = 4,096 features. Dense: 4,096 × 10 + 10 = 40,970. The pooling layer contributes 0 parameters; 163,850 would come from skipping the pooling (16,384 × 10 + 10).

</details>

---

## Section C — NLP, Transformers & LLMs (09)

**Q23.** A document has 100 words, and the term 'model' occurs 5 times in it. The corpus has 1000 documents, 10 of which contain 'model'. Using TF = count/length and IDF = log₁₀(N/df), the TF-IDF is:

- (a) 0.05
- (b) 0.50
- (c) 0.10
- (d) 2.00

<details>
<summary>Show answer</summary>

**Answer: (c) 0.10**

TF = 5/100 = 0.05, IDF = log₁₀(1000/10) = log₁₀(100) = 2. TF-IDF = 0.05 × 2 = 0.10.

</details>

**Q24.** Why is the dot product QKᵀ divided by √dₖ in scaled dot-product attention?

- (a) To make the attention matrix symmetric
- (b) To keep the variance of the scores near 1, so large dₖ does not push softmax into saturation with vanishing gradients
- (c) To reduce the O(n²) memory cost
- (d) To normalise each row so that it sums to 1

<details>
<summary>Show answer</summary>

**Answer: (b) To keep the variance of the scores near 1, so large dₖ does not push softmax into saturation with vanishing gradients**

If q and k entries have unit variance, q·k has variance dₖ. Dividing by √dₖ restores unit variance. Row-sum-to-1 is done by softmax; scaling does not change complexity.

</details>

**Q25.** A Transformer layer has d_model = 512 and 8 heads (dₖ = 64). Ignoring biases, the parameters in the Q, K, V and output projections of its self-attention are:

- (a) 786,432
- (b) 262,144
- (c) 1,048,576
- (d) 2,097,152

<details>
<summary>Show answer</summary>

**Answer: (c) 1,048,576**

Four projection matrices of 512 × 512 = 262,144 each → 1,048,576. (Total across heads is the same as one big d_model × d_model matrix per projection; 786,432 forgets W_O.)

</details>

**Q26.** In a decoder's self-attention, how is the causal (look-ahead) mask implemented?

- (a) Future tokens' embeddings are zeroed after softmax
- (b) Future positions' scores are set to −∞ before softmax, giving them zero weight
- (c) The model is run once per token with a shorter input
- (d) Future positions get dropout with p = 1 after the output projection

<details>
<summary>Show answer</summary>

**Answer: (b) Future positions' scores are set to −∞ before softmax, giving them zero weight**

Adding −∞ (a large negative number) to the upper-triangular scores makes softmax assign them exactly zero probability, while keeping training parallel.

</details>

**Q27.** Logits for two tokens are [2, 1]. Sampling uses temperature T = 0.5. The probability of the top token is approximately:

- (a) 0.73
- (b) 0.62
- (c) 0.88
- (d) 0.50

<details>
<summary>Show answer</summary>

**Answer: (c) 0.88**

Logits/T = [4, 2], so p = e⁴/(e⁴ + e²) = 1/(1 + e⁻²) = 0.881. At T = 1 it would be 0.73. Lower temperature sharpens the distribution.

</details>

**Q28.** Sorted token probabilities are 0.50, 0.30, 0.10, 0.06, 0.04. With top-p (nucleus) sampling at p = 0.85, how many tokens can be sampled from?

- (a) 2
- (b) 3
- (c) 4
- (d) 5

<details>
<summary>Show answer</summary>

**Answer: (b) 3**

Cumulative: 0.50, 0.80 (< 0.85), 0.90 (≥ 0.85). The smallest set reaching p includes 3 tokens.

</details>

**Q29.** Two embedding vectors are a = (1, 2, 2) and b = (2, 0, 1). Their cosine similarity is approximately:

- (a) 0.89
- (b) 0.60
- (c) 0.44
- (d) 4.00

<details>
<summary>Show answer</summary>

**Answer: (b) 0.60**

a·b = 2 + 0 + 2 = 4. |a| = 3, |b| = √5 = 2.236. cos = 4/(3 × 2.236) = 0.596. 4.00 is the unnormalised dot product.

</details>

**Q30.** Which pairing of model, architecture and pre-training objective is correct?

- (a) GPT: encoder-only with masked language modelling
- (b) T5: decoder-only with next-sentence prediction
- (c) BERT: encoder-only with masked language modelling
- (d) BERT: decoder-only with causal next-token prediction

<details>
<summary>Show answer</summary>

**Answer: (c) BERT: encoder-only with masked language modelling**

BERT is a bidirectional encoder trained with MLM. GPT is a causal decoder (next-token). T5 is an encoder–decoder with text-to-text span corruption.

</details>

**Q31.** LoRA with rank r = 8 is applied to a single 4096 × 4096 weight matrix. How many trainable parameters does the adapter add for that matrix?

- (a) 16,777,216
- (b) 32,768
- (c) 65,536
- (d) 131,072

<details>
<summary>Show answer</summary>

**Answer: (c) 65,536**

ΔW = B·A with A: 8 × 4096 and B: 4096 × 8 → 2 × 4096 × 8 = 65,536 (≈ 0.4% of the 16.8M original weights).

</details>

**Q32.** A language model has an average cross-entropy of 3 bits per token on a test set. Its perplexity is:

- (a) 3
- (b) 8
- (c) 9
- (d) log₂3

<details>
<summary>Show answer</summary>

**Answer: (b) 8**

Perplexity = 2^(cross-entropy in bits) = 2³ = 8. It is the effective number of equally likely choices per token; lower is better.

</details>

**Q33.** Skip-gram Word2Vec with window size 2 is trained on 'I love deep learning models'. For the centre word 'deep', how many (centre, context) training pairs are generated?

- (a) 2
- (b) 3
- (c) 4
- (d) 5

<details>
<summary>Show answer</summary>

**Answer: (c) 4**

Context words within distance 2: 'I', 'love', 'learning', 'models' → 4 pairs. (CBOW would instead combine these 4 words to predict 'deep'.)

</details>

---

## Section D — Classical AI: Search, Games & Agents (10)

**Q34.** Edges: S–A = 2, S–B = 5, A–C = 2, C–G = 8, B–G = 4. Heuristic h: S = 6, A = 5, B = 3, C = 6, G = 0. In which order does A* expand nodes (ties not required)?

- (a) S, B, G
- (b) S, A, B, G
- (c) S, A, C, G
- (d) S, B, A, G

<details>
<summary>Show answer</summary>

**Answer: (b) S, A, B, G**

f(A) = 2 + 5 = 7, f(B) = 5 + 3 = 8 → expand A. C: f = 4 + 6 = 10. Frontier {B: 8, C: 10} → expand B, giving G with f = 9. G (9) < C (10) → expand G. Cost 9 via S–B–G. Greedy best-first would have gone S, B, G.

</details>

**Q35.** MAX root with three MIN children; the leaves left to right are [3, 12, 8], [2, 4, 6], [14, 5, 2]. With alpha-beta pruning (left to right), the root value and the number of leaves pruned are:

- (a) Value 3, no pruning
- (b) Value 2, 2 leaves pruned
- (c) Value 3, 2 leaves pruned
- (d) Value 3, 4 leaves pruned

<details>
<summary>Show answer</summary>

**Answer: (c) Value 3, 2 leaves pruned**

MIN₁ = 3 → α = 3. In MIN₂ the first leaf 2 ≤ α, so 4 and 6 are pruned (2 leaves). MIN₃ gives 14, 5, 2 → 2 (nothing left to prune). Root = max(3, 2, 2) = 3.

</details>

**Q36.** A goal is at depth d = 4 and the branching factor is b = 3. How many nodes does Iterative Deepening DFS generate in total (limits 0 to 4)?

- (a) 121
- (b) 179
- (c) 81
- (d) 243

<details>
<summary>Show answer</summary>

**Answer: (b) 179**

Limit-L search generates (3^(L+1) − 1)/2 nodes: 1 + 4 + 13 + 40 + 121 = 179. A single BFS to depth 4 generates 121, so the overhead is small.

</details>

**Q37.** 8-puzzle start state (rows) is `2 8 3 / 1 6 4 / 7 _ 5`, goal is `1 2 3 / 8 _ 4 / 7 6 5`. The Manhattan-distance heuristic h(start) is:

- (a) 4
- (b) 6
- (c) 5
- (d) 7

<details>
<summary>Show answer</summary>

**Answer: (c) 5**

Tile 2: 1, tile 8: 2, tile 1: 1, tile 6: 1; tiles 3, 4, 7, 5 are already in place → 5. The blank is not counted. Misplaced tiles would give 4; Manhattan dominates it.

</details>

**Q38.** h(A) = 7, h(B) = 4, the edge cost A→B is 2, and the only path from B to the goal costs 5. What can be concluded about h?

- (a) h is both admissible and consistent
- (b) h is inadmissible at A
- (c) h is admissible at A but violates consistency on the edge A→B
- (d) h is inconsistent but also inadmissible at B

<details>
<summary>Show answer</summary>

**Answer: (c) h is admissible at A but violates consistency on the edge A→B**

True cost h*(A) = 2 + 5 = 7, so h(A) = 7 ≤ 7 (admissible); h(B) = 4 ≤ 5 too. Consistency needs h(A) ≤ c(A,B) + h(B) = 6, but 7 > 6, so it is inconsistent.

</details>

**Q39.** Variables X and Y both have domain {1, 2, 3} with constraint X < Y. After enforcing arc consistency (AC-3), the domains are:

- (a) X = {1}, Y = {2, 3}
- (b) X = {1, 2}, Y = {2, 3}
- (c) X = {1, 2, 3}, Y = {2, 3}
- (d) X = {1, 2}, Y = {1, 2, 3}

<details>
<summary>Show answer</summary>

**Answer: (b) X = {1, 2}, Y = {2, 3}**

X = 3 has no Y > 3 and Y = 1 has no X < 1; removing them gives X = {1, 2} and Y = {2, 3}. AC-3 prunes domains without choosing values.

</details>

**Q40.** Which description of the environment 'playing poker against other agents' is correct?

- (a) Fully observable, deterministic, sequential, multi-agent
- (b) Partially observable, stochastic, sequential, multi-agent
- (c) Partially observable, deterministic, episodic, single-agent
- (d) Fully observable, stochastic, episodic, multi-agent

<details>
<summary>Show answer</summary>

**Answer: (b) Partially observable, stochastic, sequential, multi-agent**

Opponents' cards are hidden (partially observable), card deals are random (stochastic), earlier bets affect later play (sequential), and there are several players (multi-agent). Chess is the fully observable, deterministic counterpart.

</details>

**Q41.** In simulated annealing at temperature T = 1, a candidate move worsens the objective by ΔE = 2. The probability that it is accepted is approximately:

- (a) 0.368
- (b) 0.865
- (c) 0.135
- (d) 0

<details>
<summary>Show answer</summary>

**Answer: (c) 0.135**

Acceptance probability = e^(−ΔE/T) = e⁻² ≈ 0.135. As T decreases the probability shrinks, so the search behaves more like hill climbing. This is how it escapes local optima.

</details>

**Q42.** Which statement about alpha-beta pruning is correct?

- (a) It returns an approximate value that is at least as good as minimax
- (b) It returns the same minimax value as full minimax; with ideal move ordering it examines O(b^(m/2)) nodes, roughly doubling the reachable depth
- (c) Its worst-case complexity is O(b^(m/2)) regardless of move ordering
- (d) It only works when the heuristic evaluation function is admissible

<details>
<summary>Show answer</summary>

**Answer: (b) It returns the same minimax value as full minimax; with ideal move ordering it examines O(b^(m/2)) nodes, roughly doubling the reachable depth**

Pruning never changes the result. Savings depend on ordering: best case O(b^(m/2)), worst case O(bᵐ) (no pruning). Admissibility is an A* concept.

</details>

---

## Section E — Reinforcement Learning & Advanced Topics (11)

**Q43.** Q(s,a) = 2, α = 0.1, γ = 0.9, r = 1. In the next state the Q-values of the actions are [3, 5, 4], and the action actually taken next is the one with Q = 4. The new Q(s,a) under **Q-learning** is:

- (a) 2.26
- (b) 2.55
- (c) 2.35
- (d) 5.50

<details>
<summary>Show answer</summary>

**Answer: (c) 2.35**

Target = r + γ·max Q(s′) = 1 + 0.9×5 = 5.5; new Q = 2 + 0.1×(5.5 − 2) = 2.35. SARSA uses the action actually taken (4): target 4.6 → 2.26. That difference is what makes Q-learning off-policy.

</details>

**Q44.** Rewards over an episode are 1, 0, 2, 3 starting at time 0, with γ = 0.5. The return G₀ is:

- (a) 6.0
- (b) 1.875
- (c) 3.75
- (d) 1.5

<details>
<summary>Show answer</summary>

**Answer: (b) 1.875**

G₀ = 1 + 0.5·0 + 0.25·2 + 0.125·3 = 1 + 0 + 0.5 + 0.375 = 1.875. 6.0 is the undiscounted sum.

</details>

**Q45.** In state s, action a₁ gives reward 2 and moves to a state with V = 10. Action a₂ gives reward 5 and moves to a state with V = 10 or V = 12 with equal probability. With γ = 0.9, one Bellman optimality backup gives V(s) =

- (a) 11.0
- (b) 13.9
- (c) 14.9
- (d) 16.2

<details>
<summary>Show answer</summary>

**Answer: (c) 14.9**

Q(a₁) = 2 + 0.9×10 = 11. Q(a₂) = 5 + 0.9×(0.5×10 + 0.5×12) = 5 + 0.9×11 = 14.9. V(s) = max = 14.9.

</details>

**Q46.** In DQN, the roles of experience replay and the target network are, respectively:

- (a) Increase exploration; reduce the reward scale
- (b) Break correlation between consecutive samples; keep the bootstrap target stable while Q is being updated
- (c) Reduce the action space; implement the policy gradient
- (d) Store the policy; compute the advantage

<details>
<summary>Show answer</summary>

**Answer: (b) Break correlation between consecutive samples; keep the bootstrap target stable while Q is being updated**

Replay samples random past transitions (decorrelates data, reuses experience). The target network is a delayed copy of Q used to compute targets, which prevents a moving-target feedback loop.

</details>

**Q47.** A recommender ranks items with relevance grades [2, 3, 0] (positions 1–3). Using DCG = Σ rel/log₂(i+1), the NDCG@3 is approximately:

- (a) 1.00
- (b) 0.91
- (c) 0.78
- (d) 0.85

<details>
<summary>Show answer</summary>

**Answer: (b) 0.91**

DCG = 2/1 + 3/1.585 + 0 = 3.893. The ideal order [3, 2, 0] gives IDCG = 3 + 2/1.585 = 4.262. NDCG = 3.893/4.262 = 0.913.

</details>

**Q48.** A time series is 10, 13, 15, 20, 26. What is the series after applying first-order differencing **twice**?

- (a) 3, 2, 5, 6
- (b) −1, 3
- (c) −1, 3, 1
- (d) 3, 5, 6

<details>
<summary>Show answer</summary>

**Answer: (c) −1, 3, 1**

First difference: 3, 2, 5, 6. Second difference: −1, 3, 1. Each differencing shortens the series by one; ARIMA's d is the number of times this is applied.

</details>

**Q49.** Box A spans (0,0)–(4,4) and box B spans (2,2)–(6,6). The IoU of the two boxes is:

- (a) 0.25
- (b) 0.5
- (c) 1/7 ≈ 0.143
- (d) 1/3 ≈ 0.333

<details>
<summary>Show answer</summary>

**Answer: (c) 1/7 ≈ 0.143**

Intersection = (2,2)–(4,4) = 4. Each box has area 16, so union = 16 + 16 − 4 = 28. IoU = 4/28 = 0.143. 0.25 is the intersection over one box.

</details>

**Q50.** (i) A bank model sees the customers' age distribution shift younger, but the relationship between features and default is unchanged. (ii) Fraudsters change tactics, so the same feature patterns now correspond to different labels. These are respectively:

- (a) (i) concept drift; (ii) data drift
- (b) (i) data (covariate) drift; (ii) concept drift
- (c) (i) data drift; (ii) data drift
- (d) (i) concept drift; (ii) concept drift

<details>
<summary>Show answer</summary>

**Answer: (b) (i) data (covariate) drift; (ii) concept drift**

Data drift = P(X) changes. Concept drift = P(y|X) changes. Concept drift always hurts accuracy, while data drift may or may not.

</details>

**Q51.** Which property holds for SHAP values?

- (a) They are always positive and sum to 1
- (b) They give a global linear model fitted on the whole dataset
- (c) The base value plus the sum of a prediction's SHAP values equals the model output for that instance (additivity)
- (d) They need the model to be differentiable

<details>
<summary>Show answer</summary>

**Answer: (c) The base value plus the sum of a prediction's SHAP values equals the model output for that instance (additivity)**

SHAP, based on Shapley values, attributes the difference between the prediction and the average prediction among the features. LIME fits a local linear surrogate. SHAP values can be negative and are model-agnostic (for example KernelSHAP).

</details>

---

## Section F — Python & ML Libraries (12)

**Q52.** ```python
a = np.arange(6).reshape(2, 3)
b = np.array([10, 20, 30])
print((a + b).sum(axis=0))
```
What is the output?

- (a) [ 63 135]
- (b) [23 45 67]
- (c) [ 69 ]
- (d) [13 24 35]

<details>
<summary>Show answer</summary>

**Answer: (b) [23 45 67]**

b broadcasts over each row: [[10,21,32],[13,24,35]]. Summing down the rows (axis=0) → [23, 45, 67].

</details>

**Q53.** ```python
a = np.arange(5)
b = a[1:4]
c = a[[1, 2]]
b[0] = 99
c[0] = -1
print(a)
```
What is printed?

- (a) [ 0 -1  2  3  4]
- (b) [ 0  1  2  3  4]
- (c) [ 0 99  2  3  4]
- (d) [ 0 -1 99  3  4]

<details>
<summary>Show answer</summary>

**Answer: (c) [ 0 99  2  3  4]**

Slicing returns a *view*, so b[0] = 99 changes a. Fancy indexing returns a *copy*, so c[0] = -1 does not affect a.

</details>

**Q54.** ```python
df = pd.DataFrame({'A': [1, 2, 3, 4]}, index=[10, 20, 30, 40])
x = df.loc[20:40, 'A'].sum() - df.iloc[1:3]['A'].sum()
```
The value of `x` is:

- (a) 2
- (b) 4
- (c) 9
- (d) 5

<details>
<summary>Show answer</summary>

**Answer: (b) 4**

`loc` is label-based and end-inclusive → rows 20, 30, 40 → 2 + 3 + 4 = 9. `iloc[1:3]` is positional and end-exclusive → rows at positions 1 and 2 → 2 + 3 = 5. 9 − 5 = 4.

</details>

**Q55.** `df1` has ids [1, 2, 3] and `df2` has ids [1, 1, 2]. How many rows are in `df1.merge(df2, on='id', how='left')`?

- (a) 3
- (b) 6
- (c) 4
- (d) 5

<details>
<summary>Show answer</summary>

**Answer: (c) 4**

id 1 matches two rows in df2 (2 rows), id 2 matches one (1 row), id 3 has no match but is kept with NaN (1 row) → 4. Duplicate keys multiply rows in a join.

</details>

**Q56.** ```python
def f(x, l=[]):
    l.append(x)
    return l
print(f(1), f(2), f(3, []))
```
What is printed?

- (a) [1] [2] [3]
- (b) [1] [1, 2] [3]
- (c) [1, 2] [1, 2] [3]
- (d) [1, 2, 3] [1, 2, 3] [3]

<details>
<summary>Show answer</summary>

**Answer: (c) [1, 2] [1, 2] [3]**

The default list is created once and shared. f(1) and f(2) return that same object, which has [1, 2] by the time print runs. f(3, []) uses a fresh list.

</details>

**Q57.** `StandardScaler` is fitted on training values [2, 4, 6] and then applied to the test value 8. The transformed value is approximately:

- (a) 2.00
- (b) 2.45
- (c) 4.00
- (d) 1.22

<details>
<summary>Show answer</summary>

**Answer: (b) 2.45**

mean = 4. sklearn uses the *population* std: √(8/3) = 1.633. (8 − 4)/1.633 = 2.449. Using the sample std (2) would give 2.0, which is the common trap.

</details>

**Q58.** ```python
x = torch.tensor(3.0, requires_grad=True)
y = x ** 2
y.backward()
y = x ** 2
y.backward()
print(x.grad)
```
The output is:

- (a) tensor(6.)
- (b) tensor(9.)
- (c) tensor(12.)
- (d) tensor(18.)

<details>
<summary>Show answer</summary>

**Answer: (c) tensor(12.)**

dy/dx = 2x = 6 each time. PyTorch *accumulates* gradients into `.grad`, so after two backward calls it is 12. This is why `optimizer.zero_grad()` is needed.

</details>

**Q59.** ```python
model = Sequential([
    Dense(64, input_shape=(10,)),
    BatchNormalization(),
    Dense(1)])
```
How many **trainable** parameters does this model have?

- (a) 1,025
- (b) 897
- (c) 833
- (d) 769

<details>
<summary>Show answer</summary>

**Answer: (b) 897**

Dense(64): 10×64 + 64 = 704. BatchNorm(64): γ and β are trainable = 128 (moving mean and variance, 128 more, are non-trainable). Dense(1): 64 + 1 = 65. Trainable = 704 + 128 + 65 = 897; total = 1,025.

</details>

**Q60.** `train_test_split(X, y, test_size=0.25)` is called with 1001 samples. The sizes of the train and test sets are:

- (a) 751 and 250
- (b) 750 and 251
- (c) 750 and 250
- (d) 751 and 251

<details>
<summary>Show answer</summary>

**Answer: (b) 750 and 251**

sklearn uses n_test = ceil(0.25 × 1001) = ceil(250.25) = 251 and n_train = floor(0.75 × 1001) = 750, so the two add up to 1001.

</details>
