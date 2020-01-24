//[백준 2174] 로봇 시뮬레이션

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int A, B; //A = 가로, B = 세로
int N, M; //N = 로봇 수, M = 명령 수


vector<vector<int>> map; //가로 > 세로 순으로 로봇 위치 저장

vector<vector<int>> dir = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } }; //상, 우, 하, 좌

vector<tuple<int, int, int>> robotsInfo = { make_tuple(0,0,0) }; //로봇 좌표, 방향 저장

void robotInput(int N); //로봇 데이터 입력
void work(int M); //명령 수행
void rotateLeft(int n, int rp); //왼쪽 90도 회전
void rotateRight(int n, int rp); //오른쪽 90도 회전
void forward(int n, int rp); //앞으로 전진

//초기 로봇 상태 입력
void robotInput(int N) {
	for (int num{ 1 }; num <= N; num++) {
		int a, b; //가로, 세로
		char c; //방향
		cin >> a >> b >> c;

		int direction;
		if (c == 'N') direction = 0;
		else if (c == 'E') direction = 1;
		else if (c == 'S') direction = 2;
		else direction = 3;

		map[a-1][b-1] = num;
		robotsInfo.push_back(make_tuple(a - 1, b - 1, direction));
	}	

	return;
}

//명령 수행
void work(int M) { 
	for (int m{ 0 }; m < M; m++) {

		int robotNum;
		char command;
		int repeat;

		cin >> robotNum >> command >> repeat;

		//왼쪽 회전
		if (command == 'L') {
			rotateLeft(robotNum, repeat);
		}
		//오른쪽 회전
		else if (command == 'R'){ 
			rotateRight(robotNum, repeat);
		}
		//앞으로 전진
		else {
			forward(robotNum, repeat);
		}

	}
	return;
}

void rotateLeft(int n, int rp) {
	get<2>(robotsInfo[n]) -= (rp % 4);
	if (get<2>(robotsInfo[n]) < 0) get<2>(robotsInfo[n]) += 4;
	return;
}

void rotateRight(int n, int rp) {
	get<2>(robotsInfo[n]) += (rp % 4);
	if (get<2>(robotsInfo[n]) > 3) get<2>(robotsInfo[n]) -= 4;
	return;
}

void forward(int n, int rp) {
	for (int r{ 0 }; r < rp; r++) {
		int x = get<0>(robotsInfo[n]) + dir[get<2>(robotsInfo[n])][0];
		int y = get<1>(robotsInfo[n]) + dir[get<2>(robotsInfo[n])][1];

		//영역 바깥으로 나가는 경우
		if (x < 0 || x >= A || y < 0 || y >= B) {
			cout << "Robot " << n << " crashes into the wall";
			exit(0);
			return;
		}

		//다른 로봇과 충돌하는 경우
		if (map[x][y] != 0) {
			cout << "Robot " << n << " crashes into robot " << map[x][y];
			exit(0);
			return;
		}

		//문제없이 이동 가능한 경우
		map[get<0>(robotsInfo[n])][get<1>(robotsInfo[n])] = 0;

		get<0>(robotsInfo[n]) = x;
		get<1>(robotsInfo[n]) = y;
		map[x][y] = n;
	}
	return;
}

int main() {
	cin >> A >> B;
	cin >> N >> M;

	vector<int> line(B, 0);
	for (int i{ 0 }; i < A; i++) {
		map.push_back(line);
	}

	robotInput(N);
	work(M);

	
	cout << "OK";

	//system("pause");
	return 0;
}