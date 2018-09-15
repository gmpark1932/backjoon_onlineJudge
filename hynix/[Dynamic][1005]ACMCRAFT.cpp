#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1010
#define MAX_K 100010
#define MAX_D 100010

int makeTime[MAX_N];
int graphEdge[MAX_N][MAX_N];
int alreadyKnow[MAX_N];
int toVal[MAX_N];

int CalculateTime(int N,int val) {
	int result, i;
	int max;

	if (toVal[val] == 0)
		return makeTime[val];

	if (alreadyKnow[val] != -1) {
		return alreadyKnow[val];
	}

	result = makeTime[val];
	max = 0;

	for (i = 1; i <= N; i++) {
		int temp_max;
		if (graphEdge[i][val] != 0) {
			temp_max = CalculateTime(N, i);
			if (max < temp_max) max = temp_max;
		}
	}

	result += max;

	alreadyKnow[val] = result;

	return result;
}

int main(void) {
	int T;

	scanf("%d", &T);

	int t;
	for (t = 0; t < T; t++) {
		int N, K;
		int n,k;
		int target;
		int result;
		scanf("%d %d", &N, &K);
		
		memset(makeTime, 0x00, sizeof(makeTime));
		memset(graphEdge, 0x00, sizeof(graphEdge));
		memset(alreadyKnow, 0xFF, sizeof(alreadyKnow));
		memset(toVal, 0x00, sizeof(toVal));

		for (n = 1; n <= N; n++) {
			int in;
			scanf("%d", &in);
			makeTime[n] = in;
		}

		for (k = 0; k < K; k++) {
			int v1, v2;
			scanf("%d %d", &v1, &v2);
			graphEdge[v1][v2] = 1;
			toVal[v2]++;
		}

		scanf("%d", &target);

		result = CalculateTime(N, target);
		printf("%d\n", result);
	}

	//system("pause");

	return 0;
}
