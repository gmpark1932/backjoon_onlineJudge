// Problem Number: 1912						 
// URL: https://www.acmicpc.net/problem/1912 
// Date: 2017.07.10							 
// Purpose: 1) Dynamic Algorithm ( Save Already Found Cost )
//			2) Set Sum[k] : max sum start from index k


#include <cstdio>
#include <vector>

using namespace std;

#define MAX_N 100001

vector<int> arr(MAX_N);

int findMaxSequentialSum(vector<int> &arr,int size) {
	int max_sum=arr[size-1];
	int before_max=arr[size-1];

	for (int i = size - 2; i >= 0; i--) {
		int current_max;

		if (before_max < 0)
			current_max = arr[i];
		else
			current_max = before_max + arr[i];

		if (max_sum < current_max)
			max_sum = current_max;
		before_max = current_max;
	}
	
	return max_sum;
}

int main(void) {
	int n;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	
	printf("%d\n",findMaxSequentialSum(arr, n));

	return 0;
}