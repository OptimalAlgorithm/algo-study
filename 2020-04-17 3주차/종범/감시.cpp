// https://www.acmicpc.net/problem/15683

#include<bits/stdc++.h>
using namespace std;

const int MAX = 8;
const int INF = 987654321;
int N, M, ans = INF;
int MAP[MAX][MAX], CMAP[MAX][MAX];
vector<pair<int, int>> v;		// 카메라 좌표
vector<int> picked;				// 방향 조합

// 동남서북
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

void show() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << CMAP[i][j] << ' ';
		}
		cout << '\n';
	}
}

// 맵복사
void copy_MAP() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			CMAP[i][j] = MAP[i][j];
		}
	}
}

// 감시 함수
void watch(int x, int y, int dir) {
	int nx = x;
	int ny = y;
	while (true) {
		nx += dx[dir];
		ny += dy[dir];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M || CMAP[nx][ny] == 6) break;
		if (CMAP[nx][ny] >= 1 && CMAP[nx][ny] <= 5) continue;
		CMAP[nx][ny] = -1;
	}
}

int solution() {
	int cnt = 0;
	for (int i = 0; i < picked.size(); i++) {
		int dir = picked[i];
		int x = v[i].first;
		int y = v[i].second;
		int camera = MAP[x][y];

		switch (camera) {
		case 1:
			watch(x, y, dir);
			break;
		case 2:
			watch(x, y, dir);
			watch(x, y, (dir + 2) % 4);
			break;
		case 3:
			watch(x, y, dir);
			watch(x, y, (dir + 1) % 4);
			break;
		case 4:
			watch(x, y, dir);
			watch(x, y, (dir + 1) % 4);
			watch(x, y, (dir + 2) % 4);
			break;
		case 5:
			watch(x, y, 0);
			watch(x, y, 1);
			watch(x, y, 2);
			watch(x, y, 3);
			break;
		}
	}

	//show();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (CMAP[i][j] == 0)
				cnt++;
		}
	}
	return cnt;
}

// 방향 조합
void dfs() {
	if (picked.size() == v.size()) {
		copy_MAP();
		ans = min(ans, solution());
		return;
	}

	for (int i = 0; i < 4; i++) {
		picked.push_back(i);
		dfs();
		picked.pop_back();
	}
}

void solve() {
	dfs();
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] != 0 && MAP[i][j] != 6) {
				v.push_back({ i,j });
			}
		}
	}
	solve();
	return 0;
}