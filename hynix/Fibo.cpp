// P10826.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#pragma warning(disable:4996)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

typedef struct {
	unsigned long long int mat[2][2];
}Matrix;

#define MOD 1000000

const Matrix oneMatrix = { { { 1,1 },{ 1,0 } } };

Matrix MatMultiply(Matrix a, Matrix b) {
	Matrix result;
	result.mat[0][0] = (a.mat[0][0] * b.mat[0][0])%MOD + (a.mat[0][1] * b.mat[1][0])%MOD;
	result.mat[0][1] = (a.mat[0][0] * b.mat[0][1])%MOD + (a.mat[0][1] * b.mat[1][1])%MOD;
	result.mat[1][0] = (a.mat[1][0] * b.mat[0][0])%MOD + (a.mat[1][1] * b.mat[1][0])%MOD;
	result.mat[1][1] = (a.mat[1][0] * b.mat[0][1])%MOD + (a.mat[1][1] * b.mat[1][1])%MOD;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.mat[i][j] %= MOD;
		}
	}

	return result;
}

Matrix GetMatrixNSquare(Matrix a, unsigned long long int n) {
	if (n == 0)
		return { { {1,0}, {0,1} } };

	if (n == 1)
		return a;

	Matrix b = GetMatrixNSquare(a, n / 2);
	Matrix result;

	if (n % 2 == 0) {
		result = MatMultiply(b, b);
	}
	else {
		result = MatMultiply(b, MatMultiply(b, a));
	}

	return result;
}

unsigned long long int MakeFibo(unsigned long long int n) {
	Matrix result = GetMatrixNSquare(oneMatrix, n);
	return result.mat[1][0];
}

int main()
{
	unsigned long long int n;
		scanf("%llu", &n);
	
		unsigned long long int result;

		if (n == 0) {
			printf("0\n");
		}
		else {

			result = MakeFibo(n);

			printf("%llu\n",result);

		}
		//system("pause");
	return 0;
}

