// https://www.acmicpc.net/problem/2606

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int MAX = 101;
int N, M, ans;	// N 컴퓨터 대수
vector<int> graph[MAX];
bool check[MAX];

void bfs(int Sx) {
	queue<int> q;
	q.push(Sx);
	check[Sx] = true;
	
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < graph[now].size(); i++) {
			int next = graph[now][i];
			if (check[next]) continue;
			q.push(next);
			check[next] = true;
			ans += 1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	bfs(1);
	cout << ans << '\n';

	return 0;
}