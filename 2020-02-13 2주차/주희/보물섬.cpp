//[백준 2589] 보물섬
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <memory.h>

using namespace std;

int R, C;
int map[100][100];
int maxDist{ 0 };
int visited[100][100];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void input() {
	for (int r{ 0 }; r < R; r++) {
		getchar();
		for (int c{ 0 }; c < C; c++) {
			if (getchar() == 'W') { //물: 0
				map[r][c] = 0;
			}
			else map[r][c] = 1; //땅: 1
		}
	}
}

int main() {
	cin >> R >> C;

	input();

	for (int r{ 0 }; r < R; r++) {
		for (int c{ 0 }; c < C; c++) {
			if (map[r][c] == 1) {
				memset(visited, 0, sizeof(visited));
				visited[r][c] == 1;

				//r,c 에서 가장 긴 루트 찾기
				vector<pair<int, int>> temp;
				temp.push_back(make_pair(r, c));

				int len{ 0 };

				while (temp.size() > 0) {
					vector<pair<int, int>> temp2;
					for (auto t : temp) {
						for (int d{ 0 }; d < 4; d++) {
							int tx = t.first + dx[d];
							int ty = t.second + dy[d];

							if (tx >= 0 && tx < R && ty >= 0 && ty < C && map[tx][ty] == 1 && visited[tx][ty] == 0) {
								visited[tx][ty] = 1;
								temp2.push_back(make_pair(tx, ty));
							}
						}
					}
					temp = temp2;
					if (temp.size() != 0) len++;
				}
				maxDist = max(maxDist, len);
			}
		}
	}

	cout << maxDist;

	//system("pause");
	return 0;
}