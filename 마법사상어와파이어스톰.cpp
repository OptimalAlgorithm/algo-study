//https://www.acmicpc.net/problem/20058
//마법사 상어와 파이어스톰

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int N, Q;
int len;
vector<vector<int>> map;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int ice() { //남아있는 얼음의 양

	int answer = 0;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			answer += map[i][j];
		}
	}

	return answer;
}


int maxIce() {
	int answer = 0; //덩어리에 있는 최대 칸

	vector<vector<int>> visited(len, vector<int>(len, 0));
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (visited[i][j] == 0 && map[i][j] != 0) { //덩어리 시작점			

				queue<pair<int, int>> q;
				visited[i][j] = 1;
				int size = 1;
				q.push(make_pair(i, j));

				while (!q.empty()) {
					pair<int, int> p = q.front();
					q.pop();

					for (int d = 0; d < 4; d++) {
						int tr = p.first + dx[d];
						int tc = p.second + dy[d];

						if (tr >= 0 && tr < len && tc >= 0 && tc < len) {
							if (visited[tr][tc] == 0 && map[tr][tc] > 0) {
								visited[tr][tc] = 1;
								size++;
								q.push(make_pair(tr, tc));
							}
						}
					}
				}

				answer = max(answer, size);

			}
		}
	}

	return answer;
}

void simulate(int L) {
	//부분격자 회전 - 시계방향 90도
	int len2 = pow(2, L);
	for (int r = 0; r < len; r += len2) {
		for (int c = 0; c < len; c += len2) { //좌상향 좌표

			vector<vector<int>> tmpMap; //회전 후 모양 임시저장
			tmpMap.resize(len2, vector<int>(len2));
			for (int i = 0; i < len2; i++) {
				for (int j = 0; j < len2; j++) {
					tmpMap[j][len2 - i - 1] = map[r + i][c + j];
				}
			}

			for (int i = 0; i < len2; i++) { //임시저장된 값으로 map 갱신
				for (int j = 0; j < len2; j++) {
					map[i + r][j + c] = tmpMap[i][j];
				}
			}
		}
	}


	//인접 2 이하 얼음감소
	vector<vector<int>> map2 = map;

	for (int r = 0; r < len; r++) {
		for (int c = 0; c < len; c++) {

			if (map[r][c] > 0) {
				int cnt = 0; //인접한 얼음 칸
				for (int d = 0; d < 4; d++) {
					int tr = r + dx[d];
					int tc = c + dy[d];

					if (tr >= 0 && tr < len && tc >= 0 && tc < len) {
						if (map[tr][tc] > 0) cnt++;
					}
				}

				if (cnt < 3) map2[r][c]--;
			}
		}
	}

	map = map2;
}

int main() {
	cin >> N >> Q;
	len = pow(2, N);

	map.resize(len, vector<int>(len));
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			cin >> map[i][j];
		}
	}

	int L;
	for (int i = 0; i < Q; i++) {
		cin >> L;
		simulate(L);
	}

	cout << ice() << "\n" << maxIce();

}