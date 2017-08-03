#include <cstdio>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

#define MAX_N 300
#define MAX_X 2000000000

list<pair<int, int>> dom_list;
int main(void) {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, h;

		scanf("%d %d", &x, &h);

		dom_list.push_back(make_pair(x, h));
		//del_flags.push_back(false);
	}

	dom_list.sort();

	int count = 0;
	while (!dom_list.empty()) {
		//오른쪽으로 쓰러트렸을 때 가장 많은 도미노를 쓰러뜨리는 놈은?
		vector<int> r_iter(dom_list.size());
		vector<int> l_iter(dom_list.size());

		int most_right_down = -1;
		int current_idx = 0;
		//bool first_time = true;
		int right_max_idx = -1;
		int right_max_count = 0;
		int current_count = 0;

		int i = 0;
		for (list<pair<int, int>>::iterator itr = dom_list.begin(); itr != dom_list.end(); itr++) {
			if (itr->first > most_right_down) {
				current_idx = i;
				current_count = 0;
			}

			r_iter[i] = current_idx;
			current_count++;

			if (right_max_count < current_count) {
				right_max_count = current_count;
				right_max_idx = current_idx;
			}

			if (itr->first + itr->second > most_right_down)
				most_right_down = itr->first + itr->second;

			i++;
		}

		//왼쪽으로 쓰러트렸을 때 가장 많은 도미노를 쓰러뜨리는 놈은?

		int most_left_down = MAX_X * 3;
		current_idx = 0;
		int left_max_idx = N;
		int left_max_count = 0;
		current_count = 0;

		i = dom_list.size() - 1;
		for (list<pair<int, int>>::reverse_iterator itr = dom_list.rbegin(); itr != dom_list.rend(); itr++) {
			if (itr->first < most_left_down) {
				current_idx = i;
				current_count = 0;
			}

			l_iter[i] = current_idx;
			current_count++;

			if (left_max_count < current_count) {
				left_max_count = current_count;
				left_max_idx = current_idx;
			}

			if (itr->first - itr->second < most_left_down)
				most_left_down = itr->first - itr->second;

			i--;
		}

		int idx = 0;
		if (left_max_count > right_max_count) {
			for (list<pair<int, int>>::iterator itr = dom_list.begin(); itr != dom_list.end();) {
				if (l_iter[idx++] == left_max_idx) {
					itr = dom_list.erase(itr);
					if (itr == dom_list.end())
						break;
				}
				else {
					itr++;
				}
			}
		}
		else {
			for (list<pair<int, int>>::iterator itr = dom_list.begin(); itr != dom_list.end(); ) {
				if (r_iter[idx++] == right_max_idx) {
					itr = dom_list.erase(itr);
					if (itr == dom_list.end())
						break;
				}
				else {
					itr++;
				}
			}
		}

		count++;
	}

	printf("%d\n", count);

	return 0;
}