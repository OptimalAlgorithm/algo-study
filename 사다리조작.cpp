//https://www.acmicpc.net/problem/15684
//��ٸ� ����


#include <iostream>
#include <vector>

using namespace std;



int N, M, H; //N���� ���μ��� M���� ���μ�


int lines[11][31]; //N��° ���μ�, H��°��, ����-1, ������1



bool simulate() {
	for (int i = 1; i <= N; i++) {
		int start = i;

		for (int h = 1; h <= H; h++) {
			if (lines[start][h] == 0)continue;
			else if (lines[start][h] == -1) start--;
			else start++;
		}

		if (i != start)return false;
	}

	return true;
}


void select(int ans, int curN, int curH, int cnt) {
	if (cnt == 0) {
		if (simulate()) {
			cout << ans;
			exit(0);
		}
	}
	else {
		for (int i = curN; i <= N; i++) { //���μ� ��ȣ
			for (int j = curH; j <= H; j++) { //����
				if (lines[i][j] != 0) continue;

				//�������� �õ�
				if (i > 1 && lines[i - 1][j] != -1) {
					lines[i][j] = -1;
					lines[i - 1][j] = 1;

					select(ans, i, j, cnt - 1);

					lines[i][j] = 0;
					lines[i - 1][j] = 0;
				}

				//���������� �õ�
				if (i < N && lines[i + 1][j] != 1) {
					lines[i][j] = 1;
					lines[i + 1][j] = -1;

					select(ans, i, j, cnt - 1);

					lines[i][j] = 0;
					lines[i + 1][j] = 0;
				}
			}
		}

	}
}



int main() {
	cin >> N >> M >> H;

	int a, b;// b�� ���μ��� b+1�� ���μ��� a�� ���� ��ġ���� ����
	for (int i = 0; i < M; i++) {
		cin >> a >> b;

		lines[b][a] = 1;
		lines[b + 1][a] = -1;
	}

	for (int i = 0; i <= 3; i++) { //i�� ���μ� �߰� �õ�
		select(i, 1, 1, i);
	}


	cout << "-1";
}