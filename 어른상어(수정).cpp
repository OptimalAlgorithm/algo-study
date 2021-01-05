#include <iostream>
#include <vector>
#include <set>

using namespace std;

//�Լ�����
void simulate();
bool onlyShark();
void swim();
void smell();


int N, M, K; //����ĭũ��, ����, �����ð�

vector<vector<int>> map; //map

vector<int> sharkDir;//����� ���� ����

vector<vector<vector<int>>> dirPri; //��� ���� �켱����

vector<vector<pair<int, int>>> sharkSmell; //��� �������� ���� -  {����ȣ, ���� ��}

// 1, 2, 3, 4�� ���� ��, �Ʒ�, ����, �������� �ǹ��Ѵ�. - 0��°�� �ƹ��͵� �ƴ�
int dx[5] = { 3,-1,1,0,0 };
int dy[5] = { 3,0,0,-1,1 };

int seconds = 0;

void simulate() {
	if (!onlyShark()) {
		seconds++; //1�� �� ������ �ƴ϶�� �� ����
		if (seconds > 1000) {
			seconds = -1;
			return;
		}
		/*
		cout << "\n\n\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << map[i][j] << " ";
			}
			cout << "\n";
		}
		*/
	}
	else return; //1�� �� ���Ҵٸ� �ٷ� ����

	swim(); //��� �̵� - map, smell ����


	simulate();
}

void swim() { //��� �̵� - map, smell ����
	vector<vector<int>> map2(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] != 0) {
				int a = map[i][j];
				//a�� ��� ���� �̵�
				bool flag = false;
				switch (sharkDir[a]) {
				case 1:
					for (auto b : dirPri[a][0]) { //�켱 ����� Ȯ��
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][0]) { //����� ���ٸ� �ڽ��� ������ �̵�
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;
				case 2:

					for (auto b : dirPri[a][1]) { //�켱 ����� Ȯ��
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][1]) { //����� ���ٸ� �ڽ��� ������ �̵�
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;

				case 3:
					for (auto b : dirPri[a][2]) { //�켱 ����� Ȯ��
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][2]) { //����� ���ٸ� �ڽ��� ������ �̵�
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;
				case 4:

					for (auto b : dirPri[a][3]) { //�켱 ����� Ȯ��
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][3]) { //����� ���ٸ� �ڽ��� ������ �̵�
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;
				}


			}
		}
	}


	smell(); //���� ���ҽ�Ű�� - K��ĭ �����ϰ�

	//K��ĭ ���� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map2[i][j] != 0) {
				sharkSmell[i][j] = make_pair(map2[i][j], K);
			}
		}
	}
	map = map2;

}

void smell() { //���� ���ҽ�Ű�� - K��ĭ �����ϰ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (sharkSmell[i][j].second == 1) {
				sharkSmell[i][j] = make_pair(0, 0);
			}
			else if (sharkSmell[i][j].second != 0) {
				sharkSmell[i][j].second--;
			}
		}
	}
}

//1�� �� ���Ҵ��� üũ
bool onlyShark() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] > 1) return false; //1�� �� �� �߰ߵǸ� false
		}
	}

	//1�� �� ���Ҵٸ� true
	return true;
}

int main() {
	cin >> N >> M >> K;

	sharkSmell.resize(N, vector<pair<int, int>>(N, make_pair(0, 0)));


	//map�Է�
	map.resize(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			cin >> map[i][j];

			if (map[i][j] != 0) sharkSmell[i][j] = make_pair(map[i][j], K);
		}
	}

	//�ʱ� ��� ���� �Է�
	sharkDir.resize(M + 1);
	sharkDir.push_back(0);
	for (int i = 1; i <= M; i++) {
		cin >> sharkDir[i];
	}

	//��� ���� �켱���� �Է�
	vector<vector<int>> v;
	dirPri.push_back(v); //����ȣ�� 1�������̴ϱ� ������ 0��° �ڸ��� ä���

//M���� ��� ���� �̵� �켱���� �Է�
	for (int i = 0; i < M; i++) {
		vector<vector<int>> tmp(4, vector<int>(4));
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> tmp[i][j];
			}
		}
		dirPri.push_back(tmp);
	}

	//����̵� ����

	simulate();

	cout << seconds;

}