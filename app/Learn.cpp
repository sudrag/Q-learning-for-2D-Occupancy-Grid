#include "Qlearn-class.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "gnuplot_i.hpp"

void Qclass::createGrid() {
	for (int i = 3; i < 5; i++) {
		for (int j = 2; j < 5; j++) {
			grid[i][j] = 1;
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
	state = x * 5 + y;
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
	int maxQ = -10000;
	int temp = rand() % 100;
	if (temp > 70) {
		int randAction = rand() % 4;
		chosenAction = randAction;
	} else {
		for (int i = 0; i < 4; i++) {
			if (Q[state][i] > maxQ) {
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
 * @param int previous action,int x,int y, int grid[size][size]
 * @return Returns assigned reward
 */
int Qclass::rewardfunc(int lastAction, int x, int y) {
	//Add goal condition here
	int reward;
	if (lastAction == 0) {
		if (x + 1 == goal_x && y == goal_y) {
			reward = 100;
		} else {
			if (x + 1 <= 4) {
				reward = grid[x + 1][y] * -1000 - 10;
			} else {
				reward = -1000;
				restart = true;
			}
			if (grid[x + 1][y] == 1) {
				restart = true;
			}
		}
	}
	if (lastAction == 1) {
		if (x - 1 == goal_x && y == goal_y) {
			reward = 100;
		} else {
			if (x - 1 >= 0) {
				reward = grid[x - 1][y] * -1000 - 10;
			} else {
				reward = -1000;
				restart = true;
			}
			if (grid[x - 1][y] == 1) {
				restart = true;
			}
		}
	}
	if (lastAction == 2) {
		if (x == goal_x && y + 1 == goal_y) {
			reward = 100;
		} else {
			if (y + 1 <= 4) {
				reward = grid[x][y + 1] * -1000 - 10;
			} else {
				reward = -1000;
				restart = true;
			}
			if (grid[x][y + 1] == 1) {
				restart = true;
			}
		}
	}
	if (lastAction == 3) {
		if (x == goal_x && y - 1 == goal_y) {
			reward = 100;
		} else {
			if (y - 1 >= 0) {
				reward = grid[x][y - 1] * -1000 - 10;
			} else {
				reward = -1000;
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
 * @param int state is the current state of the robot.
 * @return Max Q table value for the state
 */
int Qclass::futurereward(int new_state) {
	int currMax = -100000;
	if (new_state > 24) {
		currMax = -1000;
	} else {
		for (int i = 0; i < 5; i++) {
			if (Q[new_state][i] > currMax) {
				currMax = Q[new_state][i];
			}
		}
	}
	return currMax;
}

/**
 * @brief Updates Q table based on action taken for given grid position
 * @param int previous state, previous action, state, x,y
 * @return none
 */
void Qclass::Qupdate(int lastAction, int lastState, int x, int y,
		int new_state) {
	Qclass::learn_rate = 0.5;  // variables for update equation
	Qclass::disc_rew = 0.8;
	//int reward=0;
	int reward = Qclass::rewardfunc(lastAction, x, y);
	if (restart == true) {
		Q[lastState][lastAction] = Q[lastState][lastAction]
				+ learn_rate * (reward) - Q[lastState][lastAction];
	} else {
		Q[lastState][lastAction] = Q[lastState][lastAction]
				+ learn_rate
						* (reward + (disc_rew * futurereward(new_state))
								- Q[lastState][lastAction]);
	}
}

void Qclass::Train() {
	std::cout << "Here" << std::endl;
	int firstRun = 1; // Can't update Q table on first run, no previous data to go off of
	int new_x = 0;
	int action = 0;
	int new_y = 0;
	int new_state = 0;
	int start_x = rand() % 5;
	int start_y = rand() % 5;
	int goal_state = findState(goal_x, goal_y);
	if (grid[start_x][start_y] == 1) {
		while (grid[start_x][start_y] == 1) {
			start_x = rand() % 5;
			start_y = rand() % 5;
		}
	}
	int prev_x = start_x;
	int prev_y = start_y;
	int state = findState(start_x, start_y);
	for (int k = 0; k < 1000; k++) {
		int lastState = 0;
		int lastAction = 0;
		while (lastState != goal_state) {
			//  std::cout<<"2"<<std::endl;
			if (firstRun == 0) {
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
			firstRun = 0;
			if (restart == true) {
				restart = false;   // resetting so back to false
				firstRun = 1;
				int start_x = rand() % 5;
				int start_y = rand() % 5;
				if (grid[start_x][start_y] == 1) {
					while (grid[start_x][start_y] == 1) {
						start_x = rand() % 5;
						start_y = rand() % 5;
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
	for (int i = 0; i < 25; i++) {
		std::cout << i << "  ";
		for (int j = 0; j < 4; j++) {
			std::cout << Q[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

void Qclass::execute() {
	int start_x = rand() % 5;
	int start_y = rand() % 5;
	int last_state = 500;
	int max = -1000;
	int action = 0;
	int start_state = 10;
	int goal_state = findState(goal_x, goal_y);
	if (grid[start_x][start_y] == 1) {
		while (grid[start_x][start_y] == 1) {
			start_x = rand() % 5;
			start_y = rand() % 5;
		}
	}
	std::ofstream outfile;
	outfile.open("Co_ordinates.txt", std::ios::out | std::ios::trunc);
	std::cout << "The path followed by the robot is:" << std::endl;
	outfile.precision(6);
	while (last_state != goal_state) {
		std::cout << start_x << "," << start_y << std::endl;
		outfile << std::fixed << start_x << "   " << std::fixed << start_y;
		outfile << std::endl;
		start_state = findState(start_x, start_y);
		for (int i = 0; i < 5; i++) {
			if (Q[start_state][i] > max) {
				max = Q[start_state][i];
				action = i;
			}
		}
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
		max = -1000;

	}
	std::cout << goal_x << "," << goal_y;
	outfile << std::fixed << goal_x << "   " << std::fixed << goal_y;
	outfile.close();
}

void Qclass::plot() {
	try {
		Gnuplot g1("lines");
		g1.set_grid();

		g1.set_grid();
		g1.plotfile_xy("Co_ordinates.txt", 1, 2, "Grid");
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
		cout << endl << "Press any key to continue..." << endl;

		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
		std::cout << std::endl << "Press ENTER to continue..." << std::endl;

		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
#endif

	} catch (GnuplotException& ge) {
		std::cout << ge.what() << std::endl;
	}
}

