// https://www.acmicpc.net/problem/10775
// 비행기마다 1~num까지 도킹할 수 있는데, 순서대로 num부터 도킹시켜 아래로 감소시켜나가기

#include<bits/stdc++.h>
using namespace std;

const int MAX = 100001;
int G, P, ans;
int parent[MAX];

int getParent(int x) {
	if (parent[x] == x) return x;
	return parent[x] = getParent(parent[x]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> G >> P;
	for (int i = 1; i <= G; i++) {
		parent[i] = i;
	}

	for (int i = 1; i <= P; i++) {
		int num;
		cin >> num;
		int gate = getParent(num);

		if (gate == 0) break;	// 1~num 중 도킹할 곳이 없어 gate 값이 0일때

		parent[gate] = getParent(gate - 1);
		ans++;
	}

	cout << ans << '\n';
	return 0;
}