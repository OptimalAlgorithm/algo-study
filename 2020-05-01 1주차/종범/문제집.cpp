// https://www.acmicpc.net/problem/1766

#include<bits/stdc++.h>
using namespace std;

const int MAX = 32001;
int N, M;
vector<int> graph[MAX];
int degree[MAX];

void bfs() {
	int cur = -1;
	while (true) {
		cur = -1;
		for (int i = 1; i <= N; i++) {
			if (degree[i] == 0) {
				cur = i;
				break;
			}
		}

		if (cur == -1) break;	// 풀 문제집이 없으면 break;
		cout << cur << ' ';
		degree[cur]--;

		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i];
			degree[next]--;
		}
	}
}


void solve() {
	bfs();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		degree[b]++;
	}
	solve();
	return 0;
}