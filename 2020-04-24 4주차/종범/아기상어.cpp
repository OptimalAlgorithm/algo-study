// https://www.acmicpc.net/problem/16236

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x, y, size, cnt;
}Shark;

const int MAX = 20;
int N, ans;
int MAP[MAX][MAX];
bool visited[MAX][MAX]; 
vector<pair<int, pair<int, int>>> fish;
Shark S;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

// 잡아먹을 물고기 찾기
void find_fish() {
	typedef struct {
		int x, y, dist;
	}Info;
	queue<Info> q;
	q.push({ S.x,S.y,0 });
	visited[S.x][S.y] = true;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int dist = q.front().dist;
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[nx][ny]) continue;
			if (MAP[nx][ny] == S.size || MAP[nx][ny] == 0) {	// 크기가 같으면 이동만
				q.push({ nx,ny,dist + 1 });
				visited[nx][ny] = true;
			}
			else if(MAP[nx][ny] < S.size) {
				q.push({ nx,ny,dist + 1 });
				visited[nx][ny] = true;
				fish.push_back(make_pair(dist + 1, make_pair(nx, ny)));
			}
		}
	}
}

void solve() {
	while (true) {
		fish.clear();
		memset(visited, false, sizeof(visited));

		find_fish();
		if (fish.size() == 0) break;
		sort(fish.begin(), fish.end());

		// 상어정보 갱신
		int x = fish[0].second.first;
		int y = fish[0].second.second;
		int dist = fish[0].first;
		MAP[S.x][S.y] = 0;
		S.x = x;
		S.y = y;
		S.cnt++;
		MAP[S.x][S.y] = 9;
		ans += dist;

		if (S.cnt == S.size) {
			S.cnt = 0;
			S.size++;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 9) {
				S.cnt = 0;
				S.size = 2;
				S.x = i;
				S.y = j;
			}
		}
	}
	solve();
	return 0;
}