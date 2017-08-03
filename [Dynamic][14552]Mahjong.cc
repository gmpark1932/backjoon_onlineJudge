#include <cstdio>
#include <list>
#include <cstring>

using namespace std;

bool debug_flag = false;

bool seven_head(int arr[10]) {
	for (int i = 1; i <= 9; i++) {
		if (arr[i] != 2 && arr[i] != 0) {
			return false;
		}
	}

	return true;
}

bool is_complete_body(int arr[10], int size) {
	int seq_start = 0;
	bool seq_flag = false;
	
	/*if(debug_flag)
	for (int i = 1; i <= 9; i++)
		printf("%d ", arr[i]);
	if(debug_flag)printf("\n");
*/

	/*
	if (size == 3) {
		for (int i = 1; i <= 9; i++) {
			if (arr[i] == 3)
				return true;
			
			if (seq_flag == false && arr[i] == 1) {
				seq_flag = true;
				seq_start = i;
			}
			else if (arr[i] == 1)
				seq_flag = true;
			else if (arr[i] == 0)
				seq_flag = false;
			else if (arr[i] >= 2)
				return false;

			if (seq_flag == true && seq_start != 0 && arr[i] - seq_start == 2) {
				return true;
			}
		}

		return false;
	}
*/

	if (size == 0)
		return true;

	for (int i = 1; i <= 9; i++) {
		if (arr[i] >= 3) {
			int temp_arr[10];
			memcpy(temp_arr, arr, sizeof(int) * 10);
			temp_arr[i] -= 3;
			if (is_complete_body(temp_arr, size - 3))
				return true;
		}
		
		if (seq_flag == false && arr[i] >= 1) {
			seq_flag = true;
			seq_start = i;
		}
		else if (arr[i] >= 1 && seq_flag == true && seq_start != 0 && i - seq_start >= 2) {
			int temp_arr[10];
			memcpy(temp_arr, arr, sizeof(int) * 10);
			temp_arr[i - 2]--;
			temp_arr[i - 1]--;
			temp_arr[i]--;
			if (is_complete_body(temp_arr, size - 3))
				return true;
		}
		else if (arr[i] == 0) {
			seq_flag = false;
			seq_start = 0;
		}
	}

	return false;
}

bool is_complete_head(int arr[10]) {
	for (int i = 1; i <= 9; i++) {
		int temp_arr[10];
		memcpy(temp_arr, arr, sizeof(int) * 10);
		if (temp_arr[i] >= 2) {
			temp_arr[i] -= 2;
			if (is_complete_body(temp_arr, 12))
				return true;
		}
	}

	return false;
}

int main(void) {
	int count_num[10] = { 0 }; //1 ~ 9

	for (int i = 0; i < 13; i++) {
		int c;
		scanf("%d", &c);

		count_num[c]++;
	}

	bool print = false;
	for (int i = 1; i <= 9; i++) {
		if (i == 2) debug_flag = true;
		else debug_flag = false;
		//printf("\n\nCase %d\n", i);
		if (count_num[i] <= 3) {
			int temp_arr[10];
			memcpy(temp_arr, count_num, sizeof(int) * 10);
			temp_arr[i]++;
			if (seven_head(temp_arr) || is_complete_head(temp_arr)) {
				printf("%d ", i);
				print = true;
			}
		}
	}

	if (print == false)
		printf("-1");

	printf("\n");

	return 0;
}