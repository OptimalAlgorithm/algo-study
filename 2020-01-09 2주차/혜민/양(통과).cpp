#include <iostream>
#include <vector>
using namespace std;

int R, C;
char map[251][251];
bool visited[251][251];
int dir[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
vector <pair<int, int>> allWolf;
vector <pair<int, int>> sheep;
vector <pair<int, int>> wolf;
int sheepCnt = 0;
int wolfCnt = 0;

void input()
{
	cin >> R >> C;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 'v') //늑대
				allWolf.push_back(make_pair(i, j));
			else if (map[i][j] == 'o') //양
				sheepCnt++;
		}
	}
	wolfCnt = allWolf.size();
}

void dfs(int r, int c)
{
	visited[r][c] = true;

	for (int i = 0; i < 4; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];

		if (nr < 0 || nc < 0 || nr >= R || nc >= C || visited[nr][nc]) //범위 벗어남
			continue;

		visited[nr][nc] = true;

		if (map[nr][nc] == '#') //울타리
			continue;
		else if (map[nr][nc] == 'o') //양
			sheep.push_back(make_pair(nr, nc));
		else if (map[nr][nc] == 'v') //늑대
			wolf.push_back(make_pair(nr, nc));

		dfs(nr, nc);
	}
}

void solve()
{
	for (int i = 0; i < allWolf.size(); i++)
	{
		if (map[allWolf[i].first][allWolf[i].second] == '.') //이미 조사가 끝남
			continue;

		//초기화
		wolf.clear();
		sheep.clear();

		//영역조사
		wolf.push_back(make_pair(allWolf[i].first, allWolf[i].second));
		dfs(allWolf[i].first, allWolf[i].second);

		//양 vs 늑대
		if (wolf.size() >= sheep.size()) //양 lose
		{
			for (int j = 0; j < sheep.size(); j++) //양이 잡아먹혔다
				map[sheep[j].first][sheep[j].second] = '.';
			sheepCnt -= sheep.size();
		}
		else //양 win
			wolfCnt -= wolf.size();

		for (int j = 0; j < wolf.size(); j++) //늑대 지우기
			map[wolf[j].first][wolf[j].second] = '.';
	}
}
int main()
{
	input();
	solve();
	cout << sheepCnt << " " << wolfCnt << endl;
}