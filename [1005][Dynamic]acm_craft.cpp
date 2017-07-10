// Problem Number: 1005						 
// URL: https://www.acmicpc.net/problem/1005 
// Date: 2017.07.10							 
// Purpose: 1) Dynamic Algorithm ( Save Already Found Cost )

#include <cstdio>
#include <list>
#include <algorithm>
#include <vector>

#define MAX_N 1001
#define MAX_K 100001

using namespace std;

vector<int> make_time_arr(MAX_N);
vector<vector<int>> rule_arr(MAX_N);
vector<pair<bool, int>> already_find(MAX_N);

int find_max_path_to_leave(int goal_building) {
	if (rule_arr[goal_building].empty()) //���� �ǹ��� ���� ��� �ڽ��� �ǹ� ���� �ð� ��ȯ
		return make_time_arr[goal_building];

	int result = 0;

	vector<int> &target_rule = rule_arr[goal_building];
	//���� ���� �� ���� ���� �ڽ�Ʈ�� ������ ����
	for (vector<int>::iterator iter = target_rule.begin(); iter != target_rule.end();iter++) {
		int temp_result;
		if (already_find.at(*iter).first == true) {
			temp_result = already_find.at(*iter).second;
		}
		else {
			temp_result = find_max_path_to_leave(*iter);
			already_find.at(*iter).first = true;
			already_find.at(*iter).second = temp_result;
		}

		if (temp_result > result)
			result = temp_result;
	}

	if (result == 0) //�߻��� �� ���� ���(Run time error ����)
		exit(1);

	result += make_time_arr[goal_building];
	return result;	
}

int main(void) {
	int T;

	scanf("%d", &T);
	for (int t = 0;t < T;t++) {
		int N, K, goal_building;
		scanf("%d %d", &N, &K);

		for (int i = 1;i <= N;i++) {
			scanf("%d", &make_time_arr.at(i));
		}

		for (int i = 1;i <= N;i++) {
			already_find.at(i).first = false;
		}

		for (int i = 1;i <= N;i++) {
			rule_arr.at(i).clear();
		}

		for (int i = 0;i < K;i++) {
			int dest, source;
			scanf("%d %d", &source, &dest);
			rule_arr.at(dest).push_back(source); //A->B�� Rule�� B rule vector�� A�� �����Ѵ�.
		}

		scanf("%d", &goal_building);
		
		printf("%d\n", find_max_path_to_leave(goal_building));
	}
	return 0;
}