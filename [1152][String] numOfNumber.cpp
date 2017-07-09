// Problem Number: 1152						 
// URL: https://www.acmicpc.net/problem/1152 
// Date: 2017.07.09							 
// Purpose: 1) String Tokenize
// Time: O(MAXLENGTH)

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 1000000

int main(void) {
	char arr[MAXLENGTH];

	fgets(arr, MAXLENGTH, stdin);

	char* token = strtok(arr, " \n");
	int count=0;
	while (token!=NULL) {
		count++;
		token = strtok(NULL," \n");
	}

	printf("%d\n", count);

	return 0;
}