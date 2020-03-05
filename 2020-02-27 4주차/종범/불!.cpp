// https://www.acmicpc.net/problem/4179
// 초기에 불이 여러 좌표에 존재할 수 있다는것을 간과했다

#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

const int MAX = 1000;
const int INF = 987654321;
int R, C, ans = INF;
char MAP[MAX][MAX];
int fire[MAX][MAX];
bool check[MAX][MAX];
pair<int, int> p;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
queue<pair<int, int>> fq;

void show() {
	cout << "----------------------------" << '\n';
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << fire[i][j] << ' ';
		}
		cout << '\n';
	}
}

void fire_bfs() {
	while (!fq.empty()) {
		int x = fq.front().first;
		int y = fq.front().second;
		fq.pop();

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 0 && nx < R && ny >= 0 && ny < C) {
				if (MAP[nx][ny] != '#' && fire[x][y] + 1 < fire[nx][ny]) {
					fire[nx][ny] = fire[x][y] + 1;
					fq.push({ nx,ny });
				}
			}
		}
	}
}

void bfs() {
	queue<pair<pair<int, int>, int>> q;
	q.push(make_pair(make_pair(p.first, p.second), 0));
	check[p.first][p.second] = true;

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) {
				ans = min(ans, cnt + 1);
				continue;
			}
			else if(nx >= 0 && nx < R && ny >= 0 && ny < C){
				if (MAP[nx][ny] != '#' && fire[nx][ny] > cnt + 1 && !check[nx][ny]) {
					check[nx][ny] = true;
					q.push(make_pair(make_pair(nx, ny), cnt + 1));
				}
			}
		}
	}
}

void solution() {
	fire_bfs();
	bfs();
	if (ans == INF) {
		cout << "IMPOSSIBLE" << '\n';
	}
	else cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'J') {
				p.first = i;
				p.second = j;
				fire[i][j] = INF;
			}
			else if (MAP[i][j] == 'F') {
				fq.push({ i,j });
				fire[i][j] = 0;
			}
			else fire[i][j] = INF;
		}
	}

	solution();
	return 0;
}