
import torch
from torchvision import transforms
from torch.utils.data import Dataset, DataLoader
import torch.nn as nn
import torchvision
import torchvision.datasets as datasets


class Create_loades:
  def __init__(self, test_size = 0.0, batch_size = 64):
        super().__init__()
        
        self.batch_size = batch_size
        self.test_size = test_size
        
        
  def forward(self, dataset):
        self.dataset = dataset
        train_transfrorms = torchvision.transforms.Compose([
                                    torchvision.transforms.ToTensor(),
                                    torchvision.transforms.Normalize(
                                      (0.1307,), (0.3081,)),
                                    # torchvision.transforms.Resize(64)
                                  ])
        test_transforms  = torchvision.transforms.Compose([
                                    torchvision.transforms.ToTensor(),
                                    torchvision.transforms.Normalize(
                                      (0.1307,), (0.3081,)),
                                    # torchvision.transforms.Resize(64)
                                      
                                  ])
        if self.dataset == 'mnist':
            mnist = datasets.MNIST(root='./data', train=True, download=True, transform = train_transfrorms )
            mnist_testset = datasets.MNIST(root='./data', train=False, download=True, transform = test_transforms)
        if self.dataset == 'mnist_fashion':
            mnist = datasets.FashionMNIST(root='./data', train=True, download=True, transform = train_transfrorms)
            mnist_testset = datasets.FashionMNIST(root='./data', train=False, download=True, transform = test_transforms)
        
        a = int(len(mnist)*self.test_size)
        b = len(mnist) - a
        mnist_trainset,mnist_valset = torch.utils.data.random_split(mnist, [a, b])

        

        train_loader = torch.utils.data.DataLoader(
                                  mnist_trainset,
                                  batch_size=self.batch_size, 
                                  shuffle=True)
        val_loader = torch.utils.data.DataLoader(
                                    mnist_valset,
                                    batch_size=self.batch_size, 
                                    shuffle=False)


        test_loader = torch.utils.data.DataLoader(
                                    mnist_testset,
                                  batch_size=batch_size, 
                                  shuffle=False)
  return train_loader, val_loader, test_loader