// https://www.acmicpc.net/problem/2026

#include<bits/stdc++.h>
using namespace std;

const int MAX = 901;
int K, N, F;
bool graph[MAX][MAX];
bool visited[MAX];
int friendCnt[MAX];
vector<int> picked;

// ���� ���� person�� �̹� ���� �ֵ�� ģ������ Ȯ��
bool check(int person) {
	for (int i = 0; i < picked.size(); i++) {
		if (visited[picked[i]]) {
			if (!graph[person][picked[i]])
				return false;
		}
	}
	return true;
}

void dfs(int idx) {
	if (picked.size() == K) {
		for (int i = 0; i < picked.size(); i++) {
			cout << picked[i] << '\n';
		}
		exit(0);
	}
	
	for (int i = idx+1; i <= N; i++) {
		if (!graph[idx][i]) continue;
		if (!check(i)) continue;
		visited[i] = true;
		picked.push_back(i);
		dfs(i);
		visited[i] = false;
		picked.pop_back();
	}
}

void solve() {
	for (int i = 1; i <= N; i++) {
		if (friendCnt[i] < K - 1) continue;	// ģ���� K-1�� ���� ����� ��ǳ�� �� �ڰ��� ����

		visited[i] = true;
		picked.push_back(i);
		dfs(i);
		visited[i] = false;
		picked.pop_back();
	}

	cout << -1 << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> K >> N >> F;
	for (int i = 0; i < F; i++) {
		int a, b;
		cin >> a >> b;
		graph[a][b] = true;
		graph[b][a] = true;
		friendCnt[a]++;
		friendCnt[b]++;
	}
	solve();
	return 0;
}