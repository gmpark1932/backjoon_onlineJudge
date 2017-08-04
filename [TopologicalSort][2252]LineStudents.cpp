#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

#define DFS false
#define INDEGREE true

using namespace std;

#define MAX_N 32010
#define MAX_M 100010

//dfs를 이용한 풀이법
vector<vector<int>> graph;
vector<bool> visited;

void topologySort(vector<bool>& visited, stack<int>& result,int start) {
	visited[start] = true;
	for (vector<int>::iterator itr = graph[start].begin(); itr != graph[start].end(); itr++) {
		if (visited[*itr])
			continue;
		topologySort(visited,result,*itr);
	}
	result.push(start);
}

//In degree를 이용한 풀이법
int in_degree[MAX_N] = { 0 };

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	graph.resize(n + 1);
	visited.resize(n + 1, false);
	
	for (int i = 0; i < m; i++) {
		int st1, st2;
		scanf("%d %d", &st1, &st2);
		graph[st1].push_back(st2);
		
		in_degree[st2]++;
	}

	//DFS를 이용한 풀이법
	if (DFS) {
		stack<int> result;

		for (int i = 1; i <= n; i++) {
			if (visited[i] == false)
				topologySort(visited, result, i);
		}
		while (!result.empty()) {
			int node = result.top();
			printf("%d ", node);
			result.pop();
		}

		printf("\n");
	}

	if (INDEGREE) {
		queue<int> result;
		for (int i = 1; i <= n; i++) {
			if (in_degree[i] == 0)
				result.push(i);
		}

		while (result.size() != 0) {
			int v = result.front();
			result.pop();
			printf("%d ", v);
			for (int to_v : graph[v]) {
				in_degree[to_v]--;
				if (in_degree[to_v] == 0) {
					result.push(to_v);
				}
			}
		}

		printf("\n");
	}

	return 0;
}