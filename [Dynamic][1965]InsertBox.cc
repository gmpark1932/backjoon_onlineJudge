#include <cstdio>

using namespace std;

#define MAX_N 1001

int D[MAX_N] = { 0 };
int Box[MAX_N];

int main(void) {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int b;
		scanf("%d", &b);
		Box[i] = b;
	}

	D[n] = 1;
	Box[0] = 0;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j <= n; j++) {
			if (Box[i] < Box[j] && D[i] < D[j] + 1) {
				D[i] = D[j] + 1;
			}
		}
		if (D[i] == 0)
			D[i] = 1;
	}

	printf("%d\n", D[0] - 1);

	return 0;
}