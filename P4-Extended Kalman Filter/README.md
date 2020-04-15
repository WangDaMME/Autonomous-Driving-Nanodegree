# :checkered_flag: Project 4: Extended Kalman Filter
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Key Concepts: Sensor Fusion, Extended Kalman Filter, Tracking

<div align="center">
<img src="result_gif/Algorithm_Map.PNG" width="600" alt="Combined Image" />
<center> Process Flow </center>
  
Imagine you are in a car equipped with sensors on the outside. The car sensors can detect objects moving around: for example, the sensors might detect a pedestrian, as described in the video, or even a bicycle. For variety, let's step through the Kalman Filter algorithm using the bicycle example.

The Kalman Filter algorithm will go through the following steps:

first measurement - the filter will receive initial measurements of the bicycle's position relative to the car. These measurements will come from a radar or lidar sensor.
initialize state and covariance matrices - the filter will initialize the bicycle's position based on the first measurement.
then the car will receive another sensor measurement after a time period \Delta{t}Δt.
predict - the algorithm will predict where the bicycle will be after time \Delta{t}Δt. One basic way to predict the bicycle location after \Delta{t}Δt is to assume the bicycle's velocity is constant; thus the bicycle will have moved velocity * \Delta{t}Δt. In the extended Kalman filter lesson, we will assume the velocity is constant.
update - the filter compares the "predicted" location with what the sensor measurement says. The predicted location and the measured location are combined to give an updated location. The Kalman filter will put more weight on either the predicted location or the measured location depending on the uncertainty of each value.
then the car will receive another sensor measurement after a time period \Delta{t}Δt. The algorithm then does another predict and update step.
</div>

<hr>

### Overview 

In this project, I implemented the Extended Kalman Filter algorithm to estimate and track the state of a moving object of interest, ie. a bicyle which travels around the vehicle with noisy lidar and radar measurements. To evaluate the performance of tracking, I calculated the RMSE (root mean square erro) value of each state and make sure that are lower than the tolerance outlined in the project rubric. 

### Code Structure
The c++ src code covers 3 main steps for programming a Kalman Filter:

<ul>
  <li> <b>intializing</b> - intializing Kalman filter variables </li>
  <li> <b>Motion Prediction</b> - predicting where our object is going to be after a time step, Δt </li>
  <li> <b>Measurement Update</b> - updating where our object is based on sensor measurements </li>
</ul>


    |- src                             # source code folder
    |
    │   ├── main.cpp                   # receive data measurement, calls Kalman Filter func, calls RMSE func
    │     
    │   ├── FunctionEKF.cpp            # initialize the filter, calls Prediction func, calls Update func, via ekf_ instanse
    │
    │   ├── kalman_filter.cpp          # define Prediction func, Update func for lidar, Update func for radar
    │
    │   ├── tools.cpp                  # define RMSE func, Jacobian func to linearize radar measurements
    │
    │   ├── measurement_package.h      # define raw measurement data types
    │
    |- data
    │   ├── obj_pose-laser-radar-synthetic-input.txt      
    |   # R(Radar):  raw measurement data types sensor_type, rho_measured, phi_measured, rhodot_measured, timestamp, x_groundtruth, y_groundtruth, vxgroundtruth, vy_groundtruth, yaw_groundtruth, yawrate_groundtruth.
    |   # L(Lidar):  sensor_type, x_measured, y_measured, timestamp, x_groundtruth, y_groundtruth, vx_groundtruth, vy_groundtruth, yaw_groundtruth, yawrate_groundtruth.
    
    
This repository includes two files that can be used to set up and install [uWebSocketIO](https://github.com/uWebSockets/uWebSockets) for either Linux or Mac systems. For windows you can use either Docker, VMware, or even [Windows 10 Bash on Ubuntu](https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/) to install uWebSocketIO. Please see the uWebSocketIO Starter Guide page in the classroom within the EKF Project lesson for the required version and installation scripts.

Once the install for uWebSocketIO is complete, the main program can be built and run by doing the following from the project top directory.

1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./ExtendedKF

Tips for setting up your environment can be found in the classroom lesson for this project.

Note that the programs that need to be written to accomplish the project are src/FusionEKF.cpp, src/FusionEKF.h, kalman_filter.cpp, kalman_filter.h, tools.cpp, and tools.h

The program main.cpp has already been filled out, but feel free to modify it.

Here is the main protocol that main.cpp uses for uWebSocketIO in communicating with the simulator.


INPUT: values provided by the simulator to the c++ program

["sensor_measurement"] => the measurement that the simulator observed (either lidar or radar)


OUTPUT: values provided by the c++ program to the simulator

["estimate_x"] <= kalman filter estimated position x
["estimate_y"] <= kalman filter estimated position y
["rmse_x"]
["rmse_y"]
["rmse_vx"]
["rmse_vy"]

---

## Other Important Dependencies

* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make` 
   * On windows, you may need to run: `cmake .. -G "Unix Makefiles" && make`
4. Run it: `./ExtendedKF `

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## File Structure


## Generating Additional Data

This is optional!

If you'd like to generate your own radar and lidar data, see the
[utilities repo](https://github.com/udacity/CarND-Mercedes-SF-Utilities) for
Matlab scripts that can generate additional data.

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project resources page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/382ebfd6-1d55-4487-84a5-b6a5a4ba1e47)
for instructions and the project rubric.

## Hints and Tips!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.
* Students have reported rapid expansion of log files when using the term 2 simulator.  This appears to be associated with not being connected to uWebSockets.  If this does occur,  please make sure you are conneted to uWebSockets. The following workaround may also be effective at preventing large log files.

    + create an empty log file
    + remove write permissions so that the simulator can't write to log
 * Please note that the ```Eigen``` library does not initialize ```VectorXd``` or ```MatrixXd``` objects with zeros upon creation.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to ensure
that students don't feel pressured to use one IDE or another.

However! We'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Regardless of the IDE used, every submitted project must
still be compilable with cmake and make.

## Result Description

Radar measurements are blue circles with an arrow pointing in the direction of the observed angle, and estimation markers are green triangles. The video below shows what the simulator looks like when a c++ script is using its Kalman filter to track the object. The simulator provides the script the measured data (either lidar or radar), and the script feeds back the measured estimation marker, and RMSE values from its Kalman fil

<div align="center">
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/P4-Extended%20Kalman%20Filter/result_gif/Data1.gif.gif" width="480" height="320">
</div>


<div align="center">
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/P4-Extended%20Kalman%20Filter/result_gif/Data2.gif.gif" width="480" height="320">
</div>
