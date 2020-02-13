// https://www.acmicpc.net/problem/6593

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

typedef struct {
	int x, y, z;
}Pos;

const int MAX = 30;
int L, R, C, ans;
char MAP[MAX][MAX][MAX];	// 층,x,y
bool check[MAX][MAX][MAX];	

int dx[] = { 0,0,0,0,1,-1 };	// 동서
int dy[] = { 0,0,1,-1,0,0 };	// 남북
int dz[] = { 1,-1,0,0,0,0 };	// 상하

Pos start, dest;

void bfs() {
	queue<pair<pair<int, int>, pair<int,int>>> q;	// x,y좌표 z좌표, 걸어다닌 횟수
	check[start.z][start.x][start.y] = true;
	q.push(make_pair(make_pair(start.x, start.y), make_pair(start.z, 0)));

	while (!q.empty()) {
		int z = q.front().second.first;
		int x = q.front().first.first;
		int y = q.front().first.second;
		int cnt = q.front().second.second;
		q.pop();

		// 도달했으면 출력후 함수 종료
		if (x == dest.x && y == dest.y && z == dest.z) {
			cout << "Escaped in " << cnt << " minute(s)." << '\n';
			return;
		}

		for (int k = 0; k < 6; k++) {
			int nz = z + dz[k];
			int nx = x + dx[k];
			int ny = y + dy[k];

			if (nz < 0 || nz >= L || nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			if (MAP[nz][nx][ny] == '#' || check[nz][nx][ny] == true) continue;
			q.push(make_pair(make_pair(nx, ny), make_pair(nz, cnt + 1)));
			check[nz][nx][ny] = true;
		}
	}
	cout << "Trapped!" << '\n';
}

void show() {
	cout << "------------------------------" << '\n';
	for (int h = 0; h < L; h++) {
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cout << check[h][i][j] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	while (true) {
		cin >> L >> R >> C;
		if (L == 0 && R == 0 && C == 0) {
			break;
		}

		for (int h = 0; h < L; h++) {
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					cin >> MAP[h][i][j];
					if (MAP[h][i][j] == 'S') {	// 시작점
						start.z = h;
						start.x = i;
						start.y = j;
					}
					else if (MAP[h][i][j] == 'E') {		// 탈출점
						dest.z = h;
						dest.x = i;
						dest.y = j;
					}
				}
			}
		}
		bfs();
		//show();

		memset(MAP, NULL, sizeof(MAP));
		memset(check, false, sizeof(check));
	}

	return 0;
}
