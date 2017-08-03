#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define MAX_RC 1010
#define MAX_N 20
#define VALID 1
#define INF -1


int street[MAX_RC][MAX_RC] = { 0 };

struct Rule{
	int r;
	int c;
};

Rule rule[MAX_N];

struct Node {
	int r;
	int c;
};

vector<Node> graph[MAX_RC][MAX_RC];

int r_size;
int c_size;

bool can_go(int cur_r, int cur_c, Rule _rule) {
	int next_r = cur_r + _rule.r;
	int next_c = cur_c + _rule.c;
	
	if (next_r >= 0 && next_r < r_size && next_c >= 0 && next_c < c_size
		&& street[next_r][next_c] == VALID) {
		return true;
	}

	return false;
}

Node applyRule(int r, int c, Rule _rule) {
	Node t;
	t.r = r + _rule.r;
	t.c = c + _rule.c;
	return t;
}

void makeGraph(int rule_number) {
	int r = r_size;
	int c = c_size;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (int k = 0; k < rule_number; k++) {
				if (can_go(i, j, rule[k])) {
					graph[i][j].push_back(applyRule(i, j, rule[k]));
				}
			}
		}
	}

	for (int i = 0; i < c_size; i++) {
		if (street[0][i] == VALID) {
			Node t;
			t.r = 0;
			t.c = i;
			graph[r_size][c_size].push_back(t);
		}
	}
}

struct GraphNode {
	int ver_r;
	int ver_c;
	int cost;
};

struct comparator {
	bool operator()(GraphNode i, GraphNode j) {
		return i.cost > j.cost;
	}
};

priority_queue < GraphNode, std::vector<GraphNode>, comparator> minHeap;
int dist[MAX_RC][MAX_RC];

int getMinStep(void){
	int start_r = r_size;
	int start_c = c_size;
	
	fill(&dist[0][0], &dist[MAX_RC - 1][MAX_RC], INF);
	
	minHeap.push({ start_r,start_c,0 });

	dist[start_r][start_c] = 0;

	while (!minHeap.empty()) {
		GraphNode node = minHeap.top();
		minHeap.pop();

		for (vector<Node>::iterator itr = graph[node.ver_r][node.ver_c].begin()
			; itr != graph[node.ver_r][node.ver_c].end(); itr++) {
			int minDist = dist[node.ver_r][node.ver_c] + 1;

			if (dist[itr->r][itr->c] == INF) {
				dist[itr->r][itr->c] = minDist;
				minHeap.push({ itr->r,itr->c,minDist });
			}
			else if (dist[itr->r][itr->c] > minDist) {
				dist[itr->r][itr->c] = minDist;
			}
		}
	}

	int min = INF;
	for (int i = 0; i < c_size; i++) {
		if (street[r_size - 1][i] == VALID) {
			if (min == INF || (dist[r_size-1][i] != INF && min > dist[r_size - 1][i])) {
				min = dist[r_size - 1][i];
			}
		}
	}

	if (min == INF)
		return -1;
	else
		return min-1;
}

int main(void) {
	int r, c;
	scanf("%d %d", &r, &c);

	r_size = r;
	c_size = c;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int s;
			scanf("%d", &s);
			street[i][j] = s;
		}
	}

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int y, x;
		scanf("%d %d", &y, &x);
		rule[i].r = y;
		rule[i].c = x;
	}

	makeGraph(n);

	int result = getMinStep();

	printf("%d\n", result);

	return 0;
}