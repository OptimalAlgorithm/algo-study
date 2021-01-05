#include <iostream>
#include <vector>
using namespace std;
#define MAPSIZE 4

int map[MAPSIZE][MAPSIZE][2];
int dir[9][2] = { {0,0}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1} };

struct Fish {
	int r, c, d; //행 열 방향
	bool dead;
	Fish(int _r, int _c, int _d) { r = _r; c = _c; d = _d; dead = false; }
};
vector <Fish> fish;
int ans;

int move_fish_and_shark(int sr, int sc, int sd, int level)
{
	int tmp[MAPSIZE][MAPSIZE][2]; //map정보 저장
	int r, c, d, nr, nc, num; //물고기 이동을 위한 변수
	int nsr, nsc; //상어 이동을 위한 변수
	int rslt; //각 상어 이동에 해당하는 결과값
	int maxRslt = 0;

	//0. map정보 저장
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			tmp[i][j][0] = map[i][j][0];
			tmp[i][j][1] = map[i][j][1];
		}
	}

	//1.물고기가 이동한다.
	for (int i = 1; i < fish.size(); i++)
	{
		if (fish[i].dead) //죽은 물고기 제외
			continue;

		r = fish[i].r; //현재 위치
		c = fish[i].c;
		d = fish[i].d - 1; //방향은 현재 위치의 전 단계로.. 밑의 반복문에서 하나 더하고 시작하기 때문에
		if (d <= 0)
			d = 8;

		for (int j = 1; j <= 8; j++) //방향은 총 8번 돈다
		{
			if (++d % 9 == 0) //45도 회전
				d = 1;
			nr = r + dir[d][0];//새로운 위치
			nc = c + dir[d][1];

			if (nr < 0 || nc < 0 || nr >= MAPSIZE || nc >= MAPSIZE) //이동 불가 : 경계 밖
				continue;

			if (nr == sr && nc == sc) //이동 불가 : 상어
				continue;

			break; //이동 가능
		}

		//물고기 이동
		num = map[nr][nc][0]; //이동할 칸의 물고기 번호 저장
		map[r][c][0] = 0; //현재 위치 지우고
		map[nr][nc][0] = i; //새 위치로 옮긴다
		map[nr][nc][1] = d;
		fish[i].r = nr; //물고기 데이터도 갱신
		fish[i].c = nc;
		fish[i].d = d;

		if (num != 0) //이동한 칸이 빈칸이 아니었다면 = 물고기 존재하므로 자리 스위치.
		{
			map[r][c][0] = num; 
			map[r][c][1] = fish[num].d;
			fish[num].r = r; //물고기 데이터도 갱신
			fish[num].c = c;
		}
	}

	//2.상어가 이동한다.
	nsr = sr;
	nsc = sc;
	while (true)
	{
		nsr += dir[sd][0]; //상어가 이동할 위치
		nsc += dir[sd][1];

		if (nsr < 0 || nsc < 0 || nsr >= MAPSIZE || nsc >= MAPSIZE) //이동 불가 : 경계 밖
			break;

		if (map[nsr][nsc][0] == 0) //이동 불가 : 빈칸
			continue;

		//물고기 먹을 수 있다!
		num = map[nsr][nsc][0]; //먹은 물고기 번호 저장
		fish[num].dead = true; //물고기 죽음
		map[nsr][nsc][0] = 0; //먹은 위치는 빈자리로

		rslt = num + move_fish_and_shark(nsr, nsc, fish[num].d, level + 1); //먹고 다음턴으로.
		maxRslt = maxRslt > rslt ? maxRslt : rslt; //최댓값 갱신

		//백트레킹 : 죽은 물고기 되살리기
		fish[num].dead = false;
		map[nsr][nsc][0] = num;
	}

	//3. 백트레킹 : map 정보 되살리기
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			map[i][j][0] = tmp[i][j][0];
			map[i][j][1] = tmp[i][j][1];

			fish[map[i][j][0]].r = i;
			fish[map[i][j][0]].c = j;
			fish[map[i][j][0]].d = map[i][j][1];
		}
	}

	return maxRslt; //현재 level에서 도출한 최댓값을 리턴
}

void solve()
{
	//1. 물고기 데이터 제대로 해주기
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
			fish[map[i][j][0]] = (Fish(i, j, map[i][j][1]));
	}

	//2.상어는 (0,0) 물고기를 먹는다.
	ans = map[0][0][0];
	fish[map[0][0][0]].dead = true;
	map[0][0][0] = 0;

	//3.재귀적으로 돌면서 최댓값을 도출할 최선의 선택을 찾아낸다.
	ans += move_fish_and_shark(0, 0, map[0][0][1], 1);
}

int main()
{
	fish.push_back(Fish(0,0,0)); //1번부터 시작하려고 0번 채우기...

	//input
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			cin >> map[i][j][0] >> map[i][j][1];
			fish.push_back(Fish(0,0,0));
		}
	}

	solve();

	//output
	cout << ans << endl;
}