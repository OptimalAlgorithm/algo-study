//[백준 1613] 역사

#include <iostream>

using namespace std;

int N, K;
int graph[401][401];
int a, b;

int main() {
	ios_base::sync_with_stdio(0);

	cin >> N >> K;

	for (int i{ 0 }; i < K; i++) {
		cin >> a >> b;

		graph[a][b] = -1;
		graph[b][a] = 1;
	}

	for (int k{ 1 }; k <= N; k++) {
		for (int i{ 1 }; i <= N; i++) {
			for (int j{ 1 }; j <= N; j++) {
				if (graph[i][k] == -1 && graph[k][j] == -1) {
					graph[i][j] = -1;
					graph[j][i] = 1;
				}
			}
		}
	}

	int s;
	cin >> s;
	for (int i{ 0 }; i < s; i++) {
		cin >> a >> b;
		cout << graph[a][b] << "\n";
	}

	//system("pause");
	return 0;
}