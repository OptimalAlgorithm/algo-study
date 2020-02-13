// https://www.acmicpc.net/problem/2589

#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

const int MAX = 50;
int N, M, ans;
char MAP[MAX][MAX];
bool check[MAX][MAX];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int bfs(int sx, int sy) {
	queue<pair<pair<int, int>, int>> q;
	q.push(make_pair(make_pair(sx, sy), 0));
	check[sx][sy] = true;

	int ret = 0;
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		ret = max(ret, cnt);
		
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M || check[nx][ny]) continue;
			if (MAP[nx][ny] == 'L') {
				q.push(make_pair(make_pair(nx, ny), cnt + 1));
				check[nx][ny] = true;
			}
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 'L') {
				ans = max(ans, bfs(i, j));
				memset(check, false, sizeof(check));
			}
		}
	}
	cout << ans << '\n';
	return 0;
}