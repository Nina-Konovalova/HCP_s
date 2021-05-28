import torch
from tqdm import tqdm, tqdm_notebook
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter
import torch.optim as optim


def train(train_loader, val_loader, model, epochs, experiment_name,logs_base_dir = "./logs1" ):
    #train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    #val_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False)
    DEVICE = torch.device("cuda")
    history = []
    log_template = "\nEpoch {ep:03d} train_loss: {t_loss:0.4f} \
     train_acc {t_acc:0.4f} "
    
    writer = SummaryWriter(f'{logs_base_dir}/{experiment_name}')
    #exp_lr_scheduler = lr_scheduler.StepLR(optimizer_ft, step_size=7, gamma=0.1)
    lr = 0.01
    gamma  = 0.0001
    power = 0.75
    iter = 0
    with tqdm(desc="epoch", total=epochs) as pbar_outer:
        optimizer = optim.SGD(model.parameters(), lr=lr )
        criterion = nn.CrossEntropyLoss()
        iter = 0

        for epoch in range(epochs):

          running_loss = 0.0
          running_corrects = 0
          processed_data = 0
        
          for inputs, labels in train_loader:
              inputs = inputs.to(DEVICE)
              labels = labels.to(DEVICE)
              optimizer.zero_grad()

              outputs = model(inputs)
              loss = criterion(outputs, labels)
              
              loss.backward()
              optimizer.step()

              preds = torch.argmax(outputs, 1)
              running_loss += loss.item() * inputs.size(0)
              running_corrects += torch.sum(preds == labels.data)
              processed_data += inputs.size(0)

              lr = lr*(1+gamma*iter)**(-power)
              iter += 1
                    
          train_loss = running_loss / processed_data
          train_acc = running_corrects.cpu().numpy() / processed_data

          writer.add_scalar(f'Train_loss', train_loss, global_step=iter)
          writer.add_scalar(f'Train_acc', train_acc, global_step=iter)

          model.eval()
          running_loss = 0.0
          running_corrects = 0
          processed_size = 0

          # for inputs, labels in val_loader:
          #     inputs = inputs.to(DEVICE)
          #     labels = labels.to(DEVICE)

          #     with torch.set_grad_enabled(False):
          #         outputs = model(inputs)
          #         loss = criterion(outputs, labels)
          #         preds = torch.argmax(outputs, 1)

          #     running_loss += loss.item() * inputs.size(0)
          #     running_corrects += torch.sum(preds == labels.data)
          #     processed_size += inputs.size(0)
          # val_loss = running_loss / processed_size
          # val_acc = running_corrects.double() / processed_size 

          # writer.add_scalar(f'Val_loss', val_loss, global_step=epoch)
          # writer.add_scalar(f'Val_acc', val_acc, global_step=epoch) 

          history.append((train_loss, train_acc))
                  
          pbar_outer.update(1)
          tqdm.write(log_template.format(ep=epoch+1, t_loss=train_loss,\
                                           t_acc=train_acc))
    print(iter)       
    return history