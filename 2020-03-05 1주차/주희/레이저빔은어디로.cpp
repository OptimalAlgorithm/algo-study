//[백준 3709] 레이저빔은 어디로

#include <iostream>
#include <memory.h>
#include <vector>
#include <set>

using namespace std;

//x:가로 y:세로

int N, r;
int map[50][50]; //0:빈공간 1:우향우
int cx, cy, cd; //현재x, 현재y, 현재방향

				//상 우 하 좌
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	int T;
	cin >> T;

	for (int t{ 0 }; t < T; t++) {
		memset(map, 0, sizeof(map));
		cin >> N >> r;

		//우향우 위치 입력
		int x, y;
		for (int i{ 0 }; i < r; i++) {
			cin >> x >> y;

			map[x - 1][y - 1] = 1;
		}

		//레이저 시작점
		cin >> cx >> cy;
		cx--; cy--;

		//초기 레이저 진행 방향 구하기
		if (cx == -1) {
			cd = 2; //하
		}
		else if (cx == N) {
			cd = 0; //상
		}
		else if (cy == -1) {
			cd = 1; //우
		}
		else {
			cd = 3; //좌
		}

		//visited
		set<int> visited[50][50];

		while (true) {
			int tx = cx + dx[cd];
			int ty = cy + dy[cd];

			//보드 내
			if (tx >= 0 && tx < N && ty >= 0 && ty < N) {
				//제자리
				if (visited[tx][ty].count(cd) == 1) {
					cout << "0 0\n";
					break;
				}

				visited[tx][ty].insert(cd);

				//우향우
				if (map[tx][ty] == 1) {
					//방향전환
					cd++;
					cd %= 4;

					//좌표이동
					cx = tx;
					cy = ty;
				}
				//빈공간
				else {
					cx = tx;
					cy = ty;
				}
			}
			//보드 바깥
			else {
				cout << tx + 1 << " " << ty + 1 << "\n";
				break;
			}
		}
	}


	//system("pause");
	return 0;
}