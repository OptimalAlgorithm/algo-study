#include <iostream>
#include <vector>
using namespace std;
//#define DEBUG
#define MAX 51

int N, M, K;
struct Fireball {
	int r, c, m, s, d;
	bool dead;
	Fireball(int _r, int _c, int _m, int _s, int _d) { r = _r; c = _c; m = _m; s = _s; d = _d; dead = false; }
};
vector <Fireball> fireball;
int dir[8][2] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
int rslt = 0;

void solve()
{
	vector<int> map[MAX][MAX];
	int sumM, sumS, sumD;

	while (K--)
	{
		//1. 모든 파이어볼이 자신의 방향 di로 속력 si칸 만큼 이동한다.
		for (int i = 0; i < fireball.size(); i++)
		{
			if (fireball[i].dead) //죽은 행성 제외
				continue;

			for (int j = 0; j < fireball[i].s; j++) //s칸 이동 = 한 칸씩 s번
			{
				fireball[i].r += dir[fireball[i].d][0]; //한 칸 이동
				fireball[i].c += dir[fireball[i].d][1];

				if (fireball[i].r < 1) //위치 조정
					fireball[i].r = N;
				if (fireball[i].r > N)
					fireball[i].r = 1;
				if (fireball[i].c < 1)
					fireball[i].c = N;
				if (fireball[i].c > N)
					fireball[i].c = 1;
			}

			map[fireball[i].r][fireball[i].c].push_back(i); //map에 새로운 위치 저장
		}

		//2.이동이 모두 끝난 뒤, 2개 이상의 파이어볼이 있는 칸에서는 모두 하나로 합쳐지고, 4개로 나눠진다.
		for (int i = 1; i <= N; i++) //map 전체를 돌면서
		{
			for (int j = 1; j <= N; j++)
			{
				if (map[i][j].empty()) //아무 소행성 없음
					continue; 
				else if (map[i][j].size() == 1) //하나만 있을 때
				{
					map[i][j].clear(); //초기화
				}
				else //2개 이상의 파이어볼이 있을 때
				{
					sumM = sumS = 0;
					sumD = -1;
					for (int m = 0; m < map[i][j].size(); m++)
					{
						fireball[map[i][j][m]].dead = true; //2-4. 질량이 0인 파이어볼은 소멸되어 없어진다.
						sumM += fireball[map[i][j][m]].m;
						sumS += fireball[map[i][j][m]].s;

						if (sumD == -1 || sumD == fireball[map[i][j][m]].d % 2) //처음이거나 방향 같으면
							sumD = fireball[map[i][j][m]].d % 2; //1 or 0 이 저장
						else
							sumD = 2; 
					}
					sumM /= 5; //2-1. 질량은 ⌊(합쳐진 파이어볼 질량의 합)/5⌋이다.
					sumS /= map[i][j].size(); //2-2. 속력은 ⌊(합쳐진 파이어볼 속력의 합)/(합쳐진 파이어볼의 개수)⌋이다.
					sumD = (sumD == 2) ? 1 : 0; //2-3. 합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6이 되고, 그렇지 않으면 1, 3, 5, 7이 된다.
				
					if (sumM > 0) //질량이 0보다 커야함. 아니면 소멸
					{
						for (int d = sumD; d <= 7; d += 2) //4개의 파이어볼로 나누어진다.
							fireball.push_back(Fireball(i, j, sumM, sumS, d));
					}
					
					map[i][j].clear(); //초기화
				}
			}
		}
	}
}

int main()
{
	//input
	int r, c, m, s, d;
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++)
	{
		cin >> r >> c >> m >> s >> d;
		fireball.push_back(Fireball(r, c, m, s, d));
	}

	solve();

	//output
	for (int i = 0; i < fireball.size(); i++)
	{
		if (!fireball[i].dead)
			rslt += fireball[i].m;
	}
	cout << rslt << endl;
}
