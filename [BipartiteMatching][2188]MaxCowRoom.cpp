#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_NM 201

int cow_to_room[MAX_NM];
int room_to_cow[MAX_NM];
bool visited[MAX_NM];
vector<int> adj[MAX_NM];

bool dfs(int a) {
	visited[a] = true;
	for (int room : adj[a]) {
		if (room_to_cow[room] == -1 || !visited[room_to_cow[room]] && dfs(room_to_cow[room])) {
			cow_to_room[a] = room;
			room_to_cow[room] = a;
			return true;
		}
	}
	return false;
}

int main(void) {
	int N, M;

	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++) {
		int count;
		scanf("%d", &count);

		for (int j = 1; j <= count; j++) {
			int t;
			scanf("%d", &t);
			adj[i].push_back(t);
		}
	}

	fill(cow_to_room, cow_to_room + MAX_NM, -1);
	fill(room_to_cow, room_to_cow + MAX_NM, -1);

	int result = 0;
	for (int i = 1; i <= N; i++) {
		if (cow_to_room[i] == -1) {
			fill(visited, visited + MAX_NM, false);
			if (dfs(i))
				result++;
		}
	}

	printf("%d\n", result);

	return 0;
}