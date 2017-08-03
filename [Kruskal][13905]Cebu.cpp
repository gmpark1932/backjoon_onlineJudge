// Problem Number: 13905						 
// URL: https://www.acmicpc.net/problem/13905 
// Date: 2017.08.02							 
// Purpose: 1) Kruskal Algorithm

#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define MAX_N 100010
#define MAX_M 300010

struct DisjointSet {
	//private:
	vector<int> parent;

	//public:
	DisjointSet(int size) {
		parent.resize(size);
		for (int i = 0; i < parent.size(); i++)
			parent[i] = i;
	}

	int Find(int idx) {
		if (parent[idx] == idx) return idx;
		return parent[idx] = Find(parent[idx]);
	}

	bool Union(int v1, int v2) {
		int g1 = Find(v1);
		int g2 = Find(v2);

		if (g1 == g2) {
			return false;
		}

		parent[g1] = g2;
		return true;
	}
};

struct Node {
	int v1, v2;
	int cost;
};

struct comparator {
	bool operator() (Node a, Node b) {
		return a.cost < b.cost;
	}
};

int main(void) {
	int n, m, s, e;
	scanf("%d %d %d %d", &n, &m, &s, &e);

	DisjointSet ds(n + 1);

	priority_queue<Node,vector<Node>,comparator> maxHeap;

	for (int i = 0; i < m; i++) {
		int v1, v2, cost;
		scanf("%d %d %d", &v1, &v2, &cost);

		maxHeap.push({ v1,v2,cost });
	}

	int result = 0;

	while (maxHeap.empty() == false) {
		int v1 = maxHeap.top().v1;
		int v2 = maxHeap.top().v2;
		int cost = maxHeap.top().cost;

		maxHeap.pop();
		if (ds.Union(v1, v2)) {
			if (ds.Find(s) == ds.Find(e)) {
				result = cost;
				break;
			}
		}
	}

	printf("%d\n", result);

	return 0;
}