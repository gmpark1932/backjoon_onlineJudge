#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 1010

struct Node {
	enum Choice {
		LEFT, RIGHT
	} choice;
	int max_point;
};

vector<vector<Node>> D(MAX_N, vector<Node>(MAX_N));
vector<int> Cost(MAX_N);

int larger(int a, int b) {
	return (a < b) ? b : a;
}

int solve(int left, int right) {
	if (left == right) {
		D[left][right] = { Node::LEFT, Cost[left] };
		return Cost[left];
	}
	if (left > right)
		return 0;

	if (D[left][right].max_point != -1)
		return D[left][right].max_point;

	int pick_left = 0, pick_right = 0;

	pick_left += Cost[left];
	//left + 1 ~ right가 남았고, 이에 대해서 상대방은 최선의 선택을 한다.
	solve(left + 1, right);
	if (D[left + 1][right].choice == Node::LEFT) {
		pick_left += solve(left + 2, right);
	}
	else {
		pick_left += solve(left + 1, right - 1);
	}


	pick_right += Cost[right];
	solve(left, right - 1);
	if (D[left][right - 1].choice == Node::LEFT) {
		pick_right += solve(left + 1, right - 1);
	}
	else {
		pick_right += solve(left, right - 2);
	}

	int result = 0;
	if (pick_left < pick_right) {
		result = pick_right;
		D[left][right] = { Node::RIGHT, pick_right };
	}
	else {
		result = pick_left;
		D[left][right] = { Node::LEFT,pick_left };
	}

	return result;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		for (int i = 0; i < MAX_N; i++)
			for (int j = 0; j < MAX_N; j++)
				D[i][j] = { Node::LEFT , -1 };
		fill(Cost.begin(), Cost.end(), 0);

		int n;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			int c;
			scanf("%d", &c);
			Cost[i] = c;
		}

		printf("%d\n", solve(0, n - 1));
	}
	return 0;
}