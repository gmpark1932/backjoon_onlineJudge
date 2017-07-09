// Problem Number: 7469						 
// URL: https://www.acmicpc.net/problem/7469 
// Date: 2017.07.09							 
// Purpose: 1) Using stl sort
// Time: O(MAX_M * MAX_N)

#include <stdio.h>
#include <algorithm>

#define MAX_N 100000
#define MAX_M 5000

typedef struct _node {
	int idx;
	int data;
}Node;

Node arr[MAX_N];

bool cmp(Node &a, Node &b) {
	return a.data < b.data;
}

int find_k_th(int goal_idx ,int size, int left, int right) {
	for (int i = 0; i < size; i++) {
		if (arr[i].idx >= left && arr[i].idx <= right) {
			goal_idx--;
			if (goal_idx == 0)
				return arr[i].data;
		}
	}

	return -1;
}

int main(void) {
	int n, m;

	scanf("%d %d",&n, &m);

	for (int i = 0; i < n; i++) {
		arr[i].idx = i;
		scanf("%d", &arr[i].data);
	}

	std::sort(arr, arr + n,cmp);

	for (int i = 0; i < m; i++) {
		int left, right, goal_idx;

		scanf("%d %d %d", &left, &right, &goal_idx);

		printf("%d\n", find_k_th(goal_idx,n, left - 1, right - 1));
	}

	return 0;
}