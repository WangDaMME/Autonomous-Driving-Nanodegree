# :checkered_flag: Project 7: PID Controller

[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Key Concepts: PID Controls Implementation, Twiddle Algorithm.

<hr>

### Overview

In this project, I implemented a PID controller in C++ to tune the PID hyperparameters to maneuver the vehicle around the track!
The simulator will provide you the cross track error (CTE) and the velocity (mph) in order to compute the appropriate steering angle.
One more thing. The speed limit has been increased from 30 mph to 100 mph. Get ready to channel your inner Vin Diesel and try to drive SAFELY as fast as possible! NOTE: you don't have to meet a minimum speed to pass.

### Results
#### PID Controller Implementation
```
<div align="center">
<img src="Result/Path_Planning.PNG" width="600" alt="Combined Image" />
</div>
```

```

#### Detailed Video Link

<a href="https://www.youtube.com/watch?v=NSgxW-0lui8" target="_blank"> Youtube Link</a>

### Project Rubrics

```
(Will be filled in after the Submission Review)



### Prerequisites

####   Simulator.
You can download the Term3 Simulator which contains the Path Planning Project from the [releases tab (https://github.com/udacity/self-driving-car-sim/releases/tag/T3_v1.2).  

To run the simulator on Mac/Linux, first make the binary file executable with the following command:
```shell
sudo chmod u+x {simulator_file_name}
```

### Dependencies

Dependencies
cmake >= 3.5
All OSes: click here for installation instructions
make >= 4.1(mac, linux), 3.81(Windows)
Linux: make is installed by default on most Linux distros
Mac: install Xcode command line tools to get make
Windows: Click here for installation instructions
gcc/g++ >= 5.4
Linux: gcc / g++ is installed by default on most Linux distros
Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
Windows: recommend using MinGW
uWebSockets
Run either ./install-mac.sh or ./install-ubuntu.sh.
If you install from source, checkout to commit e94b6e1, i.e.
git clone https://github.com/uWebSockets/uWebSockets 
cd uWebSockets
git checkout e94b6e1
Some function signatures have changed in v0.14.x. See this PR for more details.
Simulator. You can download these from the project intro page in the classroom.
Fellow students have put together a guide to Windows set-up for the project here if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this PR.


### Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 


### Code Description

