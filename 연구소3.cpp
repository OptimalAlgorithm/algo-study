//https://www.acmicpc.net/problem/17142
//������3


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

int N, M; //������ ũ��, ���̷��� ��

vector<vector<int>> map; // 0�� �� ĭ, 1�� ��, 2�� ���̷����� ���� �� �ִ� ��ġ

vector<pair<int, int>> virus; //���̷����� �� �� �ִ� ��ġ

vector<int> selected;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int minSeconds = INT_MAX;

bool isFinished(vector<vector<int>> tmpMap) {
	bool flag = true;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tmpMap[i][j] == 0) return false;
		}
	}

	return true;
}

void bfs() {
	vector<vector<int>> tmpMap = map;
	
	//�۶߸������������� �۶߸���
	queue<pair<int, int>> q; //0ĭ����
	for (auto a : selected) {
		q.push(make_pair(virus[a].first, virus[a].second));
		tmpMap[virus[a].first][virus[a].second] = 1;
	}

	queue<pair<int, int>> q2; //2ĭ����

	int cnt1 = 0;
	int cnt2 = 0;
	while (!(q.empty() && q2.empty())) {
		bool flag = true; //cnt1��������
		int size = q.size();
		int size2 = q2.size();

		for (int i = 0; i < size2; i++) {
			pair<int, int > p = q2.front();
			q2.pop();

			for (int d = 0; d < 4; d++) {
				int r = p.first + dx[d];
				int c = p.second + dy[d];

				if (r < 0 || r >= N || c < 0 || c >= N)continue;

				if (tmpMap[r][c] == 0) {
					tmpMap[r][c] = 1;
					q.push(make_pair(r, c));
					
					if (cnt1 < cnt2 + 1) {
						cnt1 = cnt2 + 1;
						flag = false;
					}
				}
				else if (tmpMap[r][c] == 2) {
					tmpMap[r][c] = 1;
					q2.push(make_pair(r, c));
				}

			}
		}
		

		for (int i = 0; i < size; i++) {
			pair<int, int > p = q.front();
			q.pop();

			for (int d = 0; d < 4; d++) {
				int r = p.first + dx[d];
				int c = p.second + dy[d];

				if (r < 0 || r >= N || c < 0 || c >= N)continue;

				if (tmpMap[r][c] == 0) {
					tmpMap[r][c] = 1;
					q.push(make_pair(r, c));
				}
				else if (tmpMap[r][c] == 2) {
					tmpMap[r][c] = 1;
					q2.push(make_pair(r, c));
				}

			}
		}
		
		if(flag && q.size() > 0) cnt1++;		
		if (q2.size() > 0 || q.size() > 0) cnt2++;
	}


	//�� �������� Ȯ���ؼ� min ����
	if (isFinished(tmpMap)) {
		minSeconds = min(minSeconds, cnt1);
	}

}

void select(int idx, int cnt) {//idx���� cnt�� ����
	if (cnt == 0) { //M�� �� ������� bfs
		bfs(); 
	}
	else {
		for (int i = idx; i <= virus.size() - cnt; i++){
			selected.push_back(i);
			select(i + 1, cnt - 1);
			selected.pop_back();
		}
	}
}

int main() {

	cin >> N >> M;
	map.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			if (map[i][j] == 2) {
				virus.push_back(make_pair(i, j));
			}
		}
	}

	select(0, M);

	if (minSeconds == INT_MAX)cout << "-1";
	else cout << minSeconds;

}