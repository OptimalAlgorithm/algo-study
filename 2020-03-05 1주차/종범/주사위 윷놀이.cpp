// https://www.acmicpc.net/problem/17825
// �ʿ� �����ִ� ���ڴ� ����ĭ�� ����ְ�, Ư�������� �������� ������ȯ �����ָ��
// �� ������ �ٽ��� ����

#include<bits/stdc++.h>
using namespace std;

int MAP[33];		// ������ : 0, ������ : 32, total 33��
int score[33];		// ��ġ���� �����ִ� ����
int point[33];		// Ư�� ��������
int chess[4];		// 4���� ��
int ans;
bool visited[33];
vector<int> cmd;

// �� �ʱ�ȭ
void init() {
	for (int i = 0; i < 21; i++) {
		MAP[i] = i + 1;	// ��ĭ�� �� ����
	}
	MAP[21] = 21;	// ��������
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
		if (point[now] != 0) {		// Ư��������
			cnt--;
			next = point[now];		// Ư���� �������� �̸� ���������´�.
		}
		else next = now;

		for (int k = 0; k < cnt; k++) {
			next = MAP[next];		// ��� ��ĭ�� ����
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