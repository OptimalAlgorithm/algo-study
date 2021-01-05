#include <iostream>
#include <vector>
using namespace std;
#define MAX 20
#define MAXPRIORITY MAX*MAX*MAX

int N, M, K;
int map[MAX][MAX][2];
int dir[5][2] = { {0,0}, {-1,0}, {1,0}, {0,-1}, {0,1} }; //그대로 위 아래 왼 오른
struct Shark {
	int num, r, c, d; //번호, 현재 위치, 현재 방향
	int priority[5][5]; //우선순위 
	bool dead; //격자 밖으로 쫒겨나는지
	Shark(int _num) { num = _num; dead = false; }
};
vector <Shark> shark;
int ans = 0;

void solve()
{
	int r, c, nr, nc;
	int saveD, saveS, saveP; //저장칸 정보. (이동하려는 곳의 방향, 냄새, 우선순위를 저장)
	int moveD, moveS, moveP; //이동칸 정보.
	int cnt = 0; //쫒겨난 상어 갯수
	int tmp[MAX][MAX][2]; //각 턴마다 map정보를 저장

	while (true)
	{
		if (++ans > 1000) //1,000초가 넘어도 다른 상어가 격자에 남아 있으면 -1을 출력
		{
			ans = -1;
			break;
		}

		//0. 상어 이동 전 기초 과정.
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++)
			{
				tmp[i][j][0] = map[i][j][0]; //현재 map상태를 복사
				tmp[i][j][1] = map[i][j][1];
			}
		}

		//1. 상어 이동
		for (int m = 1; m < shark.size(); m++) //상어
		{
			if (shark[m].dead) //죽은 상어는 제외
				continue;

			r = shark[m].r; //현재 상어의 좌표
			c = shark[m].c;

			saveD = saveS = saveP = MAXPRIORITY + 1; //저장칸 초기화

			for (int d = 1; d <= 4; d++) //네 방향을 돌면서 최선의 이동칸을 저장 => 저장칸에
			{
				nr = r + dir[d][0]; //이동칸의 좌표
				nc = c + dir[d][1];

				if (nr < 0 || nc < 0 || nr >= N || nc >= N) //격자 범위 넘어감
					continue;

				//이동칸의 냄새 분류
				if (tmp[nr][nc][0] == 0) //빈칸
					moveS = 0;
				else if (tmp[nr][nc][0] == m) //내 냄새
					moveS = m;
				else
					moveS = MAXPRIORITY; //다른 냄새

				//저장칸과 이동칸을 비교하여 최선의 위치를 찾는다!
				if (saveS == moveS) //저장칸, 이동칸 모두 같은 냄새
				{
					//그럼 우선순위로 따진다.
					if (saveP > shark[m].priority[shark[m].d][d]) //저장칸 우선순위 > 이동칸 우선순위 => 이동칸이 숫자가 더 작으니까 더 우선순위가 높다
					{
						saveD = d; //방향 저장
						saveP = shark[m].priority[shark[m].d][d]; //우선순위 저장
					}
				}
				else if (saveS > moveS) //저장칸 냄새 > 이동칸 냄새 => 저장칸 냄새보다 이동칸 냄새가 더 우선순위가 높다
				{
					saveS = moveS; //냄새 저장
					saveD = d; //방향 저장
					saveP = shark[m].priority[shark[m].d][d]; //우선순위 저장
				}
			}

			//저장한 곳으로 이동
			shark[m].r += dir[saveD][0];
			shark[m].c += dir[saveD][1];
			shark[m].d = saveD;

			//3.한 칸에 여러 마리의 상어, 가장 작은 번호를 가진 상어 제외, 모두 격자 밖으로 쫓겨난다.
			if (map[shark[m].r][shark[m].c][0] != 0 && map[shark[m].r][shark[m].c][0] < m) //빈칸 아님 && 이미 앞 번호의 상어가 그 자리를 차지하고 있음
			{
				shark[m].dead = true; //뒷 번호 상어는 쫒겨난다
				cnt++;

				if (cnt >= M - 1) //1번 상어만 남고 다 쫒겨난 경우
					return;
			}
			else
			{
				map[shark[m].r][shark[m].c][0] = m; //map에도 이동한걸 갱신..
				map[shark[m].r][shark[m].c][1] = K + 1; //냄새를 뿌린다(각 턴 초반에 냄새를 1씩 지우고 시작하므로 K가 아닌 K+1만큼 뿌린다)
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j][1] > 0) //모든 칸의 냄새를 1만큼 감소
				{
					--map[i][j][1];
					if (map[i][j][1] == 0) //냄새는 상어가 k번 이동하고 나면 사라진다.
						map[i][j][0] = 0;
				}
			}
		}
	}
}

int main()
{
	int tmp;

	//input
	cin >> N >> M >> K;

	for (int i = 0; i <= M; i++) //M개의 상어
		shark.push_back(Shark(i));

	for (int i = 0; i < N; i++) //격자 정보
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j][0];

			if (map[i][j][0] > 0) //상어
			{
				map[i][j][1] = K; //처음부터 자신의 위치에 냄새를 뿌린다
				shark[map[i][j][0]].r = i; // 현재 위치 저장
				shark[map[i][j][0]].c = j;
			}
		}
	}

	for (int i = 1; i <= M; i++) //상어 방향
		cin >> shark[i].d;

	for (int i = 1; i <= M; i++) //각 상어의 우선순위
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 1; k <= 4; k++)
			{
				cin >> tmp;
				shark[i].priority[j][tmp] = k;
			}
		}
	}

	//solve
	solve();

	//output
	cout << ans << endl;
}