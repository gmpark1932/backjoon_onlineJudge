#include <cstdio>

#define MAX_N 100010

int main(void) {
	int n;
	scanf("%d", &n);

	int arr[MAX_N];

	for (int i = 0; i < n; i++) {
		int s;
		scanf("%d", &s);
		arr[i] = s;
	}

	long long int result = 0;
	long long int sum = arr[0];

	for (int i = 1; i < n; i++) {
		result += sum * arr[i];
		sum += arr[i];
		//printf("%lld\n", result);
	}

	printf("%lld\n", result);

	return 0;
}