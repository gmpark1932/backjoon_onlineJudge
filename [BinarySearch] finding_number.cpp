// Problem Number: 1920						 
// URL: https://www.acmicpc.net/problem/1920 
// Date: 2017.07.09							 
// Purpose: 1) Binary Search
// Time: O(MAX_N * log(MAX_N))

#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 100001

using namespace std;

int isExistInVector(int goal, vector<int>&arr,int left,int right) {
	while (left <= right) {
		int mid = (left + right) / 2;

		if (arr.at(mid) == goal)
			return 1;
		else if (arr.at(mid) > goal)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return 0;
}

int main(void) {
	int N, M;
	vector<int> arr;
	vector<int> goal_arr;

	scanf("%d", &N);

	for(int i=0;i<N;i++){
		int temp;
		scanf("%d", &temp);
		arr.push_back(temp);
	}

	scanf("%d", &M);

	for (int i = 0;i < M;i++) {
		int temp;
		scanf("%d", &temp);
		goal_arr.push_back(temp);
	}

	sort(arr.begin(),arr.end());

	for (int i = 0;i < M;i++) {
		printf("%d\n", isExistInVector(goal_arr.at(i), arr,0,N-1));
	}

	return 0;
}