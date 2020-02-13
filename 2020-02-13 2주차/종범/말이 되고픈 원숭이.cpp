// https://www.acmicpc.net/problem/1600
// 다익스트라

#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

typedef struct {
	int x, y, depth, cnt;
}Monkey;

const int MAX = 200;
const int INF = 987654321;
int K, W, H, ans = INF;
int MAP[MAX][MAX];
int dist[MAX][MAX][31];		// 원숭이가 말 처럼 이동한 횟수마다 depth를 담는 배열

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int DX[] = { -2,-1,1,2,2,1,-1,-2 };
int DY[] = { 1,2,2,1,-1,-2,-2,-1 };

void bfs() {
	queue<Monkey> q;
	q.push({ 0,0,0,0 });
	dist[0][0][0] = 0;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int depth = q.front().depth;
		int cnt = q.front().cnt;
		q.pop();
		
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= H || ny < 0 || ny >= W || MAP[nx][ny] == 1) continue;
			if (depth + 1 < dist[nx][ny][cnt]) {
				q.push({ nx,ny,depth + 1,cnt });
				dist[nx][ny][cnt] = depth + 1;
			}
		}

		// 말 이동처럼 움직인 횟수가 K보다 작다면
		if (cnt < K) {
			for (int k = 0; k < 8; k++) {
				int nx = x + DX[k];
				int ny = y + DY[k];
				if (nx < 0 || nx >= H || ny < 0 || ny >= W || MAP[nx][ny] == 1) continue;
				if (depth + 1 < dist[nx][ny][cnt+1]) {
					q.push({ nx,ny,depth + 1, cnt + 1 });
					dist[nx][ny][cnt + 1] = depth + 1;
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);


	cin >> K >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			for (int k = 0; k <= K; k++) {
				dist[i][j][k] = INF;
			}
		}
	}

	bfs();
	for (int k = 0; k <= K; k++) {
		ans = min(ans, dist[H - 1][W - 1][k]);
	}

	if (ans == INF) cout << -1 << '\n';
	else cout << ans << '\n';
	return 0;
}