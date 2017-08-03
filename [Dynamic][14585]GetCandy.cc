#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 301

int candy_map[MAX_N][MAX_N];

int main(void) {
	int N, M;

	scanf("%d %d", &N, &M);

	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < MAX_N; j++)
			candy_map[i][j] = 0;

	for (int i = 0; i < N; i++) {
		int x, y;

		scanf("%d %d", &x, &y);

		if (x + y < M)
			candy_map[x][y] = M - (x + y);
	}

	/*for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			printf("%d ", candy_map[i][j]);
		}
		printf("\n");
	}
*/
	for (int i = MAX_N - 1; i >= 0; i--) {
		for (int x = i, y = MAX_N - 1; x < MAX_N; x++, y--) {
			
			int right_result = 0;
			int up_result = 0;
			if (x < MAX_N - 1)
				right_result = candy_map[x + 1][y];
			if (y < MAX_N - 1)
				up_result = candy_map[x][y + 1];
			//printf("%d %d [%d][%d]\n", x, y,right_result,up_result);
			candy_map[x][y] += (right_result > up_result) ? right_result : up_result;
		}
	}

	for (int i = MAX_N - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			int x = j;
			int y = i - j;

			int right_result = 0;
			int up_result = 0;
			if (x < MAX_N - 1)
				right_result = candy_map[x + 1][y];
			if (y < MAX_N - 1)
				up_result = candy_map[x][y + 1];
			//printf("%d %d [%d][%d]\n", x, y, right_result, up_result);
			candy_map[x][y] += (right_result > up_result) ? right_result : up_result;
		}
	}

	printf("%d\n", candy_map[0][0]);

	return 0;
}