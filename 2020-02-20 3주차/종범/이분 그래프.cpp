// https://www.acmicpc.net/problem/1707

#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

const int MAX = 20001;
int V, E, K;
bool ans = true;
vector<int> graph[MAX];
int check[MAX];

void init() {
	for (int i = 1; i <= V; i++) 
		graph[i].clear();
	memset(check, false, sizeof(check));
	ans = true;
}

void dfs(int cur, int color) {
	check[cur] = color;

	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];
		// 이분 그래프에 위배되는 조건
		if (check[next] != 0 && check[cur] == check[next] && check[cur] != 0) {
			ans = false;
			return;
		}
		if (check[next] != 0) continue;
		dfs(next, 3 - color);
	}
}

void check_graph() {
	int color = 2;
	for (int i = 1; i <= V; i++) {
		if (check[i] == 0) {
			dfs(i, color);
		}
	}
	if (ans) cout << "YES" << '\n';
	else cout << "NO" << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> K;
	while (K--) {
		cin >> V >> E;
		for (int i = 0; i < E; i++) {
			int a, b;
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		check_graph();
		init();
	}
	return 0;
}