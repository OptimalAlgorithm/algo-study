// https://www.acmicpc.net/problem/1613
// 플로이드 미적용, 비효율적인 코드

#include<bits/stdc++.h>
using namespace std;

const int MAX = 401;
int n, k, s;
bool visited[MAX];
vector<int> graph[MAX];

bool bfs(int start, int dest) {
	queue<int> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		if (cur == dest) {
			memset(visited, false, sizeof(visited));
			return true;
		}

		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i];
			if (visited[next])continue;
			q.push(next);
			visited[next] = true;
		}
	}
	memset(visited, false, sizeof(visited));
	return false;
}

void solve(int a, int b) {
	if (a > n || b > n) {
		cout << 0 << '\n';
		return;
	}
	else if(a <b) {
		if (bfs(a, b)) {
			cout << -1 << '\n';
			return;
		}
		else if (bfs(b, a)) {
			cout << 1 << '\n';
			return;
		}
	}
	else if (a > b) {
		if (bfs(b, a)) {
			cout << 1 << '\n';
			return;
		}
		else if (bfs(a, b)) {
			cout << -1 << '\n';
			return;
		}
	}

	cout << 0 << '\n';
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}
	cin >> s;
	for (int i = 0; i < s; i++) {
		int a, b;
		cin >> a >> b;
		solve(a, b);
	}
	return 0;
}