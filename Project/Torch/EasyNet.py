
import torch
import torchvision
from torchvision import transforms
from torch.utils.data import Dataset, DataLoader
import torch.nn as nn

import torchvision.datasets as datasets


class EasyNet(nn.Module):
  
    def __init__(self, n_classes):
        super().__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels=1, out_channels=20, kernel_size=5, padding = 0),
            nn.MaxPool2d(kernel_size=2),
        )
      
        
        self.lin1 = nn.Linear(2880, n_classes)
        
  
    def forward(self, x):
        x = self.conv1(x)
        
      
        x = x.view(x.size(0), -1)
        #print(x.shape)
        
        logits = self.lin1(x)
        return logits