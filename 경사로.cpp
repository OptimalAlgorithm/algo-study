//https://www.acmicpc.net/problem/14890
//경사로


//실수한점: cur값 갱신을 깜빡함
//높이차가 1만 가능하다는 조건을 깜빡함

#include <iostream>
#include <vector>


using namespace std;


int N, L;

vector<vector<int>> map; //행, 열
vector<vector<int>> rmap; //열, 행

int cnt = 0;

void countRoad(vector<vector<int>> tmp) {
	vector<vector<int>> slide = tmp; //경사로:-1
	for (int i = 0; i < N; i++) {
		bool flag = true;

		int idx = 1;
		int cur = tmp[i][0]; //직전높이
		while (true) {
			if (idx >= N)break;

			if (tmp[i][idx] == cur) { //동일높이면 그대로 진행
				idx++;
				continue;
			}
			else if (tmp[i][idx] > cur) { //오르막길이면

				if (tmp[i][idx] - cur > 1 || idx < L) { //높이차, 경사로 길이 체크
					flag = false;
					break;
				}

				bool flag2 = true;
				for (int len = 1; len <= L; len++) { //경사로 중복 체크
					if (slide[i][idx - len] == -1) {
						flag2 = false;
						flag = false;
						break;
					}
				}
				if (!flag2)break;

				for (int len = 1; len <= L; len++) {
					slide[i][idx - len] = -1; //경사로 설치
				}


				cur = tmp[i][idx];
				idx++;
			}
			else { //내리막길이면
				if (cur - tmp[i][idx] > 1 || idx > N - L) { //높이차, 경사로 길이 체크
					flag = false;
					break;
				}

				int cmp = tmp[i][idx];
				bool flag2 = true;

				for (int len = 0; len < L; len++) { //경사로 높이 체크
					if (tmp[i][idx + len] != cmp) {
						flag2 = false;
						flag = false;
						break;
					}
				}

				if (!flag2)break;

				for (int len = 0; len < L; len++) {
					slide[i][idx + len] = -1; //경사로 설치
				}


				cur = tmp[i][idx];
				idx += L;
			}
		}

		if (flag) {

			cnt++;
		}
	}

}

int main() {
	cin >> N >> L;

	map.resize(N, vector<int>(N));
	rmap.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			rmap[j][i] = map[i][j];
		}
	}

	countRoad(map);
	countRoad(rmap);

	cout << cnt;

}