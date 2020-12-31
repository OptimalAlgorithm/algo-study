#include <iostream>
#include <cstring>
using namespace std;
#define MAX 500
//#define DEBUG

int N;
int A[MAX][MAX];
int dir[4][2] = { {0,-1}, {1,0}, {0,1}, {-1,0} };

double rate[4][5][5] = { {{0,		0,		0.02,	0,		0},
							{0,		0.1,	0.07,	0.01,	0},
							{0.05,	0,		0,		0,		0},
							{0,		0.1,	0.07,	0.01,	0},
							{0,		0,		0.02,	0,		0}}, };
int ans = 0;

void solve()
{
	int r, c, d, change, t, remain, spread;
	r = c = N / 2; //정가운데 시작
	d = 0; //왼쪽으로
	change = 2; //크기 주기
	t = 0; //현재 시간
	remain = 0; //모래 양

	while (true)
	{
		if (r == 0 && c == 0) //토네이도는 (1, 1)까지 이동한 뒤 소멸
			break;

		//move
		r += dir[d][0];
		c += dir[d][1];
		t++;

		//spread
		remain = A[r][c];
		if (A[r][c] != 0) //뿌릴 모래가 있으면
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (r - 2 + i < 0 || c - 2 + j < 0 || r - 2 + i >= N || c - 2 + j >= N) //범위 넘어감
					{
						spread = (int)(A[r][c] * (double)rate[d][i][j]);
						ans += spread;
						remain -= spread;
					}
					else
					{
						spread = (int)(A[r][c] * (double)rate[d][i][j]);
						A[r - 2 + i][c - 2 + j] += spread;
						remain -= spread;
					}
				}
			}

			if (r + dir[d][0] < 0 || r + dir[d][0] >= N || c + dir[d][1] < 0 || c + dir[d][1] >= N)
				ans += remain;
			else
				A[r + dir[d][0]][c + dir[d][1]] += remain;
			A[r][c] = 0;
		}

		if (change == t * 2) //방향을 바꿔야 할 때
			d = (d + 1) % 4;
		else if (change == t) //방향, 크기 바꿔야할 때
		{
			t = 0;
			change += 2;
			d = (d + 1) % 4;
		}
	}
}

void init()
{
	memset(A, 0, sizeof(A));

	for (int i = 4; i >= 0; i--) //아래
	{
		for (int j = 0; j < 5; j++)
			rate[1][4 - i][j] = rate[0][j][i];
	}

	for (int i = 0; i < 5; i++) //오른쪽
	{
		for (int j = 4; j >= 0; j--)
			rate[2][i][4 - j] = rate[0][i][j];
	}

	for (int i = 0; i < 5; i++) //위
	{
		for (int j = 4; j >= 0; j--)
			rate[3][i][j] = rate[0][j][i];
	}
}

int main()
{
	//init
	init();

	//input
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cin >> A[i][j];
	}

	//solve
	solve();

	//output
	cout << ans << endl;
}