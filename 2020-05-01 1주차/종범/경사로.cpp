// https://www.acmicpc.net/problem/14890

#include<bits/stdc++.h>
using namespace std;

const int MAX = 100;
int N, L, ans;
int MAP[MAX][MAX];

bool column(int c) {
	int cnt = 1;
	int r = 0;

	while (r != N - 1) {
		if (MAP[r][c] == MAP[r + 1][c]) {
			cnt++;
			r++;
			continue;
		}
		else if (MAP[r][c] == MAP[r + 1][c] - 1) {		// 다음이 1 높은경우
			if (cnt >= L) {
				r++;
				cnt = 1;
				continue;
			}
			else return false;
		}
		else if (MAP[r][c] == MAP[r + 1][c] + 1) {			// 다음이 1 낮은경우
			int h = MAP[r + 1][c];
			int tcnt = 0;
			for (int i = r + 1; i < N; i++) {
				if (MAP[i][c] == h) tcnt++;
				else break;
			}
			if (tcnt >= L) {
				cnt = 0;
				r += L;
				continue;
			}
			else return false;
		}
		else return false;
	}
	return true;
}

bool row(int r) {
	int cnt = 1;
	int c = 0;

	while (c != N - 1) {
		if (MAP[r][c] == MAP[r][c + 1]) {
			cnt++;
			c++;
			continue;
		}
		else if (MAP[r][c] == MAP[r][c + 1] - 1) {		// 다음이 1 높은경우
			if (cnt >= L) {
				c++;
				cnt = 1;
				continue;
			}
			else return false;
		}
		else if (MAP[r][c] == MAP[r][c + 1] + 1) {			// 다음이 1 낮은경우
			int h = MAP[r][c + 1];
			int tcnt = 0;
			for (int i = c + 1; i < N; i++) {
				if (MAP[r][i] == h) tcnt++;
				else break;
			}
			if (tcnt >= L) {
				cnt = 0;
				c += L;
				continue;
			}
			else return false;
		}
		else return false;
	}
	return true;
}

void solve() {
	for (int i = 0; i < N; i++) {
		if (column(i)) ans++;
		if (row(i)) ans++;
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
	solve();
	return 0;
}