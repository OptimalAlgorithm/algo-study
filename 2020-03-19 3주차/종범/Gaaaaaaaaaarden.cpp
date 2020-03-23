// https://www.acmicpc.net/problem/18809
// 지역으로 선언해도 pair는 무조건 0으로 초기화 해줌

#include<bits/stdc++.h>
using namespace std;

const int MAX = 50;
const int INF = 987654321;
int N, M, G, R, ans;
int MAP[MAX][MAX];
vector<pair<int, int> > v, r, g;		// 황토좌표, 빨강, 초록

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int solution() {
	queue<pair<int, int>> q;
	pair<int,int> visited[MAX][MAX];		// first=dist, second = 0:empty, 1:레드, 2:그린, 3:꽃
	for (int i = 0; i < g.size(); i++) {
		visited[g[i].first][g[i].second].first = 0;
		visited[g[i].first][g[i].second].second = 2;
		q.push(g[i]);
	}
	for (int i = 0; i < r.size(); i++) {
		visited[r[i].first][r[i].second].first = 0;
		visited[r[i].first][r[i].second].second = 1;
		q.push(r[i]);
	}

	int cnt = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (visited[x][y].second == 3) continue;

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M || MAP[nx][ny] == 0) continue;
			if (visited[nx][ny].second == 1) {		// Red일떄
				if (visited[nx][ny].first == visited[x][y].first + 1 && visited[x][y].second == 2) {
					visited[nx][ny].second = 3;		// 꽃으로 변경
					cnt++;
				}
			}
			else if (visited[nx][ny].second == 2) {		// Green일때
				if (visited[nx][ny].first == visited[x][y].first + 1 && visited[x][y].second == 1) {
					visited[nx][ny].second = 3;			// 꽃으로 변경
					cnt++;
				}
			}
			else if (visited[nx][ny].second == 0) {		// Red던 Green이던 방문한적이 없을 경우에만 퍼트림
				visited[nx][ny].first = visited[x][y].first + 1;
				visited[nx][ny].second = visited[x][y].second;
				q.push({ nx,ny });
			}
		}
	}
	return cnt;
}

void dfs(int idx, int red, int green) {
	if (red == 0 && green == 0) {
		if (r.size() > 0 && g.size() > 0) {
			ans = max(ans, solution());
		}
		return;
	}
	if (idx >= v.size()) return;

	for (int i = idx; i < v.size(); i++) {
		if (red > 0) {
			r.push_back(v[i]);
			dfs(i + 1, red - 1, green);
			r.pop_back();
		}
		if (green > 0) {
			g.push_back(v[i]);
			dfs(i + 1, red, green - 1);
			g.pop_back();
		}
	}
}

void solve() {
	dfs(0, R, G);
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> G >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2) {
				v.push_back({ i,j });
			}
		}
	}

	solve();
	return 0;
}