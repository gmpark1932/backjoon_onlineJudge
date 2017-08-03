#include <cstdio>

#define MAX_N 1001

using namespace std;

int D[MAX_N] = { 0 };
int Seq[MAX_N];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int e;
		scanf("%d", &e);
		Seq[i] = e;
	}

	Seq[0] = 0;
	D[n] = Seq[n];



	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j <= n; j++) {
			if (Seq[i] < Seq[j] && D[i] < D[j] + Seq[i]) {
				D[i] = D[j] + Seq[i];
			}
		}
		if (D[i] == 0)
			D[i] = Seq[i];
	}

	printf("%d\n", D[0]);

	return 0;
}