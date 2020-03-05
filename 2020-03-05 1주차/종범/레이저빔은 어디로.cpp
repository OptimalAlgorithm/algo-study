// https://www.acmicpc.net/problem/3709

#include<iostream>
#include<cstring>

using namespace std;

const int MAX = 52;
int T, N, R;	// tc, 맵크기, 거울개수
int MAP[MAX][MAX];
int sx, sy;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int start_dir() {
	if (sx == 0) return 2;
	else if (sx == N + 1) return 3;
	else if (sy == 0) return 0;
	else if (sy == N + 1) return 1;
}

int turn_right(int dir) {
	if (dir == 0) return 2;
	else if (dir == 1) return 3;
	else if (dir == 2) return 1;
	else if (dir == 3) return 0;
}

void solve() {
	int dir = start_dir();
	int nx = sx + dx[dir];
	int ny = sy + dy[dir];
	while (true) {
		if (nx < 1 || nx > N || ny < 1 || ny > N) {		// 밖으로 나갔다
			cout << nx << ' ' << ny << '\n';
			break;
		}
		if (MAP[nx][ny] == 1) dir = turn_right(dir);
		nx += dx[dir];
		ny += dy[dir];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> T;
	for (int test = 0; test < T; test++) {
		memset(MAP, 0, sizeof(MAP));

		cin >> N >> R;
		for (int i = 0; i < R; i++) {
			int x, y;
			cin >> x >> y;
			MAP[x][y] = 1;	// 거울설치
		}
		cin >> sx >> sy;	// 레이저 시작위치

		solve();
	}
	return 0;
}