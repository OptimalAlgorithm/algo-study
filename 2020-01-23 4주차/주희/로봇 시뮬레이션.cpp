//[백준 2174] 로봇 시뮬레이션 
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

int main() {

	int A, B;
	cin >> A >> B;

	int N, M;
	cin >> N >> M;

	vector<pair<int, int>> dir;
	dir.push_back(make_pair(0, 1)); //상
	dir.push_back(make_pair(1, 0)); //우
	dir.push_back(make_pair(0, -1)); //하
	dir.push_back(make_pair(-1, -0)); //좌

	//인덱스 == 로봇번호, x좌표, y좌표, 방향 
	vector<tuple<int,int,int>> robots(N);

	for (int n{ 1 }; n <= N; n++) {
		int x, y;
		char f;
		cin >> x >> y >> f;

		if (f == 'N') f = '0';
		else if (f == 'E') f = '1';
		else if (f == 'S') f = '2';
		else f = '3';
		
		robots[n - 1] = make_tuple(x, y, (int)(f - '0'));
	}
	
	for (int m{ 0 }; m < M; m++) {
		int robot;
		char command;
		int repeat;

		cin >> robot >> command >> repeat;

		//왼쪽으로 90도
		if (command == 'L') { 
			get<2>(robots[robot - 1]) -= (repeat % 4);
			if (get<2>(robots[robot - 1]) < 0) get<2>(robots[robot - 1]) += 4;

		}//오른쪽으로 90도
		else if (command == 'R') {
			get<2>(robots[robot - 1]) += (repeat % 4);
			if (get<2>(robots[robot - 1]) > 3) get<2>(robots[robot - 1]) -= 4;

		}//앞으로 한칸
		else {
			for (int r{ 0 }; r < repeat; r++) {
				int tempX = get<0>(robots[robot - 1]) + dir[get<2>(robots[robot - 1])].first;
				int tempY = get<1>(robots[robot - 1]) + dir[get<2>(robots[robot - 1])].second;

				//영역 밖으로 나갈때
				if (tempX <= 0 || tempX > A || tempY <= 0 || tempY > B) {
					cout << "Robot " << robot << " crashes into the wall";
					system("pause");
					return 0;
				}
				
				//다른 로봇과 충돌할 때
				for (int test{ 0 }; test < robots.size(); test++) {
					if (test != robot) {
						if (get<0>(robots[test]) == tempX && get<1>(robots[test]) == tempY) {
							cout << "Robot " << robot << " crashes into robot " << test+1;
							system("pause");
							return 0;
						}
					}
				}

				//이동해도 문제 없을 때
				get<0>(robots[robot - 1]) = tempX;
				get<1>(robots[robot - 1]) = tempY;
			}
		}

	}
	cout << "OK";

	system("pause");
	return 0;
}