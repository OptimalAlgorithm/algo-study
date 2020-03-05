#include <iostream>
using namespace std;
#define MAX 52

int T, N, R;
int board[MAX][MAX];
pair<int, int> laser;
int t;
int dir[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} }; //북서남동
int changeDir[4] = { 3, 0, 1, 2 }; //오른쪽 방향전환

void solve()
{
	int r, c, d;

	//레이저 초기값
	r = laser.first;
	c = laser.second;
	if (laser.first > N) //북
		d = 0;
	else if (laser.second > N) //서
		d = 1;
	else if (laser.first < 1) //남
		d = 2;
	else //(laser.second < 1) //동
		d = 3;

	while (true)
	{
		r += dir[d][0]; //한칸 전진
		c += dir[d][1];

		if (r < 1 || c < 1 || r > N || c > N) //범위 벗어났다
		{
			laser = make_pair(r, c);
			return;
		}

		if (board[r][c] == t) //거울
			d = changeDir[d]; //오른쪽으로 방향 전환
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int r, c;
	cin >> T;
	for (t = 1; t <= T; t++)
	{
		//input
		cin >> N >> R;
		for (int i = 0; i < R; i++)
		{
			cin >> r >> c;
			board[r][c] = t; //true false 대신 해당 TC번호로 구분하면 초기화 안해도 된다!
		}
		cin >> laser.first >> laser.second;

		solve();

		//output
		cout << laser.first << " " << laser.second << endl;
	}
}
