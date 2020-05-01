// https://www.acmicpc.net/problem/1563

#include<bits/stdc++.h>
using namespace std;

const int MAX = 1000;
int N, ans;
int cache[MAX][MAX][2][3];

// 일수, 출석, 지각, 결석
int dfs(int cnt, int go, int late, int no) {
	if (late == 2 || no == 3) return 0;
	if (cnt == N) return 1;

	int &result = cache[cnt][go][late][no];
	if (result != -1)
		return result;

	// 출석한 경우
	result = dfs(cnt + 1, go, late, 0);
	// 지각한 경우 
	result += dfs(cnt + 1, go, late + 1, 0);
	// 결석한 경우
	result += dfs(cnt + 1, go, late, no + 1);
	return result % 1000000;
}

void solve() {
	memset(cache, -1, sizeof(cache));
	ans = dfs(0, 0, 0, 0);
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	cin >> N;
	solve();
	return 0;
}