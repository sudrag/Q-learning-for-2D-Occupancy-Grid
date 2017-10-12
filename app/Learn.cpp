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
int Qclass::findpos(int lastAction,int prev_x,int prev_y){
	if (lastAction==0){
	   int new_x=prev_x;
	   int new_y=prev_y;
	}
	if (lastAction==1){
		   int new_x=prev_x;
		   int new_y=prev_y;
		}
	if (lastAction==2){
		   int new_x=prev_x;
		   int new_y=prev_y;
		}
	if (lastAction==3){
		   int new_x=prev_x;
		   int new_y=prev_y;
		}
	return prev_x,prev_y;
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
int Qclass::rewardfunc(int lastAction,int x,int y,bool restart) {
	//Add goal condition here
  int reward;
  if(lastAction==0){
	  if(x== goal_x && y==goal_y){
		  reward=100;
	  }
	  else{
	  if(x+1<=5)
    reward=grid[x+1][y]*-100-1;
	  else
		  reward=-100;
	  restart=true;
	  if(grid[x+1][y]==1)
	 		  restart=true;
	  }
	  }
  if(lastAction==1){
	  if(x== goal_x && y==goal_y){
	 		  reward=100;
	 	  }
	 	  else{
	  if(x-1>=0)
	  reward=grid[x-1][y]*-100-1;
	  else
		  reward=-100;
	  restart=true;
	  if(grid[x-1][y]==1)
	 		  restart=true;
  }
  }
  if(lastAction==2){
	  if(x== goal_x && y==goal_y){
	 		  reward=100;
	 	  }
	 	  else{
	  if(y+1<=5)
     reward=grid[x][y+1]*-100-1;
	  else
		  reward=-100;
	      restart=true;
	  if(grid[x][y+1]==1)
	 		  restart=true;
	 	  }
  }
  if(lastAction==3){
	  if(x== goal_x && y==goal_y){
	 		  reward=100;
	 	  }
	 	  else{
	  if(y-1>=0)
     reward=grid[x][y-1]*-100-1;
	  else
		  reward=-100;
	  	  restart=true;
	  if(grid[x+1][y]==1)
	 		  restart=true;
	 	  }
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
void Qclass::Qupdate(int lastAction, int lastState, int x,int y, int state, bool restart) {
  Qclass::learn_rate=0.5;  // variables for update equation
  Qclass::disc_rew=0.8;
  //int reward=0;
  int reward = Qclass::rewardfunc(lastAction,x,y,restart);
  if(restart==true){
    Q[lastState][lastAction] = Q[lastState][lastAction] + learn_rate * (reward)
        - Q[lastState][lastAction];
  }
  else{
  Q[lastState][lastAction]=Q[lastState][lastAction]+ learn_rate * (reward + (disc_rew * futurereward(state))
                  - Q[lastState][lastAction]);
  }
  }

void Qclass::Train() {
	int firstRun = 1;  // Can't update Q table on first run, no previous data to go off of
	  int lastState;
	  int lastAction;
	  int start_x = rand % 5;
	  int start_y = rand % 5;
	  bool restart =false;
	  int goal_state=findState(goal_x,goal_y);
	  while (grid(start_x,start_y)==1){
		  int start_x=rand % 5;
		  int start_y=rand % 5;
	  }
	  int prev_x=start_x;
	  int prev_y=start_y;
	  for (int i = 0; i < 1000; i++) {
	   int state = findState(start_x, start_y);
	    while(state != goal_state){
	    if (firstRun == 0) {
	      prev_x,prev_y=findpos(lastAction,prev_x,prev_y);
	      Qupdate(lastAction, lastState,prev_x,prev_y, state,restart);
	    }
	    int action = detAction(state);
	    lastState = state;
	    lastAction = action;
	    if (restart == true) {
	      restart = false;   // resetting so back to false
	      firstRun = 0;
	    }
	  }
}
	  for (int i=0;i<25;i++){
		  for (int j=0;j<4;j++){
			  std::cout<<Q[i][j]<<"  ";
		  }
	  std::cout<<std::endl;
	  }
}

void Qclass::execute() {

}

int main()
{
Qclass Q1;
