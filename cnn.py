# 日期：2021年07月17日
import torch.nn as nn
import torch.nn.functional as F
from torch.nn.init import xavier_uniform_, xavier_normal_, zeros_

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.net = nn.Sequential(
            nn.Conv2d(1, 32, 5, padding=2),
            nn.BatchNorm2d(32),
            nn.MaxPool2d(2, 2),
            nn.Conv2d(32, 64, 5, padding=2),
            nn.BatchNorm2d(64),
            nn.MaxPool2d(2, 2),
            nn.Flatten(),
            nn.Linear(3136, 1024),
            nn.Dropout(0.1),
            nn.BatchNorm1d(1024),
            nn.Linear(1024, 10)
        )
        self._init_weights()

    def _init_weights(self):
        for i in self.net:
            if isinstance(i, nn.Conv2d):
                i.weight = xavier_normal_(i.weight)
                i.bias = zeros_(i.bias)
            elif isinstance(i, nn.Linear):
                i.weight = xavier_uniform_(i.weight)
                i.bias = zeros_(i.bias)


    def forward(self, x):
        return self.net(x)

class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=10, kernel_size=(5,5))
        self.conv2 = nn.Conv2d(10, 20, kernel_size=(3,3))
        self.fc1 = nn.Linear(in_features=20*10*10, out_features=500)
        self.fc2 = nn.Linear(500, 10)
        self.maxpool = nn.MaxPool2d(2, 2)

    def forward(self, x):
        # x.shape = batch_size * channels( = 1) *28 * 28
        input_size=x.size(0)   # 获取batch_size

        x=self.conv1(x)
        # input:batch_size * 1 * 28 * 28   (in_channels=1, out_channels=10)
        # oouput:batch_size * 10 * 24 * 24  (24=28-5+1)

        x=F.relu(x)
        # 激活函数保持shape不变
        # 激活函数使神经网络变成非线性，解决线性模型所不能解决的问题。

        # x=F.max_pool2d(x,kernel_size=2,stride=2)
        x = self.maxpool(x)
        # input:batch_size * 10 * 24 * 24
        # output:batch_size * 10 * 12 * 12    (stride=2,因此尺寸减半)

        x=self.conv2(x)
        # input:batch_size * 10 * 12 * 12   (in_channels=1, out_channels=10)
        # output:batch_size * 20 * 10 * 10  (10=12-3+1)

        x=F.relu(x)

        x=x.view(input_size,-1)
        # view()中，当某一维是-1时，会根据给定维度自动计算它的大小
        # 因此-1表示的维度是： batch_size * 20 * 10 * 10 / batch_size = 20 * 10 * 10 =2000

        x=self.fc1(x)
        # input:batch_size * 2000
        # output:batch_size * 500

        x=F.relu(x)

        x=self.fc2(x)
        # input:batch_size * 500
        # output:batch_size * 10    变成十分类

        output=F.log_softmax(x,dim=1)
        # 计算x属于每个分类的概率
        # dim=1表示按行计算

        return output



if __name__ == '__main__':
    import torch
    model = Net()
    x = torch.randn(2, 1, 28, 28)
    out = model(x)
    print(out.shape)