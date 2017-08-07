// [Dynamic][1562]StairNumber.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>

#define MAX_N 110
#define DIGIT 10
#define MOD 1000000000
#define MODE_NUM 4 //0~9, 1~9, 0~8, 1~8

using namespace std;

int D[MODE_NUM][MAX_N][DIGIT];

struct Mode {
	int min;
	int max;
}const mode_arr[MODE_NUM] = { {0,9},{1,9},{0,8},{1,8} };

int main()
{
	int n;
	scanf("%d", &n);

	for (int m = 0; m < MODE_NUM; m++) {
		Mode mode = mode_arr[m];

		for (int j = mode.min; j <= mode.max; j++) {
			D[m][1][j] = 1;
		}

		for (int i = 2; i <= n; i++) {
			for (int j = mode.min; j <= mode.max; j++) {
				if (j == mode.min) D[m][i][j] = D[m][i - 1][j + 1];
				else if (j == mode.max) D[m][i][j] = D[m][i - 1][j - 1];
				else D[m][i][j] = D[m][i - 1][j - 1] + D[m][i - 1][j + 1];
				D[m][i][j] %= MOD;
			}
		}
	}

	int result = 0;
	Mode mode = mode_arr[0];
	for (int i = mode.min + 1; i <= mode.max; i++) {
		result += D[0][n][i];
		result %= MOD;
	}

	mode = mode_arr[1];
	for (int i = mode.min; i <= mode.max; i++) {
		result -= D[1][n][i];
		result %= MOD;
	}

	mode = mode_arr[2];
	for (int i = mode.min + 1; i <= mode.max; i++) {
		result -= D[2][n][i];
		result %= MOD;
	}

	mode = mode_arr[3];
	for (int i = mode.min; i <= mode.max; i++) {
		result += D[3][n][i];
		result %= MOD;
	}

	printf("%d\n", result);

	return 0;
}

