// https://www.acmicpc.net/problem/8972
// 19�� �Ϲݱ� DS 2�� ������ �����

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x, y;
	bool alive;
}Info;

const int MAX = 100;
const int INF = 987654321;
int R, C;
bool finish;
char MAP[MAX][MAX];
vector<int> board[MAX][MAX];
vector<Info> crazy;
vector<int> cmd;
int sx, sy;

int dx[] = { 0,1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 0,-1,0,1,-1,0,1,-1,0,1 };

void show() {
	cout << "----------------------------" << '\n';
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << MAP[i][j];
		}
		cout << '\n';
	}
}

void solve() {
	for (int i = 0; i < cmd.size(); i++) {
		// ������ �̵�
		MAP[sx][sy] = '.';
		int dir = cmd[i];
		sx += dx[dir];
		sy += dy[dir];
		if (MAP[sx][sy] == 'R') {
			cout << "kraj " << i + 1;
			return;
		}
		MAP[sx][sy] = 'I';

		// ��ģ �Ƶ��̳��� �̵�
		for (int j = 0; j < crazy.size(); j++) {
			if (crazy[j].alive == false) continue;	// ���� �Ƶ��̳�� ����
			int x = crazy[j].x;
			int y = crazy[j].y;

			if (board[x][y].size() == 1) {
				MAP[x][y] = '.';
				board[x][y].clear();
			}
			else {
				int start = 0;
				for (start = 0; start < board[x][y].size(); start++) {
					if (board[x][y][start] == j) break;
				}
				board[x][y].erase(board[x][y].begin() + start);
			}

			// ���� ������ ��������� ���� ���ϱ�
			int idx = 0, mindist = INF;
			for (int k = 1; k <= 9; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
				int dist = abs(sx - nx) + abs(sy - ny);
				if (mindist > dist) {
					mindist = dist;
					idx = k;
				}
			}
			int nx = x + dx[idx];
			int ny = y + dy[idx];
			if (MAP[nx][ny] == 'I') {		// ��ģ �Ƶ��̳밡 �������� ������ ���� ����
				cout << "kraj " << i + 1;
				return;
			}
			MAP[nx][ny] = 'R';
			crazy[j].x = nx;
			crazy[j].y = ny;
			board[nx][ny].push_back(j);
		}

		// �ߺ��� �Ƶ��̳� ��Ʈ����
		for (int j = 0; j < crazy.size(); j++) {
			if (crazy[j].alive == false) continue;
			int x = crazy[j].x;
			int y = crazy[j].y;
			if (board[x][y].size() > 1) {		// �Ƶ��̳밡 2���̻� �����ִ�
				vector<int> temp;
				temp = board[x][y];
				board[x][y].clear();
				MAP[x][y] = '.';
				for (int k = 0; k < temp.size(); k++) {
					crazy[temp[k]].alive = false;
				}
			}
		}
		//show();
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << MAP[i][j];
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> R >> C;
	int cnt = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'R') {
				Info I;
				I.x = i;
				I.y = j;
				I.alive = true;
				crazy.push_back(I);
				board[I.x][I.y].push_back(cnt++);
			}
			else if (MAP[i][j] == 'I') {
				sx = i;
				sy = j;
			}
		}
	}
	string str;
	cin >> str;
	for (int i = 0; i < str.size(); i++) {
		cmd.push_back(str[i] - '0');
	}

	solve();
	return 0;
}