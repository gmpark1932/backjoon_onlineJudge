// Problem Number: 1931						 
// URL: https://www.acmicpc.net/problem/1931 
// Date: 2017.07.10							 
// Purpose: 1) Greedy Algorithm - Select The Earliest End Time Meeting Available

#include <cstdio>
#include <utility>
#include <algorithm>

#define MAX_N 100001

typedef struct Meeting {
	int start;
	int end;
	int diff;
};

using namespace std;

pair<unsigned int,unsigned int> meeting_time[MAX_N]; //first: end time, second: start time

int max_meeting(pair<unsigned int,unsigned int> time_arr[],int size) {
	int current_end_time;
	int result_count = 0;
	int current_idx = 0;

	do {
		result_count++;
		current_end_time = time_arr[current_idx].first;

		int i=current_idx+1;
		while (i < size) {
			if (time_arr[i].second >= current_end_time)
				break;
			i++;
		}
		current_idx = i;

	} while (current_idx <= size - 1);

	return result_count;
}

int main(void) {
	int N;

	scanf("%d", &N);

	for (int i = 0;i < N;i++) {
		scanf("%d %d", &meeting_time[i].second, &meeting_time[i].first);
	}

	sort(meeting_time, meeting_time + N);

	printf("%d\n", max_meeting(meeting_time, N));
	
	return 0;
}