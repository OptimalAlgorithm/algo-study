//[백준 1325] 효율적인 해킹
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> trust;
vector<int> hack;
int t;
int sum{ 0 };

vector<int> visited;

void dfs(int i) {

	if (visited[i] == 0) {
		visited[i] = 1;
		t++;
		for (auto a : trust[i]) dfs(a);
	}
	return;
}

int main() {
	cin >> N >> M;
	trust.resize(N);
	hack = vector<int>(N, 0);
	
	for (int i{ 0 }; i < M; i++) {
		int A, B;
		cin >> A >> B;

		trust[B-1].push_back(A-1);
	}

	for (int i{ 0 }; i < N; i++) {
		visited = vector<int>(N, 0);
		t = 0;
		visited[i] = 1;
		for (auto a : trust[i]) {
			dfs(a);
		}

		hack[i] = t;
		if (sum < t) sum = t;
	}

	for (int i{ 0 }; i < N; i++) {
		if (hack[i] == sum) cout << i+1 << " ";
	}

	system("pause");
	return 0;
}