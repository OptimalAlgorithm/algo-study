// https://www.acmicpc.net/problem/1035

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

const int INF = 987654321;
const int MAX = 5;
int ans = INF;
char MAP[MAX][MAX];
vector<pair<int, int>> v, picked, Pos;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

// 최소거리 반환 함수
int find_minDist() {
	int sum = 0;
	bool check[MAX];
	memset(check, false, sizeof(check));
	int cycle = picked.size();
	for (int i = 0; i < v.size(); i++) {
		int idx = 0;
		int min_dist = INF;
		for (int j = 0; j < picked.size(); j++) {
			if (check[j]) continue;
			int dist = abs(v[i].first - picked[j].first) + abs(v[i].second - picked[j].second);
			if (min_dist > dist) {
				min_dist = dist;
				idx = j;
			}
		}
		check[idx] = true;
		sum += min_dist;
	}
	return sum;
}

// 조합에서 뽑은 좌표중에 첫번째를 큐에 넣어 모두 인접해있는지 확인
bool is_connected() {
	bool check[MAX][MAX];
	memset(check, true, sizeof(check));
	for (int i = 0; i < picked.size(); i++) {
		check[picked[i].first][picked[i].second] = false;
	}
	queue<pair<int, int>> q;
	q.push(picked[0]);
	check[picked[0].first][picked[0].second] = true;

	int cnt = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		if (cnt == picked.size()) 
			return true;

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) continue;
			if (check[nx][ny] == false) {
				q.push({ nx,ny });
				check[nx][ny] = true;
				cnt += 1;
			}
		}
	}
	return false;
}

void dfs(int index) {
	if (picked.size() == v.size()) {
		if (is_connected()) {
			ans = min(ans, find_minDist());
		}
		return;
	}

	for (int i = index; i < Pos.size(); i++) {
		picked.push_back(Pos[i]);
		dfs(i + 1);
		picked.pop_back();
	}
}

void solve() {
	dfs(0);
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == '*') v.push_back({ i,j });
			Pos.push_back({ i,j });
		}
	}
	solve();
	return 0;
}