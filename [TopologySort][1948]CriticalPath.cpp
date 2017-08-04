#include <cstdio>
#include <queue>
#include <vector>

#define MAX_N 10010
#define INF_ROAD 300000

using namespace std;

struct Road {
	int to_v;
	int cost;
};

vector<Road> graph[MAX_N];
vector<int> maxArriveTime(MAX_N, 0);
//vector<int> criticalArrive(MAX_N, 0);
vector<int> inDegree(MAX_N, 0);
vector<int> criticalRoute[MAX_N];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int v1, v2, cost;
		scanf("%d %d %d", &v1, &v2, &cost);
		graph[v1].push_back({ v2,cost });
		inDegree[v2]++;
	}

	int start, end;
	scanf("%d %d", &start, &end);

	for (int i = 1; i <= n; i++) {
		if (inDegree[i] == 0 && i != start)
			inDegree[i] = INF_ROAD;

		if (graph[i].empty() && i != end)
			inDegree[i] = INF_ROAD;
	}

	queue<int> q;
	q.push(start);

	while (!q.empty()) {
		int city = q.front();
		q.pop();

		for (Road r : graph[city]) {
			inDegree[r.to_v]--;
			if (inDegree[r.to_v] == 0)
				q.push(r.to_v);

			int time = maxArriveTime[city] + r.cost;
			if (maxArriveTime[r.to_v] < time) {
				//criticalArrive[r.to_v] = criticalArrive[city]+1;
				maxArriveTime[r.to_v] = time;

				criticalRoute[r.to_v].clear();
				criticalRoute[r.to_v].push_back(city);
			}
			else if (maxArriveTime[r.to_v] == time) {
				//criticalArrive[r.to_v] += (criticalArrive[city] + 1);

				criticalRoute[r.to_v].push_back(city);
			}
		}
	}

	int count = 0;
	queue<int> crq;
	crq.push(end);
	vector<bool> visited(MAX_N, false);
	while(!crq.empty()) {
		int v = crq.front();
		crq.pop();
		if (visited[v])
			continue;
		visited[v] = true;

		for (int to_v : criticalRoute[v]) {
			crq.push(to_v);
			count++;
		}
	}


	printf("%d\n%d\n", maxArriveTime[end], count);

	return 0;
}