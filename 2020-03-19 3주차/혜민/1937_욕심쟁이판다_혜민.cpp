#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 501

int N;
int map[MAX][MAX];
struct Bamboo
{
	int r, c, s; //행, 열, 크기
	Bamboo() {}
	Bamboo(int _r, int _c, int _s) { r = _r; c = _c; s = _s; }
};
vector <Bamboo> bamboo;

int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
int memo[MAX][MAX] = { 0, };
int ans = 0;

bool compare(Bamboo a, Bamboo b)
{
	return a.s < b.s;
}

int DP(int r, int c) //처음엔 bfs로 돌리면 될거라 생각했는데.. 그럼 최대 n^2만큼 bfs돌릴수도...
{
	int nr, nc, rslt, maxrslt = 0;

	if (memo[r][c] > 0) //이미 구했으면..
		return memo[r][c];

	for (int i = 0; i < 4; i++)
	{
		nr = r + dir[i][0];
		nc = c + dir[i][1];

		if (nr < 0 || nc < 0 || nr >= N || nc >= N) //범위 벗어남
			continue;

		if (map[r][c] >= map[nr][nc]) //단식투쟁 = 옮긴 지역에 그 전 지역보다 대나무가 많이 있어야 한다. 
			continue;

		rslt = DP(nr, nc);
		maxrslt = maxrslt > rslt ? maxrslt : rslt; //최대생존일수
	}

	memo[r][c] = maxrslt + 1;
	return memo[r][c];
}

void solve()
{
	sort(bamboo.begin(), bamboo.end(), compare); //대나무 양을 기준으로 오름차순 정렬

	for (int i = 0; i < bamboo.size(); i++)
	{
		if (ans >= bamboo.size() - i) //이번 타임에 남아있는 모든 대나무를 먹어도, 여태까지 구한 최대생존일수보다 작거나 같다.
			break;

		DP(bamboo[i].r, bamboo[i].c);
		ans = ans > memo[bamboo[i].r][bamboo[i].c] ? ans : memo[bamboo[i].r][bamboo[i].c];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			bamboo.push_back(Bamboo(i, j, map[i][j]));
		}
	}

	solve();

	//output
	cout << ans << endl;
}
