#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX 51

int T, M, N;
char map[MAX][MAX];
pair <int, int> pman[2];

struct Loc {
	int r1, r2, c1, c2;
	Loc() { r1 = -1; c1 = -1; r2 = -1; c2 = -1; }
	Loc(int _r1, int _c1, int _r2, int _c2) { r1 = _r1; c1 = _c1; r2 = _r2; c2 = _c2; }
};

queue <Loc> q;
int visited[MAX][MAX][MAX][MAX] = { 0, };
Loc prevLoc[MAX][MAX][MAX][MAX];

int dir[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} }; //N, E, S, W
char dirchar[4] = { 'N', 'E', 'S', 'W' };

Loc solve() //bfs
{
	int rc[2][2], nrc[2][2];

	while (!q.empty()) //초기화
		q.pop();
	memset(visited, 0, sizeof(visited));	

	q.push(Loc(pman[0].first, pman[0].second, pman[1].first, pman[1].second));
	visited[pman[0].first][pman[0].second][pman[1].first][pman[1].second] = 1;
	prevLoc[pman[0].first][pman[0].second][pman[1].first][pman[1].second] = Loc();

	while (!q.empty())
	{
		rc[0][0] = q.front().r1;
		rc[0][1] = q.front().c1;
		rc[1][0] = q.front().r2;
		rc[1][1] = q.front().c2;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			nrc[0][0] = rc[0][0] + dir[i][0]; //r1
			nrc[0][1] = rc[0][1] + dir[i][1]; //c1
			nrc[1][0] = rc[1][0] + dir[i][0]; //r2
			nrc[1][1] = rc[1][1] + dir[i][1]; //c2

			for (int j = 0; j < 2; j++) //범위 벗어난 것들 위치 조정.
			{
				if (nrc[j][0] < 0) //북
					nrc[j][0] = M - 1;
				else if (nrc[j][0] >= M) //남
					nrc[j][0] = 0;
				else if (nrc[j][1] < 0) //서
					nrc[j][1] = N - 1;
				else if (nrc[j][1] >= N) //동
					nrc[j][1] = 0;
			}

			for (int j = 0; j < 2; j++)  //벽이면 위치 조정.
			{
				if (map[nrc[j][0]][nrc[j][1]] == 'X')
				{
					nrc[j][0] = rc[j][0];
					nrc[j][1] = rc[j][1];
				}
			}

			if (visited[nrc[0][0]][nrc[0][1]][nrc[1][0]][nrc[1][1]] > 0) //이미 방문
				continue;

			if (map[nrc[0][0]][nrc[0][1]] == 'G' || map[nrc[1][0]][nrc[1][1]] == 'G') //유령
				continue;

			//이동.
			q.push(Loc(nrc[0][0], nrc[0][1], nrc[1][0], nrc[1][1]));
			visited[nrc[0][0]][nrc[0][1]][nrc[1][0]][nrc[1][1]] = visited[rc[0][0]][rc[0][1]][rc[1][0]][rc[1][1]] + 1;
			prevLoc[nrc[0][0]][nrc[0][1]][nrc[1][0]][nrc[1][1]] = Loc(rc[0][0], rc[0][1], rc[1][0], rc[1][1]); //방향(과거 위치) 저장.

			if (nrc[0][0] == nrc[1][0] && nrc[0][1] == nrc[1][1]) //팩맨을 합치는 것이 가능
				return Loc(nrc[0][0], nrc[0][1], nrc[1][0], nrc[1][1]);
		}
	}

	return Loc(-1, -1, -1, -1); //팩맨을 합치는 것이 불가능
}

int main(void)
{
	int t;
	Loc now, prev;

	cin >> T;
	for (int tc = 1; tc <= T; tc++) //testcase 수 만큼
	{
		//input
		t = 0;
		cin >> M >> N;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 'P')
					pman[t++] = make_pair(i, j);
			}
		}

		now = solve(); //마지막(합쳐지는) 위치

		//output
		if (now.r1 == -1)
			cout << "IMPOSSIBLE" << endl;
		else
		{
			int nrc[2][2];		
			int rsltcnt = visited[now.r1][now.c1][now.r2][now.c2] - 1;
			string rsltstr = "";

			for (int cnt = 0; cnt < rsltcnt; cnt++) //이동한 횟수만큼
			{
				prev = prevLoc[now.r1][now.c1][now.r2][now.c2]; //직전 위치

				for (int i = 0; i < 4; i++) //현재 위치에서 사방으로 직전 위치를 탐색.
				{
					nrc[0][0] = now.r1 - dir[i][0];
					nrc[0][1] = now.c1 - dir[i][1];
					nrc[1][0] = now.r2 - dir[i][0];
					nrc[1][1] = now.c2 - dir[i][1];

					for (int j = 0; j < 2; j++) //범위 벗어난 것들 위치 조정.
					{
						if (nrc[j][0] < 0) //북
							nrc[j][0] = M - 1;
						else if (nrc[j][0] >= M) //남
							nrc[j][0] = 0;
						else if (nrc[j][1] < 0) //서
							nrc[j][1] = N - 1;
						else if (nrc[j][1] >= N) //동
							nrc[j][1] = 0;
					}

					//팩맨1의 직전 위치를 찾음 or 팩맨2의 직전 위치를 찾음
					//이렇게 하는 이유: 팩맨 하나는 벽에 가로막혀 움직이지 않고, 하나는 움직이는 경우가 있어서..
					if ((nrc[0][0] == prev.r1 && nrc[0][1] == prev.c1) || (nrc[1][0] == prev.r2 && nrc[1][1] == prev.c2)) 
					{
						rsltstr += dirchar[i];
						now = prev; //직전 위치를 기준으로 더 직전 위치를 탐색.
						break;
					}
				}
			}

			cout << rsltcnt << " "; //이동 횟수
			for (int i = rsltstr.size() - 1; i >= 0; i--) //이동경로를 거꾸로 출력..(마지막(합쳐치는 곳)부터 거슬러 올라가며 결과를 저장했으므로.
				cout << rsltstr[i];
			cout << endl;
		}
	}
}