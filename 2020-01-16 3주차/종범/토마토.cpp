// https://www.acmicpc.net/problem/7576

#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 1000;
int N, M, zero_total, ans;
int MAP[MAX][MAX];
bool check[MAX][MAX];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

queue<pair<pair<int, int>, int>> q;

void bfs() {
	int zero_cnt = 0;
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		ans = max(ans, cnt);

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M || check[nx][ny]) continue;
			if (MAP[nx][ny] == 0) {
				q.push(make_pair(make_pair(nx, ny), cnt + 1));
				check[nx][ny] = true;
				zero_cnt += 1;
			}
		}
	}

	if (zero_total - zero_cnt == 0)
		cout << ans << '\n';
	else cout << -1 << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				q.push(make_pair(make_pair(i, j), 0));
				check[i][j] = true;
			}
			else if (MAP[i][j] == 0)
				zero_total += 1;
		}
	}

	bfs();

	return 0;
}