// https://www.acmicpc.net/problem/2842
// 갓 투포인터

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x, y;
}Info;

const int MAX = 50;
const int INF = 987654321;
int N, ans = INF, total, sx, sy, minV, maxV;
char MAP[MAX][MAX];
int pirodo[MAX][MAX];
bool visited[MAX][MAX];
vector<pair<int, int>> v;
vector<int> p;

int dx[] = { 0,1,1,1,0,-1,-1,-1 };
int dy[] = { 1,1,0,-1,-1,-1,0,1 };

void show() {
	cout << "----------------------------" << '\n';
	cout << minV << ' ' << maxV << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << visited[i][j] << ' ';
		}
		cout << '\n';
	}
}

void bfs() {
	queue<Info> q;
	q.push({ sx,sy });
	visited[sx][sy] = true;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		q.pop();

		for (int i = 0; i < 8; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[nx][ny]) continue;
			if (pirodo[nx][ny] >= minV && pirodo[nx][ny] <= maxV) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
			}
		}
	}
}

bool check() {
	if (pirodo[sx][sy] >= minV && pirodo[sx][sy] <= maxV) {		// 시작위치가 최소, 최대 범위에 속하는지 확인
		memset(visited, false, sizeof(visited));
		bfs();
		//show();

		// K모두 방문했는지 확인
		for (int i = 0; i < v.size(); i++) {
			if (visited[v[i].first][v[i].second] == false)
				return false;
		}
		return true;
	}
	return false;
}

void solve() {
	//투포인터로 탐색시간 단축

	int start = 0, end = 0;
	for(int end = 0; end < p.size(); end++){
		for( ; start < p.size(); start++){
			minV = p[start];
			maxV = p[end];
			if (check() == false) break;
			ans = min(ans, maxV - minV);
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'K')
				v.push_back({ i,j });
			else if (MAP[i][j] == 'P') {
				sx = i;
				sy = j;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> pirodo[i][j];
			p.push_back(pirodo[i][j]);
		}
	}

	sort(p.begin(), p.end());
	auto it = unique(p.begin(), p.end());	// 쓰레기값 시작위치 반환
	p.erase(it, p.end());					// 쓰레기값 지우기

	solve();
	return 0;
}