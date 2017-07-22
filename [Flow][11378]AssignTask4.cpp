// Problem Number : 11378
// URL: https://www.acmicpc.net/problem/11378 
// Date: 2017.07.21							 
// Purpose: 1) Ford-Fulkerson Max Flow Algorithm

#include <cstdio>
#include <vector>

using namespace std;

#define MAX_N 1000
#define MAX_M 1000

#define GRAPH_SIZE MAX_N + MAX_M + 2
#define NOT_NODE -1

char graph[GRAPH_SIZE][GRAPH_SIZE] = { 0 };
//	Source Node : No.0
//	Terminal Node : No.(M+N+1)
//	People : No.(1 ~ N)
//	Task : No.(N+1 ~ N+M)

inline int findNotVisited(int node, bool visited[]) {
	for (int i = 0; i < GRAPH_SIZE; i++) {
		if (visited[i] == false && graph[node][i] > 0) {
			return i;
		}
	}

	return NOT_NODE;
}

//Find path Source ~ Terminal
bool dfs(vector<pair<int, int>> &path, const int source, const int terminal) {
	path.clear();
	bool visited[GRAPH_SIZE];

	fill(visited, visited + GRAPH_SIZE, false);

	int current_node = source;

	while (current_node != terminal) {
		visited[current_node] = true;

		int next_node = findNotVisited(current_node, visited);
		if (next_node != NOT_NODE) {
			path.push_back(make_pair(current_node, next_node));
			current_node = next_node;
		}
		else {
			if (path.empty())
				return false;
			else {
				current_node = path.back().first;
				path.pop_back();
			}
		}
	}

	return true;
}

inline void applyPathToGraph(vector<pair<int, int>>& path) {
	for (vector<pair<int, int>>::iterator itr = path.begin(); itr != path.end(); itr++) {
		graph[itr->first][itr->second] -= 1;
		graph[itr->second][itr->first] += 1;
	}
}

int main(void) {
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);

	// Start Init Graph

	for (int i = 1; i <= N; i++) {
		graph[0][i] = 1;

		int task_count;
		scanf("%d", &task_count);
		for (int j = 1; j <= task_count; j++) {
			int task;
			scanf("%d", &task);
			task += N;

			graph[i][task] = 1;
		}
	}

	for (int i = N + 1; i <= N + M; i++)
		graph[i][N + M + 1] = 1;

	// End Init Graph
	int count = 0;
	vector<pair<int, int>> dfs_path;

	while (dfs(dfs_path, 0, N + M + 1)) {
		applyPathToGraph(dfs_path);
		count++;
	}

	// Every People's available task + 1
	int change = 1;
	int addition_count = 0;
	while (change != 0) {
		int before_addition = addition_count;
		for (int i = 1; i <= N; i++)
			graph[0][i] += 1;

		
		while (dfs(dfs_path, 0, N + M + 1)) {
			applyPathToGraph(dfs_path);
			addition_count++;
			if (addition_count == K)
				break;
		}
		if (addition_count == K)
			break;

		change = addition_count - before_addition;
	}

	printf("%d\n", count + addition_count);

	return 0;
}