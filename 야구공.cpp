//https://www.acmicpc.net/problem/17281
//�߱���


#include <iostream>
#include <vector>



using namespace std;


int N;

int maxPoints = 0;

vector<int> visited;

vector<int> order; //Ÿ��

vector<vector<int>> result;

void play() {

	//cout << "\norder: ";
	//for (auto a : order)cout << a << " ";

	int points = 0;

	int idx = 0; //���� Ÿ���ε���
	

	for (int i = 0; i < N; i++) {
		int pos[9] = { 0, }; //���� ��ġ
		int out = 0;

		while (true) {
			if (out == 3)break;
		
			int rt = result[i][order[idx]];
			
			switch (rt) {
			case 1: //��Ÿ

				pos[idx]++;
				if (pos[idx] == 4) {
					pos[idx] = 0;
					points++;
				}

				for (int j = 0; j < 9; j++) {
					if (j==idx || pos[j] == 0)continue;

					pos[j]++;
					if (pos[j] == 4) {
						pos[j] = 0;
						points++;
					}
				}
				break;
			case 2: //2��Ÿ

				pos[idx]+=2;
				if (pos[idx] >= 4) {
					pos[idx] = 0;
					points++;
				}

				for (int j = 0; j < 9; j++) {
					if (j == idx || pos[j] == 0)continue;

					pos[j]+= 2;
					if (pos[j] >= 4) {
						pos[j] = 0;
						points++;
					}
				}
				break;
			case 3: //3��Ÿ

				pos[idx] += 3;
				if (pos[idx] >= 4) {
					pos[idx] = 0;
					points++;
				}

				for (int j = 0; j < 9; j++) {
					if (j == idx || pos[j] == 0)continue;

					pos[j] += 3;
					if (pos[j] >= 4) {
						pos[j] = 0;
						points++;
					}
				}
				break;
			case 4: //Ȩ��
				pos[idx] = 0;
				points++;

				for (int j = 0; j < 9; j++) {
					if (j == idx || pos[j] == 0)continue;

					pos[j] = 0;
					points++;
				}

				break;
			case 0: //�ƿ�
				out++;
				break;
			}

			idx++;
			if (idx == 9)idx = 0;

		}
	}

	if(points > maxPoints)maxPoints = points;
}


void getOrder(int cnt) {
	if (cnt == 9) {
		play();
	}
	else {
		if (cnt == 3) {
			order.push_back(0);
			getOrder(cnt + 1);
			order.pop_back();
		}
		else {
			for (int i = 1; i < 9; i++) {
				if (visited[i] == 0) {
					visited[i] = 1;
					order.push_back(i);

					getOrder(cnt + 1);

					visited[i] = 0;
					order.pop_back();
				}
			}
		}
	}
}


int main() {
	cin >> N;

	result.resize(N, vector<int>(9));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> result[i][j];
		}
	}

	visited.resize(9, 0);
	visited[0] = 1;

	getOrder(0);
	
	cout << maxPoints;
}