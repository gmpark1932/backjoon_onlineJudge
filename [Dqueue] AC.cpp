/* Problem Number: 5430						 */
/* URL: https://www.acmicpc.net/problem/5430 */
/* Date: 2017.07.03							 */
/* Purpose: Using Dqueue					 */

#include <iostream>
#include <string>
#include <string.h>
#include <deque>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

void Tokenize(const string& str,
	vector<string>& tokens,
	const string& delimiters = " ")
{
	// �� ù ���ڰ� �������� ��� ����
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// �����ڰ� �ƴ� ù ���ڸ� ã�´�
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// token�� ã������ vector�� �߰��Ѵ�
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// �����ڸ� �پ�Ѵ´�.  "not_of"�� �����϶�
		lastPos = str.find_first_not_of(delimiters, pos);
		// ���� �����ڰ� �ƴ� ���ڸ� ã�´�
		pos = str.find_first_of(delimiters, lastPos);
	}
}

int main() {
	int test_count;
	cin >> test_count;
	cin.ignore(256, '\n');


	for (int i = 0; i < test_count; i++) {
		string function;
		int que_count = 0;
		bool turn_around = false;
		bool error = false;
		deque <char*> deqNum;
		deque <char*>::iterator ite;
		ite = deqNum.begin();
		ite = deqNum.end();

		getline(cin, function);

		cin >> que_count;
		cin.ignore(256, '\n');

		string tmp1;
		getline(cin, tmp1);
	
		char* tmp_str = new char[tmp1.length()+1];
		strcpy(tmp_str, tmp1.c_str());
		char* tok;

		tok = strtok(tmp_str, ",[]");
		while (tok) {
		//	int storage = atoi(tok);
			//deqNum.push_back(storage);
			deqNum.push_back(tok);
			tok = strtok(NULL, ",[]");
		}
		
			for (int j = 0; j < function.size(); j++) {
			if (function[j] == 'R')
				turn_around = !turn_around;

			else if (function[j] == 'D') {
				if (deqNum.empty()) {
					error = true;
					break;
				} 
				if (turn_around)
					deqNum.pop_back();
				else
					deqNum.pop_front();
			}
		}

			if (error)
			cout << "error" << endl;
			
		else {  
			cout << "[";
			if (turn_around) {
				for (int j = deqNum.size() - 1; j >= 0; j--) {
					cout << deqNum.at(j);
					if (j != 0)
						cout << ",";
				}
			}
			else if(!turn_around) {
				for (int j = 0; j < deqNum.size(); j++) {
					cout << deqNum.at(j);
					if (j != deqNum.size() - 1)
						cout << ",";
				}
			}
			cout << "]" << endl;
		} 

		
	}
}