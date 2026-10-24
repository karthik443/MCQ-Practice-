# 08 — Neural Networks & Deep Learning

## 1. Perceptron & Neuron ⭐
- **Neuron:** output = **f(w·x + b)**, where f is the activation function.
- **Perceptron:** single neuron with a step activation. Learns **linearly separable** problems only.
- **XOR cannot be solved by a single perceptron**; it needs a hidden layer (MLP). Classic interview question.
- **Multi-Layer Perceptron (MLP):** input → hidden layer(s) → output. Fully connected. **Universal approximation:** one hidden layer with enough neurons can approximate any continuous function.
- **Deep** = many hidden layers.

**Parameter count (dense layer):** inputs × outputs + outputs (biases). Example: 10 → 5 = 10×5 + 5 = **55**.

## 2. Activation Functions ⭐⭐
Without a non-linear activation, stacked layers collapse into a single linear model.
| Function | Formula | Range | Notes |
|----------|---------|-------|-------|
| **Sigmoid** | 1/(1+e⁻ˣ) | (0, 1) | Binary output. **Vanishing gradient**, not zero-centered |
| **Tanh** | (eˣ−e⁻ˣ)/(eˣ+e⁻ˣ) | (−1, 1) | Zero-centered, still vanishes |
| **ReLU** | max(0, x) | [0, ∞) | **Default for hidden layers.** Fast, sparse. **Dying ReLU** problem |
| **Leaky ReLU** | max(0.01x, x) | (−∞, ∞) | Fixes dying ReLU |
| **GELU / Swish** | smooth variants | | Used in transformers |
| **Softmax** | eˣⁱ / Σeˣʲ | (0, 1), sums to 1 | **Multi-class output layer** |

**Output layer choice:** regression → **linear**; binary → **sigmoid**; multi-class (one label) → **softmax**; multi-label → **sigmoid per class**.

## 3. Loss Functions
| Task | Loss |
|------|------|
| Regression | MSE / MAE / Huber |
| Binary classification | **Binary cross-entropy** |
| Multi-class | **Categorical cross-entropy** (softmax) |
| Margin classification | Hinge |

## 4. Training: Forward & Backpropagation ⭐⭐
1. **Forward pass:** compute predictions layer by layer.
2. **Loss:** compare with the target.
3. **Backward pass (backpropagation):** apply the **chain rule** to compute the gradient of the loss w.r.t. every weight, from output to input.
4. **Update:** w ← w − η·∇L (via the optimizer).
Repeat over batches and epochs.

- Weight **initialization** matters: never all zeros (symmetry problem: all neurons learn the same thing). Use **Xavier/Glorot** (sigmoid/tanh) or **He** (ReLU).

### Vanishing & Exploding Gradients ⭐
- **Vanishing:** gradients shrink toward zero through many layers (sigmoid/tanh) → early layers don't learn. Fixes: **ReLU, residual connections (ResNet), batch norm, LSTM/GRU, good init.**
- **Exploding:** gradients grow huge. Fixes: **gradient clipping**, proper init, normalization.

## 5. Optimizers ⭐
| Optimizer | Idea |
|-----------|------|
| **SGD** | Basic mini-batch update |
| **SGD + Momentum** | Accumulates past gradients, smooths the path, speeds up |
| **RMSprop** | Adaptive per-parameter learning rate (divides by running average of squared gradients) |
| **Adam** | **Momentum + RMSprop.** Most popular default (lr ≈ 1e-3) |
| **AdamW** | Adam with proper weight decay (used for transformers) |
| **Adagrad** | Per-parameter rate that decays (good for sparse data) |

Learning-rate **schedules** (step decay, cosine, warm-up) help convergence.

## 6. Regularization in Deep Learning ⭐
- **Dropout:** randomly zero a fraction of neurons **during training only** (off at inference). Prevents co-adaptation.
- **L1/L2 (weight decay).**
- **Early stopping** on validation loss.
- **Data augmentation** (flip, rotate, crop, noise).
- **Batch normalization:** normalizes layer inputs per mini-batch → faster, more stable training, slight regularizing effect. **Layer norm** is used in transformers/RNNs (independent of batch size).
- **Transfer learning / fine-tuning** with pre-trained models when data is small.

## 7. Convolutional Neural Networks (CNN) ⭐⭐
For **images / grid data**. Exploits **local connectivity**, **weight sharing**, and **translation invariance**.

**Layers:**
- **Convolution:** slide a **filter/kernel** over the input to produce a **feature map** (edges → textures → objects).
- **Activation:** ReLU.
- **Pooling:** downsample (**max pool** most common, average pool). Reduces size, adds small translation invariance, no learnable parameters.
- **Flatten + Fully connected + Softmax** at the end.

**Output size formula ⭐:** **O = (W − F + 2P) / S + 1**
(W = input size, F = filter size, P = padding, S = stride)
- Example: 32×32 input, 5×5 filter, P = 0, S = 1 → (32−5)/1+1 = **28**.
- Example: 28×28, 3×3, P = 1, S = 1 → (28−3+2)/1+1 = **28** ("same" padding).
- Max pool 2×2, stride 2 on 28×28 → **14×14**.

**Conv layer parameters:** (F × F × C_in + 1) × C_out. Example: 3×3 kernel, 3 input channels, 16 filters = (27+1)×16 = **448**.

**Famous architectures:** LeNet (digits), AlexNet (2012 ImageNet breakthrough), VGG (deep 3×3), **ResNet (skip/residual connections → very deep nets)**, Inception, MobileNet (light), EfficientNet.
**Tasks:** classification, **object detection (YOLO, Faster R-CNN)**, **segmentation (U-Net, Mask R-CNN)**.
**Transfer learning:** freeze early layers (generic features), retrain the last layers.

## 8. Recurrent Neural Networks (RNN) ⭐
For **sequences** (text, time series, speech). The hidden state carries memory: hₜ = f(W·xₜ + U·hₜ₋₁ + b). **Same weights shared across time steps.**
- **Problem:** vanishing gradient → can't learn long-range dependencies. Trained with **Backpropagation Through Time (BPTT)**.
- **LSTM:** gates (**forget, input, output**) + a cell state → long-term memory.
- **GRU:** simpler (**update, reset** gates), fewer parameters, often similar performance.
- **Bidirectional RNN:** reads the sequence both directions.
- **Seq2Seq (encoder–decoder):** translation. Improved by **attention**, then replaced by **Transformers** (see 09).
- RNNs process **sequentially** (can't parallelize); transformers are parallel.

## 9. Other Architectures (one-liners)
- **Autoencoder:** encoder compresses → bottleneck → decoder reconstructs. Uses: denoising, dimensionality reduction, anomaly detection.
- **GAN:** generator vs discriminator (see 11).
- **VAE:** probabilistic autoencoder for generation.
- **Transformer:** attention-based (see 09).
- **Diffusion models:** generate images by denoising (Stable Diffusion, DALL·E).

## 10. Frameworks
**TensorFlow / Keras** (Google), **PyTorch** (Meta; dominant in research; dynamic graphs), JAX. GPUs/TPUs speed up the matrix math.

## 11. Common Interview Questions
1. Explain how a neural network learns (forward, loss, backprop, update).
2. Why do we need non-linear activations?
3. ReLU vs sigmoid vs tanh? What is the dying ReLU problem?
4. What are vanishing/exploding gradients and their fixes?
5. What is backpropagation?
6. SGD vs Adam?
7. What is dropout? Is it used at test time? (No.)
8. Batch normalization: what and why?
9. How does a CNN work? Why CNN over a plain MLP for images? (Fewer parameters, local patterns, weight sharing.)
10. What does pooling do?
11. LSTM vs RNN? Why LSTM solves vanishing gradients (gated additive cell state).
12. What is transfer learning?
13. Why can't a perceptron solve XOR?

## MCQ Traps
- **Softmax for multi-class, sigmoid for binary.**
- **Dropout is applied only during training.**
- **Never initialize all weights to zero.**
- Pooling layers have **no learnable parameters**.
- **ReLU → default hidden activation**, but sigmoid/tanh cause vanishing gradients.
- **Adam = momentum + RMSprop.**
- Epoch ≠ iteration ≠ batch.
- CNN output size: **(W−F+2P)/S + 1**.
- LSTM has **3 gates** (forget, input, output); GRU has **2** (update, reset).
- A single perceptron: **linearly separable only**.

## Practice MCQs
1. Input 64×64, filter 3×3, stride 1, no padding → **62×62**
2. Which activation for multi-class output? → **Softmax**
3. Dying ReLU means → **neurons output 0 for all inputs and stop learning**
4. Parameters in Dense(100 → 10) → 100×10 + 10 = **1010**
5. Which layer type reduces spatial size with no weights? → **Pooling**
