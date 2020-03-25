// https://www.acmicpc.net/problem/14888

#include<bits/stdc++.h>
using namespace std;

int N, MAX = -1000000000, MIN = 1000000000;
int operation[4];	// 0 : + , 1 : - , 2 : * , 3 : /
vector<int> v;

void dfs(int sum, int index) {
	if (index == N) {
		MAX = max(MAX, sum);
		MIN = min(MIN, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int temp = sum;
		if (operation[i] <= 0) continue;
		switch (i) {
		case 0:
			temp = sum + v[index];
			break;
		case 1:
			temp = sum - v[index];
			break;
		case 2:
			temp = sum * v[index];
			break;
		case 3:
			temp = sum / v[index];
			break;
		}
		operation[i]--;
		dfs(temp, index + 1);
		operation[i]++;
	}
}

void solve() {
	dfs(v[0], 1);
	cout << MAX << '\n' << MIN << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}
	for (int i = 0; i < 4; i++) {
		cin >> operation[i];
	}
	solve();
	return 0;
}
