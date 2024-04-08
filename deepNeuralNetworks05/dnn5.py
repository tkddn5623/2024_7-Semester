import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np

# Task 1
x1 = np.array([1.0, 2.0, 3.0], dtype=np.float32)
x2 = np.array([4.0, 5.0, 6.0], dtype=np.float32)
w1 = np.array([[0.1, 0.2, 0.3, 0.4], [0.5, 0.6, 0.7, 0.8], [0.9, 1.0, 1.1, 1.2]], dtype=np.float32)
w2 = np.array([[0.2, 0.3], [0.4, 0.5], [0.6, 0.7], [0.8, 0.9]], dtype=np.float32)


class DNN_torch(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.w1 = nn.Linear(3, 4, bias=False)
        self.w2 = nn.Linear(4, 2, bias=False)
        self.w1.weight = nn.Parameter(torch.from_numpy(w1).transpose(0, 1))
        self.w2.weight = nn.Parameter(torch.from_numpy(w2).transpose(0, 1))
        self.relu = nn.ReLU()
        self.softmax = nn.Softmax(dim=0)
        self.dropout = nn.Dropout(0.4)

    def forward(self, x: torch.Tensor):
        y = self.w1(x)
        y = self.w2(y)
        return y

    def softmax(self, a: torch.Tensor):
        exp_a = torch.exp(a)
        sum_exp_a = torch.sum(exp_a)
        y = exp_a / sum_exp_a
        return y

    def cross_entropy_error(self, y: torch.Tensor, t: torch.Tensor):
        delta = 1e-7
        return -torch.sum(t * torch.log(y + delta)) / 2


class DNN_numpy:
    def __init__(self) -> None:
        self.w1 = w1
        self.w2 = w2

    def forward(self, x: np.ndarray):
        y = x @ w1
        y = y @ w2
        return y

    def softmax(self, a: np.ndarray):
        exp_a = np.exp(a)
        sum_exp_a = np.sum(exp_a)
        y = exp_a / sum_exp_a
        return y

    def cross_entropy_error(self, y: np.ndarray, t: np.ndarray):
        delta = 1e-7
        return -np.sum(t * np.log(y + delta)) / 2


dnn_torch = DNN_torch()
dnn_numpy = DNN_numpy()
x = np.concatenate(([x1], [x2]), axis=0)
x_ts = torch.from_numpy(x)

print('task 1 Torch result: \n', dnn_torch.forward(x_ts))
print('task 1 Numpy result: \n', dnn_numpy.forward(x), '\n')


# Task 2
y1 = np.array([0, 1], dtype=np.float32)
y2 = np.array([1, 0], dtype=np.float32)
y = np.concatenate(([y1], [y2]), axis=0)
y_ts = torch.from_numpy(y)
w1 = np.array([[0.1, 0.2, 0.3, 0.4], [0.5, 0.6, 0.7, 0.8], [0.9, 1.0, 1.1, 1.2]], dtype=np.float32)
w1_ts = torch.from_numpy(w1)

# loss = nn.CrossEntropyLoss()
# print(loss(dnn_torch.forward(x_ts), y_ts))
# print('answer: ', F.cross_entropy(dnn_torch.forward(x_ts), y_ts))

x_softmax_torch = [dnn_torch.softmax(dnn_torch.forward(x_ts[_])) for _ in range(2)]
x_softmax_torch = torch.row_stack((x_softmax_torch[0], x_softmax_torch[1]))
# print(x_softmax_torch)

x_softmax_np = [dnn_numpy.softmax(dnn_numpy.forward(x[_])) for _ in range(2)]
x_softmax_np = np.concatenate(([x_softmax_np[0]], [x_softmax_np[1]]), axis=0)

print('task 2 Torch result: \n', dnn_torch.cross_entropy_error(x_softmax_torch, y_ts))
print('task 2 Numpy result: \n', dnn_numpy.cross_entropy_error(x_softmax_np, y))
