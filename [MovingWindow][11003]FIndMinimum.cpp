// Problem Number: 11003						 
// URL: https://www.acmicpc.net/problem/11003 
// Date: 2017.07.20							 
// Purpose: 1) Sliding Window
//			2) Min Heap

#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

class Heap { //MIN Heap
private:
	struct Node {
		int val;
		int data_to_index;
	};
	deque<Node> data;
	deque<int> index;
	int adjustValue=0;

public:
	Heap() {
		Node temp = { 0,0 };
		data.push_back(temp);
		index.push_back(0);
	}

	void adjustUntilRoot(int start){
		for (int i = start; i / 2 != 1; i /= 2) {
			if (data[i / 2].val > data[i].val) {
				swap(data[i / 2], data[i]);
				swap(index[i / 2], index[i]);
			}
		}
	}

	void insert(int num,int idx) {
		Node t = { num,idx };

		data.push_back(t);
		index.push_back(idx);

		for (int i = data.size() - 1; i != 1; i /= 2) {
			if (data[i].val < data[i / 2].val) {
				swap(index[data[i].data_to_index-adjustValue], index[data[i / 2].data_to_index-adjustValue]);
				swap(data[i], data[i / 2]);
			}
		}
	}

	void remove(void) {
		//제거 후 가장 마지막 노드를 그 자리에 넣는다.
		int t_index = index[1];

		index[data[data.size() - 1].data_to_index-adjustValue] = index[1];
		swap(data[index[1]], data[data.size() - 1]);

		index.pop_front();
		index.pop_front();
		index.push_front(0);
		data.pop_back();

		adjustValue++;

		//t_index -= adjustValue;
		if(t_index != 1 && data[t_index/2].val > data[t_index].val){
			//위로 가면서 adjust
			for (int i = t_index; i != 1; i /= 2) {
				if (data[i / 2].val > data[i].val) {
					swap(index[data[i / 2].data_to_index - adjustValue], index[data[i].data_to_index - adjustValue]);
					swap(data[i / 2], data[i]);
				}
			}
		}
		else {
			//아래로 가면서 adjust
			int i = t_index;
			while(true) {
				if (i * 2 + 1 < data.size()) {
					int min3 = min_of_3(data[i].val, data[i * 2].val, data[i * 2 + 1].val);
					if (min3 == data[i].val)
						break;
					else if (min3 == data[i * 2].val) {
						swap(index[data[i].data_to_index - adjustValue], index[data[i * 2].data_to_index - adjustValue]);
						swap(data[i * 2], data[i]);
						i = i * 2;
					}
					else if (min3 == data[i * 2 + 1].val) {
						swap(index[data[i].data_to_index - adjustValue], index[data[i * 2 + 1].data_to_index - adjustValue]);
						swap(data[i * 2 + 1], data[i]);
						i = i * 2 + 1;
					}
					else {
						break;
					}
				}
				else if(i*2 < data.size()) {
					if (data[i].val > data[i * 2].val) {
						swap(index[data[i].data_to_index - adjustValue], index[data[i * 2].data_to_index - adjustValue]);
						swap(data[i * 2], data[i]);
						i = i * 2;
						break;
					}
					else
						break;
				}
				else {
					break;
				}
			}
		}
	}

	void replace(int num, int idx) {
		int t_index = index[1];
		
		data[index[1]].data_to_index = idx;
		data[index[1]].val = num;

		adjustValue++;

		index.push_back(index[1]);
		index.pop_front();
		index.pop_front();
		index.push_front(0);

		if (t_index != 1 && data[t_index / 2].val > data[t_index].val) {
			for (int i = t_index; i != 1; i /= 2) {
				if (data[i / 2].val > data[i].val) {
					swap(index[data[i / 2].data_to_index - adjustValue], index[data[i].data_to_index - adjustValue]);
					swap(data[i / 2], data[i]);
				}
			}
		}
		else {
			int i = t_index;
			while (true) {
				if (i * 2 + 1 < data.size()) {
					int min3 = min_of_3(data[i * 2 + 1].val, data[i * 2].val, data[i].val);
					if (min3 == data[i].val)
						break;
					else if (min3 == data[i * 2].val) {
						swap(index[data[i * 2].data_to_index - adjustValue], index[data[i].data_to_index - adjustValue]);
						swap(data[i * 2], data[i]);
						i = i * 2;
					}
					else {
						swap(index[data[i * 2 + 1].data_to_index - adjustValue], index[data[i].data_to_index - adjustValue]);
						swap(data[i * 2 + 1], data[i]);
						i = i * 2 + 1;
					}
				}
				else if (i * 2 < data.size()) {
					if (data[i * 2].val < data[i].val) {
						swap(index[data[i * 2].data_to_index - adjustValue], index[data[i].data_to_index - adjustValue]);
						swap(data[i * 2], data[i]);
					}
					break;
				}
				else break;
			}
		}
	}

	static int min_of_3(int a, int b, int c) {
		if (a <= b && a <= c) {
			return a;
		}
		else if (b <= a && b <= c) {
			return b;
		}
		else return c;
	}

	int getMin(void) {
		return data[1].val;
	}

	void printAll(void) {
		printf("\n\n");
		for (int i = 0; i < data.size(); i++) {
			printf("[%2d,%2d] - ", data[i].val,data[i].data_to_index);
		}
		printf("\n");
		for (int i = 0; i < data.size(); i++) {
			printf("[%5d] - ", index[i]);
		}
		printf("\n");
		printf("AdjustVale = %d\n", adjustValue);
	}
};

int main(void) {
	int N, L;
	scanf("%d %d", &N, &L);

	vector<int> numbers;
	numbers.push_back(0);//Heap에서 사용하지 않는 index 0을 삽입

	for (int i = 0; i < N; i++) {
		int temp;
		scanf("%d", &temp);
		numbers.push_back(temp);
	}

	Heap window;

	for (int i = 1; i <= N; i++) {
		
		if (i > L) {
			window.replace(numbers[i], i);
		}
		else {
			window.insert(numbers[i], i);
		}

		printf("%d ", window.getMin());
	}
	printf("\n");

	return 0;
}