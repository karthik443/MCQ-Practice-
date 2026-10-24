# 09 — NLP, Transformers & LLMs

## 1. NLP Pipeline & Preprocessing ⭐
Raw text → **lowercasing → tokenization → stop-word removal → stemming / lemmatization → vectorization → model**.
| Step | Note |
|------|------|
| **Tokenization** | Split into words / subwords / characters |
| **Stop words** | Remove very common words (the, is, and). Not always (hurts sentiment/LLMs) |
| **Stemming** | Chop suffixes by rules: *running → run*, *studies → studi* (crude; may give non-words). Fast. (Porter) |
| **Lemmatization** | Dictionary-based base form: *better → good*, *studies → study*. Accurate, slower |
| **POS tagging** | Noun, verb, etc. |
| **NER** | Named Entity Recognition: person, place, org |
| **n-grams** | Sequences of n words (bigram = 2) |

Common NLP tasks: sentiment analysis, text classification, NER, machine translation, summarization, QA, chatbots, spelling correction.

## 2. Text Representation ⭐⭐
| Method | Idea | Drawback |
|--------|------|----------|
| **Bag of Words (BoW)** | Count of each word. Ignores order | Sparse, no semantics |
| **TF-IDF** | TF × IDF. Weights words that are frequent in a doc but rare across docs | No semantics/order |
| **Word embeddings** (Word2Vec, GloVe, fastText) | **Dense** vectors where similar words are close | **Static**: one vector per word regardless of context |
| **Contextual embeddings** (ELMo, BERT, GPT) | Vector depends on the sentence ("bank" river vs money) | Heavy compute |

**TF-IDF:**
- TF(t, d) = count of t in d / total words in d
- IDF(t) = log(N / df(t)) (N = docs, df = docs containing t)
- **Words in every document get IDF ≈ 0.**
- Example: "the" appears in all 100 docs → IDF = log(1) = **0**. "quantum" in 2 of 100 docs → IDF = log(50) ≈ **1.7**.

**Word2Vec:** **CBOW** predicts a word from its context; **Skip-gram** predicts context from a word (better for rare words). Famous analogy: **king − man + woman ≈ queen**. **GloVe** uses global co-occurrence counts. **fastText** uses subword n-grams (handles OOV words).

**Similarity:** **cosine similarity** between vectors. **One-hot** vectors are sparse, orthogonal, carry no similarity.

## 3. Language Models
- **n-gram LM:** P(wₙ | previous n−1 words). Limited context, sparse.
- **Neural LMs:** RNN/LSTM, then **Transformers**.
- **Perplexity:** a metric for language models. **Lower = better**.
- **Evaluation:** BLEU (translation), ROUGE (summarization), accuracy/F1 (classification), exact match/F1 (QA).

## 4. Attention & Transformers ⭐⭐⭐
**Why?** RNNs are sequential (slow) and forget long context. **Transformers ("Attention Is All You Need", 2017)** process all tokens **in parallel** using **self-attention**.

### Self-Attention
Each token produces **Query (Q), Key (K), Value (V)** vectors.
**Attention(Q, K, V) = softmax(QKᵀ / √dₖ) · V**
- QKᵀ = relevance of every token to every other.
- **√dₖ scaling** stops dot products from growing large and saturating softmax.
- Output = weighted sum of values.
- **Multi-head attention:** several attention heads in parallel learn different relations; outputs are concatenated.
- **Complexity:** O(n²) in sequence length (why long context is costly).

### Transformer building blocks
- **Positional encoding:** attention has no notion of order, so position information is added to embeddings.
- **Feed-forward network** per token, **residual connections**, **layer normalization**.
- **Encoder** (understands input; bidirectional) and **Decoder** (generates; **masked / causal self-attention** so a token can't see the future; cross-attention to the encoder).

### Model families ⭐
| Type | Example | Attention | Best for |
|------|---------|-----------|----------|
| **Encoder-only** | **BERT**, RoBERTa | Bidirectional | Classification, NER, QA, embeddings |
| **Decoder-only** | **GPT**, LLaMA, Claude | Causal (left-to-right) | Text generation, chat |
| **Encoder–decoder** | **T5**, BART, original Transformer | Both | Translation, summarization |

- **BERT pre-training:** **Masked Language Modeling** (predict masked words) + Next Sentence Prediction. Then fine-tune.
- **GPT pre-training:** **next-token prediction** (autoregressive).

## 5. Large Language Models (LLMs) ⭐⭐
- **Tokens:** LLMs operate on **subword tokens** (BPE, WordPiece, SentencePiece), not whole words. Rule of thumb: 1 token ≈ ¾ word (~4 characters in English).
- **Context window:** max tokens (prompt + output) the model can attend to.
- **Training stages:** **Pre-training** (huge unlabeled text, next-token) → **Supervised fine-tuning / instruction tuning** → **RLHF / preference tuning** (align with human preferences).
- **Scaling laws:** more parameters + data + compute → better performance.
- **Emergent abilities, in-context learning:** the model learns from examples in the prompt, with no weight update.

### Generation controls ⭐
| Parameter | Effect |
|-----------|--------|
| **Temperature** | **Low (→0): deterministic, focused.** **High: random, creative**. Scales logits before softmax |
| **Top-k** | Sample only from the k most probable tokens |
| **Top-p (nucleus)** | Sample from the smallest set whose cumulative probability ≥ p |
| **Greedy decoding** | Always the most probable token |
| **Beam search** | Keeps the top-b candidate sequences |
| **Max tokens / stop sequences** | Length and termination |

### Prompting
- **Zero-shot** (no examples), **few-shot** (a few examples), **Chain-of-Thought (CoT)** ("think step by step"), role/system prompts, structured output.
- **Prompt engineering** = improving outputs without changing weights.

### Hallucination ⭐
Model produces **fluent but false / made-up** content. Mitigate with **RAG**, grounding in sources, lower temperature, citations, verification, better prompts.

### RAG — Retrieval-Augmented Generation ⭐⭐
1. **Chunk** documents and create **embeddings** → store in a **vector database** (FAISS, Pinecone, Chroma).
2. At query time, embed the query → **retrieve top-k similar chunks** (cosine similarity).
3. Put the chunks in the **prompt** → the LLM answers using them.
- Pros: up-to-date and private data without retraining, fewer hallucinations, cites sources.
- **RAG vs fine-tuning:** RAG = inject **knowledge** at inference time (easy to update). Fine-tuning = change **behaviour / style / format** (bakes into weights; costly to update).

### Fine-tuning approaches
- **Full fine-tuning:** all weights (expensive).
- **PEFT:** **LoRA** (train small low-rank adapter matrices), QLoRA (4-bit quantized base + LoRA), prefix/prompt tuning. Much cheaper.
- **Quantization:** lower-precision weights (int8/int4) for smaller, faster inference.
- **Distillation:** small "student" learns from a large "teacher".

### Agents & tools
**LLM agents** use tools (search, code, APIs) in a loop: plan → act → observe. Function/tool calling; MCP (Model Context Protocol) standardizes tool connections.

### Other
- **Embeddings** (sentence-transformers) power semantic search and clustering.
- **Multimodal** models handle text + image + audio.
- **Safety:** prompt injection, jailbreaks, bias, privacy, guardrails.

## 6. Common Interview Questions
1. What is tokenization? Stemming vs lemmatization?
2. Explain TF-IDF. Why IDF?
3. BoW vs embeddings? What is Word2Vec (CBOW vs skip-gram)?
4. Explain self-attention. Why divide by √dₖ?
5. Why Transformers over RNNs/LSTMs?
6. What is positional encoding and why is it needed?
7. BERT vs GPT?
8. What is multi-head attention?
9. What is temperature? Top-k vs top-p?
10. What is hallucination and how do you reduce it?
11. Explain RAG. RAG vs fine-tuning?
12. What is LoRA?
13. What is a context window? Why is long context expensive? (O(n²) attention)
14. Zero-shot vs few-shot vs CoT?
15. How does RLHF work at a high level? (Humans rank outputs → reward model → optimize the policy.)

## MCQ Traps
- **BERT = encoder-only, bidirectional, masked LM. GPT = decoder-only, causal, next-token.**
- **Stemming is rule-based and may produce non-words; lemmatization uses a dictionary.**
- **TF-IDF penalizes common words.**
- **Word2Vec embeddings are static/context-independent; BERT's are contextual.**
- **Low temperature = deterministic.**
- **Attention is O(n²)** in sequence length.
- **Transformers need positional encoding** (no inherent order).
- **RAG doesn't change the model weights.**
- **Perplexity: lower is better.**
- **BLEU → translation; ROUGE → summarization.**

## Practice MCQs
1. Which model is encoder-only? **(a) GPT (b) BERT (c) LLaMA (d) T5** → **b**
2. Word in every document has TF-IDF ≈ → **0**
3. To get more creative, varied output, you → **raise the temperature**
4. Which retrieves external knowledge at inference? → **RAG**
5. Attention(Q,K,V) = → **softmax(QKᵀ/√dₖ)·V**
