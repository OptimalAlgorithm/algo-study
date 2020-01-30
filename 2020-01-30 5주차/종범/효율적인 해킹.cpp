// https://www.acmicpc.net/problem/1325

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

const int MAX = 10000;
int N, M, ans;
bool check[MAX+1];
vector<int> graph[MAX+1];
vector<int> v;

int bfs(int Sx) {
	queue<int> q;
	q.push(Sx);
	check[Sx] = true;

	int cnt = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < graph[now].size(); i++) {
			int next = graph[now][i];
			if (check[next]) continue;
			q.push(next);
			check[next] = true;
			cnt++;
		}
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		graph[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) {
		int ret = bfs(i);
		ans = max(ret, ans);
		v.push_back(ret);
		memset(check, false, sizeof(check));
	}

	for (int i = 0; i < v.size(); i++) {
		if (ans == v[i])
			cout << i + 1 << ' ';
	}
	cout << '\n';
	return 0;
}