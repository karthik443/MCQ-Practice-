# 12 — Python & ML Libraries

OAs often include "what is the output?" and "which function?" questions.

## 1. Python Essentials for ML
- **Mutable:** list, dict, set. **Immutable:** tuple, str, int, float, frozenset.
- **List comprehension:** `[x**2 for x in range(5)]` → `[0, 1, 4, 9, 16]`
- `range(5)` → 0..4. `range(1, 10, 3)` → 1, 4, 7.
- Slicing: `a[start:stop:step]`; `a[::-1]` reverses. Negative index `a[-1]` = last.
- `lambda x: x+1`, `map`, `filter`, `zip`, `enumerate`.
- **Shallow vs deep copy:** `copy.copy` shares nested objects; `copy.deepcopy` doesn't.
- **Default mutable argument trap:** `def f(x, l=[])` reuses the same list across calls.
- `is` compares identity, `==` compares value.
- Generators (`yield`) are lazy and memory-efficient.
- `*args`, `**kwargs`; decorators; context managers (`with`).

## 2. NumPy ⭐
```python
import numpy as np
a = np.array([[1, 2, 3], [4, 5, 6]])
a.shape      # (2, 3)
a.ndim       # 2
a.T          # transpose, shape (3, 2)
a.reshape(3, 2)
a.sum(axis=0)   # column sums -> [5 7 9]
a.sum(axis=1)   # row sums    -> [ 6 15]
a.mean()        # 3.5
a @ a.T         # matrix multiply (also np.dot)
a * 2           # element-wise
```
- **axis=0 → down the rows (per column). axis=1 → across the columns (per row).**
- **Broadcasting:** smaller arrays stretch to match when dimensions are equal or 1. `(3,3) + (3,)` works, `(3,3) + (2,)` doesn't.
- `np.zeros`, `np.ones`, `np.eye(n)`, `np.arange(0,10,2)`, `np.linspace(0,1,5)`, `np.random.rand` (uniform), `np.random.randn` (standard normal), `np.random.seed(42)`.
- `*` is **element-wise**; `@` / `np.dot` is **matrix multiplication**.
- NumPy arrays are **faster** than lists (contiguous memory, vectorized C code), and hold **one dtype**.
- Boolean masking: `a[a > 3]`. `np.argmax`, `np.where`, `np.unique`, `np.concatenate`, `np.vstack/hstack`.
- Views vs copies: slicing gives a **view**; fancy indexing gives a **copy**.

## 3. Pandas ⭐
```python
import pandas as pd
df = pd.read_csv("data.csv")
df.head(); df.info(); df.describe(); df.shape
df.isnull().sum()                 # missing values per column
df.dropna()                       # drop rows with NaN
df["age"].fillna(df["age"].median(), inplace=True)
df[df["age"] > 30]                # filter
df.loc[0:2, "name"]               # label-based (inclusive end)
df.iloc[0:2, 0]                   # position-based (exclusive end)
df.groupby("city")["salary"].mean()
df.sort_values("age", ascending=False)
df.drop_duplicates()
df.merge(df2, on="id", how="left")  # join
pd.concat([df1, df2])
df["col"].value_counts()
df.apply(func); df["col"].map(dict)
pd.get_dummies(df, columns=["city"])   # one-hot
```
- **Series** = 1-D labelled array; **DataFrame** = 2-D table.
- **`loc` is label-based and end-inclusive; `iloc` is integer-position-based and end-exclusive.**
- `df.describe()` shows count, mean, std, min, quartiles, max for numeric columns.
- Joins: `inner`, `left`, `right`, `outer`. `pivot_table`, `melt`.
- `NaN` propagates; `df.corr()` gives the correlation matrix.

## 4. Matplotlib / Seaborn (which chart?)
| Goal | Plot |
|------|------|
| Distribution of one numeric variable | **Histogram**, KDE, **box plot** (outliers) |
| Relationship between two numeric variables | **Scatter plot** |
| Trend over time | **Line chart** |
| Compare categories | **Bar chart** |
| Correlations | **Heatmap** of the correlation matrix |
| Many pairwise relationships | **Pair plot** |
| Proportions | Pie chart (use sparingly) |

## 5. Scikit-learn Workflow ⭐⭐
```python
from sklearn.model_selection import train_test_split, cross_val_score, GridSearchCV
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.pipeline import Pipeline
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)   # fit ONLY on train
X_test  = scaler.transform(X_test)        # transform only on test

model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
print(accuracy_score(y_test, y_pred))
```
- **API pattern:** `fit()` learns, `predict()` predicts, `transform()` applies, `fit_transform()` = both. `score()` gives accuracy (classifiers) / R² (regressors).
- **`fit_transform` on train, `transform` on test.** Fitting on test = data leakage.
- **`random_state`** makes results reproducible. **`stratify=y`** preserves class ratios.
- **Pipeline** chains preprocessing + model and prevents leakage in cross-validation.
- **`GridSearchCV`** = grid search + CV. `cross_val_score(model, X, y, cv=5)` → 5 scores.
- Common estimators: `LinearRegression`, `Ridge`, `Lasso`, `LogisticRegression`, `KNeighborsClassifier`, `DecisionTreeClassifier`, `SVC`, `KMeans`, `PCA`, `GaussianNB`.
- `model.coef_`, `model.intercept_` (linear), `model.feature_importances_` (trees), `kmeans.inertia_`, `kmeans.labels_`, `pca.explained_variance_ratio_`.
- `SimpleImputer(strategy="median")`, `LabelEncoder` (target), `OrdinalEncoder`, `ColumnTransformer`.
- `classification_report` gives precision, recall, F1, and support per class.

## 6. Deep Learning Code Basics
### Keras
```python
from tensorflow import keras
model = keras.Sequential([
    keras.layers.Dense(64, activation="relu", input_shape=(10,)),
    keras.layers.Dropout(0.3),
    keras.layers.Dense(1, activation="sigmoid")])
model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])
model.fit(X_train, y_train, epochs=20, batch_size=32, validation_split=0.2)
```
### PyTorch
```python
import torch, torch.nn as nn
class Net(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc = nn.Linear(10, 1)
    def forward(self, x):
        return torch.sigmoid(self.fc(x))
opt = torch.optim.Adam(net.parameters(), lr=1e-3)
loss_fn = nn.BCELoss()
for x, y in loader:
    opt.zero_grad()            # clear old gradients
    loss = loss_fn(net(x), y)
    loss.backward()            # backprop
    opt.step()                 # update weights
```
- **`optimizer.zero_grad()`** is needed because PyTorch **accumulates** gradients.
- `model.eval()` turns off dropout/batchnorm updates; `torch.no_grad()` skips gradient tracking at inference.
- `.to("cuda")` moves to the GPU. Tensors ≈ NumPy arrays with GPU + autograd.
- Dense(64) with input 10 → parameters = 10×64 + 64 = **704**.

## 7. Code-Output Practice
1. `np.array([1,2,3]) * np.array([4,5,6])` → `[ 4 10 18]`
2. `np.dot([1,2,3],[4,5,6])` → **32**
3. `np.arange(5).reshape(5,1).shape` → `(5, 1)`
4. `a = [1,2,3]; b = a; b.append(4); print(a)` → `[1, 2, 3, 4]`
5. `df.iloc[0:2]` returns → **2 rows** (positions 0, 1); `df.loc[0:2]` (default index) → **3 rows**
6. `np.zeros((2,3)).sum(axis=0).shape` → `(3,)`
7. `print(type(np.array([1,2.5])[0]))` → `numpy.float64` (upcast to a single dtype)
8. `sorted([3,1,2], reverse=True)` → `[3, 2, 1]`

## 8. Common Interview Questions
1. NumPy array vs Python list? Why is NumPy faster?
2. Difference between `loc` and `iloc`?
3. How do you handle missing values in Pandas?
4. What does `fit`, `transform`, `fit_transform` do? Why not fit on test data?
5. What is a scikit-learn Pipeline and why use it?
6. How do you do hyperparameter tuning in sklearn?
7. TensorFlow vs PyTorch?
8. Why `zero_grad()` in PyTorch?
9. How would you read a large CSV that doesn't fit in memory? (`chunksize`, dtypes, Dask)
10. What is broadcasting?

## MCQ Traps
- `*` is element-wise; `@` is matrix multiplication.
- `axis=0` collapses rows (column-wise result).
- `loc` is end-**inclusive**; `iloc` is end-**exclusive**.
- `fit_transform(train)` / `transform(test)`.
- `train_test_split`: `stratify` for class balance; `random_state` for reproducibility.
- `LabelEncoder` is meant for **targets**; use `OneHotEncoder` for features.
- Lists copy by reference (`b = a`); use `a.copy()`.

## Practice MCQs
1. `np.array([[1,2],[3,4]]).sum(axis=1)` → **[3 7]**
2. Which method learns the scaling parameters? → **fit**
3. PyTorch's `loss.backward()` does → **computes gradients (backprop)**
4. Best chart for outliers in one variable → **Box plot**
5. `df.drop_duplicates()` → **removes duplicate rows**
