// https://www.acmicpc.net/problem/2617

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

const int MAX = 100;
int N, M, ans;
bool check[MAX];
bool result[MAX];				// �߰����� ���ܵǴ� ������ true
vector<int> graph1[MAX];		// ���� ū ����
vector<int> graph2[MAX];		// ���� ���� ����

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
		graph1[b].push_back(a);	// b���� ���԰� ū ������ a�̴�
		graph2[a].push_back(b);	// a���� ���԰� ���� ������ b�̴�
	}

	// i�� �������� ���԰� ū ������ ��̸� �� ������ �߰���ġ���� ū�� Ȯ��
	for (int i = 1; i <= N; i++) {
		check[i] = true;
		int ret = dfs1(i);
		if (ret > (N + 1) / 2)
			result[i] = true;
		memset(check, false, sizeof(check));
	}

	// i�� �������� ���԰� ���� ������ ��̸� �� ������ �߰���ġ���� ������ Ȯ��
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