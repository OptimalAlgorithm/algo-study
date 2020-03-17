// https://www.acmicpc.net/problem/1516

#include<bits/stdc++.h>
using namespace std;

const int MAX = 501;
int N;
int degree[MAX];
int cost[MAX];
int result[MAX];
vector<int> graph[MAX];

void bfs() {
	queue<int> q;
	for (int i = 1; i <= N; i++) {
		if (degree[i] == 0) q.push(i);
		result[i] += cost[i];
	}

	for(int i = 1; i <= N; i++) {
		int cur = q.front();
		q.pop();

		for (int j = 0; j < graph[cur].size(); j++) {
			int next = graph[cur][j];
			result[next] = max(result[next], result[cur] + cost[next]);
			degree[next]--;
			if (degree[next] == 0) 
				q.push(next);
		}
	}
}

void solve() {
	bfs();
	for (int i = 1; i <= N; i++) {
		cout << result[i] << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> cost[i];
		int num;
		while (true) {
			cin >> num;
			if (num == -1) break;
			graph[num].push_back(i);
			degree[i]++;
		}
	}
	solve();
	return 0;
}