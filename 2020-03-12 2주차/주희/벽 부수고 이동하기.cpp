//[백준 2206] 벽 부수고 이동하기

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int N, M; //세로, 가로
vector<string> map;
vector<vector<set<int>>> visited; //1:그대로 옴 0: 한번 부수고 옴

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int len{ 0 };

void setMap() {
	string s;
	for (int i{ 0 }; i < N; i++) {
		cin >> s;
		map.push_back(s);
	}

	return;
}

void setVisited() {
	visited.resize(N, vector<set<int>>(M));
	return;
}

void findRoute() {
	set<pair<int, int>> tmp = { make_pair(0,0) };
	visited[0][0].insert(1); //아직 안부숨

	while (tmp.size() > 0) {
		set<pair<int, int>> tmp2;
		len++;

		for (auto a : tmp) {
			if (a.first == N && a.second == M) {
				cout << len;
				return;
			}

			for (int i{ 0 }; i < 4; i++) {
				int x = a.first + dx[i];
				int y = a.second + dy[i];


				if (x >= 0 && x <= N && y >= 0 && y <= M) {

					//벽이고 한번 부술 수 있다면
					if (map[x][y] == '1' && visited[a.first][a.second].count(1) == 1) {
						if (visited[x][y].count(0) == 0) {
							visited[x][y].insert(0);
							tmp2.insert(make_pair(x, y));
						}
					}
					//벽이 아님
					else if (map[x][y] == '0') {
						int t = visited[a.first][a.second].count(1);
						if (visited[x][y].count(t) == 0) {
							visited[x][y].insert(t);
							tmp2.insert(make_pair(x, y));
						}
					}
					else {}
				}
			}
		}

		tmp = tmp2;
	}

	cout << "-1";
	return;
}

int main() {
	cin >> N >> M;

	setMap();

	setVisited();


	N--; M--;

	if (N == 0 && M == 0)cout << "1";
	else findRoute();

	//system("pause");
	return 0;
}