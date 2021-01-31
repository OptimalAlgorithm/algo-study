//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE&problemTitle=%EB%AA%A8%EC%9D%98&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
//�ɺ� ����


//�Ǽ�����:
//wormholes������ �ʱ�ȭ �����༭ �ε��� ������
//map[r][c] = r,c�� ���� �� >> �̷����� ���� �ι��� ���� r,c���� �ٲ� �ȵ�
// >> tmp ���� �ϳ� ��Ƽ� �ذ�
//maxHits�ʱ�ȭ ��ġ �߸�����


#include <iostream>
#include <vector>


using namespace std;


int N;

int hits; //����

int maxHits;


vector<vector<int>> map; //���, ��Ȧ, ��Ȧ

vector<pair<int, int>> blackholes;

int dr[4] = { 0,0,1,-1 }; // �� �� �� ��
int dc[4] = { 1,-1,0,0 };

vector<vector<pair<int, int>>> wormholes;

void inputMap() {

	blackholes.clear();

	wormholes.clear();
	wormholes.resize(5);

	map.clear();
	map.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			//��Ȧ
			if (map[i][j] == -1)blackholes.push_back(make_pair(i, j));

			if (map[i][j] >= 6 && map[i][j] <= 10) {
				wormholes[map[i][j] - 6].push_back(make_pair(i, j));
			}
		}
	}


	//cout << "��Ȧ�Է��׽�Ʈ:\n";
	//for (int i = 0; i < 5; i++) {
	//	for (auto a : wormholes[i])cout << "\ni:" << i << a.first << " " << a.second << "\n";
	//}
}

void simulate(int i, int j) {
	

	for (int d = 0; d < 4; d++) { //4�������� ���
		hits = 0;
		

		int r = i;
		int c = j;
		int dir = d;

		while (true) {
			//cout << "\nhits:" << hits << " r,c, dir: " << r << " " << c << " " << dir;
			r += dr[dir];
			c += dc[dir];

			//���� �ε���
			if (r < 0 || r >= N || c < 0 || c >= N) { 
				//cout << "���� �ε���";
				hits++;

				switch (dir) {
				case 0: //�� > ��
					dir = 1;
					break;
				case 1: //�� > ��
					dir = 0;
					break;
				case 2: //�� > ��
					dir = 3;
					break;
				case 3: //�� > ��
					dir = 2;
					break;
				}

				continue;
			}

			
			//��Ͽ� ����
			if (map[r][c] >= 1 && map[r][c] <= 5) { 
				//cout << map[r][c] << "�� ��� ����";
				hits++;

				switch (map[r][c]) { //��Ϲ�ȣ
				case 1:
					switch (dir) {
					case 0: //��
						dir = 1;
						break;
					case 1: //��
						dir = 3;
						break;
					case 2: //��
						dir = 0;
						break;
					case 3: //��
						dir = 2;
						break;
					}

					break;
				case 2:
					switch (dir) {
					case 0: //��
						dir = 1;
						break;
					case 1: //��
						dir = 2;
						break;
					case 2: //��
						dir = 3;
						break;
					case 3: //��
						dir = 0;
						break;
					}

					break;
				case 3:
					switch (dir) {
					case 0: //��
						dir = 2;
						break;
					case 1: //��
						dir = 0;
						break;
					case 2: //��
						dir = 3;
						break;
					case 3: //��
						dir = 1;
						break;
					}

					break;
				case 4:
					switch (dir) {
					case 0: //��
						dir = 3;
						break;
					case 1: //��
						dir = 0;
						break;
					case 2: //��
						dir = 1;
						break;
					case 3: //��
						dir = 2;
						break;
					}

					break;
				case 5:
					switch (dir) {
					case 0: //��
						dir = 1;
						break;
					case 1: //��
						dir = 0;
						break;
					case 2: //��
						dir = 3;
						break;
					case 3: //��
						dir = 2;
						break;
					}

					break;
				}

				continue;
			}

			//��Ȧ ����
			if (map[r][c] >= 6 && map[r][c] <= 10) { 
				//cout << "��Ȧ����";
				pair<int, int> p = make_pair(r, c);
				
				if (wormholes[map[r][c] - 6][0] == p) {
			
					int tmp1 = wormholes[map[r][c] - 6][1].first;
					int tmp2 = wormholes[map[r][c] - 6][1].second;

					r = tmp1;
					c = tmp2;
				}
				else {
				
					int tmp1 = wormholes[map[r][c] - 6][0].first;
					int tmp2 = wormholes[map[r][c] - 6][0].second;

					r = tmp1;
					c = tmp2;
				}
				
				continue;

			}

			//��Ȧ ������ ����
			if (map[r][c] == -1) {
				//cout << "��Ȧ����";
				break;
			}

			//������ġ�� �ͼ� ����
			if (r == i && c == j) {
				//cout << "������ġ�ο�";
				break;
			}
		}

		//cout << "\nHITS: " << hits << "\n";
		maxHits = max(maxHits, hits);
	}
}

int main() {

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N;
		
		inputMap();

		maxHits = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 0)simulate(i, j); //i,j��ġ ��������� ���
			}
		}

		cout << "#" << t << " " << maxHits << "\n";
	}
}