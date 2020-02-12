# :checkered_flag: Project 1: Finding Lane Lines on the Road
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Key Concepts: Computer Vision, OpenCV
<hr>

### Overview 

When we drive, the lane lines on the road act as our constant reference for where to steer the vehicle. Naturally, one of the first things we'd like to do is to detect lane lines using an algorithm.
This project aims to automatically identify the lane lines on the road using Computer Vision techniques from camera information. Following the pipeline I developed in §Reflection, the effect will first tested on different individual images and later apply the result to a video stream (really just a series of images).

### Results
```
1. Placeholder  - Images Test
2. Video - Whitelane
3. Video - Yellowlane
```

### Reflection

### 1. Describe the pipeline, ie. draw_lines() function.

My pipeline consists of 8 steps. 
<ol>
   <li> Read images from the directory. (matplotlib.image.imread)
   <li> Convert the images to the grayscale which returns only 1 color channel. (cv2.cvtColor)
   <li> Apply Gaussian Blur to suppress noise and spurious gradients. (gaussian_blur)
   <li> Apply Canny Edge Detections to identify boundaries in images by strength of gradients.(canny)
   <li> Create a quadrilateral masked edges image for Region of Interest. (the rest region is set to black)
   <li> Implement Hough Transformation to identify lines, containing the endpoints (x1, y1, x2, y2) of all line segments.(cv2.HoughLinesP)
   <li> Show result lines overlaying on original images (cv2.addWeighted)
   <li> Save the result in the output directory.
</ol>
```
Placeholder : Pipeline process image
```

#### <u> Improvement on the pipeline </u>

You will then refine your pipeline with parameter tuning and by averaging and extrapolating the lines.
At this point,I have the detected Hough lines drawn onto the road, but in line segments. So, to identify the full extent of the lane marking, I need to define a line to run the full length of the visible lane based on the line segments from the Hough Transformation. First, I take down endpoints (x1, y1, x2, y2) for every line segments and caculate the line slope ((y2-y1)/(x2-x1)) to classify which segments are part of the left line vs. the right line. Then, I average the position of each of the lines , get the average slope (k) and average intersection (b), and extrapolate to the top and bottom of the lane.

```
Placeholder : Extrapolate line - Full extent image
```
### 2. Potential shortcomings.

1. One potential shortcoming would be the quadrilateral-masked region of interest is determined after we have seen the effects from test images.That means we assumed in advance that the region appears at the middle-bottom part of the image in a fixed order. Under the case that the camera is not mounted in a proper location, it will lead 2 line lanes to be out of the expected mask region.
2. Another shortcoming could be my pipeline uses 2 straight lines (left and right) to represent the steering direction. However, it is not suitable for the curving sections.
3. When using extrapolate/average method to get the full extent of lane, it is a little hard to tune the slope threshold value to an ideal value so that it can filter out the flying lines among all the endpoints we gathered.
4. The pipeline depends on the light contrast condition to some extent. When lane lines are in or even overlayed by shadows, these sections will not be easily detected by simply convering the image to grayscale. 

### 3. Suggested Improvements.
In the challenge section, I modified the pipeline to be more generalized for different size of images and videos and maske the quadrilateral region based on the proportion of the image.To improve the robustness for lighting contrast, images can be converted into HSV color other than RGB. To improve the robustness of quadrilateral masking, it might be worth thinking to set a random size region first and see if the lines detected by Hough Transform reach certain threshold. If not, updating the shape of region by increasing with a certain step value untill it fails and breaks when the region coordinates reach predefined maximum values. To reduce the visual effect of vibrating/flying lines, an algorithm can be developed to compare the slopes between consecutive frame and make sure changes are in expected interval, ±10%.

### Rubric
```
xxxxxxxxx
```







# **Finding Lane Lines on the Road** 
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

<img src="examples/laneLines_thirdPass.jpg" width="480" alt="Combined Image" />

Overview
---

When we drive, we use our eyes to decide where to go.  The lines on the road that show us where the lanes are act as our constant reference for where to steer the vehicle.  Naturally, one of the first things we would like to do in developing a self-driving car is to automatically detect lane lines using an algorithm.

In this project you will detect lane lines in images using Python and OpenCV.  OpenCV means "Open-Source Computer Vision", which is a package that has many useful tools for analyzing images.  

To complete the project, two files will be submitted: a file containing project code and a file containing a brief write up explaining your solution. We have included template files to be used both for the [code](https://github.com/udacity/CarND-LaneLines-P1/blob/master/P1.ipynb) and the [writeup](https://github.com/udacity/CarND-LaneLines-P1/blob/master/writeup_template.md).The code file is called P1.ipynb and the writeup template is writeup_template.md 

To meet specifications in the project, take a look at the requirements in the [project rubric](https://review.udacity.com/#!/rubrics/322/view)


Creating a Great Writeup
---
For this project, a great writeup should provide a detailed response to the "Reflection" section of the [project rubric](https://review.udacity.com/#!/rubrics/322/view). There are three parts to the reflection:

1. Describe the pipeline

2. Identify any shortcomings

3. Suggest possible improvements

We encourage using images in your writeup to demonstrate how your pipeline works.  

All that said, please be concise!  We're not looking for you to write a book here: just a brief description.

You're not required to use markdown for your writeup.  If you use another method please just submit a pdf of your writeup. Here is a link to a [writeup template file](https://github.com/udacity/CarND-LaneLines-P1/blob/master/writeup_template.md). 


The Project
---

## If you have already installed the [CarND Term1 Starter Kit](https://github.com/udacity/CarND-Term1-Starter-Kit/blob/master/README.md) you should be good to go!   If not, you should install the starter kit to get started on this project. ##

**Step 1:** Set up the [CarND Term1 Starter Kit](https://classroom.udacity.com/nanodegrees/nd013/parts/fbf77062-5703-404e-b60c-95b78b2f3f9e/modules/83ec35ee-1e02-48a5-bdb7-d244bd47c2dc/lessons/8c82408b-a217-4d09-b81d-1bda4c6380ef/concepts/4f1870e0-3849-43e4-b670-12e6f2d4b7a7) if you haven't already.

**Step 2:** Open the code in a Jupyter Notebook

You will complete the project code in a Jupyter notebook.  If you are unfamiliar with Jupyter Notebooks, check out <A HREF="https://www.packtpub.com/books/content/basics-jupyter-notebook-and-python" target="_blank">Cyrille Rossant's Basics of Jupyter Notebook and Python</A> to get started.

Jupyter is an Ipython notebook where you can run blocks of code and see results interactively.  All the code for this project is contained in a Jupyter notebook. To start Jupyter in your browser, use terminal to navigate to your project directory and then run the following command at the terminal prompt (be sure you've activated your Python 3 carnd-term1 environment as described in the [CarND Term1 Starter Kit](https://github.com/udacity/CarND-Term1-Starter-Kit/blob/master/README.md) installation instructions!):

`> jupyter notebook`

A browser window will appear showing the contents of the current directory.  Click on the file called "P1.ipynb".  Another browser window will appear displaying the notebook.  Follow the instructions in the notebook to complete the project.  

**Step 3:** Complete the project and submit both the Ipython notebook and the project writeup

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

