# Comparison of CuDNN and Pytorch

The main idea if this project is to compare CuDNN and Torch time and accuracy performance.

Link to the presentation: https://www.canva.com/design/DAEfnmXM5ok/y6Kn-u4BvYZ2lMwHXKF5Lg/view?utm_content=DAEfnmXM5ok&utm_campaign=designshare&utm_medium=link&utm_source=sharebutton.


In this projects 2 datasets are used:
- MNIST (60 000 pictures and 10 classes)
- Fashion MNIST (60 000 pictures and 10 classes)

MNIST                     |  Fashion MNIST
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/Other/MNIST.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/Other/Fashion_MNIST.png)



Main architectures that were used for this project are:
- SimpleNet;
- Lenet
- ReLUNet
- LargeNet


SimpleNet                   |  Lenet
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/Other/SimpleNet_pic.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/Other/LeNet_pic.png)


ReLUNet                     |  LargeNet
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/Other/ReLUNet_pic.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/Other/LargeNet_pic.png)





Both models were traind with:
- SGD optimizer
- for differnt number of epoches (1,5,15,30 and 45)

## Calculation results

### SimpleNet

#### time

 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/simplenet_f_t.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/simplenet_m_t.png)

#### accuracy

 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/simplenet_f.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/simplenet_m.png)

### LeNet

#### time


 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/Lenet_f_t.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/lenet_m_t.png)

#### accuracy

 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/Lenet_f.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/lenet_m.png)

### ReLUNet

#### time

 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/ReLuNet_f_t.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/ReLuNet_m_t.png)

#### accuracy


 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/ReLuNet_f.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/ReLuNet_m.png)

### LargeNet

#### time


 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/largenet_f_t.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/time/largenet_m_t.png)

#### accuracy


 MNIST                      | Fashion MNIST 
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/largenet_f.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/Project/pictures/experiments/accuracy/largenet_m.png)
