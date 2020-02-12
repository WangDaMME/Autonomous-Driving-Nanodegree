# :checkered_flag: Project 1: Finding Lane Lines on the Road
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Key Concepts: Computer Vision, OpenCV

<img src="examples/laneLines_thirdPass.jpg" width="480" alt="Combined Image" />
<hr>

### Overview 

When we drive, the lane lines on the road act as our constant reference for where to steer the vehicle. Naturally, one of the first things we'd like to do is to detect lane lines using an algorithm.
This project aims to automatically identify the lane lines on the road using Computer Vision techniques from camera information. Following the pipeline I developed in §Reflection, the effect will first tested on different individual images and later apply the result to a video stream (really just a series of images).

### Results
1. Solid White Lane at the Right side
<div align="center">
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/CarND-LaneLines-P1/GIF_Result/solidWhiteRight.gif" width="480" height="320">
</div>

2. Solid Yellow Lane at the Left side
<div align="center">
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/CarND-LaneLines-P1/GIF_Result/solidYellowLeft.gif" width="480" height="320">
</div>


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

<i> Unextrapolated </i>
<div align="center">
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/CarND-LaneLines-P1/GIF_Result/Unextrapolated.PNG" >
</div>
<i> Extrapolated </i>
<div align="center">
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/CarND-LaneLines-P1/GIF_Result/Extrpolated.PNG" >
</div>
### 2. Potential shortcomings.

1. One potential shortcoming would be the quadrilateral-masked region of interest is determined after we have seen the effects from test images.That means we assumed in advance that the region appears at the middle-bottom part of the image in a fixed order. Under the case that the camera is not mounted in a proper location, it will lead 2 line lanes to be out of the expected mask region.
2. Another shortcoming could be my pipeline uses 2 straight lines (left and right) to represent the steering direction. However, it is not suitable for the curving sections.
3. When using extrapolate/average method to get the full extent of lane, it is a little hard to tune the slope threshold value to an ideal value so that it can filter out the flying lines among all the endpoints we gathered.
4. The pipeline depends on the light contrast condition to some extent. When lane lines are in or even overlayed by shadows, these sections will not be easily detected by simply convering the image to grayscale. 

### 3. Suggested Improvements.
In the challenge section, I modified the pipeline to be more generalized for different size of images and videos and maske the quadrilateral region based on the proportion of the image.To improve the robustness for lighting contrast, images can be converted into HSV color other than RGB. To improve the robustness of quadrilateral masking, it might be worth thinking to set a random size region first and see if the lines detected by Hough Transform reach certain threshold. If not, updating the shape of region by increasing with a certain step value untill it fails and breaks when the region coordinates reach predefined maximum values. To reduce the visual effect of vibrating/flying lines, an algorithm can be developed to compare the slopes between consecutive frame and make sure changes are in expected interval, ±10%.

### Rubric
1. Does the pipeline for line identification take road images from a video as input and return an annotated video stream as output?
   <b>The output video is an annotated version of the input video.</b>
2. Has a pipeline been implemented roughly identify the left nad right lane lines with either line segments or solid lines?
   <b>In a rough sense, the left and right lane lines are accurately annotated throughout almost all of the video. Annotations can be segmented or solid lines.</b>

### Feedback
This pipeline chalks out straight lines, hence it works best on straight roads. Using it on curved roads and also on roads on a downhill or sometimes also on a uphill wouldn’t result in satisfactory results as it would best fit the curve with a straight line.

The shortcoming of the curved lane could be solved by using a quadratic fit, instead of a linear fit, where we’d have more coefficients and we could create the curved lane accordingly. The problem of ending one lane could be solved by creating a temporary parallel lane for the vanished lane allowing the car to change lanes until it finds well defined lanes. The problem of cracks on the roads leading to edges in the region of interest could be solved by creating a regions of interest which is a combination of offsetted trapezium, with parallel edges, one sitting inside and one outside. This would only keep the lanes in the region and as long as a lanes are defined, we’ll have our lines.

One improvement can be using a different color space. HSL will be much more efficient in finding the yellow lane line and in case of shadows.The HSL color mask in this sceneario performs better than the RGB because it is able to consistently filters smooth yellow pixels than RGB color mask, despite it sometimes picks up unwanted noises such as yellow road sign and the lawn on the right. However, these minor imperfections of HLS mask should not be a problem, as later we can apply region of interest to specifically crop the non-road regions.


### Parameter Explanation
<ul>
   <li><b>max_line_gap</b> that defines the maximum distance between segments that will be connected to a single line. </li>
   <li><b>min_line_len</b> that defines the minimum length of a line that will be created.
       Increasing min_line_lenand max_line_gap(~100 and above) for Hough Transform will make your lines longer and will have less number of breaks.(this will make the solid annotated line longer in the output)Increasing max_line_gap will allow points that are farther away from each other to be connected with a single line.
   </li><b>threshold</b>increasing(~ 50-60) will rule out the spurious lines.(defines the minimum number of intersections in a given grid cell that are required to choose a line.)</li>
   <li>Decreasing the <b>kernel-size</b> in the Gaussian Filter might also help, as this will remove the noise making the image less blurry.</li>
   <li>Consider using <b>rho value</b> of 2 ( rho, distance resolution of the Hough accumulator in pixels.)</li>
   </li>Removing lane shakiness: (averaging using previous frames) If we simply apply the image pipeline, the video feed has no prior knowledge of the frame before, and thus slight deviations are very obvious in the annotated output video. An easy fix is to average the current frame lines with the previous frame lines, and if one of the lanes isn’t computed properly, substitute the prior working lane line.So, in the next frame when a line is detected, it can again be averaged with the older working line.The detection of straight edges through Hough transform will induce some uncertainties because of the variations in the photograph conditions such as lighting, shadow, vibrations etc. This makes the calculations of the slopes and the end points fluctuate within a certain zone. In order to avoid this noise, a Kalman filter can also be used to smoothen out the fluctuations in the slope and end point estimation.</li>


### [CarND Term1 Starter Kit](https://github.com/udacity/CarND-Term1-Starter-Kit/blob/master/README.md) 
you should be good to go!   If not, you should install the starter kit to get started on this project. 

**Step 1:** Set up the [CarND Term1 Starter Kit](https://classroom.udacity.com/nanodegrees/nd013/parts/fbf77062-5703-404e-b60c-95b78b2f3f9e/modules/83ec35ee-1e02-48a5-bdb7-d244bd47c2dc/lessons/8c82408b-a217-4d09-b81d-1bda4c6380ef/concepts/4f1870e0-3849-43e4-b670-12e6f2d4b7a7) if you haven't already.

**Step 2:** Open the code in a Jupyter Notebook

You will complete the project code in a Jupyter notebook.  If you are unfamiliar with Jupyter Notebooks, check out <A HREF="https://www.packtpub.com/books/content/basics-jupyter-notebook-and-python" target="_blank">Cyrille Rossant's Basics of Jupyter Notebook and Python</A> to get started.

Jupyter is an Ipython notebook where you can run blocks of code and see results interactively.  All the code for this project is contained in a Jupyter notebook. To start Jupyter in your browser, use terminal to navigate to your project directory and then run the following command at the terminal prompt (be sure you've activated your Python 3 carnd-term1 environment as described in the [CarND Term1 Starter Kit](https://github.com/udacity/CarND-Term1-Starter-Kit/blob/master/README.md) installation instructions!):

`> jupyter notebook`

A browser window will appear showing the contents of the current directory.  Click on the file called "Finding Lane Line.ipynb".  Another browser window will appear displaying the notebook.  Follow the instructions in the notebook to complete the project.  

