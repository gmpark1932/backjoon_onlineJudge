/* Problem Number: 2749									  */
/* URL: https://www.acmicpc.net/problem/2749			  */
/* Date: 2017.07.05										  */
/* Purpose: 1) Recursion Formula -> Matrix Multiplication */
/*			2) Matrix Multiplication -> D&C				  */

#include <iostream>

#define _isEven(n) (n%2 == 0)

#define MOD 1000000

class Matrix_2x2 {
private:
	long long int data[2][2];

public:
	Matrix_2x2* operator=(const Matrix_2x2& m);
	Matrix_2x2(const long long int[][2]);
	Matrix_2x2(const long int a, const long int b, const long int c, const long int d) {
		data[0][0] = a;
		data[0][1] = b;
		data[1][0] = c;
		data[1][1] = d;
	}
	long long int operator[](const int idx) {
		return data[idx / 2][idx % 2];
	}
	Matrix_2x2 operator*(const Matrix_2x2& m);
	void printData(void) {
		printf("%d %d\n%d %d\n", data[0][0], data[0][1], data[1][0], data[1][1]);
		printf("-----------------------\n");
	}
};

Matrix_2x2::Matrix_2x2(const long long int m[][2]) {
	data[0][0] = m[0][0]%MOD;
	data[0][1] = m[0][1]%MOD;
	data[1][0] = m[1][0]%MOD;
	data[1][1] = m[1][1]%MOD;
}

Matrix_2x2* Matrix_2x2::operator=(const Matrix_2x2& m) {
	this->data[0][0] = m.data[0][0];
	this->data[0][1] = m.data[0][1];
	this->data[1][0] = m.data[1][0];
	this->data[1][1] = m.data[1][1];

	return this;
}

Matrix_2x2 Matrix_2x2::operator*(const Matrix_2x2& m) {
	long long int t[2][2] = {
		((data[0][0] * m.data[0][0])%MOD + (data[0][1] * m.data[1][0])%MOD)%MOD,
		((data[0][0] * m.data[0][1])%MOD + (data[0][1] * m.data[1][1])%MOD)%MOD,
		((data[1][0] * m.data[0][0])%MOD + (data[1][1] * m.data[1][0])%MOD)%MOD,
		((data[1][0] * m.data[0][1])%MOD + (data[1][1] * m.data[1][1])%MOD)%MOD
	};
	Matrix_2x2 result(t);
	return result;
}

Matrix_2x2 powerMatrix(const Matrix_2x2& m,long long int n) {
	if (n == 0) {
		Matrix_2x2 result(1, 0, 0, 1);
		return result;
	}

	if (n == 1) {
		return m;
	}
	 
	Matrix_2x2 halfResult = powerMatrix(m, n / 2);
	//halfResult.printData();
	if (_isEven(n)) {
		return halfResult*halfResult;
	}
	else {
		return halfResult*halfResult*m;
	}
}

using namespace std;

int main(void) {
	Matrix_2x2 A(1,1,1,0);
	long long int n;

	//A.printData();
	cin >> n;
	//powerMatrix(A, n - 1).printData();
	cout << powerMatrix(A, n-1)[0] << endl;

	return 0;
}