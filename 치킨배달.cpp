//https://www.acmicpc.net/problem/15686
//치킨 배달



#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>


using namespace std;

int N, M;
int map[50][50];// 0은 빈 칸, 1은 집, 2는 치킨집

vector<pair<int, int>> house;
vector<pair<int, int>> chicken;

vector<vector<int>> dist;

int minDist = INT_MAX;

vector<int> selected; //선택된 치킨집 인덱스

int calDist() { //선택된 치킨집으로 치킨거리의 합 계산
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

	//치킨집 - 집 사이의 모든 거리를 미리 구해둔다// 행:집 열: 치킨집
	dist.resize(house.size(), vector<int>(chicken.size()));
	for (int i = 0; i < house.size(); i++) {
		for (int j = 0; j < chicken.size(); j++) {
			dist[i][j] = abs(house[i].first - chicken[j].first) + abs(house[i].second - chicken[j].second);
		}
	}

	
	select(0, M);



	cout << minDist;
}