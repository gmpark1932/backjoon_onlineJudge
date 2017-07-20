// Problem Number: 2580						 
// URL: https://www.acmicpc.net/problem/2580 
// Date: 2017.07.20							 
// Purpose: 1) BackTracking

#include <cstdio>
#include <vector>
using namespace std;

class BitMap {
private:
	int data; //오른쪽에서부터 1 ~ 9를 9번째 bit까지를 사용하여 표현
	int temp_data;
	int count;

public:
	BitMap() {
		data = 511; // 111111111(2)
	}

	void setExistFlag(int num) {
		int t = 1 << (num - 1);
		data = data & (~t);
	}

	void unSetExistFlag(int num) {
		int t = 1 << (num - 1);
		data = data | t;
	}

	void initGetNext(void) {
		temp_data = data;
		count = 1;
	}

	int getNextNumber(void) {
		while (count <= 9) {
			if (temp_data % 2 == 1) {
				temp_data = temp_data >> 1;
				return count++;
			}
			temp_data = temp_data >> 1;
			count++;
		}

		if (count == 10)
			return -1;
	}

	bool isEmpty(void) {
		return data == 0;
	}

	void setData(int a) {
		data = a;
	}

	int getData(void) {
		return data;
	}
};

BitMap threeIntersection(BitMap& a, BitMap& b, BitMap& c) {
	BitMap t;
	
	t.setData(a.getData() & b.getData() & c.getData());

	return t;
}

int sudoku[9][9];
BitMap remainCol[9];
BitMap remainRow[9];
BitMap remainRoom[3][3];

vector<pair<int, int>> unknown_space;

bool completeSudoku(vector<pair<int, int>>::iterator &itr) {
	if (itr == unknown_space.end())
		return true;

	BitMap possible_number = threeIntersection(remainRow[itr->first], remainCol[itr->second], remainRoom[itr->first / 3][itr->second / 3]);
	
	if (possible_number.isEmpty())
		return false;
	
	int nextNum;
	possible_number.initGetNext();
	while ((nextNum = possible_number.getNextNumber()) != -1) {
		remainRow[itr->first].setExistFlag(nextNum);
		remainCol[itr->second].setExistFlag(nextNum);
		remainRoom[itr->first / 3][itr->second / 3].setExistFlag(nextNum);
		bool result = completeSudoku(++itr);
		itr--;
		if (result == true) {
			sudoku[itr->first][itr->second] = nextNum;
			return true;
		}
		else {
			remainRow[itr->first].unSetExistFlag(nextNum);
			remainCol[itr->second].unSetExistFlag(nextNum);
			remainRoom[itr->first / 3][itr->second / 3].unSetExistFlag(nextNum);
		}
	}

	return false;
}

int main(void) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			scanf("%d", &sudoku[i][j]);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (sudoku[i][j] != 0) {
				remainCol[j].setExistFlag(sudoku[i][j]);
				remainRow[i].setExistFlag(sudoku[i][j]);
				remainRoom[i / 3][j / 3].setExistFlag(sudoku[i][j]);
			}
			else {
				unknown_space.push_back(make_pair(i, j));
			}
		}
	}

	vector<pair<int,int>>::iterator itr = unknown_space.begin();
	
	bool result = completeSudoku(itr);
	if (result == false)
		printf("FLASE\n");

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			printf("%d ", sudoku[i][j]);
		printf("\n");
	}

	return 0;
}