#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
#define MAX 1501

int R, C;
char map[MAX][MAX];
vector <pair <int, int>> swan;
queue <pair<int, int>> water;
int days[MAX][MAX] = { 0, }; //해당 위치의 얼음이 녹는 시간을 저장
bool visited[MAX][MAX];
int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
int ans = 1; //결과값
int maxdays = 0; //모든 얼음이 녹기까지 걸리는 시간
int mid; //이분 탐색에서의 중간값

void bfs()
{
	int r, c, nr, nc;

	while (!water.empty()) //얼음의 가장자리는 1로 설정. 가장자리부터 bfs를 돌면서 녹을 때까지 걸리는 시간을 구한다.
	{
		r = water.front().first;
		c = water.front().second;
		water.pop();

		for (int i = 0; i < 4; i++)
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= R || nc >= C)
				continue;

			if (map[nr][nc] == 'X' && (days[nr][nc] == 0 || days[r][c] + 1 < days[nr][nc])) //얼음이고, (아직 방문 안한 지점 or 갱신해야 하는 지점)
			{
				water.push(make_pair(nr, nc));
				days[nr][nc] = days[r][c] + 1;
				maxdays = maxdays > days[nr][nc] ? maxdays : days[nr][nc]; //모든 얼음이 녹는 시간이 언제인지도 구한다.
			}
		}
	}
}

bool dfs(int r, int c)
{
	int nr, nc;

	for (int i = 0; i < 4; i++)
	{
		nr = r + dir[i][0];
		nc = c + dir[i][1];

		if (nr < 0 || nc < 0 || nr >= R || nc >= C || visited[nr][nc])
			continue;

		if (swan[1].first == nr && swan[1].second == nc) //백조끼리 만났다.
			return true;

		if (days[nr][nc] <= mid)
		{
			visited[nr][nc] = true;
			if (dfs(nr, nc))
				return true;
		}
	}

	return false; //만날 수 없다.
}

void solve()
{
	bfs(); //얼음이 녹는데 걸리는 시간을 구한다.

	while (ans < maxdays) //이분 탐색으로 최솟값을 찾아나간다.
	{
		mid = ans + (maxdays - ans) / 2;

		memset(visited, false, sizeof(visited)); //초기화
		visited[swan[0].first][swan[0].second] = true;

		if (dfs(swan[0].first, swan[0].second)) //dfs를 돌려서 백조끼리 만날 수 있는지 검사
			maxdays = mid; //mid 시간에서 만날 수 있다면, 이것보다 더 작은 시간에서도 만날 수 있는지 다시 본다.
		else
			ans = mid + 1; //mid 시간에서 만날 수 없다면, 이것보다 더 큰 시간에서 만날 것이다.
	}

	ans--; //처음 얼음이 녹는 시간을 구할 때 1부터 시작했기 때문에 -1을 해준다.
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	char tmp;
	cin >> R >> C;
	for (int i = 0; i < R; i++)
	{
		tmp = 'A';
		for (int j = 0; j < C; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 'L') //백조
			{
				swan.push_back(make_pair(i, j));
				map[i][j] = '.';
			}

			if (tmp == '.' && map[i][j] == 'X' && j > 0 && !days[i][j - 1]) //얼음의 가장자리
			{
				water.push(make_pair(i, j - 1));
				days[i][j - 1] = true;
			}
			else if (tmp == 'X' && map[i][j] == '.' && !days[i][j])
			{
				water.push(make_pair(i, j));
				days[i][j] = true;
			}

			tmp = map[i][j];
		}
	}

	for (int j = 0; j < C; j++) //세로로도 돌면서 얼음의 가장자리를 찾는다
	{
		tmp = 'A';
		for (int i = 0; i < R; i++)
		{
			if (tmp == '.' && map[i][j] == 'X' && i > 0 && !days[i - 1][j])
			{
				water.push(make_pair(i - 1, j));
				days[i - 1][j] = true;
			}
			else if (tmp == 'X' && map[i][j] == '.' && !days[i][j])
			{
				water.push(make_pair(i, j));
				days[i][j] = true;
			}
			tmp = map[i][j];
		}
	}

	solve();

	//output
	cout << ans << endl;
}