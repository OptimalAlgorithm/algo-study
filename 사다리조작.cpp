//https://www.acmicpc.net/problem/15684
//사다리 조작


#include <iostream>
#include <vector>

using namespace std;



int N, M, H; //N개의 세로선과 M개의 가로선


int lines[11][31]; //N번째 세로선, H번째줄, 왼쪽-1, 오른쪽1



bool simulate() {
	for (int i = 1; i <= N; i++) {
		int start = i;

		for (int h = 1; h <= H; h++) {
			if (lines[start][h] == 0)continue;
			else if (lines[start][h] == -1) start--;
			else start++;
		}

		if (i != start)return false;
	}

	return true;
}


void select(int ans, int curN, int curH, int cnt) {
	if (cnt == 0) {
		if (simulate()) {
			cout << ans;
			exit(0);
		}
	}
	else {
		for (int i = curN; i <= N; i++) { //세로선 번호
			for (int j = curH; j <= H; j++) { //높이
				if (lines[i][j] != 0) continue;

				//왼쪽으로 시도
				if (i > 1 && lines[i - 1][j] != -1) {
					lines[i][j] = -1;
					lines[i - 1][j] = 1;

					select(ans, i, j, cnt - 1);

					lines[i][j] = 0;
					lines[i - 1][j] = 0;
				}

				//오른쪽으로 시도
				if (i < N && lines[i + 1][j] != 1) {
					lines[i][j] = 1;
					lines[i + 1][j] = -1;

					select(ans, i, j, cnt - 1);

					lines[i][j] = 0;
					lines[i + 1][j] = 0;
				}
			}
		}

	}
}



int main() {
	cin >> N >> M >> H;

	int a, b;// b번 세로선과 b+1번 세로선을 a번 점선 위치에서 연결
	for (int i = 0; i < M; i++) {
		cin >> a >> b;

		lines[b][a] = 1;
		lines[b + 1][a] = -1;
	}

	for (int i = 0; i <= 3; i++) { //i개 가로선 추가 시도
		select(i, 1, 1, i);
	}


	cout << "-1";
}