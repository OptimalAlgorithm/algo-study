#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
//#define DEBUG
#define MAX 64
#define MAXSPELL 1000

int N, Q;
int grid[MAX][MAX];
int gridsize = 0;
int L[MAXSPELL];

bool visited[MAX][MAX];
queue <pair<int, int>> ice;
vector <pair<int, int>> decrease;
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

int maxIceSize = 0;
int total = 0;

int find_cluster(int i, int j) //덩어리 찾기
{
	int r, c, nr, nc;
	int icesize = 0;

	ice.push(make_pair(i, j));
	visited[i][j] = true;

	while (!ice.empty())
	{
		r = ice.front().first;
		c = ice.front().second;
		icesize++;
		ice.pop();

		for (int d = 0; d < 4; d++)
		{
			nr = r + dir[d][0];
			nc = c + dir[d][1];

			if (nr < 0 || nc < 0 || nr >= gridsize || nc >= gridsize || visited[nr][nc]) ///범위 벗어났거나 이미 방문
				continue;

			if (grid[nr][nc] <= 0) //얼음 없음
				continue;

			ice.push(make_pair(nr, nc));
			visited[nr][nc] = true;
		}
	}

	return icesize;
}

void check(int r, int c) //줄어들 얼음이 있는지 조사
{
	int nr, nc;
	int icesize = 0;

	for (int d = 0; d < 4; d++)
	{
		nr = r + dir[d][0];
		nc = c + dir[d][1];

		if (nr < 0 || nc < 0 || nr >= gridsize || nc >= gridsize) //범위 벗어났음
			continue;

		if (grid[nr][nc] <= 0) //얼음 없음
			continue;

		icesize++;
	}

	if (icesize < 3) //인접 얼음이 3개 미만
		decrease.push_back(make_pair(r, c));
}

void solve()
{
	int tmp[MAX][MAX];
	int Lsize = 0;
	int icesize = 0;

	for (int q = 0; q < Q; q++) //마법 횟수만큼
	{
		//1.회전
		Lsize = pow(2, L[q]);
		for (int i = 0; i < gridsize; i += Lsize)
		{
			for (int j = 0; j < gridsize; j += Lsize)
			{
				for (int c = j; c < j + Lsize; c++)
				{
					for (int r = i + Lsize - 1; r >= i; r--)
						tmp[c - j + i][j + i + Lsize - 1 - r] = grid[r][c];
				}
			}
		}
		swap(tmp, grid);

		//2.얼음 양 감소
		decrease.clear();
		for (int i = 0; i < gridsize; i++)
		{
			for (int j = 0; j < gridsize; j++)
				check(i, j);
		}

		for (int i = 0; i < decrease.size(); i++)
			grid[decrease[i].first][decrease[i].second]--; //얼음의 양이 1 줄어든다
	}

	//결과값 계산
	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
		{
			if (grid[i][j] > 0)
			{
				total += grid[i][j];

				if (!visited[i][j])
				{
					icesize = find_cluster(i, j);
					maxIceSize = maxIceSize > icesize ? maxIceSize : icesize; //max값 찾기
				}
			}
		}
	}
}

int main()
{
	//input
	cin >> N >> Q;
	gridsize = pow(2, N);
	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
			cin >> grid[i][j];
	}
	for (int i = 0; i < Q; i++)
		cin >> L[i];

	solve();

	//output
	cout << total << endl;
	cout << maxIceSize << endl;
}