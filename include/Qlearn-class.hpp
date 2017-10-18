/**
 * @file        : Qlearn-class.hpp
 * @author      : Sudarshan Raghunathan
 * @copyright   : 2017 Sudarshan Raghunathan
 * @brief       : Qlearning class members
 */
#ifndef QCLASS_H_ // NOLINT
#define QCLASS_H_

// Define Q Learning Class which contains all variables for Q learning
// There are as many states as grid cells and 4 actions(up,down,left,right)
/**
 *@class Qclass
 */
class Qclass {
public:
  ~Qclass();
  int state;
  /**
  *@name State
  *@var state
  */
  int grid[50][50] = {};
  int action;
  double Q[2500][4] = {};
  bool restart = false;
  int goal_x = 3;
  int goal_y = 0;
  double learn_rate = 0.5;
  double disc_rew = 0.8;
  /**
   * @brief Creates the grid with obstacles in it.Obstacle added to .txt file to plot
   */
  void createGrid();
  /**
   * @brief Finds current state based on x,y position
   * @param x  grid position x
   * @param y  grid position y
   * @return state current
   */
  int findState(int x, int y);
  /**
   * @brief Determines the action to be performed next
   * @param state -Current state of the robot.
   * @return action decided out of the possible 4 choices (up,down,left and right)
   */
  int detAction(int state);
  /**
   * @brief Assigns a reward based on action chosen
   *@param lastAction
   *@param x
   *@param y
   * @return reward assigned
   */
  int rewardfunc(int prevAction, int x, int y);
  /**
   * @brief Finds the highest reward considering future rewards
   *@param new_state is the next state of the robot for action taken in current state
   * @return currMax table value for the state
   */
  int futurereward(int state);
  /**
   * @brief Updates Q table based on action taken for given grid position
   *@param lastState
   *@param lastAction
   *@param x
   *@param y
   *@param new_state
   */
  void Qupdate(int prevAction, int prevState, int x, int y, int state);
  /**
   * @brief Performs the training for the Q learning algorithm for a large number of trials
   * @return 0 when training is complete
   */
  int Train();
  /**
   * @brief Finds the path from start to goal node using optimized Q table
   * @return 0 when goal node is reached
   */
  int execute();
  /**
   * @brief Plots the path and obstacles stored in txt files
   * @return 0 when path plotting is complete
   */
  int plot();
};

#endif /* QCLASS_H_ */ // NOLINT
