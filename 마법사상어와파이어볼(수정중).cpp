//https://www.acmicpc.net/problem/20056
//������ ���� ���̾

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int N, M, K;

int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,1,1,1,0,-1,-1,-1 };

struct fireball {
	int r, c;
	int m, s, d;
	bool dead;
};


vector<fireball> fbList;
vector<int> map[51][51];

void resetMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j].clear();
		}
	}
}

void simulate() {
	resetMap();

	//��� ���̾�� �ڽ��� ���� di�� �ӷ� siĭ ��ŭ �̵��Ѵ�.
	int size = fbList.size();
	for (int i = 0; i < size; i++) {
		fireball a = fbList[i];
		if (!a.dead) {
			//������ ���
			int tr = (a.r + dr[a.d] * a.s);
			int tc = (a.c + dc[a.d] * a.s);

			if (tr < 0) {
				int tmp = (-1 * tr) % N;
				tr = -1 * tmp + N;
			}
			else tr %= N;

			if (tc < 0) {
				int tmp = (-1 * tc) % N;
				tc = -1 * tmp + N;
			}
			else tc %= N;

			//a.r = tr; //���⼭ �Ǽ���
			//a.c = tc;
			fbList[i].r = tr;
			fbList[i].c = tc;
			//cout << "\ntr tc: " << a.r << " " << a.c;
			map[tr][tc].push_back(i);
		}
	}

	//�̵��� ��� ���� ��, 2�� �̻��� ���̾�� �ִ� ĭ������ ������ ���� ���� �Ͼ��.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j].size() > 1) {
				int sumM = 0; //���� ��
				int sumS = 0; //�ӷ� ��

				int evenDirCnt = 0;

				for (auto idx : map[i][j]) {
					sumM += fbList[idx].m;
					sumS += fbList[idx].s;

					if (fbList[idx].d % 2 == 0)evenDirCnt++;
				}

				sumM /= 5;
				sumS /= map[i][j].size();

				for (auto idx : map[i][j]) {
					fbList[idx].dead = true;
				}

				if (sumM != 0) {
					if (evenDirCnt == map[i][j].size() || evenDirCnt == 0) {
						for (int c = 0; c < 4; c++) {
							fireball f;
							f.r = i;
							f.c = j;
							f.m = sumM;
							f.s = sumS;
							f.d = 2 * c;
							f.dead = false;

							fbList.push_back(f);
						}
					}
					else {
						for (int c = 0; c < 4; c++) {
							fireball f;
							f.r = i;
							f.c = j;
							f.m = sumM;
							f.s = sumS;
							f.d = 2 * c + 1;
							f.dead = false;

							fbList.push_back(f);
						}
					}
				}

			}
		}
	}

}

int getSum() { //���� ���̾ ���� ���
	int sum = 0;

	for (auto a : fbList) {
		if (!a.dead)sum += a.m;
	}

	return sum;
}


int main() {
	cin >> N >> M >> K;

	int r, c, m, s, d;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> m >> s >> d;

		r--; c--;

		fireball fb;
		fb.r = r;
		fb.c = c;
		fb.m = m;
		fb.s = s;
		fb.d = d;
		fb.dead = false;

		fbList.push_back(fb);
	}

	for (int i = 0; i < K; i++) {
		simulate();
		/*
		cout << "\n\nsimulate ��:\n";
		for (auto a : fbList) {
			if (true) {
				cout << a.r << " " << a.c << " " << a.m << " " << a.s << " " << a.d << " " << a.dead << "\n";
			}
		}*/
	}

	cout << getSum();
}
