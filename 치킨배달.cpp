//https://www.acmicpc.net/problem/15686
//ġŲ ���



#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>


using namespace std;

int N, M;
int map[50][50];// 0�� �� ĭ, 1�� ��, 2�� ġŲ��

vector<pair<int, int>> house;
vector<pair<int, int>> chicken;

vector<vector<int>> dist;

int minDist = INT_MAX;

vector<int> selected; //���õ� ġŲ�� �ε���

int calDist() { //���õ� ġŲ������ ġŲ�Ÿ��� �� ���
	int sum = 0;

	for (int h = 0; h < house.size(); h++) {
		int tmp = INT_MAX;

		for (auto a : selected) tmp = min(tmp, dist[h][a]);

		sum += tmp;

	}

	return sum;
}

void select(int idx, int cnt) {
	if (cnt == 0) {
		minDist = min(minDist, calDist());
	}
	else {
		for (int i = idx; i <= chicken.size() - cnt; i++) {
			selected.push_back(i);
			select(i + 1, cnt - 1);
			selected.pop_back();
		}
	}
}



int main() {
	
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			if (map[i][j] == 1) {
				house.push_back(make_pair(i, j));
			}
			if (map[i][j] == 2) {
				chicken.push_back(make_pair(i, j));
			}


		}
	}

	//ġŲ�� - �� ������ ��� �Ÿ��� �̸� ���صд�// ��:�� ��: ġŲ��
	dist.resize(house.size(), vector<int>(chicken.size()));
	for (int i = 0; i < house.size(); i++) {
		for (int j = 0; j < chicken.size(); j++) {
			dist[i][j] = abs(house[i].first - chicken[j].first) + abs(house[i].second - chicken[j].second);
		}
	}

	
	select(0, M);



	cout << minDist;
}