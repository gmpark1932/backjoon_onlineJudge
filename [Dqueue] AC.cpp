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
	// 맨 첫 글자가 구분자인 경우 무시
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// 구분자가 아닌 첫 글자를 찾는다
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// token을 찾았으니 vector에 추가한다
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// 구분자를 뛰어넘는다.  "not_of"에 주의하라
		lastPos = str.find_first_not_of(delimiters, pos);
		// 다음 구분자가 아닌 글자를 찾는다
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