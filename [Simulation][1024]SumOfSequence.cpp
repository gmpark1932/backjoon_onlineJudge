// Problem Number: 1024						 
// URL: https://www.acmicpc.net/problem/1024 
// Date: 2017.07.16							 
// Purpose: 1) Simulation

#include <iostream>

using namespace std;

int main(void) {
	int N, L;

	cin >> N >> L;

	int seq_start;
	int i;

	for (i = L; i <= 100; i++) {
		seq_start = (2 * N - i*(i - 1));
		if (seq_start % (2 * i) == 0 && seq_start >= 0) {
			seq_start /= 2 * i;
			break;
		}
	}

	if (i == 101)
		cout << -1 << endl;
	else {
		for (int j = 0; j < i; j++) {
			cout << seq_start + j << " ";
		}
		cout << endl;
	}

	return 0;
}