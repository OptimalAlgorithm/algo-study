//BOJ_7576_토마토
#include <iostream>
#include <queue>
using namespace std;
#define MAX 1001

int N, M;
int map[MAX][MAX];
queue <pair<int, int>> q;
bool visited[MAX][MAX];
int d[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
int day = 0;
int notripen = 0;

void input()
{
	bool flag = true;

	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 0)//안 익은 토마토
				notripen++;
			else if (map[i][j] == 1)//익은 토마토
			{
				q.push(make_pair(i, j));
				visited[i][j] = true;
			}
		}
	}
}

void bfs()
{
	while (true)
	{
		queue <pair<int, int>> tmpQ;

		while (!q.empty())
		{
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int nr = r + d[i][0];
				int nc = c + d[i][1];

				if (nr < 0 || nc < 0 || nr >= N || nc >= M || visited[nr][nc])
					continue;

				if (map[nr][nc] == 0) //안익은 토마토
				{
					map[nr][nc] = 1; //익은 토마토로 변신!
					notripen--;
					tmpQ.push(make_pair(nr, nc)); //일단 tmp queue에 저장
					visited[nr][nc] = true;
				}
			}
		}

		if (tmpQ.empty()) //더이상 익게 만들 토마토가 없음...
		{
			if (notripen > 0) //토마토가 모두 익지는 못하는 상황
				day = -1;

			break;
		}

		while (!tmpQ.empty()) //원래 큐에 넣기
		{
			q.push(tmpQ.front());
			tmpQ.pop();
		}

		day++; //하루 지났다.
	}
}

int main()
{
	input();

	if (notripen == 0)//안 익은 토마토가 없음 = 모든 토마토가 익었다
	{
		cout << "0" << endl;
		return 0;
	}

	bfs();
	cout << day << endl;
}