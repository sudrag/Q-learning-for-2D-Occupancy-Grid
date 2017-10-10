#include "Qlearn-class.hpp"
#include <stdlib.h>// NOLINT
#include <iostream>


void Qclass::createGrid(int grid[5][5]){
	for(int i=3;i<5;i++){
		for(int j=2;j<5;j++){
			grid[i][j]=1;
		}
	}
}


/**
 * @brief Finds current state based on x,y position
 * @param int x and int y are grid positions
 * @return Current state
 */
int Qclass::findState(int x, int y) {
  int state = 0;
  state=x*y+y;
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
int Qclass::rewardfunc(int lastAction,int x,int y,int grid[5][5]) {
	//Add goal condition here
  int reward;
  if(lastAction==0){
	  if(x+1<=5)
    reward=grid[x+1][y]*-100-1;
	  else
		  reward=-100;
  }
  if(lastAction==1){
	  if(x-1>=0)
	  reward=grid[x-1][y]*-100-1;
  }
  if(lastAction==2){
	  if(y+1<=5)
     reward=grid[x][y+1]*-100-1;
	  else
		  reward=-100;
  }
  if(lastAction==3){
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
int Qclass::futurereward(int state) {
  int currMax = -100000;

  for (int i = 0; i != 4; i++) {
    if (Q[state][i] > currMax)
      currMax = Q[state][i];
  }
  return currMax;
}

/**
 * @brief Updates Q table based on action taken for given grid position
 * @param int previous state, previous action, state, x,y
 * @return none
 */
void Qclass::Qupdate(int lastAction, int lastState, int x,int y, int state) {
  Qclass::learn_rate=0.5;  // variables for update equation
  Qclass::disc_rew=0.8;
  int reward=0;
  //int reward = rewardfunc(lastAction,x,y,grid[size][size]);
    Q[lastState][lastAction] = Q[lastState][lastAction] + learn_rate * (reward)
        - Q[lastState][lastAction];
  Q[lastState][lastAction]=Q[lastState][lastAction]+ learn_rate * (reward + (disc_rew * futurereward(state))
                  - Q[lastState][lastAction]);
}

void Qclass::Train() {

}

void Qclass::execute() {

}
