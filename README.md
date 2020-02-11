# :checkered_flag: Project 1: Finding Lane Lines on the Road
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)
<hr>
Key Concepts: Computer Vision, OpenCV
<hr>

### Overview 

When we drive, the lane lines on the road act as our constant reference for where to steer the vehicle. Naturally, one of the first things we'd like to do is to detect lane lines using an algorithm.
This project aims to automatically identify the lane lines on the road using Computer Vision techniques from camera information. Following the pipeline I developed in §Reflection, the effect will first tested on different individual images and later apply the result to a video stream (really just a series of images).

### Reflection

### 1. Describe the pipeline, ie. draw_lines() function.

My pipeline consisted of 8 steps. 
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

#### <u> Improvement on the pipeline </u>

You will then refine your pipeline with parameter tuning and by averaging and extrapolating the lines.

Finally, you'll make a brief writeup report. The workspace github repository has a writeup_template.md that can be used as a guide.

Have a look at the video clip called "P1_example.mp4" in the repository to see an example of what your final output should look like. Two videos are provided for you to run your code on. These are called "solidWhiteRight.mp4" and solidYellowLeft.mp4".


### 1. Describe the pipeline, ie. draw_lines() function.

---

### Rubric

### 2. Potential shortcomings.


One potential shortcoming would be what would happen when ... 

Another shortcoming could be ...


### 3. Suggested Improvements.

A possible improvement would be to ...

Another potential improvement could be to ...


### Rubric



