// https://www.acmicpc.net/problem/11048

#include<bits/stdc++.h>
using namespace std;

const int MAX = 1002;
int N, M, ans;
int MAP[MAX][MAX];
int cache[MAX][MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cache[i][j] = max(cache[i - 1][j] + MAP[i][j], max(cache[i - 1][j - 1] + MAP[i][j], cache[i][j - 1] + MAP[i][j]));
		}
	}

	cout << cache[N][M];
	return 0;
}