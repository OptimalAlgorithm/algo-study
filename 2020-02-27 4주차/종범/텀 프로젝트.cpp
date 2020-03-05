// https://www.acmicpc.net/problem/9466
// dfs/사이클 문제

#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int MAX = 100001;
int T, N, ans, cnt;
bool check[MAX];
bool done[MAX];
vector<int> graph[MAX];

void init() {
	memset(done, false, sizeof(done));
	memset(check, false, sizeof(check));
	cnt = 0; ans = 0;
	for (int i = 1; i <= N; i++) {
		graph[i].clear();
	}
}

void dfs(int cur) {
	check[cur] = true;
	
	int next = graph[cur][0];
	if (check[next] == false) {
		dfs(next);
	}
	else {	// 이미 방문했던 곳이 다시나오면 사이클임
		if (done[next] == false) {
			for (int i = next; i != cur; i = graph[i][0]) {
				cnt++;
			}
			cnt++;
		}
	}
	done[cur] = true;	// 다시 들어갈 일 없게 해줌
}


void solution() {
	for (int i = 1; i <= N; i++) {
		if (check[i] == false) {
			dfs(i);
		}
	}

	ans = N - cnt;
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N;
		for (int i = 1; i <= N; i++) {
			int num;
			cin >> num;
			graph[i].push_back(num);
		}
		solution();
		init();
	}
	return 0;
}