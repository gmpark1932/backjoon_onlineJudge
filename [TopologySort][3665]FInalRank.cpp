#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 510

bool graph[MAX_N][MAX_N]; //"graph[i][j] is true" means i has higher rank than j
vector<int> beforeRank(MAX_N);
vector<int> inDegree(MAX_N);

int main(void) {
	int T;
	scanf("%d", &T);
	for (int _t = 0; _t < T; _t++) {
		fill(&graph[0][0], &graph[MAX_N - 1][MAX_N], false);
		fill(beforeRank.begin(), beforeRank.end(), 0);
		fill(inDegree.begin(), inDegree.end(), 0);

		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++) {
			int team;
			scanf("%d", &team);
			beforeRank[team] = i;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (beforeRank[i] < beforeRank[j]) {
					graph[i][j] = true;
					inDegree[j]++;
				}
				else {
					graph[j][i] = true;
					inDegree[i]++;
				}
			}
		}

		int m;
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int t1, t2;
			scanf("%d %d", &t1, &t2);
			if (beforeRank[t1] < beforeRank[t2]) {
				inDegree[t2]--;
				inDegree[t1]++;
			}
			else {
				inDegree[t2]++;
				inDegree[t1]--;
			}
			swap(graph[t1][t2], graph[t2][t1]);
		}

		queue<int> q;
		for (int i = 1; i <= n; i++) {
			if (inDegree[i] == 0) {
				q.push(i);
			}
		}

		bool impossible = false;
		queue<int> result;

		if (q.size() != 1) {
			impossible = true;
		}
		else {
			int visit_count = 0;

			while (!q.empty()) {
				int v = q.front();
				q.pop();
				result.push(v);
				visit_count++;

				for (int i = 1; i <= n; i++) {
					if (i != v && graph[v][i] == true) {
						inDegree[i]--;
						if (inDegree[i] == 0)
							q.push(i);
					}
				}
			}

			if (visit_count != n)
				impossible = true;
		}

		if (impossible) {
			printf("IMPOSSIBLE\n");
		}
		else {
			while (!result.empty()) {
				int v = result.front();
				result.pop();
				printf("%d ", v);
			}
			printf("\n");
		}
	}
	return 0;
}