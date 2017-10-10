
#ifndef QCLASS_H_ // NOLINT
#define QCLASS_H_

/* @brief: Define Q Learning Class which contains all variables for Q learning
 * There are as many states as grid cells and 4 actions(up,down,left,right)
 */
class Qtable {  // define class
 public:
  int state;
  int size=5;
  int grid [size][size]={};
  int rewardmatrix[size][size]={};
  int action;
  int Q[size*size][4]={ };
  double learn_rate=0.5;
  double disc_rew=0.8;
  int createGrid(int grid[size][size]);
  int findState(int x,int y);
  int detAction(int state);
  int rewardfunc(int prevAction,int x,int y,int grid[size][size]);
  int futurereward(int state);
  void Qupdate(int prevAction, int prevState,int x,int y, int state);
  void Train();
  void execute();
};



#endif /* QCLASS_H_ */ // NOLINT
