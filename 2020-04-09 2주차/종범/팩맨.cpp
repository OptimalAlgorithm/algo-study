// https://www.acmicpc.net/problem/11451

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x1, y1, x2, y2;
	string route;
}P;

const int MAX = 50;
int T, N, M;
string ans;
char MAP[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];		// 1번 팩맨, 2번 팩맨
char direct[] = { 'E', 'W', 'S', 'N' };
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void init() {
	ans.clear();
	memset(visited, false, sizeof(visited));
	memset(MAP, NULL, sizeof(MAP));
}

void bfs(P p) {
	queue<P> q;
	q.push(p);
	visited[p.x1][p.y1][p.x2][p.y2] = true;

	while (!q.empty()) {
		int x1 = q.front().x1;
		int y1 = q.front().y1;
		int x2 = q.front().x2;
		int y2 = q.front().y2;
		string route = q.front().route;
		q.pop();

		if (x1 == x2 && y1 == y2) {
			ans = route;
			return;
		}

		for (int i = 0; i < 4; i++) {
			int nx1 = x1 + dx[i];
			int ny1 = y1 + dy[i];
			int nx2 = x2 + dx[i];
			int ny2 = y2 + dy[i];
			string nroute = route;		// 하..ㅅㅂ

			// 범위 벗어난 경우
			if (nx1 < 0) nx1 = N - 1;
			else if (nx1 >= N) nx1 = 0;
			else if (ny1 < 0) ny1 = M - 1;
			else if (ny1 >= M) ny1 = 0;

			if (MAP[nx1][ny1] == 'X') {		// 벽인경우, 움직이지 말것
				nx1 = x1;
				ny1 = y1;
			}
			else if (MAP[nx1][ny1] == 'G') continue;	// 유령이면

			// 범위 벗어난 경우
			if (nx2 < 0) nx2 = N - 1;
			else if (nx2 >= N) nx2 = 0;
			else if (ny2 < 0) ny2 = M - 1;
			else if (ny2 >= M) ny2 = 0;

			if (MAP[nx2][ny2] == 'X') {		// 벽인경우, 움직이지 말것
				nx2 = x2;
				ny2 = y2;
			}
			else if (MAP[nx2][ny2] == 'G') continue;	// 유령이면

			if (visited[nx1][ny1][nx2][ny2]) continue;
			visited[nx1][ny1][nx2][ny2] = true;
			nroute.push_back(direct[i]);
			q.push({ nx1,ny1,nx2,ny2, nroute});
		}
	}
}

void solve(P p) {
	bfs(p);

	if (ans == "") cout << "IMPOSSIBLE" << '\n';
	else cout << ans.size() << ' ' << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> T;
	while (T--) {
		cin >> N >> M;
		bool flag = false;
		P p;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> MAP[i][j];
				if (MAP[i][j] == 'P') {
					if (!flag) {
						p.x1 = i;
						p.y1 = j;
						flag = true;
					}
					else {
						p.x2 = i;
						p.y2 = j;
					}
				}
			}
		}

		solve(p);
		init();
	}

	return 0;
}