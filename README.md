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
<img src="Result/pid_controller.gif" width="600" alt="Result of pid controller" />
</div>
```

```

#### Detailed Video Link

<a href="https://www.youtube.com/watch?v=4a7EJNfv-Z4" target="_blank"> Youtube Link</a>

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


### Tuning Hyperparameters

* <b>Kp</b> - propotional gain, it proportionally increases the control signal for the same level of error and tends to cause the closed-loop system to respond more quickly, but also brings overshoot more.

* <b>Ki</b> - integral gain, it tends to reduce steady-state error. But A drawback of the integral term is that it can make the system more sluggish (and oscillatory) since when the error signal changes sign.

* <b>Kd</b> - direvative gain, it adds the ability to "anticipate" error. The control signal can become large if the error begins sloping upward by accumulation, even while the magnitude of the error is still relatively small. This anticipation tends to add damping to the system, thereby decreasing overshoot. 

To set up the initial assumptions, I first set random values for Kp, Ki, Kd and observe the changing trends of P_error, I_error, D_error. From the log, we observed that I_error keeps increasing because of accumulation of +=cte in range (0,200) and Kp starts from 0.7598 and changes from -3.5 to +3.5; and D_error barely changes from 0 to maximum -0.15. Take the maximum params, -3.5Kp+0.1Kd+200Ki, I want to keep the effect of I_error small, 200Ki=0.1--> Ki=0.0005; Kd=4.0 and Kp=1/7=0.143.



| Pid Gains Data         		|     Values	        					| 
|:---------------------:|:---------------------------------------------:| 
| Kp      		|  0.055   							| 
| Ki        |  0.0005 	       |
| Kd	     		|  3.5										  |



#### Reference
1. http://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID
