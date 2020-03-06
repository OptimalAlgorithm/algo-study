#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define MAX 51

string s;
int memo[MAX][MAX][MAX][2][3] = { 0, }; //memo[i][j][k]는 A = i개, B = j개, C = k개 남았을 때의 출근기록. (0 = 미방문, 1 = 올바름, -1 = 올바르지않음)
vector <char> v;

int record(int a, int b, int c, int cb, int cc) //A 개수, B 개수, C 개수, B가 못오는 일수, C가 못오는 일수
{
	int ncb = (cb - 1 <= 0) ? 0 : cb - 1; //날짜가 음수인 경우는 없으니까, 음수인 경우 0으로 바꿔준다.
	int ncc = (cc - 1 <= 0) ? 0 : cc - 1;

	if (a <= 0 && b <= 0 && c <= 0) //종료조건
		return 1;

	if (a > 0 && memo[a - 1][b][c][ncb][ncc] >= 0) //방문x or 올바름.
	{
		if (memo[a - 1][b][c][ncb][ncc] == 0) //방문 x
			memo[a - 1][b][c][ncb][ncc] = record(a - 1, b, c, ncb, ncc);
		
		if (memo[a - 1][b][c][ncb][ncc] > 0) //올바름 
			return memo[a][b][c][cb][cc] = 1;
	}
	if (b > 0 && cb <= 0 && memo[a][b - 1][c][1][ncc] >= 0)
	{
		if (memo[a][b - 1][c][1][ncc] == 0)
			memo[a][b - 1][c][1][ncc] = record(a, b - 1, c, 1, ncc);

		if(memo[a][b - 1][c][1][ncc] > 0)
			return memo[a][b][c][cb][cc] = 1;
	}
	if (c > 0 && cc <= 0 && memo[a][b][c - 1][ncb][2] >= 0)
	{
		if (memo[a][b][c - 1][ncb][2] == 0) 
			memo[a][b][c - 1][ncb][2] = record(a, b, c - 1, ncb, 2);

		if(memo[a][b][c - 1][ncb][2] > 0)
			return memo[a][b][c][cb][cc] = 1;
	}

	return memo[a][b][c][cb][cc] = -1; //어디에도 걸리지 않았으면 올바르지 않음.
}

string print_record(int a, int b, int c, int cb, int cc) //record랑 똑같은데 출력용.. 왜때문에 출력 따로 해야 맞는지 모르겠음..
{
	int ncb = (cb - 1 <= 0) ? 0 : cb - 1;
	int ncc = (cc - 1 <= 0) ? 0 : cc - 1;

	if (a <= 0 && b <= 0 && c <= 0) //종료조건
		return "";

	if (a > 0 && memo[a - 1][b][c][ncb][ncc] > 0)
		return "A" + print_record(a - 1, b, c, ncb, ncc);
	if (b > 0 && cb <= 0 && memo[a][b - 1][c][1][ncc] > 0)
		return "B" + print_record(a, b - 1, c, 1, ncc);
	if (c > 0 && cc <= 0 && memo[a][b][c - 1][ncb][2] >= 0)
		return "C" + print_record(a, b, c - 1, ncb, 2);

	return "";
}


void solve()
{
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < s.size(); i++) //A,B,C 개수 세기
	{
		if (s[i] == 'A')
			a++;
		else if (s[i] == 'B')
			b++;
		else
			c++;
	}

	if (record(a, b, c, 0, 0) < 0) //올바른 출근 기록이 없는 경우
		cout << "-1" << endl;
	else
		cout << print_record(a, b, c, 0, 0) << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> s;

	solve();
}
