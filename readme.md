# Q Learning for Navigating a 2-D grid
## Overview
[![Build Status](https://travis-ci.org/sudrag/Q-learning-for-2D-Occupancy-Grid.svg?branch=master)](https://travis-ci.org/sudrag/Q-learning-for-2D-Occupancy-Grid)
[![Coverage Status](https://coveralls.io/repos/github/sudrag/Q-learning-for-2D-Occupancy-Grid/badge.svg?branch=master)](https://coveralls.io/github/sudrag/Q-learning-for-2D-Occupancy-Grid?branch=master)
---
Navigating and path planning are integral components of mobile robotics with an aim to provide the robot a collision free path to its goal.It is vital for the robot to avoid collisions both dynamically by making use of the on-board sensors and also statically by initially choosing a path that is devoid of any collisions. A robot is required to be adaptive to its environment and execute this collision free path planning for any given map. This task becomes difficult for the path planner to mention the safe path to the robot for each and every environment. A more robust solution is to teach the robot the right way to navigate itself in a map through reinforcement learning.Reinforcement learning is essentially used to provide positive or negative rewards to actions taken by the robot when it is in a specific state such as being at rest , being in motion , being in collision etc. Reinforcement learning has the biggest advantage of being able to expand easily whenever the number of states and actions increases. We use Q learning method in this paper as it does not require to know the model of the entire systems and only requires labeled actions and rewards to master its environment. Although Q learning faces one slight disadvantage that the knowledge learned by the system is shallow and even though it can accommodate future changes it cannot predict them. We shall further discuss the robot, the learning method and the occupational grid to be used to incorporate these factors and apply a Q-learning algorithm successfully.

## Methodology

The methodology for this project follows the activity diagram depicted below:
![activi](https://github.com/sudrag/Q-learning-for-2D-Occupancy-Grid/blob/master/UML/revised/Activity.jpg)


The Q table is declared in such a way that the 50 by 50 grid is represented as 2500 rows. Each state in this Q table has 4 potential actions UP,DOWN,LEFT and RIGHT. The algorithm is optimized by running for a large number of trials where each time the start position is randomly chosen for a fixed goal node. The Q-learning algorithm has a 20% exploration policy where it will randomly chose an action at a given state as opposed to chosing the best action there.This allows for all states to be covered more evenly. The algorithm also uses a discounted future reward value of 0.8 where the actions that will eventually lead to the goal are also rewarded. Once the algorithm is completed for a large number of trials , the Q table is optimized and we can now set a start and goal position and the algorithm will output the path it takes. This path taken is then stored into a text file to be output into a plot showing both the path and the obstacles. Some examples are shown below

![ex1](https://github.com/sudrag/Q-learning-for-2D-Occupancy-Grid/blob/master/images/Example%202.png)
![ex2](https://github.com/sudrag/Q-learning-for-2D-Occupancy-Grid/blob/master/images/Example%203.png)
## License
This project uses the MIT license as shown below:

```
MIT License

Copyright (c) 2017 Sudarshan Raghunathan

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
## Build

* To build:
```
git clone https://github.com/sudrag/Q-learning-for-2D-Occupancy-Grid.git
cd <git_workspace>
mkdir build
cd build
cmake ..
make
```

## Dependancies

This project uses GNUPLOT , a plotting function in C++ to show the final path chosen by the robot between two points. The process for installing this dependancy is:

```
* cd <git_workspace>
* git clone https://github.com/tttamaki/gnuplot-cpp
```
The directories for identifying the functions have been added to the CMakeList

## Demo and Testing

* To run demo
```
cd <git_worksapce>
cd build
./app/shell-app
```

* To run tests
```
cd<git_workspace>
cd build
./test/cpp-test
```

## Doxygen Documentation
To generate Doxygen Documentation in HTML and LaTEX, follow the next steps:

```
cd <git_workspace>
mkdir <documentation_folder>
cd <documentation_folder>
doxygen -g <config_file_name>
```
Make the following changes inside the configuration file
```
PROJECT_NAME = 'your project name'
INPUT = ../app ../include ../test
```
The doxygen documents can be generated in the current directory (unless output directory is modified in the config file) using:
```
doxygen <config_file_name>
```
To view the documents easily, access `classQclass.html`, `Learn_8cpp.html` and `app_2main_8cpp.html` with your browser.
For further information on the Doxygen Documentation: http://flcwiki.desy.de/How%20to%20document%20your%20code%20using%20doxygen


## Solo-Iterative Processes
This project was designed and developed using the SIP process. Tasks were organized after being identified and split up. The Product backlog,Iteration backlog , Time log and Defect log were recorded for each task and can be viewed in the link below:
https://docs.google.com/spreadsheets/d/1cnBrs8IrD_-zirHzKbtn1QO49DNuiES0Kdlatnw9SK8/edit?usp=sharing

* Iteration 1 involves the development of the Q learning algorithm which creates a Q table for all the state,action pairs and outputs a grid
* Iteration 2 involves the development of test cases, error debugging, code commenting and formatting 
