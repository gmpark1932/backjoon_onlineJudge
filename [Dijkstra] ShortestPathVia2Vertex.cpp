// Problem Number: 1504						 
// URL: https://www.acmicpc.net/problem/1504 
// Date: 2017.07.09							 
// Purpose: 1) Dijkstra algorithm
// Time: O(MAX_N * MAX_N)

#include <cstdio>
#include <cstring>

#define MAX_N 801
#define INF 1000000

int cost_arr[MAX_N][MAX_N]; //edge cost
int min_cost_arr_1[MAX_N]; //start vertex������ �ִܰŸ�
int min_cost_arr_2[MAX_N]; //v1������ �ִܰŸ�
int min_cost_arr_3[MAX_N]; //v2������ �ִܰŸ�
bool find_min_cost_flag[MAX_N]; //S'(�ִܰŸ��� ã�� ���� ����) ǥ��

void find_shortest_path(int min_cost[], int v1, int last_idx) {
	memset(find_min_cost_flag, 0, sizeof(bool)*MAX_N);

	for (int i = 1; i <= last_idx; i++)
		min_cost[i] = cost_arr[v1][i];

	min_cost[v1] = 0;
	find_min_cost_flag[v1] = true; //True�̸� S'�� ��� �ִ� ����

	for (int i = 1; i < last_idx; i++) {//last_idx - 1 �� �ݺ��ϸ� S'�� �� ���Ҿ� ����
		int min_idx;
		int temp_min_cost = INF;

		/* min_cost�� ã�� ���� vertex �� �Ÿ��� ���� ���� �� ã�� */
		for (int j = 1; j <= last_idx; j++) {
			if (find_min_cost_flag[j] == false && min_cost[j] <= temp_min_cost) {
				temp_min_cost = min_cost[j];
				min_idx = j;
			}
		}

		if (temp_min_cost == INF) {//S'�� ���� vertex�� �ִܰŸ��� INF��� ����
			break;
		}

		find_min_cost_flag[min_idx] = true;

		/* min_idx�� ���ļ� ���� �� ���� cost�� �� �� �ִ��� Ȯ���ϴ� ���� */
		for (int j = 1; j <= last_idx; j++) {
			if (find_min_cost_flag[j] == false &&
				(min_cost[j] > min_cost[min_idx] + cost_arr[min_idx][j])) {
				min_cost[j] = min_cost[min_idx] + cost_arr[min_idx][j];
			}
		}
	}
}

int main(void) {
	int N, E;
	int via1, via2;
	int arr[10] = { -1 };

	scanf("%d %d", &N, &E);

	for (int i = 0;i < MAX_N;i++)
		for (int j = 0;j < MAX_N;j++)
			cost_arr[i][j] = INF;

	for (int i = 0; i < E; i++) {
		int v1, v2, cost;

		scanf("%d %d %d", &v1, &v2, &cost);

		cost_arr[v1][v2] = cost;
		cost_arr[v2][v1] = cost;
	}

	scanf("%d %d", &via1, &via2);

	find_shortest_path(min_cost_arr_1, 1, N);
	find_shortest_path(min_cost_arr_2, via1, N);
	find_shortest_path(min_cost_arr_3, via2, N);

	int path1_cost, path2_cost;

	if (min_cost_arr_1[via1] == INF || min_cost_arr_2[via2] == INF || min_cost_arr_3[N] == INF)
		path1_cost = -1;
	else
		path1_cost = min_cost_arr_1[via1] + min_cost_arr_2[via2] + min_cost_arr_3[N];

	if (min_cost_arr_1[via2] == INF || min_cost_arr_3[via1] == INF || min_cost_arr_2[N] == INF)
		path2_cost = -1;
	else
		path2_cost = min_cost_arr_1[via2] + min_cost_arr_3[via1] + min_cost_arr_2[N];

	int result;

	if (path1_cost == -1) result = path2_cost;
	else if (path2_cost == -1) result = path1_cost;
	else result = (path1_cost < path2_cost) ? path1_cost : path2_cost;

	printf("%d\n", result);

	return 0;
}