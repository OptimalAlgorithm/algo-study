#include <iostream>
#include <vector>

using namespace std;

int main() {
	int M, N;
	cin >> M >> N;

	vector<int> line(M, 0);
	vector<vector<int>> tomato(N, line);

	int count0{ 0 };
	//토마토 데이터 입력
	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < M; j++) {
			cin >> tomato[i][j];
			if (tomato[i][j] == 0) count0++;
		}
	}

	if (count0 == 0) {
		cout << "0";
		system("pause");
		return 0;
	}

	vector<pair<int, int>> dir;
	dir.push_back(make_pair(-1, 0)); //상
	dir.push_back(make_pair(1, 0)); //하
	dir.push_back(make_pair(0, -1)); //좌
	dir.push_back(make_pair(0, 1)); //우


	//안 익은 토마토가 혼자 있을 경우
	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < M; j++) {
			if (tomato[i][j] == 0) {
				int count{ 0 }, count2{ 0 };
				for (auto a : dir) {
					int x = i + a.first;
					int y = j + a.second;

					if (x >= 0 && x < N && y >= 0 && y < M) {
						if (tomato[x][y] == -1) count++;
					}
					else count2++;
				}
				if (count == 4 - count2) {
					cout << "-1";
					system("pause");
					return 0;
				}
			}
		}
	}

	//모든 토마토가 익을 수 있는 경우
	int days{ 1 };
	vector<pair<int, int>> update;

	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < M; j++) {
			if (tomato[i][j] == 1) {

				for (auto a : dir) {
					int x = i + a.first;
					int y = j + a.second;

					if (x >= 0 && x < N && y >= 0 && y < M) {
						if (tomato[x][y] == 0) {
							tomato[x][y] = 1;
							count0--;
							update.push_back(make_pair(x, y));
						}
					}
				}
			}
		}
	}

	while (count0 > 0) {
		days++;
		
		vector<pair<int, int>> update2;
		for (auto u : update) {
			int x = u.first;
			int y = u.second;

			for (auto a : dir) {
				int xx = x + a.first;
				int yy = y + a.second;

				if (xx >= 0 && xx < N && yy >= 0 && yy < M) {
					if (tomato[xx][yy] == 0) {
						tomato[xx][yy] = 1;
						update2.push_back(make_pair(xx, yy));
						count0--;
					}
				}
			}
		}
		update = update2;
	}

	cout << days;

	system("pause");
	return 0;
}