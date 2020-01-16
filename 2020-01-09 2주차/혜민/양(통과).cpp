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

			if (map[i][j] == 'v') //����
				allWolf.push_back(make_pair(i, j));
			else if (map[i][j] == 'o') //��
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

		if (nr < 0 || nc < 0 || nr >= R || nc >= C || visited[nr][nc]) //���� ���
			continue;

		visited[nr][nc] = true;

		if (map[nr][nc] == '#') //��Ÿ��
			continue;
		else if (map[nr][nc] == 'o') //��
			sheep.push_back(make_pair(nr, nc));
		else if (map[nr][nc] == 'v') //����
			wolf.push_back(make_pair(nr, nc));

		dfs(nr, nc);
	}
}

void solve()
{
	for (int i = 0; i < allWolf.size(); i++)
	{
		if (map[allWolf[i].first][allWolf[i].second] == '.') //�̹� ���簡 ����
			continue;

		//�ʱ�ȭ
		wolf.clear();
		sheep.clear();

		//��������
		wolf.push_back(make_pair(allWolf[i].first, allWolf[i].second));
		dfs(allWolf[i].first, allWolf[i].second);

		//�� vs ����
		if (wolf.size() >= sheep.size()) //�� lose
		{
			for (int j = 0; j < sheep.size(); j++) //���� ��Ƹ�����
				map[sheep[j].first][sheep[j].second] = '.';
			sheepCnt -= sheep.size();
		}
		else //�� win
			wolfCnt -= wolf.size();

		for (int j = 0; j < wolf.size(); j++) //���� �����
			map[wolf[j].first][wolf[j].second] = '.';
	}
}
int main()
{
	input();
	solve();
	cout << sheepCnt << " " << wolfCnt << endl;
}