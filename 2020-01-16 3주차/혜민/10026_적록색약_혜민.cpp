//BOJ_10026_적록색약
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define MAX 101

int N;
char map[MAX][MAX];
vector <pair<int, int>> v;
vector <pair<int, int>> green;
bool visited[MAX][MAX];
int d[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char tmp = 'T';
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];

			if (tmp != map[i][j])//다른 알파벳이 나왔다
			{
				v.push_back(make_pair(i, j));
				tmp = map[i][j];
			}

			if(map[i][j] == 'G')
				green.push_back(make_pair(i, j));
		}
	}
}

int dfs(int r, int c)
{
	if (visited[r][c]) //첫타로 들어왔는데 이미 방문한 지점
		return 0;

	visited[r][c] = true;

	for (int i = 0; i < 4; i++)
	{
		int nr = r + d[i][0];
		int nc = c + d[i][1];

		if (nr < 0 || nc < 0 || nr >= N || nc >= N || visited[nr][nc])
			continue;

		if(map[r][c] == map[nr][nc]) //같은 색이면 탐색
			dfs(nr, nc);
	}

	return 1;
}

void solve()
{
	int part = 0;

	for (int i = 0; i < v.size(); i++)
		part += dfs(v[i].first, v[i].second);

	cout << part << " ";

	//적록색약 = 녹색을 다 적색으로
	for (int i = 0; i < green.size(); i++)
		map[green[i].first][green[i].second] = 'R';

	//초기화
	memset(visited, false, sizeof(visited));
	part = 0;

	for (int i = 0; i < v.size(); i++)
		part += dfs(v[i].first, v[i].second);

	cout << part << endl;
}

int main()
{
	input();
	solve();
}