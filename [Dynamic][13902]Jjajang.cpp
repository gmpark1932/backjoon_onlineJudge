#include <cstdio>
#include <list>

using namespace std;

#define MAX_M 1010
#define MAX_N 10010
#define INF 1500000000

int wuck[MAX_M];
int D[MAX_N];

list<int> C;

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		int s;
		scanf("%d", &s);
		wuck[i] = s;
	}
	
	for (int i = 0; i < m; i++) {
		C.push_back(wuck[i]);
	}

	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			C.push_back(wuck[i] + wuck[j]);
		}
	}

	C.sort();
	C.unique();

	D[0] = 0;
	for (int i = 1; i <= n; i++) {
		int min = INF;
		for (list<int>::iterator itr = C.begin(); itr != C.end(); itr++) {
			if (i - *itr < 0) {
				break;
			}
			if (D[i-*itr] != -1 && D[i - *itr] < min) {
				min = D[i - *itr];
			}
		}
		if (min == INF)
			D[i] = -1;
		else
			D[i] = min + 1;
	}

	printf("%d\n", D[n]);

	return 0;
}