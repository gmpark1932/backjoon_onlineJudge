/* Problem Number: 2261						 */
/* URL: https://www.acmicpc.net/problem/2261 */
/* Date: 2017.07.03							 */
/* Purpose: Data Structure Construction		 */

#include <iostream>
#include <math.h>
using namespace std;

struct Plant
{
	float x, y, r;
};

struct Point {
	float x, y;
};
int main() {
	int tast_count;
	cin >> tast_count;   // tast 갯수 입력
	for (int i = 0; i < tast_count; i++) {
		Plant plant[50];
		bool pass_starting_point[50] = { false };
		bool pass_arrival_point[50] = { false };
		Point starting_point;
		Point arrival_point;
		int plant_count;
		int pass_plant_count = 0;

		cin >> starting_point.x >> starting_point.y >> arrival_point.x >> arrival_point.y;   // 출발 도착 입력
		cin >> plant_count;     // 행성 갯수 입력

		for (int j = 0; j < plant_count; j++) {
			cin >> plant[j].x >> plant[j].y >> plant[j].r;
		}// 행성 갯수만큼 원점과 반지름 입력

		for (int j = plant_count-1; j >= 0; j--) {
			float tmp = pow((starting_point.x - plant[j].x), 2) + pow((starting_point.y - plant[j].y), 2);

			if (tmp <= pow(plant[j].r, 2))
				pass_starting_point[j] = true;
		}  // 출발점 비교

		for (int j = plant_count-1; j >= 0; j--) {
			float tmp = pow((arrival_point.x - plant[j].x), 2) + pow((arrival_point.y - plant[j].y), 2);

			if (tmp <= pow(plant[j].r, 2))
				pass_arrival_point[j] = true;
		} // 도착점 비교

		for (int j = 0; j < plant_count; j++) {
			if (pass_starting_point[j] && pass_arrival_point[j])
				continue;
			else if (pass_starting_point[j] || pass_arrival_point[j])
				pass_plant_count++;
		}  // 통과한 행성 갯수 확인

		cout << pass_plant_count << endl;
	}
}