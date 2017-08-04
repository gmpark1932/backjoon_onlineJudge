#include <cstdio>
#include <queue>
#include <vector>

#define MAX_N 510

using namespace std;

vector<int> build_time(MAX_N, 0);
vector<int> start_time(MAX_N, 0);
vector<int> build_rule[MAX_N];
vector<int> in_degree(MAX_N, 0);

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int time;
		scanf("%d", &time);
		build_time[i] = time;

		int before = 1;
		while (before != -1) {
			scanf("%d", &before);
			if (before != -1) {
				build_rule[before].push_back(i);
				in_degree[i]++;
			}
		}
	}

	queue<int> q;

	for (int i = 1; i <= n; i++) {
		if (in_degree[i] == 0)
			q.push(i);
	}

	while (q.empty() == false) {
		int b = q.front();
		q.pop();

		for (int after : build_rule[b]) {
			in_degree[after]--;
			if (in_degree[after] == 0)
				q.push(after);
			
			int time = start_time[b] + build_time[b];
			if (time > start_time[after])
				start_time[after] = time;
		}
	}

	for (int i = 1; i <= n; i++) {
		printf("%d\n", start_time[i] + build_time[i]);
	}

	return 0;
}