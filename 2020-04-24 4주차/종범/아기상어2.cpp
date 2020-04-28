// https://www.acmicpc.net/problem/17086

#include<bits/stdc++.h>
using namespace std;

const int MAX = 50;
const int INF = 987654321;
int N, M, ans;
int MAP[MAX][MAX];
bool check[MAX][MAX];
int dist[MAX][MAX];

vector<pair<int, int>> v;

int dx[] = { 0,1,1,1,0,-1,-1,-1 };
int dy[] = { 1,1,0,-1,-1,-1,0,1 };

void bfs(int sx, int sy) {
	queue<pair<int, int>> q;
	q.push(make_pair(sx, sy));
	check[sx][sy] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int k = 0; k < 8; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
				if (MAP[nx][ny] == 0 && !check[nx][ny]) {
					if (dist[nx][ny] > dist[x][y] + 1) {
						dist[nx][ny] = dist[x][y] + 1;
						q.push(make_pair(nx, ny));
						check[nx][ny] = true;
					}
				}
			}
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (dist[i][j] > ans) ans = dist[i][j];
		}
	}
	cout << ans << '\n';
}

void solve() {
	for (int i = 0; i < v.size(); i++) {
		memset(check, false, sizeof(check));
		bfs(v[i].first, v[i].second);
	}
	Print();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				v.push_back({ i,j });
				dist[i][j] = 0;
			}
			else dist[i][j] = INF;
		}
	}
	solve();
	return 0;
}