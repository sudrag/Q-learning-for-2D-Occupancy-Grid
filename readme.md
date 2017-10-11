# Overview
[![Build Status](https://travis-ci.org/sudrag/Q-learning-for-2D-Occupancy-Grid.svg?branch=master)](https://travis-ci.org/sudrag/Q-learning-for-2D-Occupancy-Grid)
[![Coverage Status](https://coveralls.io/repos/github/sudrag/Q-learning-for-2D-Occupancy-Grid/badge.svg?branch=master)](https://coveralls.io/github/sudrag/Q-learning-for-2D-Occupancy-Grid?branch=master)
---
Navigating and path planning are integral components of mobile robotics with an aim to provide the robot a collision free path to its goal.It is vital for the robot to avoid collisions both dynamically by making use of the on-board sensors and also statically by initially choosing a path that is devoid of any collisions. A robot is required to be adaptive to its environment and execute this collision free path planning for any given map. This task becomes difficult for the path planner to mention the safe path to the robot for each and every environment. A more robust solution is to teach the robot the right way to navigate itself in a map through reinforcement learning.Reinforcement learning is essentially used to provide positive or negative rewards to actions taken by the robot when it is in a specific state such as being at rest , being in motion , being in collision etc. Reinforcement learning has the biggest advantage of being able to expand easily whenever the number of states and actions increases. We use Q learning method in this paper as it does not require to know the model of the entire systems and only requires labeled actions and rewards to master its environment. Although Q learning faces one slight disadvantage that the knowledge learned by the system is shallow and even though it can accommodate future changes it cannot predict them. We shall further discuss the robot, the learning method and the occupational grid to be used to incorporate these factors and apply a Q-learning algorithm successfully.

# How to Build
```
$ git clone --recursive https://github.com/sudrag/Q-learning-for-2D-Occupancy-Grid.git
cd Q-learning-for-2D-Occupancy-Grid
mkdir build
cd build
cmake ..
make
```
# License
This project uses the MIT license as shown below:

```
MIT License

Copyright (c) 2017 Sudarshan Raghunathan

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

# Dependancies

This project uses GNUPLOT , a plotting function in C++ to show the final path chosen by the robot between two points. The project already includes the required header file (in include folder) which can be downloaded from:
[GNUPLOT](http://www.gnuplot.info/download.html) 
*Download from SourceForge in the link
*Extract files on your computer
*Include the headerfile *gnuplot_i.hpp* in your project workspace

All these steps have already been performed for this repository

# Solo-Iterative Processes
This project was designed and developed using the SIP process. Tasks were organized after being identified and split up. The Product backlog,Iteration backlog , Time log and Defect log were recorded for each task and can be viewed in the link below:
https://docs.google.com/spreadsheets/d/1cnBrs8IrD_-zirHzKbtn1QO49DNuiES0Kdlatnw9SK8/edit?usp=sharing

*Iteration 1 involves the development of the Q learning algorithm which creates a Q table for all the state,action pairs and outputs a grid
*Iteration 2 involves the development of test cases, error debugging, code commenting and formatting 