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
