#include <cstdio>
#include <queue>
#include <vector>
#include <functional>

#define MAX_N 32010

using namespace std;

vector<int> graph[MAX_N];
vector<int> in_degree(MAX_N);

int main(void) {
	int n,m;
	scanf("%d %d", &n, &m);

	fill(in_degree.begin(), in_degree.end(), 0);

	for (int i = 0; i < m; i++) {
		int before, after;
		scanf("%d %d", &before, &after);
		graph[before].push_back(after);
		in_degree[after]++;
	}

	priority_queue<int, vector<int>, greater<int>> minHeap;

	for (int i = 1; i <= n; i++) {
		if (in_degree[i] == 0)
			minHeap.push(i);
	}

	while (minHeap.empty() == false) {
		int p = minHeap.top();
		minHeap.pop();
		printf("%d ", p);

		for (int after : graph[p]) {
			in_degree[after]--;
			if (in_degree[after] == 0) {
				minHeap.push(after);
			}
		}
	}

	return 0;
}