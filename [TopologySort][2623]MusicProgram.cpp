#include <cstdio>
#include <queue>
#include <vector>

#define MAX_N 1010

using namespace std;

vector<int> graph[MAX_N];
vector<int> in_degree(MAX_N, 0);

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		int size;
		scanf("%d", &size);
		int before = -1;
		int after;
		for (int j = 0; j < size; j++) {
			scanf("%d", &after);
			if (before != -1) {
				graph[before].push_back(after);
				in_degree[after]++;
			}
			before = after;
		}
	}

	queue<int> q;
	queue<int> result;
	for (int i = 1; i <= n; i++) {
		if (in_degree[i] == 0)
			q.push(i);
	}

	int count = 0;
	while (!q.empty()) {
		count++;
		
		int node = q.front();
		q.pop();
		result.push(node);
		
		for (int after : graph[node]) {
			in_degree[after]--;
			if (in_degree[after] == 0)
				q.push(after);
		}
	}

	if (count != n) {
		printf("0\n");
	}
	else {
		while (!result.empty()) {
			int node = result.front();
			printf("%d\n", node);
			result.pop();
		}
	}

	return 0;
}