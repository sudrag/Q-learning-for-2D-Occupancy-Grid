/**
 * @fileName    : Learn.cpp
 * @author      : Sudarshan Raghunathan
 * @copyright   : 2017 Sudarshan Raghunathan
 * @section DESCRIPTION
 * Qlearning class member function declarations
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Qlearn-class.hpp"
#include "../gnuplot-cpp/gnuplot_i.hpp"

/**
 * @brief Destructor for the class
 */
Qclass::~Qclass() {
}
/**
 * @brief Creates the grid with obstacles in it.Obstacle added to .txt file to plot
 * @param none
 * @return none
 */

void Qclass::createGrid() {
  for (int i = 30; i < 46; i++) {
    for (int j = 40; j < 46; j++) {
      grid[i][j] = 1;
    }
  }
  for (int i = 10; i < 21; i++) {
    for (int j = 10; j < 31; j++) {
      grid[i][j] = 1;
    }
  }
  std::ofstream outfile;
  outfile.open("Obstacles1.txt", std::ios::out | std::ios::trunc);
  outfile.precision(6);
  outfile << std::fixed << 30 << "   " << std::fixed << 40;
  outfile << std::endl;
  outfile << std::fixed << 30 << "   " << std::fixed << 45;
  outfile << std::endl;
  outfile << std::fixed << 45 << "   " << std::fixed << 45;
  outfile << std::endl;
  outfile << std::fixed << 45 << "   " << std::fixed << 40;
  outfile << std::endl;
  outfile << std::fixed << 30 << "   " << std::fixed << 40;
  outfile.close();
  outfile.open("Obstacles2.txt", std::ios::out | std::ios::trunc);
  outfile.precision(6);
  outfile << std::fixed << 10 << "   " << std::fixed << 10;
  outfile << std::endl;
  outfile << std::fixed << 10 << "   " << std::fixed << 30;
  outfile << std::endl;
  outfile << std::fixed << 20 << "   " << std::fixed << 30;
  outfile << std::endl;
  outfile << std::fixed << 20 << "   " << std::fixed << 10;
  outfile << std::endl;
  outfile << std::fixed << 10 << "   " << std::fixed << 10;
  outfile.close();
}

/**
 * @brief Finds current state based on x,y position
 * @param int x and int y are grid positions
 * @return Current state
 */
int Qclass::findState(int x, int y) {
  int state = 0;
  state = x * 50 + y;
  return state;
}

/**
 * @brief Determines the action to be performed next
 * @param int state.Current state of the robot.
 * @return Decided action of the possible 4 choices (up,down,left and right)
 */
int Qclass::detAction(int state) {
  int action;
  int chosenAction;
  int temp = rand() % 100;
  if (temp > 80) {   // Randomly explores for an action 20% of the time
    int randAction = rand() % 4;
    chosenAction = randAction;
  } else {
    double maxQ = -10000;
    for (int i = 0; i < 4; i++) {
      if (Q[state][i] >= maxQ) {
        maxQ = Q[state][i];
        chosenAction = i;
      }
    }
  }
  action = chosenAction;
  return action;
}

/**
 * @brief Assigns a reward based on action chosen
 * @param int previous action,int x,int y
 * @return Returns assigned reward
 */
int Qclass::rewardfunc(int lastAction, int x, int y) {
  int reward;
  if (lastAction == 0) {
    // High positive reward for reaching the goal state
    if (x + 1 == goal_x && y == goal_y) {
      reward = 1000;
    } else {
      // High negative reward for exceeding map boundaries
      // High negative reward when obstacle is present
      if (x + 1 <= 49) {
        reward = grid[x + 1][y] * -10000 - 50;
      } else {
        reward = -10000;
        restart = true;
      }
      if (grid[x + 1][y] == 1) {
        restart = true;
      }
    }
  }
  if (lastAction == 1) {
    if (x - 1 == goal_x && y == goal_y) {
      reward = 1000;
    } else {
      if (x - 1 >= 0) {
        reward = grid[x - 1][y] * -10000 - 50;
      } else {
        reward = -10000;
        restart = true;
      }
      if (grid[x - 1][y] == 1) {
        restart = true;
      }
    }
  }
  if (lastAction == 2) {
    if (x == goal_x && y + 1 == goal_y) {
      reward = 1000;
    } else {
      if (y + 1 <= 49) {
        reward = grid[x][y + 1] * -10000 - 50;
      } else {
        reward = -10000;
        restart = true;
      }
      if (grid[x][y + 1] == 1) {
        restart = true;
      }
    }
  }
  if (lastAction == 3) {
    if (x == goal_x && y - 1 == goal_y) {
      reward = 1000;
    } else {
      if (y - 1 >= 0) {
        reward = grid[x][y - 1] * -10000 - 50;
      } else {
        reward = -10000;
        restart = true;
      }
      if (grid[x][y - 1] == 1) {
        restart = true;
      }
    }
  }
  return reward;
}

/**
 * @brief Finds the highest reward considering future rewards
 * @param int new state is the next state of the robot for action taken in current state
 * @return Max Q table value for the state
 */
int Qclass::futurereward(int new_state) {
  double currMax = -100000;
  if (new_state > 2499) {
    currMax = -100000;
  } else {   // Finds future reward benefits for state,action pair
    for (int i = 0; i < 4; i++) {
      if (Q[new_state][i] > currMax) {
        currMax = Q[new_state][i];
      }
    }
  }
  return currMax;
}

/**
 * @brief Updates Q table based on action taken for given grid position
 * @param int lastState, lastAction,x,y, new_state
 * @return none
 */
void Qclass::Qupdate(int lastAction, int lastState, int x, int y,
                     int new_state) {
  Qclass::learn_rate = 0.5;
  Qclass::disc_rew = 0.8;
  int reward = Qclass::rewardfunc(lastAction, x, y);
  if (restart == true) {
    // Future Reward not taken into account in case of collisions
    Q[lastState][lastAction] = Q[lastState][lastAction] + learn_rate * (reward)
        - Q[lastState][lastAction];
  } else {
    Q[lastState][lastAction] = Q[lastState][lastAction]
        + learn_rate
            * (reward + (disc_rew * futurereward(new_state))
                - Q[lastState][lastAction]);
  }
}
/**
 * @brief Performs the training for the Q learning algorithm for a large number of trials
 * @param none
 * @return 0 when training is complete
 */

int Qclass::Train() {
  Qclass::createGrid();
  int initialTrial = 1;
  int new_x = 0;
  int action = 0;
  int new_y = 0;
  int new_state = 0;
  int start_x = rand() % 50;
  int start_y = rand() % 50;
  int goal_state = findState(goal_x, goal_y);
  if (grid[start_x][start_y] == 1) {
    while (grid[start_x][start_y] == 1) {
      start_x = rand() % 50;
      start_y = rand() % 50;
    }
  }
  int prev_x = start_x;
  int prev_y = start_y;
  int state = findState(start_x, start_y);
  for (int k = 0; k < 50000; k++) {
    int lastState = 0;
    int lastAction = 0;
    while (lastState != goal_state) {
      // Skips this loop for first run as there are no previous nodes
      if (initialTrial == 0) {
        if (lastAction == 0) {
          new_x = prev_x + 1;
          new_y = prev_y;
        }
        if (lastAction == 1) {
          new_x = prev_x - 1;
          new_y = prev_y;
        }
        if (lastAction == 2) {
          new_x = prev_x;
          new_y = prev_y + 1;
        }
        if (lastAction == 3) {
          new_x = prev_x;
          new_y = prev_y - 1;
        }
        new_state = findState(new_x, new_y);
        Qupdate(lastAction, lastState, prev_x, prev_y, new_state);
        prev_x = new_x;
        prev_y = new_y;
        state = findState(prev_x, prev_y);
      }
      action = detAction(state);
      lastState = state;
      lastAction = action;
      initialTrial = 0;
      // Reinitialize all the training data whenever a collision occurs
      if (restart == true) {
        restart = false;
        initialTrial = 1;
        int start_x = rand() % 50;
        int start_y = rand() % 50;
        if (grid[start_x][start_y] == 1) {
          while (grid[start_x][start_y] == 1) {
            start_x = rand() % 50;
            start_y = rand() % 50;
          }
        }
        prev_x = start_x;
        prev_y = start_y;
        state = findState(start_x, start_y);
        action = detAction(state);
        lastState = state;
        lastAction = action;
      }
    }
  }
  // Outputting the Q table for 2500 states and 4 actions
  for (int i = 0; i < 2500; i++) {
    std::cout << i << "  ";
    for (int j = 0; j < 4; j++) {
      std::cout << Q[i][j] << "  ";
    }
    std::cout << std::endl;
  }
  return 0;
}
/**
 * @brief Finds the path from start to goal node using optimized Q table
 * @param none
 * @return 0 when goal node is reached
 */

int Qclass::execute() {   // Executes the learned algorithm for given start
  int start_x = 45;
  int start_y = 15;
  int last_state = 5000;
  double max = -10000;
  int action = 0;
  int goal_state = findState(goal_x, goal_y);
  std::ofstream outfile;
  outfile.open("Co_ordinates.txt", std::ios::out | std::ios::trunc);
  std::cout << "The path followed by the robot is:" << std::endl;
  outfile.precision(6);
  while (last_state != goal_state) {
    int start_state;
    std::cout << start_x << "," << start_y << std::endl;
    outfile << std::fixed << start_x << "   " << std::fixed << start_y;
    outfile << std::endl;
    start_state = findState(start_x, start_y);
    for (int i = 0; i < 4; i++) {
      if (Q[start_state][i] >= max) {
        max = Q[start_state][i];
        action = i;
      }
    }
    Q[start_state][action] = -1000;
    if (action == 0) {
      start_x = start_x + 1;
    }
    if (action == 1) {
      start_x = start_x - 1;
    }
    if (action == 2) {
      start_y = start_y + 1;
    }
    if (action == 3) {
      start_y = start_y - 1;
    }
    last_state = findState(start_x, start_y);
    max = -10000;
  }
  std::cout << goal_x << "," << goal_y;
  outfile << std::fixed << goal_x << "   " << std::fixed << goal_y;
  outfile.close();
  return 0;
}
/**
 * @brief Plots the path and obstacles stored in txt files
 * @param none
 * @return 0 when path plotting is complete
 */

int Qclass::plot() {
  try {
    Gnuplot g1("lines");
    // Plots points present in Text files
    g1.set_xrange(-10, 60);
    g1.set_yrange(-10, 60);
    g1.plotfile_xy("Co_ordinates.txt", 1, 2, "Path");
    g1.plotfile_xy("Obstacles1.txt", 1, 2, "Obstacles");
    g1.plotfile_xy("Obstacles2.txt", 1, 2, "Obstacles");

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    std::cout << std::endl << "Press ENTER to continue..." << std::endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
  } catch (GnuplotException& ge) {
    // std::cout << ge.what() << std::endl;
  }
  return 0;
}

