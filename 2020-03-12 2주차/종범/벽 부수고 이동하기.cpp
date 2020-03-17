// https://www.acmicpc.net/problem/2206

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x, y, cnt;
}Info;

const int MAX = 1000;
const int INF = 987654321;
int N, M, ans = INF;
int MAP[MAX][MAX];
int dist[MAX][MAX][2];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void bfs() {
	queue<Info> q;
	q.push({ 0,0,0 });
	dist[0][0][0] = 1;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int cnt = q.front().cnt;
		q.pop();

		if (x == N - 1 && y == M - 1) {
			ans = min(ans, dist[x][y][cnt]);
			continue;
		}

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
				if (MAP[nx][ny] == 0) {
					if (dist[nx][ny][cnt] > dist[x][y][cnt] + 1) {
						dist[nx][ny][cnt] = dist[x][y][cnt] + 1;
						q.push({ nx,ny,cnt });
					}
				}
				else {
					if (cnt < 1) {
						if (dist[nx][ny][cnt + 1] > dist[x][y][cnt] + 1) {
							dist[nx][ny][cnt + 1] = dist[x][y][cnt] + 1;
							q.push({ nx,ny, cnt + 1 });
						}
					}
				}
			}
		}
	}
}

void solve() {
	bfs();
	if (ans == INF) ans = -1;
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.size(); j++) {
			MAP[i][j] = str[j] - '0';
			dist[i][j][0] = dist[i][j][1] = INF;
		}
	}

	solve();
	return 0;
}