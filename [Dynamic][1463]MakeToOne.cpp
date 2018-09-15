#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAX_N 1000010

int alreadyKnow[MAX_N];

int minCalculate(int n) {
	int min = INT_MAX;

	if (n == 1)
		return 0;

	if (alreadyKnow[n] != -1) {
		return alreadyKnow[n];
	}

	if (n % 3 == 0) {
		int temp_min = minCalculate(n / 3) + 1;
		if (min > temp_min)
			min = temp_min;
	}

	if (n % 2 == 0) {
		int temp_min = minCalculate(n / 2) + 1;
		if (min > temp_min)
			min = temp_min;
	}

	int temp_min = minCalculate(n - 1) + 1;
	if (min > temp_min)
		min = temp_min;

	alreadyKnow[n] = min;

	return min;
}

int main(void) {
	int N;
	scanf("%d", &N);

	memset(alreadyKnow, 0xFF, sizeof(alreadyKnow));

	printf("%d\n", minCalculate(N));

	return 0;
}
