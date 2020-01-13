// https://www.acmicpc.net/problem/3678

#include<iostream>
#include<cstring> 

using namespace std;

const int MAX = 10001;
int T, N;
int MAP[1001][1001];
int COUNT[6];
int ans[MAX];
bool visited[6];

int dx[6] = { -1, -2, -1, 1, 2, 1 };
int dy[6] = { 1, 0, -1, -1, 0, 1 };

void check(int x, int y) {
	memset(visited, false, sizeof(visited));

	for (int k = 0; k < 6; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (MAP[nx][ny] != 0) {
			visited[MAP[nx][ny]] = true;
		}
	}
}

int getNum() {
	int ret = 0;
	int min = 20000;
	for (int i = 1; i <= 5; i++) {
		if (!visited[i]) {
			if (min > COUNT[i]) {
				min = COUNT[i];
				ret = i;
			}
		}
	}
	return ret;
}

void simulate() {
	int x = 500;
	int y = 500;

	MAP[x][y] = 1;
	COUNT[1]++;
	ans[1] = 1;
	int idx = 1;
	int k = 1;
	while (idx <= 10000) {
		for (int d = 0; d < 6; d++) {
			int len = d == 1 ? k - 1 : k;
			for (int u = 0; u < len; u++) {
				x += dx[d];
				y += dy[d];
				check(x, y);
				int num = getNum();
				MAP[x][y] = num;
				ans[++idx] = num;
				COUNT[num]++;
			}
		}
		k++;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		simulate();
		cout << ans[N] << '\n';

		memset(MAP, 0, sizeof(MAP));
		memset(COUNT, 0, sizeof(COUNT));
		memset(ans, 0, sizeof(ans));
	}

	return 0;
}
