// https://www.acmicpc.net/problem/1113
// 704ms : 효율이 썩..

#include<bits/stdc++.h>
using namespace std;

const int MAX = 52;
int N, M, ans, maxH;
int MAP[MAX][MAX];
bool visited[MAX][MAX];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void show() {
	cout << "-------------------------------" << '\n';
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= M + 1; j++) {
			cout << MAP[i][j] << ' ';
		}
		cout << '\n';
	}
}

void bfs(int sx, int sy, int H) {
	queue<pair<int, int>> q;
	q.push({ sx,sy });
	visited[sx][sy] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx > N + 1 || ny < 0 || ny > M + 1 || visited[nx][ny]) continue;
			if (MAP[nx][ny] >= H) continue;
			visited[nx][ny] = true;
			q.push({ nx,ny });
		}
	}
}

bool check() {
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= M + 1; j++) {
			if (i == 0 || i == N + 1 || j == 0 || j == M + 1) {
				if (visited[i][j]) return false;
			}
		}
	}
	return true;
}

// 수면 한단계씩 상승시키기
void UP(int H) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (visited[i][j]) {
				ans++;
				MAP[i][j] = H;
			}
		}
	}
}

void solve() {
	for (int H = 1; H <= maxH; H++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (MAP[i][j] < H) {
					bfs(i,j,H);
					if (check()) {		// 물이 맵 범위 밖으로 새지 않았다면
						UP(H);			// 수면 올리기
					}
					memset(visited, false, sizeof(visited));
				}
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		string str;
		cin >> str;
		for (int j = 1; j <= M; j++) {
			MAP[i][j] = str[j - 1] - '0';
			if (MAP[i][j] > maxH) maxH = MAP[i][j];
		}
	}

	solve();
	return 0;
}