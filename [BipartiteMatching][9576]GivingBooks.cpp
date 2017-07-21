// Problem Number: 9576						 
// URL: https://www.acmicpc.net/problem/9576 
// Date: 2017.07.21							 
// Purpose: 1) BipartiteMatching

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_NM 1001

int stu_to_book[MAX_NM];
int book_to_stu[MAX_NM];
bool visited[MAX_NM];
vector<int> adj[MAX_NM];

bool dfs(int a) {
	visited[a] = true;
	for (int book : adj[a]) {
		if (book_to_stu[book] == -1 || !visited[book_to_stu[book]] && dfs(book_to_stu[book])) {
			stu_to_book[a] = book;
			book_to_stu[book] = a;
			return true;
		}
	}
	return false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	
	for (int tc = 0; tc < T; tc++) {
		int N, M;

		scanf("%d %d", &N, &M);

		for (int i = 1; i <= M; i++) {
			int start, end;
			scanf("%d %d", &start, &end);

			adj[i].clear();

			for (int j = start; j <= end; j++) {
				adj[i].push_back(j);
			}
		}

		fill(stu_to_book, stu_to_book + MAX_NM, -1);
		fill(book_to_stu, book_to_stu + MAX_NM, -1);

		int result = 0;
		for (int i = 1; i <= M; i++) {
			if (stu_to_book[i] == -1) {
				fill(visited, visited + MAX_NM, false);
				if (dfs(i))
					result++;
			}
		}

		printf("%d\n", result);
	}
	return 0;
}