#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <algorithm>

#define MAX_N 100010

#define SWAP(a,b,t) { t = a; a = b; b = t;}

typedef struct {
	int start;
	int end;
}Meeting;

bool isSmall(Meeting a, Meeting b) {
	if (a.end != b.end)
		return a.end < b.end;
	else
		return a.start < b.start;
}

int partition(Meeting meet[], int left, int right) {
	int i = left;
	int j = right;
	Meeting pivot = meet[left];
	Meeting temp;

	while (i < j) {
		while (isSmall(pivot,meet[j])) { 
			j--;
		}
		while (i < j && !isSmall(pivot,meet[i])) {
			i++;
		}

		SWAP(meet[i], meet[j], temp);
	}

	meet[left] = meet[i];
	meet[i] = pivot;
	return i;	
}

void sortMeeting(Meeting meet[],int left,int right) {
	if (left >= right) return;

	int pivot_idx = partition(meet, left, right);

	sortMeeting(meet, left, pivot_idx - 1);
	sortMeeting(meet, pivot_idx + 1, right);
}

int calculateMaxMeet(Meeting meet[], int size) {
	int cur_time=0;
	int count_meeting = 0;
	for (int i = 0; i < size; i++) {
		if (meet[i].start >= cur_time) {
			cur_time = meet[i].end;
			count_meeting++;
		}
	}

	return count_meeting;
}



int main(void) {
	Meeting meet[MAX_N];

	int N, start, end;
	scanf("%d", &N);

	for (int n = 0; n < N; n++) {
		scanf("%d %d", &start, &end);

		meet[n] = { start, end };
	}

	sortMeeting(meet,0,N-1);

	//std::sort(meet, meet + N,isSmall);

	printf("%d\n", calculateMaxMeet(meet, N));

	//system("pause");

	return 0;
}
