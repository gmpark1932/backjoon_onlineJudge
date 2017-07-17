// Problem Number: 1107						 
// URL: https://www.acmicpc.net/problem/1107 
// Date: 2017.07.17							 
// Purpose: 1) Simulation ( generate all number of 1 ~ 6 digit in unbroken numbers )

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

#define INF 1000000

using namespace std;

char cur_num[7];
vector<int> broken_number;
vector<int> unbroken_number;

int cur_digit;
int max_index;
int index_arr[6];

inline void init_index(void) {
	memset(index_arr, 0, sizeof(int) * 6);
}

int next_number(bool first_time = false) {
	int carry = 0;

	int result = 0;
	
	if (!first_time) {
		for (int i = 0; i < cur_digit; i++) {
			if (i == 0)
				index_arr[i] += 1;
			index_arr[i] += carry;
			if (index_arr[i] >= max_index) {
				index_arr[i] -= max_index;
				carry = 1;
			}
			else {
				carry = 0;
			}
			result *= 10;
			result += unbroken_number[index_arr[i]];
		}
	}
	else {
		for (int i = 0; i < cur_digit; i++) {
			result *= 10;
			result += unbroken_number[index_arr[0]];
		}
	}

	if (carry == 1) //overflow
		return -1;
	else
		return result;
}

int digit_count(int number) {
	int count = 1;
	int digit = 10;
	
	while (true) {
		number = number / 10;
		if (number == 0)
			break;
		count++;
	}

	return count;
}

int main(void) {
	int N, M;

	for (int i = 0; i < 10; i++) {
		unbroken_number.push_back(i);
	}

	scanf("%d %d", &N, &M);

	max_index = 10 - M;

	for (int i = 0; i < M; i++) {
		int t;
		scanf("%d", &t);
		broken_number.push_back(t);
	}

	for (vector<int>::iterator itr = broken_number.begin(); itr != broken_number.end(); itr++) {
		for (vector<int>::iterator un_itr = unbroken_number.begin(); un_itr != unbroken_number.end(); un_itr++) {
			if (*itr == *un_itr) {
				un_itr = unbroken_number.erase(un_itr);
				if (un_itr == unbroken_number.end())
					break;
			}
		}
	}

	int max_unbroken = -1;
	int min_unbroken = 11;
	for (vector<int>::iterator itr = unbroken_number.begin(); itr != unbroken_number.end(); itr++) {
		if (max_unbroken < *itr)
			max_unbroken = *itr;
		if (min_unbroken > *itr)
			min_unbroken = *itr;
	}

	if (unbroken_number.empty() == false) {
		//N보다 크거나 같은 수 중에서 가장 작은 수 생성
		int min_large = 999999;
		for (int i = 1; i <= 6; i++) {
			init_index();
			cur_digit = i;
			int cur_num = next_number(true);

			while (cur_num != -1) {
				if (min_large > cur_num && cur_num >= N)
					min_large = cur_num;

				cur_num = next_number();
			}
		}
		
		int number_and_down;
		if (min_large == 999999)
			number_and_down = INF;
		else
			number_and_down = digit_count(min_large) + (min_large - N);

		//N보다 작거나 같은 수 중에서 가장 큰 수 생성
		int max_small = -1;
		for (int i = 1; i <= 6; i++) {
			init_index();
			cur_digit = i;
			
			int cur_num = next_number(true);
			while (cur_num != -1) {
				if (max_small < cur_num && cur_num <= N)
					max_small = cur_num;

				cur_num = next_number();
			}
		}
		
		int number_and_up;
		if (max_small == -1)
			number_and_up = INF;
		else
			number_and_up = digit_count(max_small) + (N - max_small);
	
		int only_up_down = (N < 100) ? 100 - N : N - 100;

		if (number_and_up <= number_and_down && number_and_up <= only_up_down)
			printf("%d\n", number_and_up);
		else if (number_and_down <= number_and_up && number_and_down <= only_up_down)
			printf("%d\n", number_and_down);
		else
			printf("%d\n", only_up_down);
	}
	else {
		printf("%d\n", (N < 100) ? 100 - N : N - 100);
	}

	return 0;
}