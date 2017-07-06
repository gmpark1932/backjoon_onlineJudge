// Problem Number: 2448									
// URL: https://www.acmicpc.net/problem/2448			  
// Date: 2017.07.06										  
// Purpose: 1) Divide and Conquer Example			  

#include <iostream>
#include <stdlib.h>

#define STAR '*'

char outputArray[3072][6144];

void printMinimumTriangle(int x, int y) {
	outputArray[y][x] = STAR;
	outputArray[y + 1][x - 1] = STAR;
	outputArray[y + 1][x + 1] = STAR;
	for (int i = x - 2;i <= x + 2;i++)
		outputArray[y + 2][i] = STAR;

}
void printStars(int n, int x, int y) {
	if (n <= 3) {
		printMinimumTriangle(x, y);
		return;
	}
	printStars(n / 2, x, y);
	printStars(n / 2, x - n / 2, y + n / 2);
	printStars(n / 2, x + n / 2, y + n / 2);
}

void initOutputArray(int n) {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < 2 * n - 1;j++) {
			outputArray[i][j] = ' ';
		}
	}
}

using namespace std;

void printOutputArray(int n) {
	for (int i = 0;i<n;i++) {
		outputArray[i][2 * n - 1] = '\0';
		cout << outputArray[i] << endl;
	}
}

int main(void) {
	int n;
	cin >> n;

	initOutputArray(n);

	printStars(n, n - 1, 0);

	printOutputArray(n);

	return 0;
}
