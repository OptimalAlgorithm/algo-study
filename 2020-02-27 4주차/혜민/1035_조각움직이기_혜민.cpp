#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define MAX 5

char board[MAX][MAX];
vector <pair<int, int>> piece; //조각

int ans = 10000000;

vector <pair<int, int>> pick;
vector <pair<int, int>> possible;
bool visited[MAX][MAX];
bool chooseLoc[MAX];
vector <int> permutation;
int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

void perm() //뽑은 위치들에 어떤 조각이 들어갈지 순서를 정한다.(순열)
{
	int rslt = 0;

	if (permutation.size() == piece.size() - 1) //한조각은 고정이므로, 나머지 조각 개수만큼 순서를 정했다면
	{
		for (int i = 0; i < permutation.size(); i++) //얼만큼 이동해야 하는지 계산
			rslt += abs(piece[permutation[i]].first - pick[i].first) + abs(piece[permutation[i]].second - pick[i].second);

		ans = ans < rslt ? ans : rslt; //최저값 갱신

		return;
	}

	for (int i = 0; i < piece.size(); i++)
	{
		if (!chooseLoc[i]) //아직 순서를 못 정한 조각
		{
			chooseLoc[i] = true;
			permutation.push_back(i);
			perm();
			permutation.pop_back();
			chooseLoc[i] = false;
		}
	}
}

void comb(int r, int c) //해당 조각 주변에 다른 조각들을 배치하도록 위치를 선정한다.(조합)
{
	int nr, nc;
	int possibleSize = possible.size(); //현재 후보군(*이 올 수 있는 곳)의 개수

	if (pick.size() == piece.size() - 1) //한조각은 고정이므로, 나머지 조각 개수만큼 위치를 뽑았다면
	{
		perm(); //어디에 놓을지 순서를 정한다.(순열)
		return;
	}

	//후보군(*이 올 수 있는 곳) 찾기
	for (int i = 0; i < 4; i++) //현재 선택한 위치에 *이 놓이면, 그 위치의 사방이 *이 올 수 있는 곳이다.
	{
		nr = r + dir[i][0];
		nc = c + dir[i][1];

		if (nr < 0 || nc < 0 || nr >= MAX || nc >= MAX || visited[nr][nc])
			continue;

		possible.push_back(make_pair(nr, nc));
	}

	//*놓을 곳을 뽑는다 = 조합. (dfs)
	for (int i = 0; i < possible.size(); i++)
	{
		visited[r][c] = true;
		pick.push_back(make_pair(possible[i].first, possible[i].second));
		comb(possible[i].first, possible[i].second);
		visited[r][c] = false;
		pick.pop_back();
	}

	while (possibleSize < possible.size()) //이번 회차에 넣었던 후보군(*이 올 수 있는 곳) 지우기
		possible.pop_back();
}

void solve()
{
	if (piece.size() == 1) //1개
		ans = 0;
	else if (piece.size() == 2) //2개
		ans = abs(piece[0].first - piece[1].first) + abs(piece[0].second - piece[1].second) - 1;
	else //3~5개
	{
		for (int i = 0; i < piece.size(); i++) //각 조각을 기준으로 
		{
			chooseLoc[i] = true; //해당조각은 가만히 있어도 된다.
			comb(piece[i].first, piece[i].second); //해당 조각 주변에 다른 조각들을 배치하도록 위치를 선정한다.
			chooseLoc[i] = false;
		}
	}

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == '*')
				piece.push_back(make_pair(i, j)); //조각의 위치 저장
		}
	}

	solve();

	//output
	cout << ans << endl;
}
