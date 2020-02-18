//[백준 6593] 상범빌딩

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int L, R, C; //높이, 세로, 가로

vector<vector<string>> map;
vector<vector<string>> visited; // 'V' == visited

								//동 서 남 북 상 하
int dl[6] = { 0,0,0,0,-1,1 };
int dr[6] = { 0,0,1,-1,0,0 };
int dc[6] = { 1,-1,0,0,0,0 };

int gL, gR, gC; // E

int main() {
	while (true) {
		int minutes{ 0 };

		cin >> L >> R >> C;
		if (L == 0 && R == 0 && C == 0) {
			break;
		}

		map.clear();
		map.resize(L);

		int cL, cR, cC;

		//map input - 층, R, C 순으로 접근
		for (int l{ 0 }; l < L; l++) {
			for (int r{ 0 }; r < R; r++) {
				string s;
				cin >> s;
				map[l].push_back(s);

				for (int c{ 0 }; c < C; c++) {
					if (s[c] == 'S') { cL = l; cR = r; cC = c; }
					else if (s[c] == 'E') { gL = l; gR = r; gC = c; }
					else {}
				}
			}
		}

		visited = map;

		vector<vector<int>> temp;
		temp.push_back({ cL, cR, cC });

		visited[cL][cR][cC] = 'V';

		while (true) {
			minutes++;

			vector<vector<int>> temp2;
			bool b = false;

			for (auto t : temp) {
				for (int d{ 0 }; d < 6; d++) {
					int tL = t[0] + dl[d];
					int tR = t[1] + dr[d];
					int tC = t[2] + dc[d];

					if (tL >= 0 && tL < L && tR >= 0 && tR < R && tC >= 0 && tC < C) {

						if (map[tL][tR][tC] == 'E') {
							b = true;
							cout << "Escaped in " << minutes << " minute(s).\n";
							break;
						}

						if (map[tL][tR][tC] == '.' && visited[tL][tR][tC] != 'V') {
							temp2.push_back({ tL, tR, tC });
							visited[tL][tR][tC] = 'V';
						}
					}
				}
				if (b == true) break;
			}
			if (b == true) break;
			else if (temp2.size() == 0) {
				cout << "Trapped!\n";
				break;
			}
			else { temp = temp2; }
		}
	}
	//system("pause");
	return 0;
}