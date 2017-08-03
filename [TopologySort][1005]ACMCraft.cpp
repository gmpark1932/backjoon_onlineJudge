#include <cstdio>
#include <queue>
#include <vector>

#define MAX_N 1010

using namespace std;

vector<int> start_time(MAX_N);
vector<int> graph[MAX_N];
vector<int> build_time(MAX_N);
vector<int> in_degree(MAX_N);

int main(void) {
	int T;
	scanf("%d", &T);
	for (int _t = 0; _t < T; _t++) {
		int n, k;
		scanf("%d %d", &n, &k);
		
		fill(build_time.begin(), build_time.end(), 0);
		fill(start_time.begin(), start_time.end(), 0);
		fill(in_degree.begin(), in_degree.end(), 0);
		for (int i = 0; i < MAX_N; i++) {
			graph[i].clear();
		}

		for (int i = 1; i <= n; i++) {
			int time;
			scanf("%d", &time);
			build_time[i] = time;
		}

		for (int i = 1; i <= k; i++) {
			int b1, b2;
			scanf("%d %d", &b1, &b2);
			graph[b1].push_back(b2);
			in_degree[b2]++;
		}
		
		int goal_building;
		scanf("%d", &goal_building);

		queue<int> q;
		for (int i = 1; i <= n; i++) {
			if (in_degree[i] == 0)
				q.push(i);
		}

		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (int b : graph[node]) {
				in_degree[b]--;
				if (in_degree[b] == 0)
					q.push(b);

				int buildTime = start_time[node] + build_time[node];
				start_time[b] = (start_time[b] < buildTime) ? buildTime : start_time[b];
			}
		}
		
		printf("%d\n", start_time[goal_building] + build_time[goal_building]);
	}

	return 0;
}