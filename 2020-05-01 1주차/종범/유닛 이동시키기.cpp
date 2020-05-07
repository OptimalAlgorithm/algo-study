// https://www.acmicpc.net/problem/2194
// 유닛의 왼쪽 상단좌표와, 도착지점의 왼쪽 상단좌표만 생각해서 단순 bfs

#include<bits/stdc++.h>
using namespace std;

const int MAX = 500;
const int INF = 987654321;
int N, M, A, B, K, ans = INF;
int MAP[MAX][MAX];
int dist[MAX][MAX];
bool visited[MAX][MAX];
int sx, sy, ex, ey;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void bfs() {
	queue<pair<int, int>> q;
	q.push({ sx,sy });
	dist[sx][sy] = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

			// 유닛의 상단좌표로부터 A X B 만큼 끼워넣을 수 있는지
			bool flag = false;
			for (int i = nx; i < nx + A; i++) {
				for (int j = ny; j < ny + B; j++) {
					if (i >= N || j >= M) {
						flag = true;
						break;
					}
					else if (MAP[i][j] == 1) {
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
			if (!flag) {
				if (dist[nx][ny] > dist[x][y] + 1) {
					dist[nx][ny] = dist[x][y] + 1;
					q.push({ nx,ny });
				}
			}
		}
	}
}

void solve() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dist[i][j] = INF;
		}
	}
	bfs();
	if (dist[ex][ey] == INF) cout << -1 << '\n';
	else cout << dist[ex][ey] << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M >> A >> B >> K;
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		x -= 1; y -= 1;
		MAP[x][y] = 1;
	}
	cin >> sx >> sy >> ex >> ey;
	sx -= 1; sy -= 1; ex -= 1; ey -= 1;
	solve();
	return 0;
}