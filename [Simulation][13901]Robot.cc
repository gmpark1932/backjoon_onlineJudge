#include <cstdio>
#include <vector>

using namespace std;

#define MAX_N 1010

#define BLOCK 'x'
#define VISIT 'v'
#define EMPTY 0

int room[MAX_N][MAX_N] = { 0 };

enum direction {
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

direction dir_vec[4];

int height, width;

bool able_to_go(int r, int c) {
	bool ret = false;
	if (c != width - 1 && room[r][c + 1] == EMPTY) {
		return true;
	}

	if (c != 0 && room[r][c - 1] == EMPTY)
		return true;

	if (r != height - 1 && room[r + 1][c] == EMPTY)
		return true;

	if (r != 0 && room[r - 1][c] == EMPTY)
		return true;

	return false;
}

bool can_move_to_dir(int r, int c, direction dir) {
	switch (dir) {
	case UP: {
		if (r != 0 && room[r - 1][c] == EMPTY)
			return true;
	}break;
	case DOWN: {
		if (r != height - 1 && room[r + 1][c] == EMPTY)
			return true;
	}break;
	case LEFT: {
		if (c != 0 && room[r][c - 1] == EMPTY)
			return true;
	}break;
	case RIGHT:{
		if (c != width - 1 && room[r][c + 1] == EMPTY) 
			return true;
	}break;
	}

	return false;
}

void move_to_dir(int &sr, int &sc, direction dir) {
	switch (dir) {
	case LEFT: {
		sc--;
	}break;
	case RIGHT: {
		sc++;
	}break;
	case UP: {
		sr--;
	}break;
	case DOWN: {
		sr++;
	}break;
	}

	room[sr][sc] = VISIT;
}

int main(void) {
	int r, c;
	scanf("%d %d", &r, &c);
	height = r;
	width = c;
	int k;
	scanf("%d", &k);

	for (int i = 0; i < k; i++) {
		int br, bc;
		scanf("%d %d", &br, &bc);

		room[br][bc] = BLOCK;
	}

	int sr, sc;
	scanf("%d %d", &sr, &sc);
	room[sr][sc] = VISIT;

	for (int i = 0; i < 4; i++) {
		int d;
		scanf("%d", &d);
		dir_vec[i] = (direction)d;
	}

	int next_direction = 0;
	while (able_to_go(sr,sc)) {
		//printf("%d %d\n", sr, sc);
		for (int i = 0; i < 4; i++) {
			direction next = dir_vec[(next_direction + i) % 4];
			if (can_move_to_dir(sr, sc, next)) {
				move_to_dir(sr, sc, next);
				if (i != 0) {
					next_direction += i;
					next_direction %= 4;
				}
				break;
			}
		}
	}

	printf("%d %d\n", sr, sc);

	return 0;
}