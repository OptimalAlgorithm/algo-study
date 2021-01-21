//https://www.acmicpc.net/problem/14502
//연구소

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M; //세로가 N

vector<vector<int>> map;

vector<pair<int, int>> wall; //벽이 올 수 있는 곳
vector<pair<int, int>> virus; //바이러스 위치

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int answer = 0;

vector<int> selected;

void spread() {

	vector<vector<int>> tmpMap = map;

	tmpMap[wall[selected[0]].first][wall[selected[0]].second] = 1;
	tmpMap[wall[selected[1]].first][wall[selected[1]].second] = 1;
	tmpMap[wall[selected[2]].first][wall[selected[2]].second] = 1;


	vector<vector<int>> visited;
	visited.clear();
	visited.resize(N, vector<int>(M, 0));

	queue<pair<int, int>> q;
	for (auto a : virus) {
		visited[a.first][a.second] = 1;
		q.push(a);
	}

	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			int x = p.first + dx[d];
			int y = p.second + dy[d];

			if (x < 0 || x >= N || y < 0 || y >= M)continue;

			if (visited[x][y] == 0 && tmpMap[x][y] == 0) {
				visited[x][y] = 1;
				tmpMap[x][y] = 2;
				q.push(make_pair(x, y));
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmpMap[i][j] == 0)cnt++;
		}
	}

	if (cnt > answer)answer = cnt;
}


void select(int idx, int cnt) {
	if (cnt == 0) {
		spread();
	}
	else {
		for (int i = idx; i <= wall.size() - cnt; i++) {
			selected.push_back(i);
			select(i + 1, cnt - 1);
			selected.pop_back();
		}
	}
}


int main() {

	cin >> N >> M;

	map.resize(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] == 0)wall.push_back(make_pair(i, j));
			else if (map[i][j] == 2)virus.push_back(make_pair(i, j));

		}
	}

	select(0, 3); //벽을 3개 골라서 놓는다

	cout << answer;
}