// Problem Number : 9577
// URL: https://www.acmicpc.net/problem/9577 
// Date: 2017.07.21							 
// Purpose: 1) BipartiteMatching

#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#define MAX_NM 101

int time_to_piece[MAX_NM];
int piece_to_time[MAX_NM];
list<int> adj[MAX_NM];
bool visited[MAX_NM];

bool dfs(int p) {
	visited[p] = true;

	for (int t : adj[p]) {
		if (time_to_piece[t] == -1 || !visited[time_to_piece[t]] && dfs(time_to_piece[t])) {
			time_to_piece[t] = p;
			piece_to_time[p] = t;
			return true;
		}
	}

	return false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		int n, m;
		scanf("%d %d", &n, &m);

		for (int i = 0; i < MAX_NM; i++)
			adj[i].clear();

		for (int i = 1; i <= m; i++) {
			int start, end;
			scanf("%d %d", &start, &end);
			int count;
			scanf("%d", &count);
			for (int j = 0; j < count; j++) {
				int p;
				scanf("%d", &p);
				for (int k = start+1; k <= end; k++)
					adj[p].push_back(k);
			}
		}

		fill(time_to_piece, time_to_piece + MAX_NM, -1);
		fill(piece_to_time, piece_to_time + MAX_NM, -1);

		for (int i = 1; i <= n; i++) {
			adj[i].sort();
			adj[i].unique();
		}

		bool fail=false;
		for (int i = 1; i <= n; i++) {
			fill(visited, visited + MAX_NM, false);
			if (piece_to_time[i] == -1) {
				if (dfs(i) == false) {
					fail = true;
					break;
				}
			}
		}

		if (fail) printf("-1\n");
		else {//matching된 가장 마지막 시간(time)
			int last_time = 0;
			for (int i = 1; i <= 100; i++)
				if (time_to_piece[i] != -1)
					last_time = i;

			printf("%d\n", last_time);
		}
	}

	return 0;
}