//BOJ_2174_로봇시뮬레이션
#include <iostream>
#include <vector>
using namespace std;
#define MAX 101

int C, R, N, M; //A는 C, B는 R
int map[MAX][MAX];

typedef struct Robot {
	int r, c, d; //행, 열, 방향
	Robot(int _r, int _c, int _d) { r = _r;	c = _c;	d = _d; }
};
typedef struct Order {
	int r, t; //로봇, 횟수
	char o; //명령 종류
	Order(int _r, char _o, int _t) { r = _r; o = _o; t = _t; }
};
vector <Robot> robot;
vector <Order> order;

void input()
{
	robot.push_back(Robot(0, 0, 0)); //0번 로봇 안 쓰려고 그냥 만들어 둠...

	cin >> C >> R;
	cin >> N >> M;

	for (int i = 0; i < N; i++) //로봇
	{
		int r, c;
		char d;
		cin >> c >> r >> d;
		map[R - r + 1][c] = robot.size(); //행이 아래에서 시작하니까...

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

	for (int i = 0; i < M; i++) //명령
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

	if (o == 'L') //왼쪽 방향 전환
		robot[b].d = leftd[robot[b].d];

	else if (o == 'R') //오른쪽 방향 전환
		robot[b].d = rightd[robot[b].d];

	else //전진
	{
		int nr = robot[b].r + d[robot[b].d][0]; //새 좌표
		int nc = robot[b].c + d[robot[b].d][1];

		if (nr < 1 || nc < 1 || nr > R || nc > C) //벽에 부딫힘
		{
			cout << "Robot " << b << " crashes into the wall" << endl;
			exit(0);
		}
		else if (map[nr][nc] > 0) //다른 로봇이 존재
		{
			cout << "Robot " << b << " crashes into robot " << map[nr][nc] << endl;
			exit(0);
		}
		else //전진 가능
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

	cout << "OK" << endl; //제대로 끝났을 경우
}

int main()
{
	input();
	solve();
}
