//[백준 1600] 말이 되고픈 원숭이

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int K;
int W, H;

int map[200][200];
set<int> visited[200][200];

int ndx[8] = { -1,-2,-2,-1,1,2,2,1 }; //H
int ndy[8] = { -2,-1,1,2,2,1,-1,-2 }; //W
int dx[4] = { 0,0,1,-1 }; //H
int dy[4] = { 1,-1,0,0 }; //W

int main() {
	cin >> K >> W >> H;

	if (W == 1 && H == 1) { cout << "0"; return 0; }

	//map 입력
	for (int h{ 0 }; h < H; h++) {
		for (int w{ 0 }; w < W; w++) {
			cin >> map[h][w];
		}
	}

	//세로, 가로, KCount
	set<vector<int>> temp;
	temp.insert({ 0,0,K });

	visited[0][0].insert(K);

	int ans{ 0 };

	while (true) {
		set<vector<int>> temp2;

		for (auto t : temp) {
			//나이트 이동
			for (int i{ 0 }; i < 8; i++) {
				int x = t[0] + ndx[i];
				int y = t[1] + ndy[i];

				if (x >= 0 && x < H && y >= 0 && y < W && t[2] > 0) {
					if (map[x][y] == 0 && visited[x][y].count(t[2] - 1) == 0) {
						visited[x][y].insert(t[2] - 1);
						vector<int> tmp = { x, y, t[2] - 1 };
						//	if (find(temp2.begin(), temp2.end(), tmp) == temp2.end()) {
						temp2.insert({ x, y, t[2] - 1 });
						//}
					}
				}
			}

			//일반이동
			for (int i{ 0 }; i < 4; i++) {
				int x = t[0] + dx[i];
				int y = t[1] + dy[i];

				if (x >= 0 && x < H && y >= 0 && y < W) {
					if (map[x][y] == 0 && visited[x][y].count(t[2]) == 0) {
						visited[x][y].insert(t[2]);
						vector<int> tmp = { x, y, t[2] };
						//if (find(temp2.begin(), temp2.end(), tmp) == temp2.end()) {
						temp2.insert({ x, y, t[2] });
						//}
					}
				}
			}


		}
		//cout << "temp2: ";
		//for (auto a : temp2) cout << a[0] << a[1] << a[2] << " ";
		//cout << "\n";

		temp = temp2;

		if (temp.size() > 0) {
			for (auto a : temp) {
				if (a[0] == H - 1 && a[1] == W - 1) {
					ans++;
					cout << ans;
					//system("pause");
					return 0;
				}
			}
			ans++;
		}
		else { ans = -1; break; }
	}

	cout << ans;


	//system("pause");
	return 0;
}