# 01 — AI / ML Basics

## 1. AI vs ML vs DL vs Data Science ⭐
| Term | Meaning | Relationship |
|------|---------|--------------|
| **Artificial Intelligence (AI)** | Machines doing tasks that normally need human intelligence (reasoning, perception, language) | Broadest field |
| **Machine Learning (ML)** | Systems that **learn patterns from data** instead of being explicitly programmed | Subset of AI |
| **Deep Learning (DL)** | ML using **multi-layer neural networks** | Subset of ML |
| **Generative AI** | Models that generate new content (text, image, code), usually DL-based (LLMs, diffusion) | Subset of DL |
| **Data Science** | Extracting insights from data (stats + ML + domain + visualization) | Overlaps with all |

**AI ⊃ ML ⊃ DL ⊃ GenAI**

**Classic definition (Tom Mitchell):** a program learns from experience **E** on task **T** with performance measure **P**, if its performance on T, as measured by P, improves with E.

## 2. Types of Machine Learning ⭐
| Type | Data | Goal | Examples |
|------|------|------|----------|
| **Supervised** | **Labeled** (X, y) | Learn mapping X → y | Spam detection, house price, disease diagnosis |
| **Unsupervised** | **Unlabeled** (X only) | Find structure | Customer segmentation, anomaly detection, PCA |
| **Semi-supervised** | Few labels + many unlabeled | Use both | Web page classification, medical images |
| **Self-supervised** | Labels are created from the data itself | Pre-train representations | BERT (masked words), GPT (next token) |
| **Reinforcement (RL)** | Rewards from environment | Learn a policy that maximizes cumulative reward | Game AI, robotics, RLHF |

### Supervised sub-types
- **Regression:** predict a **continuous** value (price, temperature).
- **Classification:** predict a **discrete** class (spam / not spam). Binary, multi-class, multi-label.

### Unsupervised sub-types
- **Clustering** (K-Means), **dimensionality reduction** (PCA), **association rules** (Apriori), **anomaly detection**.

## 3. ML Workflow (end-to-end) ⭐
1. **Problem definition** (what to predict, what metric matters)
2. **Data collection**
3. **Data cleaning & preprocessing** (missing values, outliers, encoding, scaling)
4. **EDA** (Exploratory Data Analysis)
5. **Feature engineering / selection**
6. **Train / validation / test split**
7. **Model selection & training**
8. **Hyperparameter tuning** (Grid / Random search, cross-validation)
9. **Evaluation** on the **test set** (touched only once)
10. **Deployment & monitoring** (watch for **data drift**)

## 4. Key Terminology
| Term | Meaning |
|------|---------|
| **Feature** | Input variable (column) |
| **Label / Target** | Output to predict |
| **Sample / Instance** | One row |
| **Parameters** | Learned **by the model** during training (weights, biases) |
| **Hyperparameters** | Set **by you before training** (learning rate, k in kNN, tree depth, epochs) |
| **Training set** | Used to fit parameters |
| **Validation set** | Used to tune hyperparameters / choose models |
| **Test set** | Final unbiased performance estimate |
| **Epoch** | One full pass over the training data |
| **Batch size** | Samples per gradient update |
| **Iteration** | One gradient update (= one batch) |
| **Loss function** | Error on **one sample / batch** to be minimized |
| **Cost function** | Average loss over the whole training set |
| **Inductive bias** | Assumptions a model uses to generalize |
| **Generalization** | Performance on unseen data |

**Iterations per epoch = N / batch_size.** Example: 1000 samples, batch 100 → 10 iterations per epoch.

## 5. Parametric vs Non-parametric
| Parametric | Non-parametric |
|-----------|----------------|
| Fixed number of parameters, assumes a functional form | Number of parameters grows with data |
| Linear/logistic regression, Naive Bayes, neural nets | kNN, decision trees, kernel SVM |
| Fast, needs less data, may underfit | Flexible, needs more data, may overfit |

## 6. Discriminative vs Generative
- **Discriminative:** learns P(y | x), the decision boundary. *Logistic regression, SVM, neural nets.*
- **Generative:** learns P(x, y) = P(x|y)·P(y), so it can also **generate** data. *Naive Bayes, GMM, GANs, LLMs.*

## 7. Eager vs Lazy learning
- **Eager:** builds the model at training time (decision tree, SVM, NN). Fast prediction.
- **Lazy:** just stores data, computes at prediction time (**kNN**). Slow prediction, no training.

## 8. Common Applications (for "give an example" questions)
| Domain | Example | Problem type |
|--------|---------|--------------|
| Email | Spam filter | Binary classification |
| Finance | Credit scoring, fraud detection | Classification / anomaly detection |
| Retail | Product recommendation | Recommender / association |
| Retail | Customer segmentation | Clustering |
| Real estate | House price | Regression |
| Healthcare | Tumour detection from X-ray | Image classification (CNN) |
| Self-driving | Lane / object detection | CV + RL |
| Chatbots | Question answering | NLP / LLM |

## 9. Common Interview Questions
1. Difference between AI, ML, and DL?
2. Supervised vs unsupervised vs reinforcement learning? Give examples.
3. Parameters vs hyperparameters?
4. Why do we split data into train / validation / test?
5. What is overfitting? (link to 07)
6. Classification vs regression?
7. What is the difference between a loss function and a cost function?
8. What is data leakage? (Test information leaking into training, e.g. scaling before splitting.)
9. Generative vs discriminative models?
10. Explain the ML pipeline you used in your project.

## MCQ Traps
- **Clustering and PCA are unsupervised**, even though PCA gives "components".
- **Logistic regression is a classification algorithm** despite the name.
- **Hyperparameters are not learned** from data; parameters are.
- Self-supervised ≠ unsupervised. Labels are derived from the data.
- **Test set must not be used for tuning.**
- Predicting a **continuous** number = regression; **category** = classification.

## Practice MCQs
1. Grouping customers into segments without labels is: **(a) Classification (b) Regression (c) Clustering (d) RL** → **c**
2. Which is a hyperparameter? **(a) weights (b) bias (c) learning rate (d) gradient** → **c**
3. 2000 samples, batch size 250: iterations per epoch? → **8**
4. Which is generative? **(a) SVM (b) Logistic Reg (c) Naive Bayes (d) kNN** → **c**
5. BERT's pre-training is: **(a) supervised (b) self-supervised (c) RL (d) clustering** → **b**
