// https://www.acmicpc.net/problem/17837
// 19년 하반기 DS 2번

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x, y, dir;
}Dron;

const int MAX = 12;
int N, K;
int MAP[MAX][MAX];
vector<int> board[MAX][MAX];
vector<Dron> v;

int dx[] = { 0,0,0,-1,1 };
int dy[] = { 0,1,-1,0,0 };

void solve() {

	for (int turn = 1; turn <= 1000; turn++) {
		for (int i = 0; i < K; i++) {
			int x = v[i].x;
			int y = v[i].y;
			int dir = v[i].dir;

			int start = 0;
			vector<int> temp;
			
			// 옮기려는 말 위에 존재하는 모든 말까지 temp에 저장
			if (board[x][y][0] == i) {
				temp = board[x][y];
			}
			else {
				for (; start < board[x][y].size(); start++) {
					if (board[x][y][start] == i) break;
				}
				for (int j = start; j < board[x][y].size(); j++) {
					temp.push_back(board[x][y][j]);
				}
			}
			
			int nx = x + dx[dir];
			int ny = y + dy[dir];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N || MAP[nx][ny] == 2) {	// 범위 밖이나 파란색을 만났을 때
				if (dir == 1 || dir == 3) dir++;
				else dir--;
				v[i].dir = dir;

				int nnx = x + dx[dir];
				int nny = y + dy[dir];

				if (!(nnx < 0 || nnx >= N || nny < 0 || nny >= N || MAP[nnx][nny] == 2)) {		// 범위 밖이나 파란색이 아니라면!
					if (MAP[nnx][nny] == 1)			// 빨강으로 왔을때, 순서 뒤집어 줘야함
						reverse(temp.begin(), temp.end());

					board[x][y].erase(board[x][y].begin() + start, board[x][y].end());		// 이전 위치 갱신

					for (int k = 0; k < temp.size(); k++) {
						v[temp[k]].x = nnx;
						v[temp[k]].y = nny;
						board[nnx][nny].push_back(temp[k]);
					}
					if (board[nnx][nny].size() >= 4) {		// 옮기고 나서 그 좌표에 말이 4개 이상 존재하면 turn 출력후 종료
						cout << turn << '\n';
						return;
					}
				}
			}
			else if (MAP[nx][ny] == 0) {		// 흰색
				board[x][y].erase(board[x][y].begin() + start, board[x][y].end());		// 이전 위치 갱신

				for (int k = 0; k < temp.size(); k++) {
					v[temp[k]].x = nx;
					v[temp[k]].y = ny;
					board[nx][ny].push_back(temp[k]);
				}
				if (board[nx][ny].size() >= 4) {
					cout << turn << '\n';
					return;
				}
			}
			else if (MAP[nx][ny] == 1) {		// 빨강
				reverse(temp.begin(), temp.end());
				board[x][y].erase(board[x][y].begin() + start, board[x][y].end());		// 이전 위치 갱신

				for (int k = 0; k < temp.size(); k++) {
					v[temp[k]].x = nx;
					v[temp[k]].y = ny;
					board[nx][ny].push_back(temp[k]);
				}
				if (board[nx][ny].size() >= 4) {
					cout << turn << '\n';
					return;
				}
			}
		}
	}
	cout << -1 << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		int x, y, dir;
		cin >> x >> y >> dir;
		x -= 1; y -= 1;
		v.push_back({ x,y,dir });
		board[x][y].push_back(i);
	}
	solve();
	return 0;
}