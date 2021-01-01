//https://www.acmicpc.net/problem/20056
//마법사 상어와 파이어볼

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int N, M, K;

int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,1,1,1,0,-1,-1,-1 };


vector<vector<vector<vector<int>>>> map;
vector<vector<vector<vector<int>>>> map2;

void simulate() {
	map2.clear();
	map2.resize(N, vector<vector<vector<int>>>(N));

	//모든 파이어볼이 자신의 방향 di로 속력 si칸 만큼 이동한다.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (auto a : map[i][j]) { //질량 속력 방향 순으로 저장되어있음
				//cout << i << " " << j << " " << a[0] << a[1] << a[2] << "를\n";
				int tr = (i + dr[a[2]] * a[1]);
				int tc = (j + dc[a[2]] * a[1]);

				if (tr < 0) {
					int tmp = (-1 * tr) % N;
					tr = -1 * tmp + N;
				}
				else tr %= N;

				if (tc < 0) {
					int tmp = (-1 * tc) % N;
					tc = -1 * tmp + N;
				}
				else tc %= N;


				//cout << tr << " " << tc << " " << a[0] << a[1] << a[2] << "로\n\n";


				map2[tr][tc].push_back({ a[0],a[1],a[2] });
			}
		}
	}

	//이동이 모두 끝난 뒤, 2개 이상의 파이어볼이 
	//있는 칸에서는 다음과 같은 일이 일어난다.

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map2[i][j].size() > 1) {
				int sumM = 0; //질량 합
				int sumS = 0; //속력 합

				int evenDirCnt = 0;

				for (auto a : map2[i][j]) {
					sumM += a[0];
					sumS += a[1];
					
					if (a[2] % 2 == 0)evenDirCnt++;
				}

				sumM /= 5;
				sumS /= map2[i][j].size();

				if (sumM != 0) {
					if (evenDirCnt == map2[i][j].size() || evenDirCnt == 0) {
						map2[i][j].clear();
						for (int c = 0; c < 4; c++) {
							map2[i][j].push_back({ sumM, sumS, 2 * c});
						}
					}
					else {
						map2[i][j].clear();
						for (int c = 0; c < 4; c++) {
							map2[i][j].push_back({ sumM, sumS, 2 * c + 1 });
						}
					}
				}
				else {
					map2[i][j].clear();
				}

			}
		}
	}

	map = map2;
}

void printAnswer() { //남아있는 질량의 합 출력
	int answer = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (auto a : map[i][j]) {
				answer += a[0];
			}
		}
	}

	cout << answer;
}


int main() {
	cin >> N >> M >> K;

	map.resize(N, vector<vector<vector<int>>>(N));
	
	int r, c, m, s, d;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> m >> s >> d;
		r--;
		c--;
		map[r][c].push_back({ m,s,d });
	}
	

	for (int i = 0; i < K; i++) {
		simulate(); 
	}

	printAnswer();
}