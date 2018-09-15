#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

#define MAX_MOVE 200
#define DIRECTION_NUM 4
#define FIRST_POS 100

enum Condition{YET,PASS};

pair<int, int> position = { FIRST_POS,FIRST_POS };

char move_arr[MAX_MOVE];
int move_cnt;
int maze[MAX_MOVE][MAX_MOVE] = { 0 };
int min_col,min_row,max_col, max_row;

enum Direction {UP,RIGHT,DOWN,LEFT};
enum Command {R,L,F};

Direction cur_dir = DOWN;

void ChangeDirection(Command com) {
	switch (com) {
	case R: {
		cur_dir = (Direction)((cur_dir + 1) % DIRECTION_NUM);
	}break;
	case L: {
		cur_dir = (Direction)((cur_dir - 1) % DIRECTION_NUM);
	}break;
	case F: {
		//NOTTHING TO DO
	}break;
	}
}

void ForwardMove(void) {
	switch (cur_dir) {
	case LEFT: {
		position.second--;
		if (position.second < min_col) min_col = position.second;
	}break;
	case RIGHT: {
		position.second++;
		if (position.second > max_col) max_col = position.second;
	}break;
	case UP: {
		position.first--;
		if (position.first < min_row) min_row = position.first;
	}break;
	case DOWN: {
		position.first++;
		if (position.first > max_row) max_row = position.first;
	}break;
	}
}


void Move(Command com) {
	switch (com) {
	case F: {
		ForwardMove();
		maze[position.first][position.second] = PASS;
	}break;
	case L:
	case R: {
		ChangeDirection(com);
	}break;
	}
}

void PrintMaze(void) {
	for (int i = min_row; i <= max_row; i++) {
		for (int j = min_col; j <= max_col; j++) {
			if (maze[i][j] == YET) {
				printf("#");
			}
			else {
				printf(".");
			}
		}
		printf("\n");
	}

}

Command GetCommand(char c) {
	Command result;
	
	switch (c) {
	case 'R': {
		result = R;
	}break;
	case 'L': {
		result = L;
	}break;
	case 'F': {
		result = F;
	}break;
	}

	return result;
}

void MakeMaze(void) {
	Command cur_com;

	for (int i = 0; i < move_cnt; i++) {
		cur_com = GetCommand(move_arr[i]);
		Move(cur_com);
	}
}

int main(void) {
	max_col = max_row = min_row = min_col = FIRST_POS;
	maze[FIRST_POS][FIRST_POS] = PASS;

	cin >> move_cnt;
	cin >> move_arr;

	MakeMaze();
	PrintMaze();

	system("pause");

	return 0;
}
