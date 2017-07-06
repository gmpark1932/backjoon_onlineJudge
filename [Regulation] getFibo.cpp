/* Problem Number: 2749						 */
/* URL: https://www.acmicpc.net/problem/2749 */
/* Date: 2017.07.05							 */
/* Purpose: Find Regulation(Pisano Period)	 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/* 피사노 주기를 이용한 풀이법 */

#define MOD 1000000

#define _loopSize 1500000

int loopArr[_loopSize];

void makeFiboArr(void) {
	static int a = 0;
	static int b = 1;
	static int count = 0;
	int result;


	switch (count) {
	case 0: {
		result = a;
		break;
	}
	case 1: {
		result = b;
		break;
	}
	default:
		int temp_b = b;
		result = (a + b) % MOD;
		b = result;
		a = temp_b;
		break;
	}

	loopArr[count] = result;

	count++;
}

using namespace std;

int main(void) {
	long long int n;

	cin >> n;

	for (int i = 0;i < _loopSize;i++) {
		makeFiboArr();
	}

	int idx = n % _loopSize;

	cout << loopArr[idx] << endl;

	return 0;
}