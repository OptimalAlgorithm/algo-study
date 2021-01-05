//https://www.acmicpc.net/problem/19238
//��ŸƮ �ý�


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <math.h>



using namespace std;

int N, M, fuel;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int curX, curY; //�ý���ġ

int map[30][30]; //0:��ĭ 1:��

int guest[30][30]; //�մ���ġ

//int dest[20][20]; //������ġ

int gNum; //�մ� ��ȣ

vector<pair<int, int>> dest;


void findGuestAndMove() {
	int visited[30][30] = {};

	//bfs�� �մ�ã��
	set<pair<int, int>> tmp; //�մ� �ĺ� ���� - ��, �� �켱������ �ڵ�����	

	int dist = 0; //�մԱ��� �Ÿ����

	queue<pair<int, int>> q;
	visited[curX][curY] = 1;
	q.push(make_pair(curX, curY));

	while (true) {
		int size = q.size();

		if (size == 0) { //�մԱ��� ����
			cout << "-1";
			exit(0);
		}
		else dist++;

		for (int i = 0; i < size; i++) {
			pair<int, int> p = q.front();
			q.pop();


			for (int d = 0; d < 4; d++) {
				int tx = p.first + dx[d];
				int ty = p.second + dy[d];

				if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;

				if (guest[tx][ty] > 0) { //�մ� �߰�
				//	cout << "�մԹ߰�: " << tx << " " << ty << guest;
					tmp.insert(make_pair(tx, ty));
				}
				else if (map[tx][ty] == 0 && visited[tx][ty] != 1) {
					visited[tx][ty] = 1;
					q.push(make_pair(tx, ty));
				}
			}
		}

		if (tmp.size() > 0) break;
	}

	//���� �켱���� ���� �մ��� ������
	curX = (*tmp.begin()).first;
	curY = (*tmp.begin()).second;


	//�մԱ��� �̵�- curX, curY���� gX, gY��
	gNum = guest[curX][curY];
	guest[curX][curY] = 0; //�մ� ��Ͽ��� ����
	//cout << "�մ�Ȯ��: " << curX << " " << curY << "\n";
	fuel -= dist; //���ᰨ��


	if (fuel < 0) { //�������
		cout << "-1";
		exit(0);
	}
}

void moveToDest() {
	int visited[30][30] = {};

	queue<pair<int, int>> q;
	visited[curX][curY] = 1;
	q.push(make_pair(curX, curY));

	int dist = 0;

	while (true) {
		int size = q.size();

		if (size == 0) { //���������� ����
			cout << "-1";
			exit(0);
		}
		//else cout << size << "size\n";

		fuel--;
		if (fuel < 0) { //�������
			cout << "-1";
			exit(0);
		}

		dist++;

		for (int i = 0; i < size; i++) {
			pair<int, int> p = q.front();
			q.pop();
			//cout << "��ǥ: " << p.first << p.second << "\n";

			for (int d = 0; d < 4; d++) {
				int tx = p.first + dx[d];
				int ty = p.second + dy[d];

				if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;

				if (tx == dest[gNum].first && ty == dest[gNum].second) { //������ ����
					curX = tx;
					curY = ty;

					fuel += 2 * dist;

					return;
				}
				else if (map[tx][ty] == 0 && visited[tx][ty] != 1) {
					visited[tx][ty] = 1;
					q.push(make_pair(tx, ty));
				}
			}
		}
	}
}

void simulate() {

	if (guest[curX][curY] != 0) { //���� ��ġ�� �մ���������
		gNum = guest[curX][curY];
		guest[curX][curY] = 0;
	}
	else findGuestAndMove(); //���� ����� �մ� ã�Ƽ� �̵�	
	//cout << "\n���� �մ� �¿�: " << curX << " " << curY << " " << fuel << "\n";

	//bfs�� ���������� �̵�- curX,curY���� dest[][]���� �մԹ�ȣ ���ö�����
	if (curX != dest[gNum].first || curY != dest[gNum].second) {
		moveToDest();
	}
	//cout << "���� �������� �̵�: " << curX << " " << curY << " " << fuel << "\n";

	M--; //�մ� �Ѹ� ��������ٴ� ��
	if (M > 0)simulate(); //�մ��� ���������� �� ����
}


int main() {
	cin >> N >> M >> fuel;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	cin >> curX >> curY; //�ý���ġ
	curX--; curY--;

	dest.push_back(make_pair(-1, -1)); //�����е�

	//�մ� - 1������
	int x1, y1, x2, y2;
	for (int i = 1; i <= M; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;
		guest[x1][y1] = i;
		dest.push_back(make_pair(x2, y2));
	}

	simulate();

	cout << fuel;
}