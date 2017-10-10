#include "Qlearn-class.hpp"
#include <stdlib.h>// NOLINT
#include <iostream>

using std::cout;
using std::endl;


int Qtable::createGrid(int grid [5][5]){
	for(int i=3;i<5;i++){
		for(int j=2;j<5;j++){
			grid[i][j]=1;
		}
	}
	return grid;
}


/**
 * @brief Finds current state based on x,y position
 * @param int x and int y are grid positions
 * @return Current state
 */
int Qtable::findState(int x, int y) {  // based on sensor value combination find state
  int state = 0;
  state=x*y+y;
  return state;
}

/**
 * @brief Determines the action to be performed next
 * @param int state.Current state of the robot.
 * @return Decided action of the possible 4 choices (up,down,left and right)
 */
int Qtable::detAction(int state) {
  int action;
  int chosenAction;
  int temp = rand() % 100;
  if (temp > 65) {
    int randAction=rand() % 4;
    chosenAction=randAction;
  } else {
    int maxQ=-10000;
    for (int i = 0; i < 4; i++) {
      if (Q[state][i] > maxQ) {
        maxQ=Q[state][i];
        chosenAction = i;
      }
    }
  }
  action=chosenAction;
  return action;
}

/**
 * @brief Assigns a reward based on action chosen
 * @param int previous action,int x,int y, int grid[size][size]
 * @return Returns assigned reward
 */
int Qtable::rewardfunc(int prevAction,int x,int y,int grid[size][size]) {
	//Add goal condition here
  int reward;
  if(prevAction==0){
	  if(x+1<=size)
    reward=grid[x+1][y]*-100-1;
	  else
		  reward=-100;
  }
  if(prevAction==1){
	  if(x-1>=0)
	  reward=grid[x-1][y]*-100-1;
  }
  if(prevAction==2){
	  if(y+1<=size)
     reward=grid[x][y+1]*-100-1;
	  else
		  reward=-100;
  }
  if(prevAction==3){
	  if(y-1>=0)
     reward=grid[x][y-1]*-100-1;
	  else
		  reward=-100;
  }
  return reward;
}

/**
 * @brief Finds the highest reward considering future rewards
 * @param int state is the current state of the robot.
 * @return Max Q table value for the state
 */
int Qtable::futurereward(int state) {
  int currentMax = -100000;  // initiate var to keep track of max

  for (int i = 0; i != 4; i++) {  // cycle through every action
    if (Q[state][i] > currentMax)  // if state action pair Q value greater than current Q value
      currentMax = Q[state][i];  // set new max Q value
  }
  return currentMax;
}

/**
 * @brief Updates Q table based on action taken for given grid position
 * @param int previous state, previous action, state, x,y
 * @return none
 */
void Qtable::Qupdate(int prevAction, int prevState, int x,int y, int state) {
  Qtable::learn_rate=0.5;  // variables for update equation
  Qtable::disc_rew=0.8;
  int reward=0;
  //int reward = rewardfunc(prevAction,x,y,grid[size][size]);
    Q[prevState][prevAction] = Q[prevState][prevAction] + learn_rate * (reward)
        - Q[prevState][prevAction];
  Q[prevState][prevAction]=Q[prevState][prevAction]+ learn_rate * (reward + (disc_rew * futurereward(state))
                  - Q[prevState][prevAction]);
}

void Qtable::Train() {

}

void Qtable::execute() {

}
