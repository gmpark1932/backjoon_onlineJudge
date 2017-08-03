#include <cstdio>
#include <algorithm>

#define MAX_N 1001

int arr_P[MAX_N];

int main(void) {
	int N;

	scanf("%d", &N);

	for (int i = 0;i < N;i++) {
		scanf("%d", &arr_P[i]);
	}

	std::sort(arr_P, arr_P + N);

	int result = 0;
	int t = N;
	for (int i = 0;i < N;i++) {
		result += arr_P[i] * t--;
	}

	printf("%d\n", result);

	return 0;
}