// https://www.acmicpc.net/problem/3184

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int MAX = 250;
int R, C, sheep, wolf;
char MAP[MAX][MAX];
bool check[MAX][MAX];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

pair<int, int> bfs(int i, int j) {
	queue<pair<int, int>> q;
	q.push(make_pair(i, j));
	check[i][j] = true;

	pair<int, int> p;	// 같은 공간에서 양과 늑대의 수를 저장하기 위한 pair
	p.first = 0; p.second = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (MAP[x][y] == 'o') 	// 현위치가 양
			p.first += 1;
		else if (MAP[x][y] == 'v')  // 현위치가 늑대
			p.second += 1;

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];

			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			if (check[nx][ny] || MAP[nx][ny] == '#') continue;
			q.push(make_pair(nx, ny));
			check[nx][ny] = true;
		}
	}
	return p;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'o')
				sheep++;
			else if (MAP[i][j] == 'v')
				wolf++;
		}
	}

	pair<int, int> p;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] != '#' && check[i][j] == false) {
				p = bfs(i, j);	// 공간 내에서 first는 양의수, second는 늑대의 수

				if (p.first == 0 && p.second == 0) continue;
				if (p.first > p.second)
					wolf -= p.second;
				else if (p.first <= p.second)
					sheep -= p.first;
			}
		}
	}
	cout << sheep << ' ' << wolf << '\n';

	return 0;
}