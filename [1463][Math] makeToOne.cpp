// Problem Number: 1463						 
// URL: https://www.acmicpc.net/problem/1463 
// Date: 2017.07.09							 
// Purpose: 1) Math(Compare To Past Result -> Current Result)
//			2) Consider All Possible Option

#include <iostream>
#include <cmath>

using namespace std;

int arr[1000001];

int main(void) {
	int N;
	int result;
	cin >> N;

	arr[1] = 0;
	arr[2] = 1;
	arr[3] = 1;

	if (N == 1) result = 0;
	else if (N <= 3) result = 1;
	else {
		for (int i = 4;i <= N;i++) {
			int temp = i-1; //그냥 -1을 계속 했을 때
			if (i % 2 == 0 && temp > arr[i / 2] + 1) temp = arr[i / 2] + 1; //2로 나눌 수 있음
			if (i % 3 == 0 && temp > arr[i / 3] + 1) temp = arr[i / 3] + 1; //3으로 나눌 수 있음
			if (temp > arr[i - 1] + 1) temp = arr[i - 1] + 1; //1을 빼고 진행했을 때
			if (temp > arr[i - 2] + 2) temp = arr[i - 2] + 2; //2를 빼고 진행했을 때
			arr[i] = temp;
		}

		result = arr[N];
	}

	cout << result << endl;
	
	return 0;
}