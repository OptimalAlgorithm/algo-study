// https://www.acmicpc.net/problem/3108
// ...

#include<bits/stdc++.h>
using namespace std;

const int MAX = 2001;
int N, cnt;
int MAP[MAX][MAX];
bool visited[MAX][MAX];
int sx = 1000, sy = 1000;	// 시작위치가 1000,1000 이 되야함

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void show() {
	cout << "----------------------------------" << '\n';
	for (int i = 1000; i <= 1030; i++) {
		for (int j = 1000; j <= 1030; j++) {
			cout << visited[i][j] << ' ';
		}
		cout << '\n';
	}
}

void bfs(int a, int b) {
	queue<pair<int, int>> q;
	q.push({ a,b });
	visited[a][b] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (x == sx && y == sy) cnt -= 1;	// 시작위치에 좌표가 존재한다면 붓을 들지않아도 그릴 수 있음

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX || MAP[nx][ny] == 0 || visited[nx][ny]) continue;
			q.push({ nx,ny });
			visited[nx][ny] = true;
		}
	}
}

void solve() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (MAP[i][j] == 1 && visited[i][j] == false) {
				bfs(i, j);
				cnt++;
			}
		}
	}
	cout << cnt << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		// 500을 더하면 음수좌표도 다 양수로 올것이고, 2를 곱하면 겹쳐지지 않는 부분을 확실하게 할 수 있음
		x1 = (x1 + 500) * 2; 
		y1 = (y1 + 500) * 2;
		x2 = (x2 + 500) * 2;
		y2 = (y2 + 500) * 2;

		for (int j = x1; j <= x2; j++) {
			MAP[j][y1] = 1;
			MAP[j][y2] = 1;
		}
		for (int k = y1; k <= y2; k++) {
			MAP[x1][k] = 1;
			MAP[x2][k] = 1;
		}
	}

	solve();
	//show();
	return 0;
}