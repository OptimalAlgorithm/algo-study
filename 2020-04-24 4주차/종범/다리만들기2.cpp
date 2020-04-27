// https://www.acmicpc.net/problem/17472
// 19년 6월 상시 2번

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int a, b, dist;
}Info;

const int MAX = 10;
const int INF = 987654321;
int N, M, ans = INF, cnt;
int MAP[MAX][MAX];
bool visited[MAX][MAX];
int graph[7][7];
bool check[50];
vector<Info> v, picked;

vector<int> connected[7];
bool connect[7];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void show() {
	cout << "-------------------------" << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << MAP[i][j] << ' ';
		}
		cout << '\n';
	}
}

void numbering_bfs(int sx, int sy) {
	queue<pair<int, int>> q;
	q.push({ sx,sy });
	MAP[sx][sy] = cnt;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M || MAP[nx][ny] == 0 || MAP[nx][ny] != -1) continue;
			q.push({ nx,ny });
			MAP[nx][ny] = cnt;
		}
	}
}

// 대륙 넘버링
void numbering() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == -1) {
				++cnt;
				numbering_bfs(i, j);
			}
		}
	}
}

// 섬마다 연결가능한 다리 길이를 찾아 연결그래프 갱신하기
void find_bridge() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] != 0) {
				int startNum = MAP[i][j];
				int destNum = 0;
				int nx = i, ny = j;
				int dist = 0;
				for (int k = 0; k < 4; k++) {
					while (true) {
						nx += dx[k];
						ny += dy[k];
						dist++;
						if (nx < 0 || nx >= N || ny < 0 || ny >= M || MAP[nx][ny] == startNum) break;
						if (MAP[nx][ny] != 0) {
							destNum = MAP[nx][ny];
							dist--;
							break;
						}
					}
					if (dist < 2) {		// 다리 길이가 2보다 짧으면 탈락
						nx = i, ny = j;
						dist = 0;
						destNum = 0;
						continue;
					}
					else {
						if (destNum != 0) {		// 더 짧은길이로 갱신
							graph[startNum][destNum] = min(graph[startNum][destNum], dist);
							graph[destNum][startNum] = min(graph[startNum][destNum], dist);
						}
						nx = i, ny = j;
						dist = 0;
						destNum = 0;
						continue;
					}
				}
			}
		}
	}
}

void land_dfs(int cur) {
	connect[cur] = true;

	for (int i = 0; i < connected[cur].size(); i++) {
		int next = connected[cur][i];
		if (connect[next]) continue;
		connect[next] = true;
		land_dfs(next);
	}
}

bool is_connected() {
	memset(connect, false, sizeof(connect));
	for (int i = 1; i < 7; i++) {
		connected[i].clear();
	}

	for (int i = 0; i < picked.size(); i++) {
		connected[picked[i].a].push_back(picked[i].b);
		connected[picked[i].b].push_back(picked[i].a);
	}
	
	// picked에서 아무 대륙에서 시작해서 모든 대륙을 순회할 수 있어야함
	land_dfs(picked[0].a);

	// 모두 연결되지 않았으면 false 반환
	for (int i = 1; i <= cnt; i++) {
		if (connect[i] == false) return false;
	}
	return true;
}

void dfs() {
	if (picked.size() == cnt - 1) {	// 다리는 무조건 대륙 개수 -1개 뽑아야함
		if (is_connected()) {	// 대륙이 모두 연결됐는지
			int sum = 0;
			for (int i = 0; i < picked.size(); i++) {
				sum += picked[i].dist;
			}
			ans = min(ans, sum);
		}
		return;
	}

	for (int i = 0; i < v.size(); i++) {
		if (check[i]) continue;
		check[i] = true;
		picked.push_back(v[i]);
		dfs();
		picked.pop_back();
		check[i] = false;
	}
}

void solve() {
	numbering();

	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= cnt; j++) {
			graph[i][j] = INF;
		}
	}
	find_bridge();

	// 연결그래프에서 상단 삼각형 부분만 v에 삽입
	for (int i = 1; i <= cnt; i++) {
		for (int j = i + 1; j <= cnt; j++) {
			if (graph[i][j] != INF) v.push_back({ i,j,graph[i][j] });
		}
	}
	// 조합
	dfs();
	if (ans == INF) ans = -1;
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) MAP[i][j] = -1;
		}
	}
	solve();
	return 0;
}