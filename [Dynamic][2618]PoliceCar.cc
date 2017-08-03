#include <cstdio>
#include <algorithm>

#define MAX_N 2000
#define MAX_W 2000
#define INF 150000000

using namespace std;

struct Case {
	int y;
	int x;
};

int min(int a, int b) {
	return (a < b) ? a : b;
}

int D[MAX_W][MAX_W];
Case incident[MAX_W];
Case BackTrack[MAX_W][MAX_W];

int distance(Case a, Case b) {
	int ret = (a.y > b.y) ? (a.y - b.y) : (b.y - a.y);
	ret += (a.x > b.x) ? (a.x - b.x) : (b.x - a.x);
	return ret;
}

int main(void) {
	int n;
	scanf("%d", &n);
	int w;
	scanf("%d", &w);
	for (int i = 1; i <= w; i++) {
		int y, x;
		scanf("%d %d", &y, &x);
		incident[i] = { y,x };
	}

	fill(&D[0][0], &D[MAX_W - 1][MAX_W], INF);

	Case start1, start2;
	start1 = { 1, 1 };
	start2 = { n,n };

	for (int i = 0; i <= w; i++) {
		int x = w - i;
		int y = w;

		for (; x <= w; x++, y--) {
			if (x == y) continue;
			if (x == w || y == w) {
				D[y][x] = 0;
				continue;
			}

			int m = (y > x) ? y : x;
			m++;
			int y_to_m;
			if(y == 0)
				y_to_m = D[m][x] + distance(start1, incident[m]); 
			else
				y_to_m = D[m][x] + distance(incident[y], incident[m]);
			int x_to_m;
			if (x == 0)
				x_to_m = D[y][m] + distance(start2, incident[m]);
			else
				x_to_m = D[y][m] + distance(incident[x], incident[m]);
			D[y][x] = min(y_to_m, x_to_m);
			
			if(D[y][x] == x_to_m) {
				BackTrack[y][x].y = y;
				BackTrack[y][x].x = m;
			}else {
				BackTrack[y][x].y = m;
				BackTrack[y][x].x = x;
			}
		}
	}

	for (int i = 1; i <= w; i++) {
		int y = w - i;
		int x = 0;
		for (; x <= w-i; x++, y--) {
			if (x == y) continue;
			if (x == w || y == w) {
				D[y][x] = 0;
				continue;
			}

			int m = (y > x) ? y : x;
			m++;
			int y_to_m;
			if (y == 0)
				y_to_m = D[m][x] + distance(start1, incident[m]);
			else
				y_to_m = D[m][x] + distance(incident[y], incident[m]);
			int x_to_m;
			if (x == 0)
				x_to_m = D[y][m] + distance(start2, incident[m]);
			else
				x_to_m = D[y][m] + distance(incident[x], incident[m]);
			D[y][x] = min(y_to_m, x_to_m);
			
			if(D[y][x] == x_to_m) {
				BackTrack[y][x].y = y;
				BackTrack[y][x].x = m;
			}else {
				BackTrack[y][x].y = m;
				BackTrack[y][x].x = x;
			}
		}
	}
	if (w == 0) {
		printf("0\n");
	}
	else {
		printf("%d\n", min(D[0][1] + distance(start2, incident[1]), D[1][0] + distance(start1, incident[1])));
	}

	int x, y;
	if (min(D[0][1] + distance(start2, incident[1]), D[1][0] + distance(start1, incident[1])) == D[0][1] + distance(start2,incident[1])) {
		y = 0;
		x = 1;
	}
	else {
		y = 1;
		x = 0;
	}

	for (int i = 1; x <= w && y <= w && i <= w;i++) {
		if (i == x) {
			printf("2\n");
		}
		else {
			printf("1\n");
		}
		Case t = BackTrack[y][x];
		x = t.x;
		y = t.y;
	}

	return 0;
}