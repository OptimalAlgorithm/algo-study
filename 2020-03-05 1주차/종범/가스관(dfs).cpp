// https://www.acmicpc.net/problem/2931

#include<bits/stdc++.h>
using namespace std;

const int MAX = 30;
int R, C, sx, sy, tx, ty, X, Y;	// ����, ����, ����, ����
char MAP[MAX][MAX];
bool visited[MAX][MAX];
bool flag;
char ans;
int total_pipe;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

// �������� �´� ���� ��ȯ�Լ�
int get(char c, int dir) {
	if (c == '1') {
		switch (dir) {
		case 0:
			return -1;
		case 1:
			return 2;
		case 2:
			return -1;
		case 3:
			return 0;
		}
	}
	else if (c == '2') {
		switch (dir) {
		case 0:
			return -1;
		case 1:
			return 3;
		case 2:
			return 0;
		case 3:
			return -1;
		}
	}
	else if (c == '3') {
		switch (dir) {
		case 0:
			return 3;
		case 1:
			return -1;
		case 2:
			return 1;
		case 3:
			return -1;
		}
	}
	else if (c == '4') {
		switch (dir) {
		case 0:
			return 2;
		case 1:
			return -1;
		case 2:
			return -1;
		case 3:
			return 1;
		}
	}
	else if (c == '5') {
		switch (dir) {
		case 0:
			return -1;
		case 1:
			return -1;
		case 2:
			return 2;
		case 3:
			return 3;
		}
	}
	else if (c == '6') {
		switch (dir) {
		case 0:
			return 0;
		case 1:
			return 1;
		case 2:
			return -1;
		case 3:
			return -1;
		}
	}
	else if (c == '7') {
		return dir;
	}
}

// ��� �������� �湮�ߴ��� Ȯ��
bool check() {
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			if (MAP[i][j] != '.' && !visited[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void dfs(int x, int y, int dir, int cnt) {
	if (flag) return;
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if (nx == tx && ny == ty) {	// Z�� ����
		if (!check()) return;	// ��� �������� ���ƴ��� Ȯ��
		if (x == X && y == Y) {	// ��ģ�κ��� Z�� �����ϸ� ���� �ƴ�, ������ �����ݾ� ��...
			return;
		}
		flag = true;
		return;
	}

	if (nx < 1 || nx > R || ny < 1 || ny > C) return;
	if (MAP[nx][ny] == '.') {
		if (cnt == 0) {		// ��ŷ���� ���� ã�Ҵ�
			for (int i = 0; i < 7; i++) {
				if (flag) return;				// ���� �������� ����
				char next = char('1' + i);
				MAP[nx][ny] = next;
				int next_dir;
				X = nx, Y = ny, ans = next;		// ���亯�� ����
				next_dir = get(MAP[nx][ny], dir);
				if (next_dir == -1) continue;
				visited[nx][ny] = true;
				dfs(nx, ny, next_dir, cnt + 1);
				visited[nx][ny] = false;
				MAP[nx][ny] = '.';
			}

		}
		else return;
	}
	else if (nx == sx && ny == sy) return;	// �ٽ� ���������� ���ƿ� ���� ����
	else {
		dir = get(MAP[nx][ny], dir);
		if (dir == -1) return;
		visited[nx][ny] = true;
		dfs(nx, ny, dir, cnt);
		visited[nx][ny] = false;
	}
}

void solve() {
	visited[sx][sy] = visited[tx][ty] = 1;
	for (int i = 0; i < 4; ++i) {
		int nx = sx + dx[i];
		int ny = sy + dy[i];
		if (ny < 1 || nx > R || ny < 1 || ny > C)continue;
		if (MAP[nx][ny] != '.')		// M �������� ������ �������� ����
			dfs(sx, sy, i, 0);
	}

	if (ans == '5') ans = '|';
	else if (ans == '6') ans = '-';
	else if (ans == '7') ans = '+';
	cout << X << ' ' << Y << ' ' << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> R >> C;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'M') {
				sx = i;
				sy = j;
			}
			else if (MAP[i][j] == 'Z') {
				tx = i;
				ty = j;
			}
			else if (MAP[i][j] == '|') {
				MAP[i][j] = '5';
				total_pipe++;
			}
			else if (MAP[i][j] == '-') {
				total_pipe++;
				MAP[i][j] = '6';
			}
			else if (MAP[i][j] == '+') {
				total_pipe++;
				MAP[i][j] = '7';
			}
			else if (MAP[i][j] != '.') {
				total_pipe++;
			}
		}
	}

	solve();
	return 0;
}