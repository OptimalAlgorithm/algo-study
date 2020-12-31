//https://www.acmicpc.net/problem/20057
//마법사 상어와 토네이도

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


int N;

vector<vector<int>> map;

int out = 0;

int curR, curC; //현재 행, 열
int curDir=0; //현재 이동 방향

int dr[4] = {0,1,0,-1}; //좌 하 우 상
int dc[4] = {-1,0,1,0};

//좌로 이동하는경우: 상하좌우
//하로 이동하는경우: 좌우하상
//우로 이동하는경우: 하상우좌
//상으로 이동하는경우: 우좌상하

void simulate(int len) { //길이 len만큼 curDir방향으로 한 변 이동

	//좌 하 우 상
	int left = 0; int bottom = 1; int right = 2; int top = 3;

	//방향 환산
	switch (curDir) {
	case 0: //좌로 이동
		//방향 그대로
		break;
	case 1: //하로 이동
		top = 0; bottom = 2; left = 1; right = 3;
		break;
	case 2: //우로 이동
		top = 1; bottom = 3; left = 2; right = 0;
		break;
	case 3: //상으로 이동
		top = 2; bottom = 0; left = 3; right = 1;
		break;
	}
	
	for (int i = 0; i < len; i++) {
		
		//y좌표
		int yr = curR + dr[curDir];
		int yc = curC + dc[curDir];
		curR = yr; curC = yc;

		int sum = 0; //y에서 줄어든 양
		

		//환산된 방향으로 뿌리기
		int tmp, tr, tc;

		tmp = (map[yr][yc] * 2) / 100;
		tr = yr + dr[top] + dr[top];
		tc = yc + dc[top] + dc[top];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;			
		}
		else out += tmp;
		sum += tmp;

		tmp = (map[yr][yc] * 7) / 100;
		tr = yr + dr[top];
		tc = yc + dc[top];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;

		tmp = (map[yr][yc] * 7) / 100;
		tr = yr + dr[bottom];
		tc = yc + dc[bottom];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;

		tmp = (map[yr][yc] * 2) / 100;
		tr = yr + dr[bottom] + dr[bottom];
		tc = yc + dc[bottom] + dc[bottom];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;


		tmp = (map[yr][yc] * 10) / 100;
		tr = yr + dr[top] + dr[left];
		tc = yc + dc[top] + dc[left];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;

		tmp = (map[yr][yc] * 10) / 100;
		tr = yr + dr[bottom] + dr[left];
		tc = yc + dc[bottom] + dc[left];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;


		tmp = (map[yr][yc] * 1) / 100;
		tr = yr + dr[top] + dr[right];
		tc = yc + dc[top] + dc[right];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;


		tmp = (map[yr][yc] * 1) / 100;
		tr = yr + dr[bottom] + dr[right];
		tc = yc + dc[bottom] + dr[right];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;

		tmp = (map[yr][yc] * 5) / 100;
		tr = yr + dr[left] + dr[left];
		tc = yc + dc[left] + dr[left];
		if (tr >= 0 && tr < N && tc >= 0 && tc < N) {
			map[tr][tc] += tmp;
		}
		else out += tmp;
		sum += tmp;


		//남은 양 알파 값으로 더하기
		int ar = yr + dr[curDir];
		int ac = yc + dc[curDir];
		if (ar >= 0 && ar < N && ac >= 0 && ac < N) {
			map[ar][ac] += map[yr][yc] - sum;
		}
		else {
			out += map[yr][yc] - sum;
		}

		map[yr][yc] = 0; //y좌표 0으로
	}
}



int main() {
	cin >> N;

	map.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) { //지도 입력
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	curR = N / 2;
	curC = N / 2;
	

	for (int i = 1; i < N; i++) { //길이 i만큼

		
		simulate(i); //한변 이동
		
		curDir++; 
		if (curDir == 4)curDir = 0; //방향 전환

		simulate(i); //또 한변 이동
		curDir++;
		if (curDir == 4)curDir = 0; //방향 전환
	}

	simulate(N - 1); //마지막 맨 위 한번 더


	cout << out;
}