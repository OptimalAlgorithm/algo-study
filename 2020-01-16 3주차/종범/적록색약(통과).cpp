// https://www.acmicpc.net/problem/10026
// 흔한 대륙카운트 문제

#include<iostream>
#include<cstring>

using namespace std;

const int MAX = 100;
int N;
char MAP[MAX][MAX];
char CMAP[MAX][MAX];
bool check[MAX][MAX];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

// 적록색약이 아닌사람
void brute(int x, int y, int cnt, char color) {
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];

		if (nx < 0 || nx >= N || ny < 0 || ny >= N || check[nx][ny]) continue;
		if (MAP[nx][ny] != color) continue;
		check[nx][ny] = true;
		brute(nx, ny, cnt, color);
	}
}

// 적록색약 인사람
void dfs(int x, int y, int cnt, char color) {
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];

		if (nx < 0 || nx >= N || ny < 0 || ny >= N || check[nx][ny]) continue;
		if (CMAP[nx][ny] != color) continue;
		check[nx][ny] = true;
		dfs(nx, ny, cnt, color);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			CMAP[i][j] = MAP[i][j];
			if (CMAP[i][j] == 'G')	// 적록색약인 사람은 G랑 R을 같은색으로 본다
				CMAP[i][j] = 'R';
		}
	}

	// 적록색약 X
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j]) continue;
			brute(i, j, ++cnt, MAP[i][j]);
		}
	}
	cout << cnt << ' ';
	memset(check, false, sizeof(check));

	// 적록색약 O
	cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j]) continue;
			dfs(i, j, ++cnt, CMAP[i][j]);
		}
	}
	cout << cnt << '\n';

	return 0;
}