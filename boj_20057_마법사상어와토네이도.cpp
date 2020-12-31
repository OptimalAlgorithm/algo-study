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
	r = c = N / 2; //����� ����
	d = 0; //��������
	change = 2; //ũ�� �ֱ�
	t = 0; //���� �ð�
	remain = 0; //�� ��

	while (true)
	{
		if (r == 0 && c == 0) //����̵��� (1, 1)���� �̵��� �� �Ҹ�
			break;

		//move
		r += dir[d][0];
		c += dir[d][1];
		t++;

		//spread
		remain = A[r][c];
		if (A[r][c] != 0) //�Ѹ� �𷡰� ������
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (r - 2 + i < 0 || c - 2 + j < 0 || r - 2 + i >= N || c - 2 + j >= N) //���� �Ѿ
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

		if (change == t * 2) //������ �ٲ�� �� ��
			d = (d + 1) % 4;
		else if (change == t) //����, ũ�� �ٲ���� ��
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

	for (int i = 4; i >= 0; i--) //�Ʒ�
	{
		for (int j = 0; j < 5; j++)
			rate[1][4 - i][j] = rate[0][j][i];
	}

	for (int i = 0; i < 5; i++) //������
	{
		for (int j = 4; j >= 0; j--)
			rate[2][i][4 - j] = rate[0][i][j];
	}

	for (int i = 0; i < 5; i++) //��
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