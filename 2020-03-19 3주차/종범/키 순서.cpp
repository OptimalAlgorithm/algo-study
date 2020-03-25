// https://www.acmicpc.net/problem/2458

#include<bits/stdc++.h>
using namespace std;

const int MAX = 501;
int N, M,cnt, ans;
bool visited[2][MAX];
vector<int> graph[2][MAX];		// 0:������ ū�ֵ�, 1:������ �����ֵ�

void dfs(int dir, int cur) {
	visited[dir][cur] = true;

	for (int i = 0; i < graph[dir][cur].size(); i++) {
		int next = graph[dir][cur][i];
		if (visited[dir][next])continue;
		dfs(dir, next);
		cnt++;
	}
}

void solve() {
	for (int i = 1; i <= N; i++) {
		memset(visited, 0, sizeof(visited));
		cnt = 0;
		int small_cnt = 0, tall_cnt = 0;
		dfs(0, i);
		tall_cnt = cnt;
		cnt = 0;
		dfs(1, i);
		small_cnt = cnt;

		if (tall_cnt + small_cnt + 1 == N) ans++;
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	while (M--) {
		int a, b;
		cin >> a >> b;
		graph[0][a].push_back(b);		// a���� b�� ŭ
		graph[1][b].push_back(a);		// b���� a�� ����
	}
	solve();
	return 0;
}