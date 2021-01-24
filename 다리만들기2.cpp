//https://www.acmicpc.net/problem/17472
//�ٸ� �����2

#include <iostream>
#include <vector>
#include <queue>
#include <set>


using namespace std;


int N, M;

vector<vector<int>> map;

int dx[4] = { 0,0,1,-1 }; //�� �� �� ��
int dy[4] = { 1,-1,0,0 };

int num = 1; //���� ����+1

set<vector<int>> bridge; //�ٸ�����, ���� ����ȣ, ���� ����ȣ

void setNum() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) {
				num++;

				queue<pair<int, int>> q;
				map[i][j] = num;
				q.push(make_pair(i, j));

				while (!q.empty()) {
					pair<int, int> p = q.front();
					q.pop();

					for (int d = 0; d < 4; d++) {
						int x = p.first + dx[d];
						int y = p.second + dy[d];

						if (x >= 0 && x < N && y >= 0 && y < M && map[x][y] == 1) {
							map[x][y] = num;
							q.push(make_pair(x, y));
						}
					}
				}
			}
		}
	}
}

void addBridge() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] > 1) { //���̶��
				for (int d = 0; d < 4; d++) {//4�������� ����� 
					//�ٸ� ����
					int len = 0;

					//������ġ
					int cx = i;
					int cy = j;

					//���� �� ��ȣ
					int arrived = -1;

					bool flag = true; //�ٸ��ٸ��� �����ߴ��� ���� �ٸ��� �ǵ��ƿ°���
					while (true) {
						cx += dx[d];
						cy += dy[d];

						if (cx < 0 || cx >= N || cy < 0 || cy >= M) break;

						if (map[cx][cy] > 1 && map[cx][cy] != map[i][j]) {
							arrived = map[cx][cy];
							break;
						}

						if (map[cx][cy] == map[i][j]) {
							flag = false;
							break;
						}

						len++;
					}

					if (len >= 2 && flag && arrived != -1) {
						//cout << "\n i j d:" << i << " " << j << " " << d;
						//cout << "\n��" << len <<"\n";
						bridge.insert({ len,map[i][j], arrived });
					}

				}
			}
		}
	}
}

vector<int> parents;

int findRoot(int num) {
	if (parents[num] == -1)return num;
	else return parents[num] = findRoot(parents[num]);
}

void group(int num1, int num2) {
	int num1Root = findRoot(num1);
	int num2Root = findRoot(num2);
	if (num1Root < num2Root) {
		parents[num2Root] = num1Root;
	}
	else {
		parents[num1Root] = num2Root;
	}
}


int main() {

	cin >> N >> M;
	map.resize(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	setNum(); //������ ��ȣ�� �ű��


	addBridge(); //��ġ ������ ��� �ٸ��� �����Ѵ�


	//ũ�罺Į
	parents.resize(num + 1, -1);


	int answer = 0;
	for (auto a : bridge) { //���̰� ª�� �������
		if (findRoot(a[1]) != findRoot(a[2])) {
			group(a[1], a[2]);
			answer += a[0];
		}
	}


	set<int> roots;
	for (int i = 2; i <= num; i++) {

		roots.insert(findRoot(i));
	}

	if (roots.size() == 1)cout << answer;

	else cout << "-1";

}