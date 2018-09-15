#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>

#define MAX_K 30
#define MAX_N 450
#define MIN(a,b) ((a)>(b)?(b):(a))

long long int mem[MAX_K][MAX_N] = { 0 };

using namespace std;
int k, N;

long long int GetCountXN(int below, int remain) {
	int min = MIN(remain, below - 1);
	long long int result = 0;

	if (mem[below][remain] != 0) return mem[below][remain];

	int condition = below * (below - 1) / 2;
	if (remain > condition) return 0;
	else if (remain == condition) return 1;
	else {
		for (int i = 0; i <= min; i++) {
			result += GetCountXN(below - 1, remain - i);
		}

		mem[below][remain] = result;
	}

	return result;

}

int main(void) {
	int T;
	
	cin >> T;

	for (int t = 0; t < T; t++) {
		cin >> k >> N;

		long long int result = GetCountXN(k+1, N);

		cout << result << endl;

	}

	//system("pause");
	return 0;
}
