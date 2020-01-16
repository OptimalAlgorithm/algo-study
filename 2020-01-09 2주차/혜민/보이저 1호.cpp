#include <iostream>
#include <vector>
using namespace std;
#define MAX 501

int N, M;
char map[MAX][MAX];
pair <int, int> P; //Ž�缱 ��ġ

int dir[4][2] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } }; // URDL
int change[2][4] = { { 1,0,3,2 },{ 3,2,1,0 } }; //������ȯ. 0 = / �̰�, 1 = \ 
int rslt[4] = { 0, };

void input()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];
	}
	cin >> P.first >> P.second;
}

int move(int r, int c, int d)
{
	int cnt = 1;

	while (cnt <= MAX*MAX)
	{
		int nr = r + dir[d][0];
		int nc = c + dir[d][1];

		//����
		if (nr < 1 || nc < 1 || nr > N || nc > M)//����ε� ����
			break;
		if (map[nr][nc] == 'C') //��Ȧ
			break;

		//�̵�
		r = nr;
		c = nc;
		//������ȯ
		if (map[nr][nc] == '/')
			d = change[0][d];
		else if (map[nr][nc] == '\\')
			d = change[1][d];

		cnt++;
	}

	return cnt;
}

int solve()
{
	int max = 0;
	for (int d = 0; d < 4; d++) //�� ���⸶�� ��� ����
		rslt[d] = move(P.first, P.second, d);

	for (int d = 1; d < 4; d++) //���� �� ��
		max = rslt[max] >= rslt[d] ? max : d;

	return max;
}

void output(int i)
{
	char rsltAlpha[4] = { 'U', 'R', 'D', 'L' }; //�����¿�

	cout << rsltAlpha[i] << endl;

	if (rslt[i] >= MAX * MAX) //������ ������ ���
		cout << "Voyager" << endl;
	else
		cout << rslt[i] << endl;
}
int main()
{
	int idx = 0;
	input();
	idx = solve();
	output(idx);
}