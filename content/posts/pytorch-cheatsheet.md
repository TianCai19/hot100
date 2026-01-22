---
title: "PyTorch 速查"
difficulty: "文档"
description: "常用张量操作、模型训练与保存的 PyTorch 速查表"
---

# PyTorch 速查

## 🧱 张量基础
```python
import torch

# 创建张量
x = torch.tensor([[1, 2], [3, 4]])
zeros = torch.zeros(2, 3)
ones = torch.ones(2, 3)
randn = torch.randn(2, 3)

# 形状与类型
x.shape
x.dtype
x.float()
x.long()

# 维度操作
x.view(4)          # 视图
x.reshape(4)       # 可能拷贝
x.transpose(0, 1)
x.permute(1, 0)

# 广播与拼接
y = torch.randn(2, 1)
x + y              # broadcast
torch.cat([x, x], dim=0)
torch.stack([x, x], dim=0)
```

## ⚡ 设备与随机种子
```python
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
x = x.to(device)

torch.manual_seed(42)
torch.cuda.manual_seed_all(42)
```

## 🧮 自动求导
```python
x = torch.randn(3, requires_grad=True)
y = (x ** 2).sum()
y.backward()
x.grad

with torch.no_grad():
    y = x * 2
```

## 🧩 模型与层
```python
import torch.nn as nn

class MLP(nn.Module):
    def __init__(self, in_dim, hidden, out_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(in_dim, hidden),
            nn.ReLU(),
            nn.Linear(hidden, out_dim)
        )

    def forward(self, x):
        return self.net(x)

model = MLP(10, 32, 2).to(device)
```

## 🧪 常用层与激活
```python
nn.Conv2d(in_channels, out_channels, kernel_size, stride=1, padding=0)
nn.MaxPool2d(kernel_size, stride=None, padding=0)
nn.BatchNorm2d(num_features)
nn.Dropout(p=0.5)

nn.ReLU()
nn.LeakyReLU(negative_slope=0.01)
nn.GELU()
```

## 🧪 损失与优化器
```python
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)

optimizer.zero_grad()
logits = model(x)
loss = criterion(logits, labels)
loss.backward()
optimizer.step()
```

## 🧰 常见损失函数
```python
nn.MSELoss()
nn.CrossEntropyLoss()
nn.BCEWithLogitsLoss()
nn.NLLLoss()
```

## 🧭 学习率调度
```python
from torch.optim.lr_scheduler import StepLR, CosineAnnealingLR

scheduler = StepLR(optimizer, step_size=10, gamma=0.1)
# 或 CosineAnnealingLR(optimizer, T_max=50)

for epoch in range(epochs):
    train_one_epoch(...)
    scheduler.step()
```

## 🧱 初始化与冻结
```python
# 初始化
for m in model.modules():
    if isinstance(m, nn.Linear):
        nn.init.xavier_uniform_(m.weight)
        nn.init.zeros_(m.bias)

# 冻结/解冻
for param in model.parameters():
    param.requires_grad = False
for param in model.parameters():
    param.requires_grad = True
```

## 📦 Dataset 与 DataLoader
```python
from torch.utils.data import Dataset, DataLoader

class MyDataset(Dataset):
    def __init__(self, data, labels):
        self.data = data
        self.labels = labels

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        return self.data[idx], self.labels[idx]

dataset = MyDataset(data, labels)
loader = DataLoader(dataset, batch_size=32, shuffle=True, num_workers=2)
```

## 🧾 评估指标
```python
# top-1 accuracy
pred = logits.argmax(dim=1)
acc = (pred == y).float().mean().item()
```

## 🧪 AMP 混合精度
```python
scaler = torch.cuda.amp.GradScaler()

for x, y in loader:
    optimizer.zero_grad()
    with torch.cuda.amp.autocast():
        logits = model(x)
        loss = criterion(logits, y)
    scaler.scale(loss).backward()
    scaler.step(optimizer)
    scaler.update()
```

## 🔁 训练与评估
```python
model.train()
for x, y in loader:
    x, y = x.to(device), y.to(device)
    optimizer.zero_grad()
    logits = model(x)
    loss = criterion(logits, y)
    loss.backward()
    optimizer.step()

model.eval()
correct = 0
total = 0
with torch.no_grad():
    for x, y in loader:
        x, y = x.to(device), y.to(device)
        pred = model(x).argmax(dim=1)
        correct += (pred == y).sum().item()
        total += y.size(0)
acc = correct / total
```

## 💾 保存与加载
```python
# 只保存参数
torch.save(model.state_dict(), "model.pt")
model.load_state_dict(torch.load("model.pt", map_location=device))

# 保存完整模型 (不推荐用于长期兼容)
torch.save(model, "full_model.pt")
model = torch.load("full_model.pt", map_location=device)
```

## 🔎 常用排查
```python
# 查看参数量
sum(p.numel() for p in model.parameters())

# 只统计可训练参数
sum(p.numel() for p in model.parameters() if p.requires_grad)

# 查看梯度是否为 None
for name, p in model.named_parameters():
    if p.grad is None:
        print(name)
```
