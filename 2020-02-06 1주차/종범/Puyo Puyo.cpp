// https://www.acmicpc.net/problem/11559
// 현 보드판 상황에서 서로 다른색 1개 이상의 연쇄가 일어났더라도 횟수는 + 1임


#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 12, M = 6;
int ans;
char MAP[N][M];
bool check[N][M];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void show_map() {
	cout << "-------------------------" << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << MAP[i][j];
		}
		cout << '\n';
	}
}

// 연쇄작용한 뿌요 맵 변경
void change_MAP() {
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) 
			if (check[i][j]) MAP[i][j] = '.';
}

// 뿌요 내리기
void puyo_down(int x, int y) {
	char color = MAP[x][y];
	MAP[x][y] = '.';

	int nx = x + dx[2];	// 아래로 내리기
	while (true) {
		if (nx >= N || MAP[nx][y] != '.') {
			nx -= dx[2];
			break;
		}
		nx += dx[2];
	}
	MAP[nx][y] = color;
}

int bfs(int i, int j, char color) {
	queue<pair<int, int>> q;
	q.push(make_pair(i, j));
	check[i][j] = true;
	int cnt = 1;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M || check[nx][ny]) continue;
			if (MAP[nx][ny] == color) {
				q.push(make_pair(nx, ny));
				cnt += 1;
				check[nx][ny] = true;
			}
		}
	}
	return cnt;
}

void simulation() {
	bool flag = false;
	
	while (true) {
		flag = false;

		// 연쇄될게 있는지 찾아보자
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] != '.') {
					int ret = bfs(i, j, MAP[i][j]);
					if (ret >= 4) {
						flag = true;	// 연쇄가 일어났다
						change_MAP();	// 연쇄가 작용했다면 맵 빈칸으로 변경
					}
					memset(check, false, sizeof(check));
				}
			}
		}

		//show_map();
		
		// 연쇄가 일어났으면 횟수 + 1
		if (flag) ans++;

		// 연쇄가 더이상 없다면
		if (!flag) {		
			cout << ans << '\n';
			break;
		}

		// 공중에 있는 뿌요를 아래로 내리기
		for (int j = 0; j < M; j++) {
			for (int i = N - 1; i >= 0; i--) {
				if (MAP[i][j] != '.') {
					puyo_down(i, j);
				}
			}
		}

		//show_map();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	simulation();
	return 0;
}