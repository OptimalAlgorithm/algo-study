#include <iostream>
#include <queue>
using namespace std;
#define MAX 1001

int R, C;
char map[MAX][MAX];
queue <pair<int, int>> q; //지훈
queue <pair<int, int>> fire; //불
int visited[MAX][MAX] = { 0, };
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
int ans = MAX*MAX*MAX;

void spread_fire()
{
	int r, c, nr, nc;
	queue <pair<int, int>> nf;

	while (!fire.empty())
	{
		r = fire.front().first;
		c = fire.front().second;
		fire.pop();

		for (int i = 0; i < 4; i++)
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= R || nc >= C || map[nr][nc] == '#') //범위 벗어남 or 방문
				continue;

			map[nr][nc] = '#';
			nf.push(make_pair(nr, nc)); //다음 턴의 불을 저장
		}
	}

	swap(fire, nf); //다음 턴과 교환
}

void solve()
{
	int r = q.front().first, c = q.front().second, nr, nc;
	int time = 0;

	if (r == 0 || c == 0 || r == R - 1 || c == C - 1) //처음부터 지훈이가 가장자리에 있는 경우.
	{
		ans = 1;
		return;
	}

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		if (time < visited[r][c]) //불이퍼져야 할 시간.
		{
			spread_fire();
			time++;
		}

		for (int i = 0; i < 4; i++)
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= R || nc >= C || visited[nr][nc] > 0 || map[nr][nc] == '#') //범위 벗어남 or 방문 or 벽
				continue;

			if (nr == 0 || nc == 0 || nr == R - 1 || nc == C - 1) //가장자리에 도달한 경우
			{
				ans = visited[r][c] + 1;
				return;
			}

			q.push(make_pair(nr, nc));
			visited[nr][nc] = visited[r][c] + 1;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> R >> C;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'J')
			{
				q.push(make_pair(i, j));
				visited[i][j] = 1;
			}
			if (map[i][j] == 'F')
			{
				fire.push(make_pair(i, j));
				map[i][j] = '#'; //어차피 지훈이는 불과 벽을 지나가지 못하니까 불을 벽으로 바꿔준다.
			}
		}
	}

	solve();

	//output
	if (ans == MAX * MAX * MAX)
		cout << "IMPOSSIBLE" << endl;
	else
		cout << ans << endl;
}