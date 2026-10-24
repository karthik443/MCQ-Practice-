# 11 — Reinforcement Learning & Advanced Topics

## 1. Reinforcement Learning (RL) ⭐⭐
An **agent** interacts with an **environment**: observes **state s** → takes **action a** → gets **reward r** and next state s′. Goal: learn a **policy π(s) → a** maximizing **cumulative (discounted) reward**.

| Term | Meaning |
|------|---------|
| **Policy (π)** | Mapping from state to action |
| **Reward** | Immediate feedback signal |
| **Return** | Sum of discounted future rewards: Gₜ = rₜ + γrₜ₊₁ + γ²rₜ₊₂ + … |
| **Discount factor γ ∈ [0,1]** | γ → 0: short-sighted; γ → 1: far-sighted |
| **Value function V(s)** | Expected return from state s following π |
| **Q-function Q(s,a)** | Expected return from taking action a in s, then following π |
| **Episode** | One run from start to terminal state |
| **MDP** | Markov Decision Process: (S, A, P, R, γ). **Markov property:** the future depends only on the current state |

### Exploration vs Exploitation ⭐
- **Exploitation:** choose the best-known action. **Exploration:** try new actions to learn.
- **ε-greedy:** with probability ε pick a random action, else the best. Decay ε over time.
- **Multi-armed bandit:** the simplest exploration–exploitation problem (UCB, Thompson sampling).

### Algorithms
| Family | Examples | Note |
|--------|----------|------|
| **Value-based** | **Q-Learning**, SARSA, **DQN** | Learn Q, act greedily |
| **Policy-based** | REINFORCE, **PPO**, TRPO | Directly optimize the policy |
| **Actor–Critic** | A2C/A3C, SAC | Actor (policy) + Critic (value) |
| **Model-based** | Dyna, MuZero | Learn a model of the environment |

**Q-Learning update ⭐:** **Q(s,a) ← Q(s,a) + α [ r + γ·maxₐ′ Q(s′,a′) − Q(s,a) ]**
- α = learning rate. It is **off-policy** (learns the optimal Q regardless of the behaviour policy). **SARSA is on-policy** (uses the next action actually taken).
- **Model-free** (no knowledge of transition probabilities).

**Worked example:** Q(s,a) = 0, α = 0.5, r = 10, γ = 0.9, max Q(s′) = 20 → Q = 0 + 0.5(10 + 18 − 0) = **14**.

- **Bellman equation:** V(s) = maxₐ [R(s,a) + γ Σ P(s′|s,a) V(s′)].
- **DQN:** a neural network approximates Q; uses **experience replay** and a **target network** for stability (Atari).
- **Applications:** games (AlphaGo, Atari), robotics, recommendation, autonomous driving, **RLHF** for LLMs, resource scheduling.
- **Challenges:** sparse rewards, sample inefficiency, credit assignment, safe exploration.

## 2. Generative Models
### GAN (Generative Adversarial Network) ⭐
- **Generator** creates fake data from noise; **Discriminator** tells real from fake. They train **adversarially** (a minimax game). At equilibrium the discriminator is ~50% correct.
- Issues: **mode collapse**, unstable training. Uses: image synthesis, deepfakes, super-resolution, data augmentation.
### VAE
Encoder maps to a **distribution** (mean, variance); sample from the latent space; decoder reconstructs. Loss = reconstruction + **KL divergence**. Smooth latent space, blurrier outputs.
### Diffusion Models
Learn to **reverse a gradual noising process** → generate images by iteratively denoising (Stable Diffusion, DALL·E, Midjourney). More stable than GANs, slower to sample.
### LLMs — see file 09.

## 3. Recommender Systems ⭐
| Type | Idea | Weakness |
|------|------|----------|
| **Content-based** | Recommend items **similar to what the user liked** (item features) | Filter bubble, needs good features |
| **Collaborative filtering** | Use **user–item interactions**: "users like you liked…" (user-based / item-based) | **Cold start**, sparsity |
| **Matrix factorization** (SVD, ALS) | Learn latent factors for users/items | |
| **Hybrid** | Combine both (Netflix, Amazon) | |
| **Deep / two-tower** | Embeddings from neural nets | |

- **Cold-start problem:** new user/item with no history → use content-based, popularity, or onboarding questions.
- **Metrics:** Precision@k, Recall@k, **MAP**, **NDCG**, RMSE (ratings), CTR (online).

## 4. Time Series ⭐
Data ordered in time. Components: **Trend, Seasonality, Cyclic, Noise (residual)**.
- **Stationary:** constant mean/variance over time. Test with **ADF** test; make stationary by **differencing**.
- **Models:** moving average, **ARIMA(p, d, q)** (p = AR order, d = differencing, q = MA order), **SARIMA** (seasonal), **Exponential smoothing (Holt-Winters)**, **Prophet**, **LSTM / Transformers**, XGBoost with lag features.
- **Autocorrelation (ACF/PACF)** to pick p and q.
- **Split by time** (no shuffling, no random CV). Avoid future leakage. Metrics: MAE, RMSE, **MAPE**.

## 5. Computer Vision Tasks (recap)
Image classification, **object detection** (YOLO, SSD, Faster R-CNN; output = bounding boxes + classes; metric **IoU**, **mAP**), **semantic/instance segmentation** (U-Net, Mask R-CNN), OCR, face recognition, pose estimation. **IoU = intersection area / union area.** **Vision Transformers (ViT)** treat image patches as tokens. **Data augmentation** is key.

## 6. MLOps & Deployment ⭐
- **Pipeline:** data → train → validate → **package (Docker)** → **serve (REST API: Flask/FastAPI)** → **monitor** → retrain.
- **Model versioning & experiment tracking:** Git, **DVC, MLflow, Weights & Biases**.
- **CI/CD for ML**, feature stores, model registries. Tools: Kubernetes, Airflow, Kubeflow, SageMaker.
- **Drift:** **data drift** (input distribution changes) vs **concept drift** (relationship X→y changes). Fix: monitoring and retraining.
- **Batch vs real-time inference.** **Latency, throughput, cost** trade-offs. Model compression (quantization, pruning, distillation).
- **A/B testing** for online evaluation.

## 7. Explainable AI, Ethics & Responsible AI ⭐
- **Interpretable models:** linear/logistic regression, decision trees. **Black boxes:** deep nets, ensembles.
- **XAI tools:** **SHAP** (Shapley values: contribution of each feature), **LIME** (local linear approximation), feature importance, partial dependence, Grad-CAM (images).
- **Bias & fairness:** biased data → biased model (sampling bias, historical bias). Metrics: demographic parity, equalized odds.
- **Privacy:** anonymization, **differential privacy**, **federated learning** (train on-device, share only updates), GDPR.
- **Safety:** adversarial examples, prompt injection, deepfakes, misinformation, accountability, transparency.

## 8. Other Terms
- **Transfer learning**, **few-shot / zero-shot learning**, **active learning**, **online learning**, **meta-learning**.
- **Edge AI / TinyML:** running models on-device.
- **AGI:** hypothetical human-level general AI (vs today's **narrow AI**).
- **Knowledge graphs**, **Federated learning**, **AutoML**.

## 9. Common Interview Questions
1. Explain RL with an example. What are state, action, reward, policy?
2. Exploration vs exploitation? What is ε-greedy?
3. Explain Q-learning. On-policy vs off-policy?
4. What is the discount factor?
5. How do GANs work? What is mode collapse?
6. Content-based vs collaborative filtering? Cold start?
7. What is stationarity in time series? What is ARIMA?
8. What is data drift vs concept drift?
9. How would you deploy a model in production?
10. How do you explain a model's prediction to a non-technical user? (SHAP / LIME)
11. What is bias in ML and how do you reduce it?
12. What is federated learning?

## MCQ Traps
- **Q-learning = off-policy, model-free, value-based. SARSA = on-policy.**
- **γ close to 0 = short-sighted.**
- **GAN: generator + discriminator.** VAE uses a KL term.
- **Cold start is a collaborative filtering problem.**
- **ARIMA needs stationarity** (the d in ARIMA handles differencing).
- **Never shuffle time series before splitting.**
- **Data drift ≠ concept drift.**
- **IoU = intersection / union.**
- **SHAP and LIME** are explainability methods.

## Practice MCQs
1. The update in Q-learning uses → **max over next-state actions**
2. Which problem is typical for collaborative filtering? → **Cold start**
3. In GANs, which network tries to fool the other? → **Generator**
4. Federated learning mainly helps → **privacy (data stays on the device)**
5. ARIMA(1,1,0): the "1" in the middle means → **one order of differencing**
