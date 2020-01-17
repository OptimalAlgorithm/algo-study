//양

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int R, C;
	cin >> R >> C;

	//주어지는 데이터 입력
	vector<string> map;
	for (int r{ 0 }; r < R; r++) {
		string s;
		cin >> s;

		map.push_back(s);
	}

	//방향
	vector<pair<int, int>> dir;
	dir.push_back(make_pair(-1, 0)); //상
	dir.push_back(make_pair(1, 0)); //하
	dir.push_back(make_pair(0, -1)); //좌
	dir.push_back(make_pair(0, 1)); //우

	int sheep{ 0 }, wolf{ 0 };

	for (int i{ 0 }; i < R; i++) {
		for (int j{ 0 }; j < C; j++) {
			if (map[i][j] != 'C') {//체크안했던 곳이면
				int counto{ 0 }, countv{ 0 };
				vector<pair<int, int>> temp;
				temp.push_back(make_pair(i, j));

				while (temp.size() > 0) {
					int x = temp.back().first;
					int y = temp.back().second;

					temp.pop_back();

					for (auto a : dir) {
						int xx = x + a.first;
						int yy = y + a.second;

						if (xx >= 0 && xx < R && yy >= 0 && yy < C) {
							if (map[xx][yy] != 'C') {
								if (map[xx][yy] == '.') { //공백
									map[xx][yy] = 'C'; //체크
									temp.push_back(make_pair(xx, yy));
								}
								else if (map[xx][yy] == 'o') { //양
									map[xx][yy] = 'C'; //체크
									temp.push_back(make_pair(xx, yy));
									counto++;
								}
								else if (map[xx][yy] == 'v') { //늑대
									map[xx][yy] = 'C'; //체크
									temp.push_back(make_pair(xx, yy));
									countv++;
								}
								else {} //울타리
							}
						}
					}
				}

				if (counto > countv) sheep += counto;
				else wolf += countv;
			}
		}
	}

	cout << sheep << " " << wolf;

	system("pause");
	return 0;
}