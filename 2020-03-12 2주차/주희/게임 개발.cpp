//[���� 1516] ���� ����

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

int N;
vector<vector<int>> pre; //��庰�� ���� ����� �ϴ� �ǹ�
vector<int> cost, result; //�� ��� �� �ɸ��� �ð�, �� �ɸ��� �ð�
vector<int> degree; //���� ����� �ϴ� �ǹ� ��

void input() {
	pre.resize(N);
	cost.resize(N);
	degree.resize(N);

	//pre, degree �Է�
	for (int i{ 0 }; i < N; i++) {
		cin >> cost[i];

		int tmp;
		while (true) {
			cin >> tmp;

			if (tmp == -1) break;
			else {
				degree[i]++;
				pre[tmp-1].push_back(i); //tmp-1�� i���� ���� ����� ��
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
			result[pre[node][i]] = max(cost[pre[node][i]] + result[node], result[pre[node][i]]); //���� ������ ����ؾ���
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