#include <iostream>
#include <vector>

using namespace std;

int main() {
	int M, N;
	cin >> M >> N;

	vector<int> line(M, 0);
	vector<vector<int>> tomato(N, line);
	int count0{ 0 };
	vector<pair<int, int>> ripened;

	//토마토 데이터 입력
	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < M; j++) {
			cin >> tomato[i][j];
			if (tomato[i][j] == 0) count0++;
			if (tomato[i][j] == 1) ripened.push_back(make_pair(i, j));
		}
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
					//system("pause");
					return 0;
				}
			}
		}
	}

	//모든 토마토가 익을 수 있는 경우
	int days{ 0 };

	while (count0 > 0) {
		days++;
		vector<pair<int, int>> temp;

		for (auto a : ripened) {
			for (auto d : dir) {
				int x = a.first + d.first;
				int y = a.second + d.second;

				if (x >= 0 && x < N && y >= 0 && y < M) {
					if (tomato[x][y] == 0) {
						tomato[x][y] = 1;
						count0--;
						temp.push_back(make_pair(x, y));
					}
				}
			}
		}

		ripened = temp;
	}

	cout << days;
	//system("pause");
	return 0;
}