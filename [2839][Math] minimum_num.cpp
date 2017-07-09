// Problem Number: 2839						 
// URL: https://www.acmicpc.net/problem/2839 
// Date: 2017.07.09							 
// Purpose: 1) Math
// Time: O(MAX_N)

#include <iostream>

#define MAX_N 5001

using namespace std;

int arr[MAX_N];

int main(void) {
	int N;

	arr[0] = 0;
	arr[1] = -1;
	arr[2] = -1;
	arr[3] = 1;
	arr[4] = -1;
	arr[5] = 1;

	for (int i = 6;i < MAX_N;i++) {
		if (arr[i - 3] == -1 && arr[i - 5] == -1) {
			arr[i] = -1;
		}
		else if(arr[i-3] == -1){
			arr[i] = arr[i - 5] + 1;
		}
		else if (arr[i - 5] == -1) {
			arr[i] = arr[i - 3] + 1;
		}
		else {
			arr[i] = (arr[i - 3] > arr[i - 5]) ? arr[i - 5] + 1 : arr[i - 3] + 1;
		}
		
	}

	cin >> N;
	cout << arr[N] << endl;
	return 0;
}