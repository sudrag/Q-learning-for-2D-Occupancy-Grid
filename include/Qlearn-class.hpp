/**
 * @fileName    : Qlearn-class.hpp
 * @author      : Sudarshan Raghunathan
 * @copyright   : 2017 Sudarshan Raghunathan
 * @section DESCRIPTION
 * Qlearning class members
 */
#ifndef QCLASS_H_ // NOLINT
#define QCLASS_H_

/* @brief: Define Q Learning Class which contains all variables for Q learning
 * There are as many states as grid cells and 4 actions(up,down,left,right)
 */
class Qclass {
 public:
  ~Qclass();
  int state;
  int grid[50][50] = { };
  int action;
  double Q[2500][4] = { };
  bool restart = false;
  int goal_x = 47;
  int goal_y = 47;
  double learn_rate = 0.5;
  double disc_rew = 0.8;
  void createGrid();
  int findState(int x, int y);
  int detAction(int state);
  int rewardfunc(int prevAction, int x, int y);
  int futurereward(int state);
  void Qupdate(int prevAction, int prevState, int x, int y, int state);
  int Train();
  int execute();
  int plot();
};

#endif /* QCLASS_H_ */ // NOLINT
