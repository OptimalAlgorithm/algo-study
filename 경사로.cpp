//https://www.acmicpc.net/problem/14890
//����


//�Ǽ�����: cur�� ������ ������
//�������� 1�� �����ϴٴ� ������ ������

#include <iostream>
#include <vector>


using namespace std;


int N, L;

vector<vector<int>> map; //��, ��
vector<vector<int>> rmap; //��, ��

int cnt = 0;

void countRoad(vector<vector<int>> tmp) {
	vector<vector<int>> slide = tmp; //����:-1
	for (int i = 0; i < N; i++) {
		bool flag = true;

		int idx = 1;
		int cur = tmp[i][0]; //��������
		while (true) {
			if (idx >= N)break;

			if (tmp[i][idx] == cur) { //���ϳ��̸� �״�� ����
				idx++;
				continue;
			}
			else if (tmp[i][idx] > cur) { //���������̸�

				if (tmp[i][idx] - cur > 1 || idx < L) { //������, ���� ���� üũ
					flag = false;
					break;
				}

				bool flag2 = true;
				for (int len = 1; len <= L; len++) { //���� �ߺ� üũ
					if (slide[i][idx - len] == -1) {
						flag2 = false;
						flag = false;
						break;
					}
				}
				if (!flag2)break;

				for (int len = 1; len <= L; len++) {
					slide[i][idx - len] = -1; //���� ��ġ
				}


				cur = tmp[i][idx];
				idx++;
			}
			else { //���������̸�
				if (cur - tmp[i][idx] > 1 || idx > N - L) { //������, ���� ���� üũ
					flag = false;
					break;
				}

				int cmp = tmp[i][idx];
				bool flag2 = true;

				for (int len = 0; len < L; len++) { //���� ���� üũ
					if (tmp[i][idx + len] != cmp) {
						flag2 = false;
						flag = false;
						break;
					}
				}

				if (!flag2)break;

				for (int len = 0; len < L; len++) {
					slide[i][idx + len] = -1; //���� ��ġ
				}


				cur = tmp[i][idx];
				idx += L;
			}
		}

		if (flag) {

			cnt++;
		}
	}

}

int main() {
	cin >> N >> L;

	map.resize(N, vector<int>(N));
	rmap.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			rmap[j][i] = map[i][j];
		}
	}

	countRoad(map);
	countRoad(rmap);

	cout << cnt;

}