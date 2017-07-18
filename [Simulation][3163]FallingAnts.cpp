// Problem Number: 3163						 
// URL: https://www.acmicpc.net/problem/3163 
// Date: 2017.07.18							 
// Purpose: 1) Simulation
//			2) Mathematical Modeling
//				- Ants moving -> function
//				- Falling -> intersection with x=L, x=0


#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int start_pos;
	int id;
	int degree;
	int conflict_point;
};

struct Falling {
	int id;
	int time;
};

vector<Node> ant_functions;
vector<Falling> falling_timing;

bool falling_cmp(Falling& a, Falling& b) {
	if (a.time == b.time)
		return a.id < b.id;
	else
		return a.time < b.time;
}

int main(void) {
	int T;
	scanf("%d", &T);

	for (int testcase = 0; testcase < T; testcase++) {
		ant_functions.clear();
		falling_timing.clear();

		int N, L, k;
		scanf("%d %d %d", &N, &L, &k);
		
		for (int i = 0; i < N; i++) {
			int pi, ai;
			scanf("%d %d", &pi, &ai);
			Node temp = { pi,ai,(ai > 0) ? 1 : -1, 0 };
			ant_functions.push_back(temp);
		}

		//각 충돌점 갯수 구하기
		int minus_degree_count = 0;
		for (vector<Node>::reverse_iterator r_itr = ant_functions.rbegin(); r_itr != ant_functions.rend(); r_itr++) {
			if (r_itr->degree == 1) {
				r_itr->conflict_point = minus_degree_count;
			}
			else {
				minus_degree_count++;
			}
		}

		int plus_degree_count = 0;
		for (vector<Node>::iterator itr = ant_functions.begin(); itr != ant_functions.end(); itr++) {
			if (itr->degree == -1) {
				itr->conflict_point = plus_degree_count;
			}
			else {
				plus_degree_count++;
			}
		}

		//각 함수별 y=L, y=0과 교차하는 점을 계산하여 falling_timing에 저장
		for (int i = 0; i < ant_functions.size();i++) {
			if (ant_functions[i].degree == 1) {
				Falling t = { ant_functions[i + ant_functions[i].conflict_point].id, L - ant_functions[i].start_pos };
				falling_timing.push_back(t);
			}
			else {
				Falling t = { ant_functions[i - ant_functions[i].conflict_point].id, ant_functions[i].start_pos };
				falling_timing.push_back(t);
			}
		}

		sort(falling_timing.begin(), falling_timing.end(), falling_cmp);
		printf("%d\n", falling_timing[k - 1].id);
	}

	return 0;
}