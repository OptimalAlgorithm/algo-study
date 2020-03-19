//[백준 1516] 게임 개발

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

int N;
vector<vector<int>> pre; //노드별로 먼저 지어야 하는 건물
vector<int> cost, result; //한 노드 당 걸리는 시간, 총 걸리는 시간
vector<int> degree; //먼저 지어야 하는 건물 수

void input() {
	pre.resize(N);
	cost.resize(N);
	degree.resize(N);

	//pre, degree 입력
	for (int i{ 0 }; i < N; i++) {
		cin >> cost[i];

		int tmp;
		while (true) {
			cin >> tmp;

			if (tmp == -1) break;
			else {
				degree[i]++;
				pre[tmp-1].push_back(i); //tmp-1를 i보다 먼저 지어야 함
			}
		}
	}

	result = cost;
}

void cal() {
	queue<int> q;
	for (int i{ 0 }; i < N; i++) {
		if (degree[i] == 0) q.push(i);
	}

	while (q.size() > 0) {
		int node = q.front();
		q.pop();

		for (int i{ 0 }; i < pre[node].size(); i++) {
			if (--degree[pre[node][i]] == 0) q.push(pre[node][i]);
			result[pre[node][i]] = max(cost[pre[node][i]] + result[node], result[pre[node][i]]); //동시 진행을 고려해야함
		}
	}
}

int main() {
	cin >> N;

	input();

	cal();

	for (auto a : result) cout << a << "\n";

	system("pause");
	return 0;
}