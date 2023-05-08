import torch.nn as nn
import torch.nn.functional as F
import torch

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.regressor1 = nn.Sequential(
            nn.Linear(48, 50),
            nn.ReLU(),
            nn.Linear(50, 50),
            nn.ReLU(),
            nn.Linear(50, 1),
            nn.Sigmoid())
        self.regressor2 = nn.Sequential(
            nn.Linear(48, 50),
            nn.ReLU(),
            nn.Linear(50, 50),
            nn.ReLU(),
            nn.Linear(50, 1),
            nn.Sigmoid())
        self.classifier = nn.Sequential(
            nn.Linear(50, 50),
            nn.ReLU(),
            nn.Linear(50, 50),
            nn.ReLU(),
            nn.Linear(50, 2),
            nn.Softmax())

    def forward(self, x):
        out1 = self.regressor1(x)*200
        out2 = self.regressor2(x)*200
        tmp = torch.cat((x,out1,out2),1)
        out = self.classifier(tmp)
        return out, out1, out2
    