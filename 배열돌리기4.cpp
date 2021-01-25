//https://www.acmicpc.net/problem/17406
//배열 돌리기 4


#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>



using namespace std;


int N, M, K;
vector<vector<int>> arr;

vector<vector<int>> op;

vector<int> order;

vector<int> visited;

int answer = INT_MAX;

vector<vector<int>> rotate(vector<vector<int>>map, vector<int> opr) {

	vector<vector<int>>map2 = map;

	//r,c,s
	int r = opr[0];
	int c = opr[1];
	for (int s = 1; s <= opr[2]; s++) {
		//위쪽 가로
		for (int i = -1 * s + 1; i <= s; i++) {
			int x = r - s;
			int y = c + i;

			map2[x][y] = map[x][y - 1];
		}

		//오른쪽 세로
		for (int i = -1 * s + 1; i <= s; i++) {
			int x = r + i;
			int y = c + s;

			map2[x][y] = map[x-1][y];
		}

		//아래쪽 가로
		for (int i = -1 * s + 1; i <= s; i++) {
			int x = r + s;
			int y = c - i;

			map2[x][y] = map[x][y + 1];
		}

		//왼쪽 세로
		for (int i = -1 * s + 1; i <= s; i++) {
			int x = r - i;
			int y = c - s;

			map2[x][y] = map[x + 1][y];
		}
	}

	return map2;
}

int getVal(vector<vector<int>> map) {

	int rtn = INT_MAX;
	for (int i = 0; i < N; i++) {
		int tmp = 0;
		for (int j = 0; j < M; j++) {
			tmp += map[i][j];
		}
		rtn = min(rtn, tmp);
	}

	return rtn;
}

void calArr() {

	vector<vector<int>> arr2 = arr;

	for (auto a : order) {
		arr2 = rotate(arr2, op[a]);
	}

	answer = min(answer, getVal(arr2));
}

void getOrder(int cnt) {
	if (cnt == K) {
		calArr();
	}
	else {
		for (int i = 0; i < K; i++) {
			if (visited[i] == 0) {
				order.push_back(i);
				visited[i] = 1;

				getOrder(cnt + 1);

				order.pop_back();
				visited[i] = 0;
			}
		}
	}
}

int main() {
	cin >> N >> M >> K;

	arr.resize(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	int r, c, s;
	for (int i = 0; i < K; i++) {
		cin >> r >> c >> s;
		r--; c--;
		op.push_back({ r,c,s });
	}

	visited.resize(K, 0);
	getOrder(0);


	cout << answer;

}