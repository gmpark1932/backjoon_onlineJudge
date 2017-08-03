#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

#define alpha_num 36

int main(void) {
	int N;
	char crpt[1000];
	vector<string> d;

	scanf("%s", crpt);

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		char s[1000];

		scanf("%s", s);

		d.push_back(string(s));
	}

	string temp_s(crpt);
	
	bool found = false;

	for (int i = 0; i < alpha_num; i++) {
		for (int j = 0; j < N; j++) {
			if (strstr(crpt,d[j].c_str()) != NULL) {
				found = true;
				break;
			}
		}

		if (found)
			break;

		for (int j = 0; j < temp_s.size(); j++) {
			crpt[j]++;
			if (crpt[j] > 'z')
				crpt[j] = 'a';
		}
		//printf("%s\n", crpt);
	}

	printf("%s\n", crpt);

	return 0;
}