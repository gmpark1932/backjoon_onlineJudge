#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

#define MOD 1000000009

#define INF -1

using namespace std;

struct Node {
	int vertex;
	int cost;
};

struct Edge {
	int v;
	int cost;
};

struct comparator {
	bool operator()(Node i,Node j) {
		return i.cost > j.cost;
	}
};

vector<vector<Edge>> edges;
vector<int> dist;
vector<int> countArr;
priority_queue<Node, std::vector<Node>, comparator> minHeap;

int howManyRoute(int start, int end) {
	minHeap.push({ start,0 });

	dist[start] = 0;
	countArr[start] = 1;

	while (!minHeap.empty()) {
		Node node = minHeap.top();
		minHeap.pop();

		for (vector<Edge>::iterator itr = edges[node.vertex].begin(); itr != edges[node.vertex].end(); itr++) {
			int minDist = dist[node.vertex] + itr->cost;

			if (dist[itr->v] == -1) {
				dist[itr->v] = minDist;
				minHeap.push({ itr->v, minDist });
				countArr[itr->v] = countArr[node.vertex];
			}
			else if (dist[itr->v] == minDist) {
				countArr[itr->v]+=countArr[node.vertex];
				countArr[itr->v] %= MOD;
			}
			else if (dist[itr->v] > minDist) {
				dist[itr->v] = minDist;
				countArr[itr->v] = countArr[node.vertex];
			}
		}
	}

	return countArr[end];
}

int main(void) {
	int N, M, S, E;

	scanf("%d %d %d %d", &N, &M, &S, &E);

	edges.resize(N+1);
	dist.resize(N+1);
	countArr.resize(N+1);
	fill(dist.begin(), dist.end(), INF);
	fill(countArr.begin(), countArr.end(), 0);
	for (int i = 0; i < M; i++) {
		int v1, v2, len;

		scanf("%d %d %d", &v1, &v2, &len);

		edges[v1].push_back({ v2,len });
		edges[v2].push_back({ v1,len });
	}

	printf("%d\n", howManyRoute(S,E));

	return 0;
}