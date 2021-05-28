
import torch
import torchvision
from torchvision import transforms
from torch.utils.data import Dataset, DataLoader
import torch.nn as nn
import torchvision
import torchvision.datasets as datasets


class ReLUNet(nn.Module):
  
    def __init__(self, n_classes):
        super().__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels=1, out_channels=20, kernel_size=5, padding = 0),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2),
        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(in_channels=20, out_channels=50, kernel_size=5, padding = 0),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2)
        )

        
        self.lin1 = nn.Linear(800, 500)
        self.act =  nn.ReLU()
        self.lin2 = nn.Linear(500, 10)
  
  
    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)

        x = x.view(x.size(0), -1)
        #print(x.shape)
        x = self.lin1(x)
        x = self.act(x)
        
        
        logits = self.lin2(x)
        return logits