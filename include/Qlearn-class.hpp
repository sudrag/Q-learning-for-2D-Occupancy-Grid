
#ifndef QCLASS_H_ // NOLINT
#define QCLASS_H_

/* @brief: Define Q Learning Class which contains all variables for Q learning
 * There are as many states as grid cells and 4 actions(up,down,left,right)
 */
class Qclass {  // define class
 public:
  int state;
  int grid [5][5]={};
  int action;
  int Q[25][4]={ };
  bool restart= false;
  int goal_x =1;
  int goal_y =1;
  double learn_rate=0.5;
  double disc_rew=0.8;
  void createGrid(int grid[5][5]);
  int findState(int x,int y);
  int findpos(int lastAction,int prev_x,int prev_y);
  int detAction(int state);
  int rewardfunc(int prevAction,int x,int y,bool restart);
  int futurereward(int state);
  void Qupdate(int prevAction, int prevState,int x,int y, int state, bool restart);
  void Train();
  void execute();
};



#endif /* QCLASS_H_ */ // NOLINT
