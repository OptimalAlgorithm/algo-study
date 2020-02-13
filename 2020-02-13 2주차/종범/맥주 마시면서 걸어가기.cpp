// https://www.acmicpc.net/problem/9205
// 맥주의 개수는 전혀상관 없는 문제

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

const int MAX = 100;
int t, n;
bool flag;
bool check[MAX + 2];
vector<pair<int, int>> total;

// 페스티벌까지 도달할 수 있는지 그래프를 만들고 bfs돌려서 결과를 반환
bool make_graph(int start) {
	vector<int> graph[MAX + 2];
	for (int i = 0; i < total.size() - 1; i++) {
		for (int j = i + 1; j < total.size(); j++) {
			if (abs(total[i].first - total[j].first) + abs(total[i].second - total[j].second) <= 1000) {
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}

	int wantIdx = total.size() - 1;		// 내가 찾길 원하는 인덱스
	queue<int> q;
	q.push(start);
	check[start] = true;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		if (now == wantIdx) return true;	// 페스티벌에 도달했다

		for (int i = 0; i < graph[now].size(); i++) {
			int next = graph[now][i];
			if (check[next]) continue;
			q.push(next);
			check[next] = true;
		}
	}
	return false;
}

// 초기화 함수
void initialize() {
	total.clear();
	memset(check, false, sizeof(check));
	flag = false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> t;
	for (int tc = 0; tc < t; tc++) {
		cin >> n;
		int sx, sy, ex, ey;
		cin >> sx >> sy;	// 상근위치
		total.push_back({ sx,sy });
		for (int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			total.push_back(make_pair(x, y));	// 편의점 위치
		}
		cin >> ex >> ey;	// 페스티벌위치
		total.push_back({ ex,ey });

		// 한번에 갈 수 있을지도 모르니 점검해보자
		if (abs(sx - ex) + abs(sy - ey) <= 1000) {
			cout << "happy" << '\n';
			total.clear();
			continue;
		}
		else {
			// 페스티벌까지 닿을 수 있는지 그래프를 만들고 결과를 리턴해보자
			flag = make_graph(0);
			if (flag) {
				cout << "happy" << '\n';
				initialize();
				continue;
			}
			else {
				cout << "sad" << '\n';
				initialize();
				continue;
			}
		}
	}

	return 0;
}