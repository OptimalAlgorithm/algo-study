#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX 21
#define MAXDIST 100000

int N, M;
long long F;
int map[MAX][MAX];

pair<int, int> driver;
struct Passenger {
	int sr, sc, er, ec;
	int startdist, enddist; //택시-시작, 시작-끝의 최단거리
	bool finished;
	Passenger(int _sr, int _sc, int _er, int _ec) { sr = _sr; sc = _sc; er = _er; ec = _ec; startdist = enddist = MAXDIST;  finished = false;}
};
vector <Passenger> pass;

queue <pair<int, int>> q;
int visited[MAX][MAX];
int dir[4][2] = { {-1,0}, {0,-1}, {0,1}, {1,0} };

bool compare(Passenger a, Passenger b) //승객 정렬 비교
{
	if (a.startdist == b.startdist)
	{
		if (a.sr == b.sr) 
			return a.sc < b.sc; //3. 열이 작은 순
		else
			return a.sr < b.sr; //2. 행이 작은 순
	}
	else
		return a.startdist < b.startdist; //1. 최단거리
}

int cal_dist(int sr, int sc, int er, int ec) //각 승객의 시작-끝 최단거리 구하기(BFS)
{
	int r, c, nr, nc;
	
	if (sr == er && sc == ec) //만약 시작 = 끝이면 거리는 0
		return 0;

	//초기화
	memset(visited, 0, sizeof(visited));
	while (!q.empty())
		q.pop();

	//여기서부터 bfs 시작
	q.push(make_pair(sr, sc));
	visited[sr][sc] = 1;

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			nr = r + dir[d][0];
			nc = c + dir[d][1];

			if (nr < 1 || nc < 1 || nr > N || nc > N || visited[nr][nc] > 0) //범위 벗어남 or 이미 방문
				continue;

			if (map[nr][nc] == 1) //벽
				continue;

			if (nr == er && nc == ec) //도착지
				return visited[r][c];

			q.push(make_pair(nr, nc));
			visited[nr][nc] = visited[r][c] + 1;
		}
	}

	return MAXDIST; //도착지까지 도달 못한 경우
}

void pick_passenger() //택시-승객 최단거리 구하기(BFS)
{
	int r, c, nr, nc;

	//초기화
	memset(visited, 0, sizeof(visited));
	while (!q.empty())
		q.pop();
	for (int i = 0; i < pass.size(); i++)
		map[pass[i].sr][pass[i].sc] = 0;

	//승객 위치 map에 써놓기
	for (int i = 0; i < pass.size(); i++)
	{
		if (!pass[i].finished)
			map[pass[i].sr][pass[i].sc] = i + 2; //0,1은 벽이니까 2부터 시작
	}

	if (map[driver.first][driver.second] >= 2)  //만약 택시 = 승객이면 해당 승객의 거리는 0
		pass[map[driver.first][driver.second] - 2].startdist = 0;

	//여기서부터 bfs 시작
	q.push(driver);
	visited[driver.first][driver.second] = 1;

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			nr = r + dir[d][0];
			nc = c + dir[d][1];

			if (nr < 1 || nc < 1 || nr > N || nc > N || visited[nr][nc] > 0) //범위 벗어남 or 이미 방문
				continue;

			if (map[nr][nc] == 1) //벽
				continue;

			if (map[nr][nc] >= 2) //손님
				pass[map[nr][nc] - 2].startdist = visited[r][c]; //택시-해당 손님간 최단거리 갱신

			q.push(make_pair(nr, nc));
			visited[nr][nc] = visited[r][c] + 1;
		}
	}

	sort(pass.begin(), pass.end(), compare); //최단거리, 행, 열 순으로 정렬
}

void solve()
{
	int ppl = 0;

	//기초단계. 각 손님의 주행거리 계산
	for (int i = 0; i < pass.size(); i++)
	{
		pass[i].enddist = cal_dist(pass[i].sr, pass[i].sc, pass[i].er, pass[i].ec);

		if (pass[i].enddist == MAXDIST) //만약 어떤 손님의 시작-끝 주행 못하면
		{
			F = -1;
			return;
		}
	}

	while (true)
	{
		//0-1. 모든 손님을 다 이동시켰으면 정상 종료
		if (ppl >= pass.size())
			break;

		//0-2. 연료가 0이면 손님을 태울 수 없다
		if(F <= 0)
		{
			F = -1;
			break;
		}

		//1. 손님을 선정한다.
		pick_passenger();

		//2. 손님을 태우고 간다.
		if(pass[0].startdist == MAXDIST || F - pass[0].startdist - pass[0].enddist < 0) //택시에서 갈 수 있는 최단거리 손님이 없다.
		{
			F = -1;
			break;
		}
		else //손님 태운다.
		{
			ppl++; //주행 완료한 손님 1명 늘어남

			driver = make_pair(pass[0].er, pass[0].ec); //택시기사 위치 갱신

			F -= pass[0].startdist; //택시-시작까지 연료 소모
			F += pass[0].enddist; //시작-끝까지 연료 소모 + 주행 중 소모 연료 양의 2배 충전

			pass[0].finished = true; //손님 상태 갱신
			pass[0].startdist = MAXDIST;
		}	
	}
}

int main()
{
	int sr, sc, er, ec;

	//input
	cin >> N >> M >> F;
	for (int i = 1; i <= N; i++) //map 정보
	{
		for (int j = 1; j <= N; j++)
			cin >> map[i][j]; //0 = empty. 1 = wall
	}
	cin >> driver.first >> driver.second; //택시기사 위치
	for (int i = 1; i <= M; i++) //각 손님 위치
	{
		cin >> sr >> sc >> er >> ec;
		pass.push_back(Passenger(sr, sc, er, ec));
	}

	solve();

	//output
	cout << F << endl; //남은 연료
}