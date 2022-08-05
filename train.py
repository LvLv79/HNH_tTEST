# 日期：2021年07月17日
import os.path

import torch
import cnn
import torch.nn.functional as F
from dataset import get_data_loader
import torch.optim as optim
from torch.optim.lr_scheduler import ExponentialLR

if __name__ == "__main__":
    if not os.path.exists("./save_model/"):
        os.makedirs("./save_model/")
    # 超参
    batch_size=64
    device=torch.device("cuda" if torch.cuda.is_available() else "cpu")
    epoch = 20

    # 选择模型
    # model=cnn.CNN().to(device)
    model=cnn.Net().to(device)

    # 定义优化器
    optimizer=optim.Adam(model.parameters(), lr=8e-6)
    # define lr scheduler
    op = ExponentialLR(optimizer, gamma=0.9)
    # 加载迭代器
    train_loader, test_loader = get_data_loader()

    # 训练
    def train(epoch_i):
        model.train()   # 设置为训练模式
        for batch_i,(digit,label) in enumerate(train_loader):
            digit,label=digit.to(device),label.to(device)
            optimizer.zero_grad()    # 梯度初始化为0
            output=model(digit)     # 训练结果,output是概率
            loss=F.cross_entropy(output,label)     # 定义损失函数,交叉熵损失函数适用于多分类问题
            loss.backward()    # 反向传播
            optimizer.step()    # 更新参数

            if batch_i % 100 == 0:
                print("train    epoch_i: {}    batch_i: {}    loss: {: .8f}, lr: {: .8f}".format(epoch_i,batch_i,loss.item(), op.get_lr()[0]))

    # 测试
    def test(epoch_i):
        model.eval()    # 设置为测试模式
        acc = 0.
        loss = 0.
        with torch.no_grad():
            for digit, label in test_loader:
                digit, lable = digit.to(device), label.to(device)
                output = model(digit)  # 模型输出
                loss += F.cross_entropy(output, lable).item()

                predict = output.max(dim=1, keepdim=True)[1]
                # 找到概率最大值的下标，1表示按行计算。
                # max()返回两个值，第一个是值，第二个是索引，所以取 max[1]
                predict = predict.to(label.device)
                acc += predict.eq(label.view_as(predict)).sum().item()
            accuracy = acc / len(test_loader.dataset) * 100
            test_loss = loss / len(test_loader.dataset)
            torch.save(model.state_dict(), f"./save_model/{accuracy}_model.pt")
            print("test     epoch_i: {}    loss: {: .8f}    accuracy: {: .4f}% lr: {: .4f}".format(epoch_i,test_loss,accuracy, op.get_lr()[0]))

    # train && test
    for epoch_i in range(1,epoch+1):
        train(epoch_i)
        op.step()
        test(epoch_i)

    # 保存模型






