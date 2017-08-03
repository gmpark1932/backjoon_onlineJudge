#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_K 10010
#define INF 100000
#define MAX_N 110

int D[2][MAX_K];
int Coin[MAX_N];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		int c;
		scanf("%d", &c);
		Coin[i] = c;
	}

	fill(&D[0][0], &D[1][MAX_K - 1], INF);

	int source = 0;
	int dest = 1;
	for (int i = 0; i <= k; i++) {
		if (i % Coin[n - 1] == 0) {
			D[source][i] = i / Coin[n - 1];
		}
	}

	for (int coin_idx = n - 2; coin_idx >= 0; coin_idx--) {
		fill(&D[dest][0], &D[dest][MAX_K - 1], INF);
		for (int i = 0; i <= k; i++) {
			
			for (int j = 0; j <= k; j++) {
				if (i + Coin[coin_idx] * j <= k) {
					if (D[dest][i + Coin[coin_idx] * j] > D[source][i] + j) {
						D[dest][i + Coin[coin_idx] * j] = D[source][i] + j;
					}
				}
				else break;
			}

		}

		swap(source, dest);
	}
	if (D[source][k] == INF) {
		printf("-1\n");
	}
	else {
		printf("%d\n", D[source][k]);
	}

	return 0;
}