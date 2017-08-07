// [Dynamic][2342]DDR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_N 100010
#define DIRECTION_NUM 5

using namespace std;

enum direction {
	NOTHING = -1,
	CENTER = 0,
	UP = 1,
	LEFT = 2,
	DOWN = 3,
	RIGHT = 4
};

int move_cost(direction from, direction to) {
	if (from == to) return 1;
	else if (from == CENTER) return 2;
	else if ((from == UP && to == DOWN) || (from == DOWN && to == UP)
		|| (from == LEFT && to == RIGHT) || (from == RIGHT && to == LEFT)) {
		return 4;
	}

	return 3;
}

int D[DIRECTION_NUM][DIRECTION_NUM][MAX_N];
direction Inst[MAX_N];
int solve(direction left, direction right, int cur_inst) {
	if (Inst[cur_inst] == 0)
		return 0;
	if (D[left][right][cur_inst] != -1)
		return D[left][right][cur_inst];

	int result=0;
	int left_move = 0, right_move = 0;
	if (Inst[cur_inst] == left || Inst[cur_inst] == right) {
		result = solve(left, right, cur_inst + 1) + move_cost(Inst[cur_inst], Inst[cur_inst]);
	}
	else {
		left_move = solve(Inst[cur_inst], right, cur_inst + 1) + move_cost(left, Inst[cur_inst]);
		right_move = solve(left, Inst[cur_inst], cur_inst + 1) + move_cost(right, Inst[cur_inst]);
		result = (left_move > right_move) ? right_move : left_move;
	}

	D[left][right][cur_inst] = result;
	return result;
}

int main()
{
	fill(&Inst[0], &Inst[MAX_N], NOTHING);
	fill(&D[0][0][0], &D[DIRECTION_NUM - 1][DIRECTION_NUM - 1][MAX_N], -1);
	
	int inst = -1;
	int count = 0;
	while (inst != 0) {
		scanf("%d", &inst);
		Inst[count] = (direction)inst;
		count++;
	}

	int result = solve(CENTER, CENTER, 0);
	printf("%d\n", result);

	return 0;
}

