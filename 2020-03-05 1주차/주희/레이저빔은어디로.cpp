//[���� 3709] ���������� ����

#include <iostream>
#include <memory.h>
#include <vector>
#include <set>

using namespace std;

//x:���� y:����

int N, r;
int map[50][50]; //0:����� 1:�����
int cx, cy, cd; //����x, ����y, �������

				//�� �� �� ��
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	int T;
	cin >> T;

	for (int t{ 0 }; t < T; t++) {
		memset(map, 0, sizeof(map));
		cin >> N >> r;

		//����� ��ġ �Է�
		int x, y;
		for (int i{ 0 }; i < r; i++) {
			cin >> x >> y;

			map[x - 1][y - 1] = 1;
		}

		//������ ������
		cin >> cx >> cy;
		cx--; cy--;

		//�ʱ� ������ ���� ���� ���ϱ�
		if (cx == -1) {
			cd = 2; //��
		}
		else if (cx == N) {
			cd = 0; //��
		}
		else if (cy == -1) {
			cd = 1; //��
		}
		else {
			cd = 3; //��
		}

		//visited
		set<int> visited[50][50];

		while (true) {
			int tx = cx + dx[cd];
			int ty = cy + dy[cd];

			//���� ��
			if (tx >= 0 && tx < N && ty >= 0 && ty < N) {
				//���ڸ�
				if (visited[tx][ty].count(cd) == 1) {
					cout << "0 0\n";
					break;
				}

				visited[tx][ty].insert(cd);

				//�����
				if (map[tx][ty] == 1) {
					//������ȯ
					cd++;
					cd %= 4;

					//��ǥ�̵�
					cx = tx;
					cy = ty;
				}
				//�����
				else {
					cx = tx;
					cy = ty;
				}
			}
			//���� �ٱ�
			else {
				cout << tx + 1 << " " << ty + 1 << "\n";
				break;
			}
		}
	}


	//system("pause");
	return 0;
}