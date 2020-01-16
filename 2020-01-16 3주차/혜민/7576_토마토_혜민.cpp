//BOJ_7576_�丶��
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

			if (map[i][j] == 0)//�� ���� �丶��
				notripen++;
			else if (map[i][j] == 1)//���� �丶��
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

				if (map[nr][nc] == 0) //������ �丶��
				{
					map[nr][nc] = 1; //���� �丶��� ����!
					notripen--;
					tmpQ.push(make_pair(nr, nc)); //�ϴ� tmp queue�� ����
					visited[nr][nc] = true;
				}
			}
		}

		if (tmpQ.empty()) //���̻� �Ͱ� ���� �丶�䰡 ����...
		{
			if (notripen > 0) //�丶�䰡 ��� ������ ���ϴ� ��Ȳ
				day = -1;

			break;
		}

		while (!tmpQ.empty()) //���� ť�� �ֱ�
		{
			q.push(tmpQ.front());
			tmpQ.pop();
		}

		day++; //�Ϸ� ������.
	}
}

int main()
{
	input();

	if (notripen == 0)//�� ���� �丶�䰡 ���� = ��� �丶�䰡 �;���
	{
		cout << "0" << endl;
		return 0;
	}

	bfs();
	cout << day << endl;
}