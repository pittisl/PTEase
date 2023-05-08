import torch.nn as nn
import torch.nn.functional as F
import torch

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.encoder = nn.Sequential(
            nn.Linear(84, 100),
            nn.ReLU(),
            nn.Linear(100, 48),
            nn.ReLU(),
            nn.Linear(48, 48))
        self.decoder = nn.Sequential(
            nn.Linear(48, 48),
            nn.ReLU(),
            nn.Linear(48, 100),
            nn.ReLU(),
            nn.Linear(100, 84))

    def forward(self, x):
        out = self.encoder(x)
        out = self.decoder(out)
        return out