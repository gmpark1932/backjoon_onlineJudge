// Problem Number : 2316
// URL: https://www.acmicpc.net/problem/2316 
// Date: 2017.07.23							 
// Purpose: 1) Edmonds-Karp Max Flow Algorithm

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
	int capacity;
	int source;
	int dest;
};

class MaxFlow {
private:
	int max_flow = 0;
	int vertex_number;
	vector<vector<int>> edges;
	vector<vector<int>> flow;
	vector<bool> visited;

public:
	MaxFlow(int _n) {
		vertex_number = _n;
		edges.resize(vertex_number);
		for (int i = 0; i < vertex_number; i++) {
			edges[i].resize(vertex_number);
			fill(edges[i].begin(), edges[i].end(), 0);
		}
		visited.resize(vertex_number);
		flow.resize(vertex_number);
		for (int i = 0; i < vertex_number; i++) {
			flow[i].resize(vertex_number);
			fill(flow[i].begin(), flow[i].end(), 0);
		}
	}

	void addEdge(int v1, int v2, int capacity) {
		edges[v1][v2] = capacity;
		edges[v2][v1] = capacity;
	}

	int findMaxFlow(int source, int sink) {
		vector<int> parent(vertex_number);

		while (bfs(parent, source, sink))
			applyPathToGraph(parent, source, sink);

		return max_flow;
	}

	bool bfs(vector<int> &parent, int source, int sink) {
		queue<int> q;

		fill(parent.begin(), parent.end(), -1);

		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int cur = q.front();
			q.pop();

			for (int i = 0; i < vertex_number; i++) {
				if (edges[cur][i] - flow[cur][i] > 0 && parent[i] == -1 && !visited[i]) {
					parent[i] = cur;
					q.push(i);
				}
			}
		}

		return parent[sink] != -1;
	}

	void applyPathToGraph(vector<int>& parent, int source, int sink) {
		//Find Min Flow
		int min_flow = INT_MAX;
		for (int i = sink; i != source; i = parent[i]) {
			if (min_flow > edges[parent[i]][i])
				min_flow = edges[parent[i]][i];
		}

		for (int i = sink; i != source; i = parent[i]) {
			if (i != sink && i != source)
				visited[i] = true;
			flow[parent[i]][i] += min_flow;
			flow[i][parent[i]] -= min_flow;
		}

		max_flow += min_flow;
	}

};

int main(void) {
	int N, P;

	scanf("%d %d", &N, &P);

	MaxFlow mf(N);

	for (int i = 0; i < P; i++) {
		int v1, v2;
		scanf("%d %d", &v1, &v2);

		mf.addEdge(v1 - 1, v2 - 1, 1);
	}

	printf("%d\n", mf.findMaxFlow(0, 1));

	return 0;
}