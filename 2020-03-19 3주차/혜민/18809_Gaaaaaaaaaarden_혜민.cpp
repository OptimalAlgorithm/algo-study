#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//#define DEBUG
#define MAX 51

int N, M, G, R;
int map[MAX][MAX];
vector <pair<int, int>> ground;
int rslt = 0;

vector <int> red;
vector <int> green;
bool redCheck[10];

queue <pair<int, int>> redQ, greenQ;
int visited[MAX][MAX] = { 0, };
int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

void bfs()
{
	int flower = 0;
	int time = 3;
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < red.size(); i++) //빨간 배양액 위치
	{
		redQ.push(make_pair(ground[red[i]].first, ground[red[i]].second));
		visited[ground[red[i]].first][ground[red[i]].second] = 1;
	}
	for (int i = 0; i < green.size(); i++) //초록 배양액 위치
	{
		greenQ.push(make_pair(ground[green[i]].first, ground[green[i]].second));
		visited[ground[green[i]].first][ground[green[i]].second] = 2;
	}

	while (true) //1초에 한칸씩
	{
		queue <pair<int, int>> rnq, gnq;

		while (!redQ.empty())
		{
			int r = redQ.front().first;
			int c = redQ.front().second;
			redQ.pop();

			if (visited[r][c] % 2 == 0)//빨간 배양액 위치의 방문표시를 봤는데, 초록 배양액 방문 표시가 있다 = 꽃이 핀 자리 = 더 이상 퍼지지 않는다.
				continue;

			for (int i = 0; i < 4; i++)
			{
				int nr = r + dir[i][0];
				int nc = c + dir[i][1];

				if (nr < 0 || nc < 0 || nr >= N || nc >= M || visited[nr][nc] > 0 || map[nr][nc] == 0) //범위 벗어남 or 이미 방문 or 호수
					continue;

				rnq.push(make_pair(nr, nc));
				visited[nr][nc] = time;
			}
		}

		while (!greenQ.empty())
		{
			int r = greenQ.front().first;
			int c = greenQ.front().second;
			greenQ.pop();

			for (int i = 0; i < 4; i++)
			{
				int nr = r + dir[i][0];
				int nc = c + dir[i][1];

				if (nr < 0 || nc < 0 || nr >= N || nc >= M || map[nr][nc] == 0) //범위 벗어남, 호수
					continue;

				if (visited[nr][nc] == 0) //한 번도 방문 x
				{
					gnq.push(make_pair(nr, nc));
					visited[nr][nc] = time + 1;
				}
				else if (visited[nr][nc] == time) //이번 회차에 red가 방문
				{
					flower++;
					visited[nr][nc] = time + 1; //꽃이 핀 자리
				}
				else //지난회차들 or 이번 회차에 green이 이미 방문.
					continue;
			}
		}

		if (rnq.empty() || gnq.empty()) //둘 중에 하나라도 퍼질 수 없으면 더 이상 꽃이 피지 않는다.
			break;

		swap(redQ, rnq);
		swap(greenQ, gnq);
		time += 2;
	}

	rslt = rslt > flower ? rslt : flower;
}

void pick_green(int cnt) //green 자리 뽑기(조합)
{
	if (green.size() == G)
	{
		bfs();
		return;
	}

	for (int i = cnt; i < ground.size(); i++)
	{
		if (!redCheck[i]) //red자리가 아니면 = 빈자리
		{
			green.push_back(i);
			pick_green(i + 1);
			green.pop_back();
		}
	}
}

void pick_red(int cnt) //red 자리 뽑기(조합)
{
	if (red.size() == R)
	{
		pick_green(0);
		return;
	}

	for (int i = cnt; i < ground.size(); i++)
	{
		red.push_back(i);
		redCheck[i] = true; //red자리는 체크해줘야 green에서 안 뽑는다.
		pick_red(i + 1);
		red.pop_back();
		redCheck[i] = false;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> N >> M >> G >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 2) //배양액 뿌릴 수 있는 땅
				ground.push_back(make_pair(i, j));
		}
	}

	//solve
	pick_red(0);

	//output
	cout << rslt << endl;
}
