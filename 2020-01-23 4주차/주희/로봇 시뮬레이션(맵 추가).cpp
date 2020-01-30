//[���� 2174] �κ� �ùķ��̼�

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int A, B; //A = ����, B = ����
int N, M; //N = �κ� ��, M = ��� ��


vector<vector<int>> map; //���� > ���� ������ �κ� ��ġ ����

vector<vector<int>> dir = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } }; //��, ��, ��, ��

vector<tuple<int, int, int>> robotsInfo = { make_tuple(0,0,0) }; //�κ� ��ǥ, ���� ����

void robotInput(int N); //�κ� ������ �Է�
void work(int M); //��� ����
void rotateLeft(int n, int rp); //���� 90�� ȸ��
void rotateRight(int n, int rp); //������ 90�� ȸ��
void forward(int n, int rp); //������ ����

//�ʱ� �κ� ���� �Է�
void robotInput(int N) {
	for (int num{ 1 }; num <= N; num++) {
		int a, b; //����, ����
		char c; //����
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

//��� ����
void work(int M) { 
	for (int m{ 0 }; m < M; m++) {

		int robotNum;
		char command;
		int repeat;

		cin >> robotNum >> command >> repeat;

		//���� ȸ��
		if (command == 'L') {
			rotateLeft(robotNum, repeat);
		}
		//������ ȸ��
		else if (command == 'R'){ 
			rotateRight(robotNum, repeat);
		}
		//������ ����
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

		//���� �ٱ����� ������ ���
		if (x < 0 || x >= A || y < 0 || y >= B) {
			cout << "Robot " << n << " crashes into the wall";
			exit(0);
			return;
		}

		//�ٸ� �κ��� �浹�ϴ� ���
		if (map[x][y] != 0) {
			cout << "Robot " << n << " crashes into robot " << map[x][y];
			exit(0);
			return;
		}

		//�������� �̵� ������ ���
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