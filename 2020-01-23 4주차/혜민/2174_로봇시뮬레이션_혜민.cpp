//BOJ_2174_�κ��ùķ��̼�
#include <iostream>
#include <vector>
using namespace std;
#define MAX 101

int C, R, N, M; //A�� C, B�� R
int map[MAX][MAX];

typedef struct Robot {
	int r, c, d; //��, ��, ����
	Robot(int _r, int _c, int _d) { r = _r;	c = _c;	d = _d; }
};
typedef struct Order {
	int r, t; //�κ�, Ƚ��
	char o; //��� ����
	Order(int _r, char _o, int _t) { r = _r; o = _o; t = _t; }
};
vector <Robot> robot;
vector <Order> order;

void input()
{
	robot.push_back(Robot(0, 0, 0)); //0�� �κ� �� ������ �׳� ����� ��...

	cin >> C >> R;
	cin >> N >> M;

	for (int i = 0; i < N; i++) //�κ�
	{
		int r, c;
		char d;
		cin >> c >> r >> d;
		map[R - r + 1][c] = robot.size(); //���� �Ʒ����� �����ϴϱ�...

		switch (d)
		{
		case 'N':
			robot.push_back(Robot(R - r + 1, c, 0));
			break;
		case 'W':
			robot.push_back(Robot(R - r + 1, c, 1));
			break;
		case 'S':
			robot.push_back(Robot(R - r + 1, c, 2));
			break;
		case 'E':
			robot.push_back(Robot(R - r + 1, c, 3));
			break;
		}
	}

	for (int i = 0; i < M; i++) //���
	{
		int r, t;
		char o;
		cin >> r >> o >> t;
		order.push_back(Order(r, o, t));
	}
}

void move(int b, char o)
{
	int d[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} }; //N ,W, S, E
	int rightd[4] = { 3, 0, 1, 2 };
	int leftd[4] = { 1, 2, 3, 0 };

	if (o == 'L') //���� ���� ��ȯ
		robot[b].d = leftd[robot[b].d];

	else if (o == 'R') //������ ���� ��ȯ
		robot[b].d = rightd[robot[b].d];

	else //����
	{
		int nr = robot[b].r + d[robot[b].d][0]; //�� ��ǥ
		int nc = robot[b].c + d[robot[b].d][1];

		if (nr < 1 || nc < 1 || nr > R || nc > C) //���� �΋H��
		{
			cout << "Robot " << b << " crashes into the wall" << endl;
			exit(0);
		}
		else if (map[nr][nc] > 0) //�ٸ� �κ��� ����
		{
			cout << "Robot " << b << " crashes into robot " << map[nr][nc] << endl;
			exit(0);
		}
		else //���� ����
		{
			map[robot[b].r][robot[b].c] = 0;
			map[nr][nc] = b;
			robot[b].r = nr;
			robot[b].c = nc;
		}
	}
}

void solve()
{
	for (int i = 0; i < M; i++)
	{
		while (order[i].t--)
			move(order[i].r, order[i].o);
	}

	cout << "OK" << endl; //����� ������ ���
}

int main()
{
	input();
	solve();
}
