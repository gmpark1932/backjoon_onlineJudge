// Problem Number: 10253						 
// URL: https://www.acmicpc.net/problem/10253 
// Date: 2017.07.16							 
// Purpose: 1) Simulation

#include <iostream>

using namespace std;

int main(void) {
	int T;
	int a, b;

	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> a >> b;
		int xi;

		while (true) {
			if (b % a == 0) {
				xi = b / a;
				break;
			}
			else {
				xi = b / a + 1;
				a = a*xi - b;
				b = b*xi;
			}
		}

		cout << xi << endl;
	}

	return 0;
}