# :checkered_flag: Project 5: Kidnapped Vehicle Localization using Particle Filters
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Key Concepts: Localization, Particle Filters, Tracking


# Overview
The robot has been kidnapped and transported to a new location! Luckily it has a map of this location, a (noisy) GPS estimate of its initial location, and lots of (noisy) sensor and control data.

In this project, I implemented a 2 dimensional particle filter algorithm in C++ to localize a moving vehicle. The particle filter is given a map and some initial localization information (analogous to what a GPS would provide). At each time step the filter will also get observation and control data, and calculating the errors of [x, y, YAW_R]


<b>Algorithm Flowchart</b>

The flowchart below represents the steps of the particle filter algorithm as well as its inputs.

<div align="center">
<img src="Result/particle_filter_algorithm.PNG" width="600" alt="Combined Image" />
</div>

<b>Psuedo Code Steps</b>

This is an outline of steps you will need to take with your code in order to implement a particle filter for localizing an autonomous vehicle. The pseudo code steps correspond to the steps in the algorithm flow chart, initialization, prediction, particle weight updates, and wheel resampling. 

<div align="center">
<img src="Result/particle_filter_stepss.PNG" width="600" alt="Combined Image" />
</div>

### Code Structure
The directory structure of this repository is as follows:

intializing - intializing Kalman filter variables
Motion Prediction - predicting where our object is going to be after a time step, Δt
Measurement Update - updating where our object is based on sensor measurements

# Implementing the Particle Filter
The directory structure of this repository is as follows:




The only file you should modify is `particle_filter.cpp` in the `src` directory. The file contains the scaffolding of a `ParticleFilter` class and some associated methods. Read through the code, the comments, and the header file `particle_filter.h` to get a sense for what this code is expected to do.

If you are interested, take a look at `src/main.cpp` as well. This file contains the code that will actually be running your particle filter and calling the associated methods.

## Inputs to the Particle Filter
You can find the inputs to the particle filter in the `data` directory.

#### The Map*
`map_data.txt` includes the position of landmarks (in meters) on an arbitrary Cartesian coordinate system. Each row has three columns
1. x position
2. y position
3. landmark id

### All other data the simulator provides, such as observations and controls.

> * Map data provided by 3D Mapping Solutions GmbH.

## Success Criteria
If your particle filter passes the current grading code in the simulator (you can make sure you have the current version at any time by doing a `git pull`), then you should pass!

The things the grading code is looking for are:


1. **Accuracy**: your particle filter should localize vehicle position and yaw to within the values specified in the parameters `max_translation_error` and `max_yaw_error` in `src/main.cpp`.

2. **Performance**: your particle filter should complete execution within the time of 100 seconds.

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).


```
root
|   build.sh
|   clean.sh
|   CMakeLists.txt
|   README.md
|   run.sh
|
|___data
|   |   
|   |   map_data.txt
|   
|   
|___src
    |   helper_functions.h
    |   main.cpp
    |   map.h
    |   particle_filter.cpp
    |   particle_filter.h
```    
    

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
    


### Result
The Term 2 Simulator includes a graphical version of the Kidnapped Vehicle Project. Running the simulator you can see the path that the car drives along with all of its landmark measurements. Included in the Kidnapped Vehicle project Github repository are program files that allow you to set up and run c++ uWebSocketIO, which is used to communicate with the simulator. The simulator provides the script for the noisy position data, vehicle controls, and noisy observations. The script feeds back the best particle state.

The simulator can also display the best particle's sensed positions, along with the corresponding map ID associations. This can be extremely helpful to make sure transition and association calculations were done correctly.

Below is a video of what it looks like when the simulator successfully is able to track the car to a particle. <b>Notice that the green laser sensors from the car nearly overlap the blue laser sensors from the particle </b>, this means that the particle transition calculations were done correctly.

<div align="center">
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/P5-%20Kidnapped%20Vehicle%20Localization%20using%20Particle%20Filters/Result/Particle%20Filter.gif" width="480" height="320">
</div>

### Project Rubric
<div>
<img src="https://github.com/WangDaMME/Autonomous-Driving-Nanodegree/blob/master/P5-%20Kidnapped%20Vehicle%20Localization%20using%20Particle%20Filters/Result/Project_Rubric.PNG">

</div>


### Dependencies
Keep in mind that the minimum project dependency versions are:

cmake: 3.5

All OSes: click here for installation instructions

make: 4.1

Linux: make is installed by default on most Linux distros
Mac: install Xcode command line tools to get make
Windows: Click here for installation instructions

gcc/g++: 5.4

Linux: gcc / g++ is installed by default on most Linux distros
Mac: same deal as make - install Xcode command line tools
Windows: recommend using MinGW


### Running the Code
This project involves the Term 2 Simulator which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases)

This repository includes two files that can be used to set up and install uWebSocketIO for either Linux or Mac systems. For windows you can use either Docker, VMware, or even Windows 10 Bash on Ubuntu to install uWebSocketIO.

Once the install for uWebSocketIO is complete, the main program can be built and ran by doing the following from the project top directory.

1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./particle_filter

Alternatively some scripts have been included to streamline this process, these can be leveraged by executing the following in the top directory of the project:

1. ./clean.sh
2. ./build.sh
3. ./run.sh

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

Note that the programs that need to be written to accomplish the project are src/particle_filter.cpp, and particle_filter.h

Here is the main protocol that main.cpp uses for uWebSocketIO in communicating with the simulator.

INPUT: values provided by the simulator to the c++ program

// sense noisy position data from the simulator

["sense_x"]

["sense_y"]

["sense_theta"]

// get the previous velocity and yaw rate to predict the particle's transitioned state

["previous_velocity"]

["previous_yawrate"]

// receive noisy observation data from the simulator, in a respective list of x/y values

["sense_observations_x"]

["sense_observations_y"]


OUTPUT: values provided by the c++ program to the simulator

// best particle values used for calculating the error evaluation

["best_particle_x"]

["best_particle_y"]

["best_particle_theta"]

//Optional message data used for debugging particle's sensing and associations

// for respective (x,y) sensed positions ID label

["best_particle_associations"]

// for respective (x,y) sensed positions

["best_particle_sense_x"] <= list of sensed x positions

["best_particle_sense_y"] <= list of sensed y positions

