//https://www.acmicpc.net/problem/20055
//컨베이어 벨트 위의 로봇 

#include <iostream>
#include <vector>

using namespace std;

int N, K;

int cnt = 1;

int belt[201]; //내구도
int robots[201];

int start = 1;


bool simulate() {

	//1. 벨트가 한 칸 회전한다.
	start--;
	if (start < 1) start = 2 * N;
	//내려가는 위치 로봇 내리기
	int down = start + N - 1;
	if (down > 2 * N) down -= 2 * N;
	if (robots[down] == 1)robots[down] = 0;


	//2. 로봇 움직이기
	for (int i = 1; i < N; i++) {

		int idx = down - i;
		if (idx < 1) idx += 2 * N;
		else if (idx > 2 * N) idx -= 2 * N;

		int nxt = idx + 1;
		if (nxt > 2 * N) nxt -= 2 * N;
		else if (nxt < 1) nxt += 2 * N;

		//cout << "\nidx, nxt: " << idx << " " << nxt << " " << start << " " << down;

		if (robots[idx] == 1 && robots[nxt] == 0 && belt[nxt] > 0) {
			belt[nxt]--;
			robots[idx] = 0;
			robots[nxt] = 1;

			if (belt[nxt] == 0)K--;

			if (nxt == down)robots[nxt] = 0;
		}
	}



	//3. 올라가는 위치에 로봇 올리기
	if (robots[start] == 0 && belt[start] > 0) {
		belt[start]--;
		robots[start] = 1;

		if (belt[start] == 0)K--;
	}



	//4. 종료 결정
	if (K > 0) {
		cnt++;
		return true;
	}
	else return false;
}


int main() {
	cin >> N >> K;

	for (int i = 1; i <= 2 * N; i++) {
		cin >> belt[i];
	}

	while (true) {
		if (!simulate())break;
	}


	cout << cnt;
}