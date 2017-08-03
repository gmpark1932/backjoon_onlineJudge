#include <cstdio>
#include <algorithm> 
#include <vector>

using namespace std;

struct Task {
	int reward;
	int deadline;
};

vector<pair<bool,Task>> tasks;

bool cmp(Task a, Task b) {
	return a.deadline < b.deadline;
}

int main(void) {
	int n;

	scanf("%d", &n);
	for (int i = 0;i < n;i++) {
		int d, w;
		scanf("%d %d", &d, &w);
		Task t;
		t.reward = w;
		t.deadline = d;
		tasks.push_back(make_pair(true,t));
	}

	int max_time = 0;
	for (int i = 0;i < tasks.size();i++) {
		if (max_time < tasks[i].second.deadline) {
			max_time = tasks[i].second.deadline;
		}
	}

	int result = 0;
	int cur_t = max_time;
	for (;cur_t >= 0;cur_t--) {
		int max_idx = -1;
		int max_reward = 0;
		for (int i = 0;i < tasks.size();i++) {
			if (tasks[i].first == true && tasks[i].second.deadline > cur_t
				&& max_reward < tasks[i].second.reward) {
				max_reward = tasks[i].second.reward;
				max_idx = i;
			}
		}

		if (max_idx == -1)
			continue;
		else {
			tasks[max_idx].first = false;
			result += max_reward;
		}
	}

	printf("%d\n", result);

	return 0;
}