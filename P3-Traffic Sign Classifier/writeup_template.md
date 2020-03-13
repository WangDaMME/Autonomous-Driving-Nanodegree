# :checkered_flag: Project 3: Traffic Sign Classifier

Key Concepts: Machine Learning, Deep Learning, Tensorflow, LeNet Architecture, Computer Vision

<img src="examples/xxxxxx.jpg" width="480" alt="Combined Image" />
<hr>

### Overview 

**Build a Traffic Sign Recognition Project**

The goals / steps of this project are the following:
* Load the data set (see below for links to the project data set)
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/visualization.jpg "Visualization"
[image2]: ./examples/grayscale.jpg "Grayscaling"
[image3]: ./examples/random_noise.jpg "Random Noise"
[image4]: ./examples/placeholder.png "Traffic Sign 1"
[image5]: ./examples/placeholder.png "Traffic Sign 2"
[image6]: ./examples/placeholder.png "Traffic Sign 3"
[image7]: ./examples/placeholder.png "Traffic Sign 4"
[image8]: ./examples/placeholder.png "Traffic Sign 5"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/481/view) individually and describe how I addressed each point in my implementation.  

---
### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. You can submit your writeup as markdown or pdf. You can use this template as a guide for writing the report. The submission includes the project code.

You're reading it! and here is a link to my [project code](https://github.com/udacity/CarND-Traffic-Sign-Classifier-Project/blob/master/Traffic_Sign_Classifier.ipynb)

### Data Set Summary & Exploration

#### 1. Provide a basic summary of the data set. In the code, the analysis should be done using python, numpy and/or pandas methods rather than hardcoding results manually.

I used the pandas library to calculate summary statistics of the traffic
signs data set:

* The size of training set is <strong>34799</strong>
* The size of the validation set is <strong>4410</strong>
* The size of test set is <strong>12630</strong>
* The shape of a traffic sign image is <strong>(32,32,3</strong>
* The number of unique classes/labels in the data set is <strong>43</strong>

#### 2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set. Below is bar charts showing how the data of each class is distributed in its own dataset.

```
1. show example from each classes
2 Barcharts saved in the folder
```
### Design and Test a Model Architecture

#### 1. Describe how you preprocessed the image data. What techniques were chosen and why did you choose these techniques? Consider including images showing the output of each preprocessing technique. Pre-processing refers to techniques such as converting to grayscale, normalization, etc. (OPTIONAL: As described in the "Stand Out Suggestions" part of the rubric, if you generated additional data for training, describe why you decided to generate additional data, how you generated the data, and provide example images of the additional data. Then describe the characteristics of the augmented training set like number of images in the set, number of images for each class, etc.)

1.1 Firstly from the bar charts above, I realize the number of sign images per label colected in the given GTSRB - (German Traffic sign datasets) is not distributed evenly. So I generated the fake images for the classess which is less than 800 samples by randomly picking one of 4 <strong)Augumentation</strong> techniques(rotation, translation, add guassian noise and increase rightness). The training set then is expanded to <font color='red'> ??? </font color='red'> samples with a more balanced distribution shown below.

```
1. show example evenly-distributed bar chart

```
Here is an example of a traffic sign image after Augmentation.

```
1. show Augmentated  
```
1.2 Then with the expansion of the training set, I split smaples from the training set to validation set to keep the ideal ratio of Training data VS Validation data as 80% : 20%.

1.3 The normalization to iamges comes to the last step before putting them into Network. With mean=0 and equal variance, it is critical to make the ranges of our distributions of feature values be consistent for each feature, and thus the learning rate would cause corrections in each dimension that would differ from one another. To grayscale or not, there is always a nebulous saying that the grayscaled images are less computational expensive and good enough if only expecting the gradient of object to extract features. So, I separate 'the num_channel' from input variables and test with both RGB and Grayscale. To Lenet-5, it seems the result of grayscale is a little better than that of RGB, otherwise, you need to increase training epochs of rgb to reach the same standard of result.
![alt text][image2]

![alt text][image3]

The difference between the original data set and the augmented data set is the following ... 


#### 2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

My final model consisted of the following layers:

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 32x32x1 Grayscaled image   							| 
| Convolution 5x5     	| 1x1 stride, valid padding, outputs 28x28x6 	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 14x14x6 				|
| Convolution 5x5	    | 1x1 stride, valid padding, outputs 10x10x6			|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 5x5x16 				|
| Flatten		|    outputs 400        									|
| Fully connected		| output 120        									|
| Dropout		| keep_prob=0.75        									|
| Fully connected		| output 84        									|
| Dropout		| keep_prob=0.75        									|
| Fully connected		| output 43        									|
 


#### 3. Describe how you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

To train the model, I refer to Lenet5 architecture and add two dropout layers after each fully connected layer. The hyperparameters after tweaking is shown below.

| Hyperparameters         		|     Values	        					| 
|:---------------------:|:---------------------------------------------:| 
| Epochs         		| 45   							| 
| Batch_size    	| 100	|
| learning_rate					|	 0.001											|
| keep_prob	      	| 0.75 				|


#### 4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. Include in the discussion the results on the training, validation and test sets and where in the code these were calculated. Your approach may have been an iterative process, in which case, outline the steps you took to get to the final solution and why you chose those steps. Perhaps your solution involved an already well known implementation or architecture. In this case, discuss why you think the architecture is suitable for the current problem.

My final model results were:
* training set accuracy of ?
* validation set accuracy of ? 
* test set accuracy of ?

Typical adjustments could include choosing a different model architecture, adding or taking away layers (pooling, dropout, convolution, etc), using an activation function or changing the activation function. One common justification for adjusting an architecture would be due to overfitting or underfitting. A high accuracy on the training set but low accuracy on the validation set indicates over fitting; a low accuracy on both sets indicates under fitting.


### Test a Model on New Images

#### 1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.


```
1. show example 5 uploaded models
```
The first image might be difficult to classify because ...

#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

```
placeholder for 12 images I imported

| Image			        |     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| Stop Sign      		| Stop sign   									| 
| U-turn     			| U-turn 										|
| Yield					| Yield											|
| 100 km/h	      		| Bumpy Road					 				|
| Slippery Road			| Slippery Road      							|


```


The model was able to correctly guess 4 of the 12 traffic signs, which gives an accuracy of 80%. This compares favorably to the accuracy on the test set of ...

#### 3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. Provide the top 5 softmax probabilities for each image along with the sign type of each probability. (OPTIONAL: as described in the "Stand Out Suggestions" part of the rubric, visualizations can also be provided such as bar charts)


Use the first image as an instance, the model is relatively sure that this is a stop sign (probability of 0.6), and the image does contain a stop sign. The top five soft max probabilities were

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| .60         			| Stop sign   									| 
| .20     				| U-turn 										|
| .05					| Yield											|
| .04	      			| Bumpy Road					 				|
| .01				    | Slippery Road      							|

