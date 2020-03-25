// https://www.acmicpc.net/problem/7682
// ³ë°¡´Ù..

#include<bits/stdc++.h>
using namespace std;

const int MAX = 3;
int space;
string str;
bool flagX, flagO;
char MAP[MAX][MAX];
bool visited[MAX][MAX];

int dx[] = { 0,1,1,1,0,-1,-1,-1 };
int dy[] = { 1,1,0,-1,-1,-1,0,1 };

void init() {
	memset(visited, false, sizeof(visited));
	flagX = false, flagO = false;
	space = 0;
}

void dfs(int cnt, int x, int y, int dir, char c) {
	if (cnt == 3) {
		if (c == 'X') flagX = true;
		else flagO = true;
		return;
	}
	if (x < 0 || x >= MAX || y < 0 || y >= MAX) return;
	if (MAP[x][y] == c) cnt++;
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	dfs(cnt, nx, ny, dir, c);
	return;
}

void solve() {
	int xcnt = 0, ocnt = 0;
	if (space == 0) {	// °¡µæ Ã¡À» ¶§
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				if (MAP[i][j] == 'X') {
					for (int k = 0; k < 8; k++) {
						int nx = i + dx[k];
						int ny = j + dy[k];
						dfs(1, nx, ny, k, MAP[i][j]);
					}
					xcnt++;
				}
				else if (MAP[i][j] == 'O') {
					for (int k = 0; k < 8; k++) {
						int nx = i + dx[k];
						int ny = j + dy[k];
						dfs(1, nx, ny, k, MAP[i][j]);
					}
					ocnt++;
				}
			}
		}
		//cout << flagX << ' ' << flagO << '\n';
		if (flagO) {
			cout << "invalid" << '\n'; 
			return;
		}
		else if (flagX) {
			if (ocnt + 1 == xcnt) {
				cout << "valid" << '\n';
				return;
			}
			else {
				cout << "invalid" << '\n';
				return;
			}
		}
		else {
			if (ocnt + 1 == xcnt) {
				cout << "valid" << '\n';
				return;
			}
			else {
				cout << "invalid" << '\n';
				return;
			}
		}
	}
	else {				// ºó°ø°£ÀÌ ÀÖÀ» ¶§
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				if (MAP[i][j] == 'X') {
					for (int k = 0; k < 8; k++) {
						int nx = i + dx[k];
						int ny = j + dy[k];
						dfs(1, nx, ny, k, MAP[i][j]);
					}
					xcnt++;
				}
				else if (MAP[i][j] == 'O') {
					for (int k = 0; k < 8; k++) {
						int nx = i + dx[k];
						int ny = j + dy[k];
						dfs(1, nx, ny, k, MAP[i][j]);
					}
					ocnt++;
				}
			}
		}
		//cout << flagX << ' ' << flagO << '\n';
		if (flagX && flagO) {
			cout << "invalid" << '\n';
			return;
		}
		else if (flagX) {
			if (ocnt + 1 == xcnt) {
				cout << "valid" << '\n';
				return;
			}
			else {
				cout << "invalid" << '\n';
				return;
			}
		}
		else if (flagO) {
			if (ocnt == xcnt) {
				cout << "valid" << '\n';
				return;
			}
			else {
				cout << "invalid" << '\n';
				return;
			}
		}
		else {
			cout << "invalid" << '\n';
			return;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	while (true) {
		cin >> str;
		if (str == "end") break;

		int idx = 0;
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				MAP[i][j] = str[idx++];
				if (MAP[i][j] == '.') space++;
			}
		}

		solve();
		init();
	}
	return 0;
}