# :checkered_flag: Project 4: Behavior Cloning 

[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Key Concepts: Machine Learning, Deep Learning, Neural Networks, Transfer Learning, Tensorflow, Keras, Image Classification.
<hr>

### Overview

In this project, I implemented a PID controller in C++ to tune the PID hyperparameters to maneuver the vehicle around the track!
The simulator will provide you the cross track error (CTE) and the velocity (mph) in order to compute the appropriate steering angle.
One more thing. The speed limit has been increased from 30 mph to 100 mph. Get ready to channel your inner Vin Diesel and try to drive SAFELY as fast as possible! NOTE: you don't have to meet a minimum speed to pass.



[documentation]: (https://keras.io/getting_started/faq/)



### Results
#### PID Controller Implementation
```
<div align="center">
<img src="Result/pid_controller.gif" width="600" alt="Result of pid controller" />
</div>
```

```

#### Detailed Video Link

<a href="https://www.youtube.com/watch?v=4a7EJNfv-Z4" target="_blank"> Youtube Link</a>

### Project Rubrics

```
(Will be filled in after the Submission Review)

### Tuning Hyperparameters

* <b>Kp</b> - propotional gain, it proportionally increases the control signal for the same level of error and tends to cause the closed-loop system to respond more quickly, but also brings overshoot more.

* <b>Ki</b> - integral gain, it tends to reduce steady-state error. But A drawback of the integral term is that it can make the system more sluggish (and oscillatory) since when the error signal changes sign.

* <b>Kd</b> - direvative gain, it adds the ability to "anticipate" error. The control signal can become large if the error begins sloping upward by accumulation, even while the magnitude of the error is still relatively small. This anticipation tends to add damping to the system, thereby decreasing overshoot. 

To set up the initial assumptions, I first set random values for Kp, Ki, Kd and observe the changing trends of P_error, I_error, D_error. From the log, we observed that I_error keeps increasing because of accumulation of +=cte in range (0,200) and Kp starts from 0.7598 and changes from -3.5 to +3.5; and D_error barely changes from 0 to maximum -0.15. Take the maximum params, -3.5Kp+0.1Kd+200Ki, I want to keep the effect of I_error small, 200Ki=0.1--> Ki=0.0005; Then try to set this equation to be 0, Kd=4.0 and Kp=1/7=0.143. After manual tuning, the PID controller gains are listed below.


| Pid Gains Data         		|     Values	        					| 
|:---------------------:|:---------------------------------------------:| 
| Kp      		|  0.143   							| 
| Ki        |  0.0005 	       |
| Kd	     		|  4.0									  |


### Prerequisites

####   Simulator.
You can download the Term3 Simulator which contains the Path Planning Project from the [releases tab (https://github.com/udacity/self-driving-car-sim/releases/tag/T3_v1.2).  

To run the simulator on Mac/Linux, first make the binary file executable with the following command:
```shell
sudo chmod u+x {simulator_file_name}
```

### Dependencies


* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```

### Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 


#### Reference
1. http://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID




as a markdown or pdf file. It should explain the structure of your network and training approach. The write-up must also include examples of images from the dataset in the discussion of the characteristics of the dataset. While we recommend using English for good practice, writing in any language is acceptable (reviewers will translate). There is no minimum word count so long as there are complete descriptions of the problems and the strategies. See the rubric and the writeup_template.md for more details about the expectations.








### Code Structure

    |- model.py          # The script used to create and train the model.
    |
    |- drive.py          # The script to drive the car. 
    │     
    |- model.h5          # The saved model.  [document](https://review.udacity.com/#!/rubrics/432/view)
    │
    |- video.py          # The script to create the video recording when in autonomous mode..
    │
    |- video.mp4         # A video recording of your vehicle driving autonomously at least one lap around the track.
    │
    |- readme.md         # Explanation of the Architecture & training approach.
    │
    |- data
    
    
    
    




# **Behavioral Cloning** 

## Writeup Template

### You can use this file as a template for your writeup if you want to submit it as a markdown file, but feel free to use some other method and submit a pdf if you prefer.

---

**Behavioral Cloning Project**

The goals / steps of this project are the following:
* Use the simulator to collect data of good driving behavior
* Build, a convolution neural network in Keras that predicts steering angles from images
* Train and validate the model with a training and validation set
* Test that the model successfully drives around track one without leaving the road
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/placeholder.png "Model Visualization"
[image2]: ./examples/placeholder.png "Grayscaling"
[image3]: ./examples/placeholder_small.png "Recovery Image"
[image4]: ./examples/placeholder_small.png "Recovery Image"
[image5]: ./examples/placeholder_small.png "Recovery Image"
[image6]: ./examples/placeholder_small.png "Normal Image"
[image7]: ./examples/placeholder_small.png "Flipped Image"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/432/view) individually and describe how I addressed each point in my implementation.  

---
### Files Submitted & Code Quality

#### 1. Submission includes all required files and can be used to run the simulator in autonomous mode

My project includes the following files:
* model.py containing the script to create and train the model
* drive.py for driving the car in autonomous mode
* model.h5 containing a trained convolution neural network 
* writeup_report.md or writeup_report.pdf summarizing the results

#### 2. Submission includes functional code
Using the Udacity [rubric points](https://review.udacity.com/#!/rubrics/432/view) provided simulator and my drive.py file, the car can be driven autonomously around the track by executing 
```sh
python drive.py model.h5
```

#### 3. Submission code is usable and readable

The model.py file contains the code for training and saving the convolution neural network. The file shows the pipeline I used for training and validating the model, and it contains comments to explain how the code works.

### Model Architecture and Training Strategy

#### 1. An appropriate model architecture has been employed

My model consists of a convolution neural network with 3x3 filter sizes and depths between 32 and 128 (model.py lines 18-24) 

The model includes RELU layers to introduce nonlinearity (code line 20), and the data is normalized in the model using a Keras lambda layer (code line 18). 

#### 2. Attempts to reduce overfitting in the model

The model contains dropout layers in order to reduce overfitting (model.py lines 21). 

The model was trained and validated on different data sets to ensure that the model was not overfitting (code line 10-16). The model was tested by running it through the simulator and ensuring that the vehicle could stay on the track.

#### 3. Model parameter tuning

The model used an adam optimizer, so the learning rate was not tuned manually (model.py line 25).

#### 4. Appropriate training data

Training data was chosen to keep the vehicle driving on the road. I used a combination of center lane driving, recovering from the left and right sides of the road ... 

For details about how I created the training data, see the next section. 

### Model Architecture and Training Strategy

#### 1. Solution Design Approach

The overall strategy for deriving a model architecture was to ...

My first step was to use a convolution neural network model similar to the ... I thought this model might be appropriate because ...

In order to gauge how well the model was working, I split my image and steering angle data into a training and validation set. I found that my first model had a low mean squared error on the training set but a high mean squared error on the validation set. This implied that the model was overfitting. 

To combat the overfitting, I modified the model so that ...

Then I ... 

The final step was to run the simulator to see how well the car was driving around track one. There were a few spots where the vehicle fell off the track... to improve the driving behavior in these cases, I ....

At the end of the process, the vehicle is able to drive autonomously around the track without leaving the road.

#### 2. Final Model Architecture

The final model architecture (model.py lines 18-24) consisted of a convolution neural network with the following layers and layer sizes ...

Here is a visualization of the architecture (note: visualizing the architecture is optional according to the project rubric)

![alt text][image1]

#### 3. Creation of the Training Set & Training Process

To capture good driving behavior, I first recorded two laps on track one using center lane driving. Here is an example image of center lane driving:

![alt text][image2]

I then recorded the vehicle recovering from the left side and right sides of the road back to center so that the vehicle would learn to .... These images show what a recovery looks like starting from ... :

![alt text][image3]
![alt text][image4]
![alt text][image5]

Then I repeated this process on track two in order to get more data points.

To augment the data sat, I also flipped images and angles thinking that this would ... For example, here is an image that has then been flipped:

![alt text][image6]
![alt text][image7]

Etc ....

After the collection process, I had X number of data points. I then preprocessed this data by ...


I finally randomly shuffled the data set and put Y% of the data into a validation set. 

I used this training data for training the model. The validation set helped determine if the model was over or under fitting. The ideal number of epochs was Z as evidenced by ... I used an adam optimizer so that manually training the learning rate wasn't necessary.

