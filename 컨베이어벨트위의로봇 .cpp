//https://www.acmicpc.net/problem/20055
//�����̾� ��Ʈ ���� �κ� 

#include <iostream>
#include <vector>

using namespace std;

int N, K;

int cnt = 1;

int belt[201]; //������
int robots[201];

int start = 1;


bool simulate() {

	//1. ��Ʈ�� �� ĭ ȸ���Ѵ�.
	start--;
	if (start < 1) start = 2 * N;
	//�������� ��ġ �κ� ������
	int down = start + N - 1;
	if (down > 2 * N) down -= 2 * N;
	if (robots[down] == 1)robots[down] = 0;


	//2. �κ� �����̱�
	for (int i = 1; i < N; i++) {

		int idx = down - i;
		if (idx < 1) idx += 2 * N;
		else if (idx > 2 * N) idx -= 2 * N;

		int nxt = idx + 1;
		if (nxt > 2 * N) nxt -= 2 * N;
		else if (nxt < 1) nxt += 2 * N;

		//cout << "\nidx, nxt: " << idx << " " << nxt << " " << start << " " << down;

		if (robots[idx] == 1 && robots[nxt] == 0 && belt[nxt] > 0) {
			belt[nxt]--;
			robots[idx] = 0;
			robots[nxt] = 1;

			if (belt[nxt] == 0)K--;

			if (nxt == down)robots[nxt] = 0;
		}
	}



	//3. �ö󰡴� ��ġ�� �κ� �ø���
	if (robots[start] == 0 && belt[start] > 0) {
		belt[start]--;
		robots[start] = 1;

		if (belt[start] == 0)K--;
	}



	//4. ���� ����
	if (K > 0) {
		cnt++;
		return true;
	}
	else return false;
}


int main() {
	cin >> N >> K;

	for (int i = 1; i <= 2 * N; i++) {
		cin >> belt[i];
	}

	while (true) {
		if (!simulate())break;
	}


	cout << cnt;
}