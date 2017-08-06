#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 110
#define MAX_VAL 1010

struct Node {
	bool valid = false;
	int point;
	int count;
};

int STR[MAX_N], INT[MAX_N], PNT[MAX_N];
bool usedPoint[MAX_N];
Node DP[MAX_VAL][MAX_VAL];

int n;

void setDP(int st, int in, int count) {
	if (st > MAX_VAL - 1)
		st = MAX_VAL - 1;
	if (in > MAX_VAL - 1)
		in = MAX_VAL - 1;
	
	DP[st][in].count = count;
}

Node getDP(int st, int in, bool &getNew) {
	if (st > MAX_VAL - 1)
		st = MAX_VAL - 1;
	if (in > MAX_VAL - 1)
		in = MAX_VAL - 1;

	getNew = false;

	if (DP[st][in].valid)
		return DP[st][in];


	getNew = true;
	Node result = { true,0,0 };

	for (int i = 0; i < n; i++) {
		if (STR[i] <= st || INT[i] <= in) {
			result.count++;
			result.point += PNT[i];
		}
	}

	DP[st][in] = result;
	return result;
}

int solve(int st, int in) {
	bool getNew;
	Node node = getDP(st, in, getNew);
	if (!getNew) return node.count;

	int p = node.point - (st + in - 2);

	if (p == 0)
		return node.count;

	int max_count = 0;
	for (int i = 0; i <= p; i++) {
		int count = solve(st + i, in + p - i);
		if (max_count < count)
			max_count = count;
	}

	setDP(st, in, max_count);
	return max_count;
}

int main(void) {
	scanf("%d", &n);

	fill(&usedPoint[0], &usedPoint[MAX_N], false);
	
	for (int i = 0; i < n; i++) {
		int S, I, P;
		scanf("%d %d %d", &S, &I, &P);
		STR[i] = S;
		INT[i] = I;
		PNT[i] = P;
	}

	printf("%d\n", solve(1, 1));

	return 0;
}