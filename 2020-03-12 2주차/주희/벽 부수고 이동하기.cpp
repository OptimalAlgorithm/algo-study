//[���� 2206] �� �μ��� �̵��ϱ�

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int N, M; //����, ����
vector<string> map;
vector<vector<set<int>>> visited; //1:�״�� �� 0: �ѹ� �μ��� ��

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
	visited[0][0].insert(1); //���� �Ⱥμ�

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

					//���̰� �ѹ� �μ� �� �ִٸ�
					if (map[x][y] == '1' && visited[a.first][a.second].count(1) == 1) {
						if (visited[x][y].count(0) == 0) {
							visited[x][y].insert(0);
							tmp2.insert(make_pair(x, y));
						}
					}
					//���� �ƴ�
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