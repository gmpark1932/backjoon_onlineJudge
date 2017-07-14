// Problem Number: 2098						 
// URL: https://www.acmicpc.net/problem/2098 
// Date: 2017.07.14							 
// Purpose: 1) Dynamic Algorithm ( Save Already Found Cost )
//			2) Define already found data saving data structure( bit mask )

#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

#define MAX_N 17
#define INF_COST -1

#define DEBUG false

class VertexSet {
private:
	int bitflag=0; // 17번째 bit부터 32번째 bit까지 (15 ~ 0 번) vertex를 나타냄

public:
	VertexSet(int bitflag) {
		this->bitflag = bitflag;
	}
	VertexSet() {}

	void insertVertex(int vertex_number) {
		int t = 1 << vertex_number;
		bitflag = bitflag | t;
	}

	void removeVertex(int vertex_number) {
		int t = 1 << vertex_number;
		bitflag = bitflag & (~t);
	}

	int popFront(void) {
		int t = 1;
		int temp_bitflag = bitflag;
		for (int i = 0;i < 16;i++) {
			if (temp_bitflag & t == 1) {
				removeVertex(i);
				return i;
			}
			temp_bitflag = temp_bitflag >> 1;
		}
		return -1;
	}

	bool isEmpty(void) {
		if (bitflag == 0)
			return true;
		else return false;
	}

	VertexSet& operator=(VertexSet& set) {
		this->bitflag = set.bitflag;
		return *this;
	}

	bool operator==(VertexSet& set) {
		return this->bitflag == set.bitflag;
	}

	int getBitFlag(void) {
		return bitflag;
	}
};

vector<vector<int>> edge_cost(MAX_N, vector<int>(MAX_N));

#define AF_SIZE 65537

int already_found[MAX_N][AF_SIZE] = { 0 };

int start_vertex = 0;
int N;

int traverSetMinCost(int start_vertex, int entry_point, VertexSet others) {
	if (others.isEmpty()) {
		return edge_cost[entry_point][start_vertex];
	}
	
	VertexSet temp_vertexSet = others;

	int min_cost = INF_COST;
	int selectedVertex = -1;
	bool first_time = true;

	while (!others.isEmpty()) {
		int v = others.popFront();
		int temp_min_cost;
		
		if (edge_cost[entry_point][v] == INF_COST)
			continue;

		VertexSet t = temp_vertexSet;
		t.removeVertex(v);
		
		if (already_found[v][t.getBitFlag()] == 0) {
			temp_min_cost = traverSetMinCost(start_vertex, v, t);
			if (temp_min_cost == INF_COST) {
				already_found[v][t.getBitFlag()] = temp_min_cost;
				continue;
			}
			already_found[v][t.getBitFlag()] = temp_min_cost;				
		}
		else {
			temp_min_cost = already_found[v][t.getBitFlag()];
		}
		
		if (temp_min_cost == INF_COST)
			continue;

		temp_min_cost += edge_cost[entry_point][v];

		if (first_time) {
			min_cost = temp_min_cost;
			selectedVertex = v;
			first_time = false;
		}
		else if (min_cost > temp_min_cost) {
			selectedVertex = v;
			min_cost = temp_min_cost;
		}
	}

	return min_cost;
}

//For Debug
static void printBinary(int a) {
	int i = 7;

	for (i; i >= 0; --i)
		printf("%d", (a >> i) & 1);
}

int main(void) {
	scanf("%d", &N);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			scanf("%d", &edge_cost[i][j]);
			if (edge_cost[i][j] == 0 && i != j) // 서로 연결 되어 있지 않은 두 vertex
				edge_cost[i][j] = INF_COST;
		}
	}

	VertexSet othersOfVertexZero;

	for (int i = 1;i < N;i++)
		othersOfVertexZero.insertVertex(i);

	int min_cost = traverSetMinCost(0, 0, othersOfVertexZero);

	if (DEBUG) {
		for (int i = 0; i < N; i++) {
			printf("From : %d ->\t", i);
			for (int j = 0; j < AF_SIZE; j++)
				if (already_found[i][j] != 0) {
					printBinary(j);
					printf(": %d\t", already_found[i][j]);
				}
			printf("\n");
		}
	}

	printf("%d\n", min_cost);

	return 0;
}