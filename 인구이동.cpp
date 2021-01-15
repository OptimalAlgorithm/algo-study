//https://www.acmicpc.net/problem/16234
//인구 이동



#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>

using namespace std;


int N, L, R;

int map[51][51];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

bool  simulate() {

	vector<vector<pair<int, int>>> move; //이동시키려고 저장

	int visited[51][51] = { 0, };
	//bfs로 연합 구하기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 0) {
				visited[i][j] = 1;

				vector<pair<int, int>> tmp;
				tmp.push_back(make_pair(i, j));

				queue<pair<int, int>> q;
				q.push(make_pair(i, j));
				while (!q.empty()) {
					pair<int, int> p = q.front();
					q.pop();

					for (int d = 0; d < 4; d++) {
						int x = p.first + dx[d];
						int y = p.second + dy[d];

						if (x < 0 || x >= N || y < 0 || y >= N || visited[x][y] == 1) continue;

						//cout << "비교:" << abs(map[x][y] - map[i][j]) << "\n";


						int diff = abs(map[x][y] - map[p.first][p.second]);
						if (diff >= L && diff <= R) {
							//cout << "true\n";
							visited[x][y] = 1;
							tmp.push_back(make_pair(x, y));
							q.push(make_pair(x, y));
						}
					}

				}

				if (tmp.size() > 1) move.push_back(tmp);
			}
		}
	}


	if (move.size() == 0)return false; //이동 없으면 false 리턴
	else {
		//인구 이동시키기		
		for (auto a : move) {
			int avg = 0;

			for (auto aa : a) {
				avg += map[aa.first][aa.second];
			}

			avg /= a.size();

			for (auto aa : a) {
				map[aa.first][aa.second] = avg;
			}
		}

		return true; //이동한 인구가 있었다는 뜻
	}
}


int main() {

	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}



	int cnt = 0;
	while (true) {
		if (simulate())cnt++;
		else break;
	}

	cout << cnt;
}