//https://www.acmicpc.net/problem/17135
//캐슬 디펜스

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>


using namespace std;


int N, M, D; //행 열 공격 거리 제한

int maxKill = 0;

vector<vector<int>> map; //0은 빈 칸, 1은 적이 있는 칸

vector<int> selected; //궁수가 위치한 열

int dx[3] = { 0,0,-1 };
int dy[3] = { -1,1,0 };

int tmpCnt; //제거한 적의 수

bool cmp(pair<int, int> p1, pair<int, int> p2) {
	if (p1.second != p2.second)return p1.second < p2.second;
	else return p1.first < p2.first;
}

int remain(vector<vector<int>> tmpMap) {
	int rtn = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmpMap[i][j] == 1)rtn++;
		}
	}
	return rtn;
}

vector<vector<int>> attack(vector<vector<int>> tmpMap) {
	set<pair<int, int>> target; //공격할 적의 위치

	for (auto a : selected) { //궁수마다 적을 선택
		
		vector<pair<int, int>> tmpList; //적 후보

		queue<pair<int, int>> q;
		q.push(make_pair(N, a));

		for(int l=0; l < D; l++) {
			int size = q.size();
			if (size == 0)break;


			for (int i = 0; i < size; i++) {
				pair<int, int> p = q.front();
				q.pop();

				for (int d = 0; d < 3; d++) {
					int tx = p.first + dx[d];
					int ty = p.second + dy[d];

					if (tx < 0 || tx >= N || ty < 0 || ty >= M)continue;

					if (tmpMap[tx][ty] == 1)tmpList.push_back(make_pair(tx, ty));
					else q.push(make_pair(tx, ty));
				}
			}

			if (tmpList.size() > 0) {
				sort(tmpList.begin(), tmpList.end(), cmp);
				target.insert(tmpList[0]);
				break;
			}
		}

	}



	//적 제거
	tmpCnt += target.size();
	for (auto a : target) {
		tmpMap[a.first][a.second] = 0;
	}
	return tmpMap;
}

vector<vector<int>> targetDown(vector<vector<int>> tmpMap) {
	for (int i = N - 1; i > 0; i--) {
		for (int j = 0; j < M; j++) {
			tmpMap[i][j] = tmpMap[i - 1][j];
		}
	}

	for (int j = 0; j < M; j++) {
		tmpMap[0][j] = 0;
	}

	return tmpMap;
}

void simulate(vector<vector<int>> param) {

	vector<vector<int>> map2 = attack(param);

	map2 = targetDown(map2);

	if (remain(map2) != 0) {
		simulate(map2);
	}
	else return;
}

void select(int idx, int cnt) {
	if (cnt == 0) {
		tmpCnt = 0;
		simulate(map);
		maxKill = max(maxKill, tmpCnt);
	}
	else {
		for (int i = idx; i <= M - cnt; i++) {
			selected.push_back(i);
			select(i + 1, cnt - 1);
			selected.pop_back();
		}
	}
}

int main() {
	cin >> N >> M >> D;

	map.resize(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	select(0, 3); //궁수 위치 선택


	cout << maxKill;

}