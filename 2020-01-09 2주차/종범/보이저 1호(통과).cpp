// https://www.acmicpc.net/problem/3987

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAX = 500;
int N, M, PR, PC;
bool infinite;	// �������� ���ĵǴ��� �Ǻ��ϱ� ����
char MAP[MAX][MAX];

// 0:L, 1:D, 2:R, 3:U
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
char direct[] = { 'L', 'D', 'R', 'U' };

vector<pair<int, int>> ans;

void bfs(int dir) {
	queue<pair<pair<int, int>, pair<int, int>>> q;		// ������ ���� x,y ��ǥ, �̵��Ÿ�, ����
	q.push(make_pair(make_pair(PR, PC), make_pair(1, dir)));

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int cnt = q.front().second.first;
		int cur_dir = q.front().second.second;
		q.pop();

		int nx = x + dx[cur_dir];
		int ny = y + dy[cur_dir];

		if (nx < 0 || nx >= N || ny < 0 || ny >= M || MAP[nx][ny] == 'C') {	// ���� ��, ��Ȧ
			ans.push_back(make_pair(cnt, dir));
			return;
		}
		else if (MAP[nx][ny] == 'S') {	// ���ڸ�
			if (dir == cur_dir) {	// ������ ó���� ���ٸ� ������ ���ĵ�
				infinite = true;
				return;
			}
			else	// ó���� ���� �ʴٸ� �׳� ��������.
				q.push(make_pair(make_pair(nx, ny), make_pair(cnt + 1, cur_dir)));
		}
		else if (MAP[nx][ny] == '.') {	// ��ĭ
			q.push(make_pair(make_pair(nx, ny), make_pair(cnt + 1, cur_dir)));
		}
		else if (MAP[nx][ny] == '\\'){	// \ �༺
			if (cur_dir == 0) cur_dir = 3;
			else if (cur_dir == 1) cur_dir = 2;
			else if (cur_dir == 2) cur_dir = 1;
			else if (cur_dir == 3) cur_dir = 0;
			q.push(make_pair(make_pair(nx, ny), make_pair(cnt + 1, cur_dir)));
		}
		else if (MAP[nx][ny] == '/') { // / �༺
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
	MAP[PR][PC] = 'S';		// ������ 1ȣ�� ���� ��ġ�� S�� ����

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
