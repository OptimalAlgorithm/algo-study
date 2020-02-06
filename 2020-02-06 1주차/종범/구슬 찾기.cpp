// https://www.acmicpc.net/problem/2617

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

const int MAX = 100;
int N, M, ans;
bool check[MAX];
bool result[MAX];				// 중간에서 제외되는 구슬은 true
vector<int> graph1[MAX];		// 보다 큰 구슬
vector<int> graph2[MAX];		// 보다 작은 구슬

int dfs1(int now) {

	int cnt = 1;
	for (int i = 0; i < graph1[now].size(); i++) {
		int next = graph1[now][i];
		if (check[next]) continue;
		check[next] = true;
		cnt += dfs1(next);
	}
	return cnt;
}

int dfs2(int now) {

	int cnt = 1;
	for (int i = 0; i < graph2[now].size(); i++) {
		int next = graph2[now][i];
		if (check[next]) continue;
		check[next] = true;
		cnt += dfs2(next);
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
		graph1[b].push_back(a);	// b보다 무게가 큰 구슬은 a이다
		graph2[a].push_back(b);	// a보다 무게가 작은 구슬은 b이다
	}

	// i번 구슬보다 무게가 큰 구슬이 몇개이며 그 구슬이 중간위치보다 큰지 확인
	for (int i = 1; i <= N; i++) {
		check[i] = true;
		int ret = dfs1(i);
		if (ret > (N + 1) / 2)
			result[i] = true;
		memset(check, false, sizeof(check));
	}

	// i번 구슬보다 무게가 작은 구슬이 몇개이며 그 구슬이 중간위치보다 작은지 확인
	for (int i = 1; i <= N; i++) {
		check[i] = true;
		int ret = dfs2(i);
		if (ret > (N + 1) / 2)	
			result[i] = true;
		memset(check, false, sizeof(check));
	}

	for (int i = 1; i <= N; i++) {
		if (result[i]) ans++;
	}
	cout << ans << '\n';
	return 0;
}