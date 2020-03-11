// https://www.acmicpc.net/problem/17825
// 맵에 적혀있는 숫자는 다음칸을 담고있고, 특정지점에 왔을때만 방향전환 시켜주면됨
// 맵 셋팅이 핵심인 문제

#include<bits/stdc++.h>
using namespace std;

int MAP[33];		// 시작점 : 0, 도착점 : 32, total 33개
int score[33];		// 위치마다 적혀있는 점수
int point[33];		// 특정 지점인지
int chess[4];		// 4개의 말
int ans;
bool visited[33];
vector<int> cmd;

// 맵 초기화
void init() {
	for (int i = 0; i < 21; i++) {
		MAP[i] = i + 1;	// 한칸씩 앞 무빙
	}
	MAP[21] = 21;	// 도착지점
	MAP[22] = 23;
	MAP[23] = 24;
	MAP[24] = 30;
	MAP[25] = 26;
	MAP[26] = 30;
	for (int i = 27; i < 32; i++) {
		MAP[i] = i + 1;
	}
	MAP[32] = 20;

	for (int i = 0; i <= 20; i++) {
		score[i] = i * 2;
	}
	score[21] = 0;
	score[22] = 13;
	score[23] = 16;
	score[24] = 19;
	score[25] = 22;
	score[26] = 24;
	score[27] = 28;
	score[28] = 27;
	score[29] = 26;
	score[30] = 25;
	score[31] = 30;
	score[32] = 35;

	point[5] = 22;
	point[10] = 25;
	point[15] = 27;

	visited[0] = true;
}

void dfs(int idx, int sum) {
	if (idx == 10) {
		ans = max(ans, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (chess[i] == 21) continue;
		int now = chess[i];
		int cnt = cmd[idx];
		
		int next;
		if (point[now] != 0) {		// 특별한지점
			cnt--;
			next = point[now];		// 특별한 지점으로 미리 움직여놓는다.
		}
		else next = now;

		for (int k = 0; k < cnt; k++) {
			next = MAP[next];		// 계속 한칸씩 전진
		}

		if (!visited[next] || next == 21) {
			visited[now] = false;
			visited[next] = true;
			chess[i] = next;
			dfs(idx + 1, sum + score[next]);
			chess[i] = now;
			visited[now] = true;
			visited[next] = false;
		}
	}
}

void solve() {
	init();
	dfs(0, 0);
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	for (int i = 0; i < 10; i++) {
		int num;
		cin >> num;
		cmd.push_back(num);
	}

	solve();
	return 0;
}