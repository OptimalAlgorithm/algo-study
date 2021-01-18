//https://www.acmicpc.net/problem/15683
//감시


#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits.h>


using namespace std;



//0은 빈 칸, 6은 벽, 1~5는 CCTV의 번호, -1는 감시영역
//CCTV가 감시할 수 없는 영역은 사각지대라고 한다.



// 세로 크기 N과 가로 크기 M
int N, M;

vector<vector<int>> map;

vector<vector<int>> cctv; //몇번 cctv가 행, 열에 존재한다

int minArea = INT_MAX;//사각 지대의 최소 크기

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void countArea(vector<vector<int>> tmpMap) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmpMap[i][j] == 0)cnt++;
		}
	}

	minArea = min(minArea, cnt);


}

void setCCTV(int idx, vector<vector<int>> tmpMap) { //idx번째 인덱스의 cctv 설치
	if (idx == cctv.size()) {
		countArea(tmpMap);
	}
	else {
		switch (cctv[idx][0]) { //cctv번호
		case 1:
			for (int d = 0; d < 4; d++) {
				vector<vector<int>> tmp2 = tmpMap;

				int x = cctv[idx][1];
				int y = cctv[idx][2];
				while (true) {
					x += dx[d];
					y += dy[d];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				setCCTV(idx + 1, tmp2);
			}
			break;
		case 2:
			for (int d = 0; d < 2; d++) {
				vector<vector<int>> tmp2 = tmpMap;

				int x = cctv[idx][1];
				int y = cctv[idx][2];
				while (true) {
					x += dx[d];
					y += dy[d];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				x = cctv[idx][1];
				y = cctv[idx][2];
				while (true) {
					x += dx[d + 2];
					y += dy[d + 2];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				setCCTV(idx + 1, tmp2);
			}
			break;
		case 3:
			for (int d = 0; d < 4; d++) {
				int d2 = d + 1;
				if (d2 == 4)d2 = 0;

				vector<vector<int>> tmp2 = tmpMap;

				int x = cctv[idx][1];
				int y = cctv[idx][2];
				while (true) {
					x += dx[d];
					y += dy[d];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				x = cctv[idx][1];
				y = cctv[idx][2];
				while (true) {
					x += dx[d2];
					y += dy[d2];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				setCCTV(idx + 1, tmp2);
			}


			break;

			break;
		case 4:
			for (int d = 0; d < 4; d++) {
				int d2 = d + 1;
				if (d2 == 4)d2 = 0;

				int d3 = d + 2;
				if (d3 >= 4) d3 -= 4;

				vector<vector<int>> tmp2 = tmpMap;

				int x = cctv[idx][1];
				int y = cctv[idx][2];
				while (true) {
					x += dx[d];
					y += dy[d];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				x = cctv[idx][1];
				y = cctv[idx][2];
				while (true) {
					x += dx[d2];
					y += dy[d2];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				x = cctv[idx][1];
				y = cctv[idx][2];
				while (true) {
					x += dx[d3];
					y += dy[d3];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}

				setCCTV(idx + 1, tmp2);
			}


			break;
		case 5:
			vector<vector<int>> tmp2 = tmpMap;
			for (int d = 0; d < 4; d++) {
				int x = cctv[idx][1];
				int y = cctv[idx][2];
				while (true) {
					x += dx[d];
					y += dy[d];

					if (x < 0 || x >= N || y < 0 || y >= M)break;
					if (tmp2[x][y] == 6)break;

					tmp2[x][y] = -1;
				}
			}
			setCCTV(idx + 1, tmp2);
			break;
		}
	}
}

int main() {
	cin >> N >> M;

	map.resize(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] != 0 && map[i][j] != 6) {
				cctv.push_back({ map[i][j], i, j });
			}
		}
	}

	setCCTV(0, map);


	cout << minArea;
}