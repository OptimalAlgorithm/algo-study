// https://www.acmicpc.net/problem/2933
// ����

#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAX = 100;
const int INF = 987654321;
int R, C, N;
bool flag;
char MAP[MAX][MAX];
bool check[MAX][MAX];
bool mineral[MAX][MAX];		// ���߿� ���ִ� �̳׶����� �Ʒ��� �������� ������ �������� �迭

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

vector<int> cmd;
vector<pair<int, int>> v;	// ���߿� ���ִ� Ŭ�����͵��� ��ǥ�� ��� ����

// â ������
void throw_spear(int H, char side) {
	if (side == 'L') {
		for (int j = 0; j < C; j++) {
			if (MAP[H][j] == 'x') {
				MAP[H][j] = '.';
				break;
			}
		}
	}
	else {
		for (int j = C - 1; j >= 0; j--) {
			if (MAP[H][j] == 'x') {
				MAP[H][j] = '.';
				break;
			}
		}
	}
}

// Ŭ������ ���� Ȯ��
void bfs(int sx, int sy) {
	queue<pair<int, int>> q;
	q.push({ sx,sy });
	check[sx][sy] = true;

	while (q.empty() == 0) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];

			if (nx < 0 || nx >= R || ny < 0 || ny >= C || check[nx][ny]) continue;
			if (MAP[nx][ny] == 'x') {
				q.push({ nx,ny });
				check[nx][ny] = true;
			}
		}
	}
}

// ���߿� ���ִ� �̳׶� ó��
void air_cluster() {
	flag = false;
	// �Ʒ����� ���� �ö󰡴� ����� Ž��
	for (int j = 0; j < C; j++) {
		if (MAP[R - 1][j] == 'x' && !check[R - 1][j]) {
			bfs(R - 1, j);
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == 'x' && !check[i][j]) {		// ���߿� ���ִ� �̳׶���
				flag = true;
				v.push_back(make_pair(i, j));
				mineral[i][j] = true;
			}
		}
	}

	if (!flag) return;	// ���߿� ���ִ� �̳׶��� ������ �Լ� ����
	else {				// ������ ��������..
		int gap = INF;
		for (int idx = 0; idx < v.size(); idx++) {
			int x = v[idx].first;
			int y = v[idx].second;
			int cnt = 0;

			// ������� �ڵ�
			for (int i = x + 1; i < R; i++) {
				if (MAP[i][y] == '.') cnt++;
				else if (MAP[i][y] == 'x') {
					if (mineral[i][y]) {
						cnt = INF;
						break;
					}
					else break;
				}
			}
			gap = min(gap, cnt);
		}

		// ���� �Ʒ��κ� ���� ��������
		for (int i = v.size() - 1; i >= 0; i--) {
			MAP[v[i].first][v[i].second] = '.';
			MAP[v[i].first + gap][v[i].second] = 'x';
		}
	}
}

void solution() {
	for (int i = 0; i < cmd.size(); i++) {
		int H = cmd[i];
		H = R - H;
		char side = (i % 2) == 0 ? 'L' : 'R';	// 0,2,4.. ���� 1,3,5.. ������

		throw_spear(H, side);
		air_cluster();

		memset(check, false, sizeof(check));
		memset(mineral, false, sizeof(mineral));
		v.clear();
	}
}

void Print() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << MAP[i][j];
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
		}
	}
	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		cmd.push_back(num);
	}

	solution();
	Print();
	return 0;
}