// Problem Number: 1520						 
// URL: https://www.acmicpc.net/problem/1520 
// Date: 2017.07.10							 
// Purpose: 1) Dynamic Algorithm ( Save Already Found Cost )


#include <cstdio>
#include <vector>

#define MAX_N 503
#define INF_HEIGHT 10001
using namespace std;

vector<vector<int>> height_arr(MAX_N, vector<int>(MAX_N));
vector<vector<pair<bool, int>>> already_found(MAX_N,vector<pair<bool,int>>(MAX_N));

int countDownhillPath(int, int);

inline int one_direction_process(int y, int x) {
	if (already_found[y][x].first == true)
		return already_found[y][x].second;
	else {
		int temp_result = countDownhillPath(y, x);
		already_found[y][x] = make_pair(true, temp_result);
		return temp_result;
	}
}

int countDownhillPath(int y, int x) {
	int up_result=0, down_result=0, right_result=0, left_result=0;

	int current_height = height_arr[y][x];

	if (height_arr[y - 1][x] < current_height)
		up_result = one_direction_process(y - 1, x);
	
	if(height_arr[y+1][x] < current_height)
		down_result = one_direction_process(y + 1, x);
	
	if(height_arr[y][x-1] < current_height)
		left_result = one_direction_process(y, x - 1);
	
	if(height_arr[y][x+1] < current_height)
		right_result = one_direction_process(y, x + 1);

	return up_result + down_result + left_result + right_result;
}

int main(void) {
	int M, N;

	scanf("%d %d", &M, &N);

	for (int i = 0;i < M+2;i++) {
		for (int j = 0;j < N+2;j++) {
			if (i == 0 || j == 0 || i == M + 1 || j == N + 1)
				height_arr[i][j] = INF_HEIGHT;
			else
				scanf("%d", &height_arr[i][j]);
		}
	}

	for (int i = 0;i < M + 2;i++) {
		for (int j = 0;j < N + 2;j++) {
			if (i == 0 || j == 0 || i == M + 1 || j == N + 1)
				already_found[i][j] = make_pair(true, 0);
			else
				already_found[i][j] = make_pair(false, 0);
		}
	}

	already_found[M][N] = make_pair(true, 1);

	printf("%d\n", countDownhillPath(1, 1));

	return 0;
}