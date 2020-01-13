// https://www.acmicpc.net/problem/3987

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAX = 500;
int N, M, PR, PC;
bool infinite;	// 무한으로 전파되는지 판별하기 위함
char MAP[MAX][MAX];

// 0:L, 1:D, 2:R, 3:U
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
char direct[] = { 'L', 'D', 'R', 'U' };

vector<pair<int, int>> ans;

void bfs(int dir) {
	queue<pair<pair<int, int>, pair<int, int>>> q;		// 전파의 현재 x,y 좌표, 이동거리, 방향
	q.push(make_pair(make_pair(PR, PC), make_pair(1, dir)));

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int cnt = q.front().second.first;
		int cur_dir = q.front().second.second;
		q.pop();

		int nx = x + dx[cur_dir];
		int ny = y + dy[cur_dir];

		if (nx < 0 || nx >= N || ny < 0 || ny >= M || MAP[nx][ny] == 'C') {	// 범위 밖, 블랙홀
			ans.push_back(make_pair(cnt, dir));
			return;
		}
		else if (MAP[nx][ny] == 'S') {	// 제자리
			if (dir == cur_dir) {	// 방향이 처음과 같다면 무한히 전파됨
				infinite = true;
				return;
			}
			else	// 처음과 같지 않다면 그냥 지나간다.
				q.push(make_pair(make_pair(nx, ny), make_pair(cnt + 1, cur_dir)));
		}
		else if (MAP[nx][ny] == '.') {	// 빈칸
			q.push(make_pair(make_pair(nx, ny), make_pair(cnt + 1, cur_dir)));
		}
		else if (MAP[nx][ny] == '\\'){	// \ 행성
			if (cur_dir == 0) cur_dir = 3;
			else if (cur_dir == 1) cur_dir = 2;
			else if (cur_dir == 2) cur_dir = 1;
			else if (cur_dir == 3) cur_dir = 0;
			q.push(make_pair(make_pair(nx, ny), make_pair(cnt + 1, cur_dir)));
		}
		else if (MAP[nx][ny] == '/') { // / 행성
			if (cur_dir == 0) cur_dir = 1;
			else if (cur_dir == 1) cur_dir = 0;
			else if (cur_dir == 2) cur_dir = 3;
			else if (cur_dir == 3) cur_dir = 2;
			q.push(make_pair(make_pair(nx, ny), make_pair(cnt + 1, cur_dir)));
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) 
			cin >> MAP[i][j];
		
	cin >> PR >> PC;
	PR -= 1; PC -= 1;
	MAP[PR][PC] = 'S';		// 보이저 1호의 시작 위치를 S로 변경

	for (int k = 3; k >= 0; k--) {
		bfs(k);

		if (infinite) {
			cout << direct[k] << '\n' << "Voyager" << '\n';
			return 0;
		}
	}

	sort(ans.begin(), ans.end());
	int index = ans.size() - 1;
	cout << direct[ans[index].second] << '\n' << ans[index].first << '\n';

	return 0;
}
