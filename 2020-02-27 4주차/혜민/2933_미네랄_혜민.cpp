#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX 101

int R, C, N;
char grid[MAX][MAX];
int stick[MAX];

vector <pair<int, int>> cluster;
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
bool visited[MAX][MAX];

bool bfs(int x, int y) //클러스터를 찾는다.
{
	queue <pair<int, int>> q;
	int r, c, nr, nc;
	bool flag = true; //디폴트는 공중에 떠 있는 것.

	cluster.clear(); //초기화

	q.push(make_pair(x, y));
	visited[x][y] = true;

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		cluster.push_back(make_pair(r, c));
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 1 || nc < 1 || nr > R || nc > C || grid[nr][nc] == '.' || visited[nr][nc])
				continue;

			if (nr <= 1) //바닥에 도달
				flag = false;

			q.push(make_pair(nr, nc));
			visited[nr][nc] = true;
		}
	}

	return flag;
}

void gravity() //중력작용
{
	int r, c;
	bool flag = true;
	memset(visited, false, sizeof(visited));
	sort(cluster.begin(), cluster.end()); //제일 밑에 있는 미네랄부터 내려야 한다..

	while (flag)
	{
		for (int i = 0; i < cluster.size(); i++)
		{
			r = cluster[i].first;
			c = cluster[i].second;
			grid[r][c] = '.';
			grid[r - 1][c] = 'x';
			visited[r - 1][c] = true;
			cluster[i].first--; 

			if (r - 1 == 1 || (visited[r - 2][c] == false && grid[r - 2][c] == 'x')) //이번 단계에 바닥에 도달했거나, 다른 클러스터 위로 떨어졌다 = 더이상 내려갈 수 없다
				flag = false;
		}
	}
}

void break_mineral(int r, int c) //미네랄 깨기
{
	int nr, nc;

	grid[r][c] = '.';
	memset(visited, false, sizeof(visited));

	for (int i = 0; i < 4; i++) //깨진 미네랄을 기준으로 사방을 조사
	{
		nr = r + dir[i][0];
		nc = c + dir[i][1];

		if (nr < 1 || nc < 1 || nr > R || nc > C || grid[nr][nc] == '.' || visited[nr][nc])
			continue;

		if (bfs(nr, nc)) //아직 방문 안 한 x를 기준으로, 해당 클러스터가 공중에 떠 있는지?
			gravity(); //공중에 떠 있으면 중력 작용
	}
}

void solve()
{
	int r, c;

	for (int s = 0; s < N; s++) //막대를 던진 횟수만큼
	{
		r = stick[s];//높이
		if (s % 2 == 0) //창영(왼쪽)
		{
			for (c = 1; c <= C; c++) //막대 던지기
			{
				if (grid[r][c] == 'x') //미네랄을 만나면
				{
					break_mineral(r, c); //미네랄 깨기
					break;
				}
			}
		}
		else //상근(오른쪽)
		{
			for (c = C; c >= 1; c--) //막대 던지기
			{
				if (grid[r][c] == 'x') //미네랄을 만나면
				{
					break_mineral(r, c); //미네랄 깨기
					break;
				}
			}
		}

		/*
		for (int i = R; i >= 1; i--)
		{
			for (int j = 1; j <= C; j++)
				cout << grid[i][j];
			cout << endl;
		}
		cout << endl;
		*/
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> R >> C;
	for (int i = R; i >= 1; i--)
	{
		for (int j = 1; j <= C; j++)
			cin >> grid[i][j];
	}
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> stick[i];

	solve();

	//output
	for (int i = R; i >= 1; i--)
	{
		for (int j = 1; j <= C; j++)
			cout << grid[i][j];
		cout << endl;
	}
}