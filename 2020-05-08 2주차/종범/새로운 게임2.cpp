// https://www.acmicpc.net/problem/17837
// 19�� �Ϲݱ� DS 2��

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
			
			// �ű���� �� ���� �����ϴ� ��� ������ temp�� ����
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

			if (nx < 0 || nx >= N || ny < 0 || ny >= N || MAP[nx][ny] == 2) {	// ���� ���̳� �Ķ����� ������ ��
				if (dir == 1 || dir == 3) dir++;
				else dir--;
				v[i].dir = dir;

				int nnx = x + dx[dir];
				int nny = y + dy[dir];

				if (!(nnx < 0 || nnx >= N || nny < 0 || nny >= N || MAP[nnx][nny] == 2)) {		// ���� ���̳� �Ķ����� �ƴ϶��!
					if (MAP[nnx][nny] == 1)			// �������� ������, ���� ������ �����
						reverse(temp.begin(), temp.end());

					board[x][y].erase(board[x][y].begin() + start, board[x][y].end());		// ���� ��ġ ����

					for (int k = 0; k < temp.size(); k++) {
						v[temp[k]].x = nnx;
						v[temp[k]].y = nny;
						board[nnx][nny].push_back(temp[k]);
					}
					if (board[nnx][nny].size() >= 4) {		// �ű�� ���� �� ��ǥ�� ���� 4�� �̻� �����ϸ� turn ����� ����
						cout << turn << '\n';
						return;
					}
				}
			}
			else if (MAP[nx][ny] == 0) {		// ���
				board[x][y].erase(board[x][y].begin() + start, board[x][y].end());		// ���� ��ġ ����

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
			else if (MAP[nx][ny] == 1) {		// ����
				reverse(temp.begin(), temp.end());
				board[x][y].erase(board[x][y].begin() + start, board[x][y].end());		// ���� ��ġ ����

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