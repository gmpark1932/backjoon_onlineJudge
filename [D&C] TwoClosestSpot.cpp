/* Problem Number: 2261						 */
/* URL: https://www.acmicpc.net/problem/2261 */
/* Date: 2017.07.04							 */
/* Purpose: D&C Algorithm					 */

#include <iostream>
#include <math.h>

#define SWAP(x,y,t) {t = x;x = y;y = t;}

typedef struct Node {
	int x;
	int y;
}Node;

Node* tempNodes[100000];
Node nodes[100000];
Node* sorted_nodes[100000];

const int THR = 20;

inline int getDistanceSquare(Node* one, Node* two) {
	return (one->x - two->x)*(one->x - two->x) + (one->y - two->y)*(one->y - two->y);
}
void insertSortByY(Node** sorted_nodes, int left, int right) {
	if (right > left) {
		Node* temp;
		for (int i = left;i <= right;i++) {
			for (int j = i + 1;j <= right;j++) {
				if (sorted_nodes[i]->y > sorted_nodes[j]->y) {
					SWAP(sorted_nodes[i], sorted_nodes[j], temp);
				}
			}
		}
	}
}

void sortByY(Node** sorted_nodes, int left, int right) {
	Node* temp;

	if (right > left) {
		if (right - left <= THR) {
			insertSortByY(sorted_nodes, left, right);
			return;
		}

		int middle = (left + right) / 2;

		if ((sorted_nodes[middle]->y > sorted_nodes[right]->y && sorted_nodes[right]->y > sorted_nodes[left]->y)
			|| (sorted_nodes[middle]->y < sorted_nodes[right]->y && sorted_nodes[right]->y < sorted_nodes[left]->y))
		{
			/* right가 중간값인 경우 */
			SWAP(sorted_nodes[right], sorted_nodes[left], temp);
		}
		else if ((sorted_nodes[right]->y > sorted_nodes[middle]->y && sorted_nodes[middle]->y > sorted_nodes[left]->y)
			|| (sorted_nodes[right]->y < sorted_nodes[middle]->y && sorted_nodes[middle]->y < sorted_nodes[left]->y))
		{
			/* middle이 중간값인 경우 */
			SWAP(sorted_nodes[middle], sorted_nodes[left], temp);
		}

		int pivot = sorted_nodes[left]->y;
		int i = left + 1;
		for (int j = left + 1;j <= right;j++) {
			if (sorted_nodes[j]->y < pivot) {
				SWAP(sorted_nodes[i], sorted_nodes[j], temp);
				i++;
			}
		}
		SWAP(sorted_nodes[i - 1], sorted_nodes[left], temp);
		sortByY(sorted_nodes, left, i - 1);
		sortByY(sorted_nodes, i, right);
	}
}

void insertSortByX(Node** sorted_nodes, int left, int right) {
	if (right > left) {
		Node* temp;
		for (int i = left;i <= right;i++) {
			for (int j = i + 1;j <= right;j++) {
				if (sorted_nodes[i]->x > sorted_nodes[j]->x) {
					SWAP(sorted_nodes[i], sorted_nodes[j], temp);
				}
			}
		}
	}
}

void sortByX(Node** sorted_nodes, int left, int right) {
	Node* temp;

	if (right > left) {
		if (right - left <= THR) {
			insertSortByX(sorted_nodes, left, right);
			return;
		}

		int middle = (left + right) / 2;

		if ((sorted_nodes[middle]->x > sorted_nodes[right]->x && sorted_nodes[right]->x > sorted_nodes[left]->x)
			|| (sorted_nodes[middle]->x < sorted_nodes[right]->x && sorted_nodes[right]->x < sorted_nodes[left]->x))
		{
			/* right가 중간값인 경우 */
			SWAP(sorted_nodes[right], sorted_nodes[left], temp);
		}
		else if ((sorted_nodes[right]->x > sorted_nodes[middle]->x && sorted_nodes[middle]->x > sorted_nodes[left]->x)
			|| (sorted_nodes[right]->x < sorted_nodes[middle]->x && sorted_nodes[middle]->x < sorted_nodes[left]->x))
		{
			/* middle이 중간값인 경우 */
			SWAP(sorted_nodes[middle], sorted_nodes[left], temp);
		}

		int pivot = sorted_nodes[left]->x;
		int i = left + 1;
		for (int j = left + 1;j <= right;j++) {
			if (sorted_nodes[j]->x < pivot) {
				SWAP(sorted_nodes[i], sorted_nodes[j], temp);
				i++;
			}
		}
		SWAP(sorted_nodes[i - 1], sorted_nodes[left], temp);
		sortByX(sorted_nodes, left, i - 1);
		sortByX(sorted_nodes, i, right);
	}
}

int findClosestPair(Node** sorted_nodes, int left_idx, int right_idx) {
	int middle_idx = (left_idx + right_idx) / 2;

	//printNodes(sorted_nodes, global_size);

	if (left_idx >= right_idx) {//대상 노드가 하나 이하일 때
		return -1;
	}

	if (right_idx == left_idx + 1) {//대상 노드의 갯수가 2개일 때
		return getDistanceSquare(sorted_nodes[left_idx], sorted_nodes[right_idx]);
	}
	
	if (right_idx - left_idx <= THR) {
		int result = getDistanceSquare(sorted_nodes[left_idx],sorted_nodes[left_idx + 1]);

		for (int i = left_idx;i <= right_idx;i++) {
			for (int j = i + 1;j <= right_idx;j++) {
				if (result > getDistanceSquare(sorted_nodes[i], sorted_nodes[j])) {
					result = getDistanceSquare(sorted_nodes[i], sorted_nodes[j]);
				}
			}
		}

		return result;
	}

	int left_result = findClosestPair(sorted_nodes, left_idx, middle_idx - 1);
	int right_result = findClosestPair(sorted_nodes, middle_idx, right_idx);
	int small_result;

	if (left_result == -1) { // 대상 노드가 3개라서 1개/2개로 나뉘어 졌을 때
		int temp = getDistanceSquare(sorted_nodes[left_idx],sorted_nodes[middle_idx]);
		if (temp < right_result)
			return temp;
		else
			return right_result;
	}
	else {
		if (left_result > right_result) {
			small_result = right_result;
		}
		else {
			small_result = left_result;
		}
	}

	int k = 0;
	double small_d = sqrt((double)small_result);
	
	/*
	for (int i = left_idx;i <= right_idx;i++) {
		if (sorted_nodes[i]->x >= sorted_nodes[middle_idx]->x - small_d &&
			sorted_nodes[i]->x <= sorted_nodes[middle_idx]->x + small_d) {
			tempNodes[k++] = sorted_nodes[i];
		}
	}
	*/

	for (int i = middle_idx - 1; i >= left_idx;i--) {
		if (sorted_nodes[i]->x <= sorted_nodes[middle_idx]->x - small_d)
			break;
		tempNodes[k++] = sorted_nodes[i];
	}

	for (int i = middle_idx; i <= right_idx;i++) {
		if (sorted_nodes[i]->x >= sorted_nodes[middle_idx]->x + small_d)
			break;
		tempNodes[k++] = sorted_nodes[i];
	}

	//이 line에서 k는 tempNodes에 들어간 노드의 갯수를 저장하고 있음
	if (k <= 1) {
		return small_result;
	}

	sortByY(tempNodes, 0, k - 1);

	int middle_result;
	middle_result = getDistanceSquare(tempNodes[0],tempNodes[1]);
	for (int i = 0;i < k;i++) {
		for (int j = i + 1;j < k;j++) {
			int d = getDistanceSquare(tempNodes[i], tempNodes[j]);
			/*if (d >= small_result.distance_square || d >= middle_result.distance_square)
			break;
			*/
			if (middle_result > getDistanceSquare(tempNodes[i], tempNodes[j])) {
				middle_result = getDistanceSquare(tempNodes[i], tempNodes[j]);
			}
		}
	}

	if (middle_result < small_result)
		return middle_result;
	else
		return small_result;
}

using namespace std;

int main(void) {
	int n;

	cin >> n;

	for (int i = 0;i < n;i++) {
		cin >> nodes[i].x >> nodes[i].y;
		sorted_nodes[i] = &nodes[i];
	}

	sortByX(sorted_nodes, 0, n - 1);
	//printNodes(sorted_nodes, n);

	int closest_pair = findClosestPair(sorted_nodes, 0, n - 1);

	cout << closest_pair << endl;

	return 0;
}