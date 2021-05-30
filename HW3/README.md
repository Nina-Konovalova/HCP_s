# 1. Laplace equation:  

- solve the Laplace equation using CUDA. (10 points)

- draw the heatmap of the solution u(x,y) using anything you want (10 points)

![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/HW3/heatmap.png)

# 2. Filtering:

Take an arbitrary image and apply two types of filters to it using CUDA.

- Blurring filter (have at least 2 blurring filters - they can differ in stencil size or the values of the filter matrix for example) (15 points)

- Median filter (try to achieve the cartoonish effect) (15 points)


Blured                     |  Median
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/HW3/blured_cat.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/HW3/med_cat.png)

# 3. Histogram:

You need to plot a  histogram for a chosen picture. For this purpose:

- take any picture -> grayscale it -> calculate the histogram for the picture using CUDA (10 points)

- plot the resulting histogram using anything you want (10 points)

Hist from programm                    |  Hist from openCV
:-------------------------:|:-------------------------:
![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/HW3/hist_from_cuda.png)  |  ![](https://github.com/Nina-Konovalova/HCP_skoltech/blob/main/HW3/hist_from_cv.png)
