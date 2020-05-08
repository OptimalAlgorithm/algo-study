// https://www.acmicpc.net/problem/1194

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x, y, cnt, a, b, c, d, e, f;
}Info;

const int MAX = 50;
int N, M;
char MAP[MAX][MAX];
bool visited[MAX][MAX][2][2][2][2][2][2];
int sx, sy;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void show() {
	cout << "--------------------------" << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << MAP[i][j];
		}
		cout << '\n';
	}
}

int bfs() {
	queue<Info> q;
	q.push({ sx,sy, 0,0,0,0,0,0,0 });
	visited[sx][sy][0][0][0][0][0][0] = true;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int cnt = q.front().cnt;
		int a = q.front().a;
		int b = q.front().b;
		int c = q.front().c;
		int d = q.front().d;
		int e = q.front().e;
		int f = q.front().f;
		q.pop();

		if (MAP[x][y] == '1') {
			return cnt;
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M || MAP[nx][ny] == '#' || visited[nx][ny][a][b][c][d][e][f]) continue;
			if (MAP[nx][ny] == '.' || MAP[nx][ny] == '1') {
				q.push({ nx,ny,cnt + 1, a,b,c,d,e,f });
				visited[nx][ny][a][b][c][d][e][f] = true;
			}
			else if (MAP[nx][ny] >= 'a' && MAP[nx][ny] <= 'f') {	// ¿­¼è¸¦ ¸¸³µ´Ù
				if (MAP[nx][ny] == 'a') {
					visited[nx][ny][a][b][c][d][e][f] = true;
					q.push({ nx,ny,cnt + 1,1,b,c,d,e,f });
				}
				else if (MAP[nx][ny] == 'b') {
					visited[nx][ny][a][b][c][d][e][f] = true;
					q.push({ nx,ny,cnt + 1,a,1,c,d,e,f });
				}
				else if (MAP[nx][ny] == 'c') {
					visited[nx][ny][a][b][c][d][e][f] = true;
					q.push({ nx,ny,cnt + 1,a,b,1,d,e,f });
				}
				else if (MAP[nx][ny] == 'd') {
					visited[nx][ny][a][b][c][d][e][f] = true;
					q.push({ nx,ny,cnt + 1,a,b,c,1,e,f });
				}
				else if (MAP[nx][ny] == 'e') {
					visited[nx][ny][a][b][c][d][e][f] = true;
					q.push({ nx,ny,cnt + 1,a,b,c,d,1,f });
				}
				else if (MAP[nx][ny] == 'f') {
					visited[nx][ny][a][b][c][d][e][f] = true;
					q.push({ nx,ny,cnt + 1,a,b,c,d,e,1 });
				}
			}
			else if (MAP[nx][ny] >= 'A' && MAP[nx][ny] <= 'Z') {	// ¹®À» ¸¸³µ´Ù
				if (MAP[nx][ny] == 'A' && a == 1) {
					q.push({ nx,ny,cnt + 1, a,b,c,d,e,f });
					visited[nx][ny][a][b][c][d][e][f] = true;
				}
				else if (MAP[nx][ny] == 'B' && b == 1) {
					q.push({ nx,ny,cnt + 1, a,b,c,d,e,f });
					visited[nx][ny][a][b][c][d][e][f] = true;
				}
				else if (MAP[nx][ny] == 'C' && c == 1) {
					q.push({ nx,ny,cnt + 1, a,b,c,d,e,f });
					visited[nx][ny][a][b][c][d][e][f] = true;
				}
				else if (MAP[nx][ny] == 'D' && d == 1) {
					q.push({ nx,ny,cnt + 1, a,b,c,d,e,f });
					visited[nx][ny][a][b][c][d][e][f] = true;
				}
				else if (MAP[nx][ny] == 'E' && e == 1) {
					q.push({ nx,ny,cnt + 1, a,b,c,d,e,f });
					visited[nx][ny][a][b][c][d][e][f] = true;
				}
				else if (MAP[nx][ny] == 'F' && f == 1) {
					q.push({ nx,ny,cnt + 1, a,b,c,d,e,f });
					visited[nx][ny][a][b][c][d][e][f] = true;
				}
			}
		}
	}
	return -1;
}

void solve() {
	cout << bfs() << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == '0') {
				sx = i;
				sy = j;
				MAP[i][j] = '.';
			}
		}
	}
	solve();
	return 0;
}