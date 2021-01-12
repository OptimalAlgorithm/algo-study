//https://www.acmicpc.net/problem/17142
//연구소3


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

int N, M; //연구소 크기, 바이러스 수

vector<vector<int>> map; // 0은 빈 칸, 1은 벽, 2는 바이러스를 놓을 수 있는 위치

vector<pair<int, int>> virus; //바이러스가 올 수 있는 위치

vector<int> selected;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int minSeconds = INT_MAX;

bool isFinished(vector<vector<int>> tmpMap) {
	bool flag = true;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tmpMap[i][j] == 0) return false;
		}
	}

	return true;
}

void bfs() {
	vector<vector<int>> tmpMap = map;
	
	//퍼뜨릴수있을때까지 퍼뜨리고
	queue<pair<int, int>> q; //0칸으로
	for (auto a : selected) {
		q.push(make_pair(virus[a].first, virus[a].second));
		tmpMap[virus[a].first][virus[a].second] = 1;
	}

	queue<pair<int, int>> q2; //2칸으로

	int cnt1 = 0;
	int cnt2 = 0;
	while (!(q.empty() && q2.empty())) {
		bool flag = true; //cnt1증가여부
		int size = q.size();
		int size2 = q2.size();

		for (int i = 0; i < size2; i++) {
			pair<int, int > p = q2.front();
			q2.pop();

			for (int d = 0; d < 4; d++) {
				int r = p.first + dx[d];
				int c = p.second + dy[d];

				if (r < 0 || r >= N || c < 0 || c >= N)continue;

				if (tmpMap[r][c] == 0) {
					tmpMap[r][c] = 1;
					q.push(make_pair(r, c));
					
					if (cnt1 < cnt2 + 1) {
						cnt1 = cnt2 + 1;
						flag = false;
					}
				}
				else if (tmpMap[r][c] == 2) {
					tmpMap[r][c] = 1;
					q2.push(make_pair(r, c));
				}

			}
		}
		

		for (int i = 0; i < size; i++) {
			pair<int, int > p = q.front();
			q.pop();

			for (int d = 0; d < 4; d++) {
				int r = p.first + dx[d];
				int c = p.second + dy[d];

				if (r < 0 || r >= N || c < 0 || c >= N)continue;

				if (tmpMap[r][c] == 0) {
					tmpMap[r][c] = 1;
					q.push(make_pair(r, c));
				}
				else if (tmpMap[r][c] == 2) {
					tmpMap[r][c] = 1;
					q2.push(make_pair(r, c));
				}

			}
		}
		
		if(flag && q.size() > 0) cnt1++;		
		if (q2.size() > 0 || q.size() > 0) cnt2++;
	}


	//다 퍼졌는지 확인해서 min 갱신
	if (isFinished(tmpMap)) {
		minSeconds = min(minSeconds, cnt1);
	}

}

void select(int idx, int cnt) {//idx부터 cnt개 고르기
	if (cnt == 0) { //M개 다 골랐으면 bfs
		bfs(); 
	}
	else {
		for (int i = idx; i <= virus.size() - cnt; i++){
			selected.push_back(i);
			select(i + 1, cnt - 1);
			selected.pop_back();
		}
	}
}

int main() {

	cin >> N >> M;
	map.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			if (map[i][j] == 2) {
				virus.push_back(make_pair(i, j));
			}
		}
	}

	select(0, M);

	if (minSeconds == INT_MAX)cout << "-1";
	else cout << minSeconds;

}