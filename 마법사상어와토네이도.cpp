//https://www.acmicpc.net/problem/20057
//������ ���� ����̵�

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


int N;

vector<vector<int>> map;

int out = 0;

int curR, curC; //���� ��, ��
int curDir=0; //���� �̵� ����

int dr[4] = {0,1,0,-1}; //�� �� �� ��
int dc[4] = {-1,0,1,0};

//�·� �̵��ϴ°��: �����¿�
//�Ϸ� �̵��ϴ°��: �¿��ϻ�
//��� �̵��ϴ°��: �ϻ����
//������ �̵��ϴ°��: ���»���

void simulate(int len) { //���� len��ŭ curDir�������� �� �� �̵�

	//�� �� �� ��
	int left = 0; int bottom = 1; int right = 2; int top = 3;

	//���� ȯ��
	switch (curDir) {
	case 0: //�·� �̵�
		//���� �״��
		break;
	case 1: //�Ϸ� �̵�
		top = 0; bottom = 2; left = 1; right = 3;
		break;
	case 2: //��� �̵�
		top = 1; bottom = 3; left = 2; right = 0;
		break;
	case 3: //������ �̵�
		top = 2; bottom = 0; left = 3; right = 1;
		break;
	}
	
	for (int i = 0; i < len; i++) {
		
		//y��ǥ
		int yr = curR + dr[curDir];
		int yc = curC + dc[curDir];
		curR = yr; curC = yc;

		int sum = 0; //y���� �پ�� ��
		

		//ȯ��� �������� �Ѹ���
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


		//���� �� ���� ������ ���ϱ�
		int ar = yr + dr[curDir];
		int ac = yc + dc[curDir];
		if (ar >= 0 && ar < N && ac >= 0 && ac < N) {
			map[ar][ac] += map[yr][yc] - sum;
		}
		else {
			out += map[yr][yc] - sum;
		}

		map[yr][yc] = 0; //y��ǥ 0����
	}
}



int main() {
	cin >> N;

	map.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) { //���� �Է�
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	curR = N / 2;
	curC = N / 2;
	

	for (int i = 1; i < N; i++) { //���� i��ŭ

		
		simulate(i); //�Ѻ� �̵�
		
		curDir++; 
		if (curDir == 4)curDir = 0; //���� ��ȯ

		simulate(i); //�� �Ѻ� �̵�
		curDir++;
		if (curDir == 4)curDir = 0; //���� ��ȯ
	}

	simulate(N - 1); //������ �� �� �ѹ� ��


	cout << out;
}