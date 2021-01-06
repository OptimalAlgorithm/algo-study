#include <iostream>
#include <vector>
using namespace std;
#define MAX 20001

int N;
struct Block {
	int t, x, y;
	Block(int _t, int _x, int _y) { t = _t; x = _x; y = _y; }
};
vector <Block> block;
bool board[2][MAX][4];
int ans = 0;
int total = 0;

void solve(int k)
{
	int top = 5, bottom = 0;
	bool check;

	for (int b = 0; b < block.size(); b++) //블록 갯수만큼
	{
		//1. 내리기
		for (int r = top - 1; r >= bottom; r--)//board[k][top-1][block[b].y]에 처음 놨다고 가정
		{
			if (r == bottom || board[k][r - 1][block[b].y]) //마지막 or 아래에 블록이 존재 = 더이상 못 내린다
			{
				board[k][r][block[b].y] = true;

				if (block[b].t == 2)
					board[k][r][block[b].y + 1] = true;
				else if (block[b].t == 3)
					board[k][r + 1][block[b].y] = true;
				break;
			}
			else if (block[b].t == 2 && board[k][r - 1][block[b].y + 1]) //t = 2인데, 아래 오른쪽에 블록 존재
			{
				board[k][r][block[b].y] = board[k][r][block[b].y + 1] = true;
				break;
			}
		}

		//2. 한줄완성 찾기
		for (int r = top; r >= bottom; r--)
		{
			check = true;
			for (int c = 0; c < 4; c++)
			{
				if (!board[k][r][c]) //블럭이 없으면 한줄 완성 아님
				{
					check = false;
					break;
				}
			}

			if (check)//한 줄 지워야 함
			{
				ans++;
				for (int nr = r; nr <= top; nr++) //아래로 끌어내리기
				{
					for (int c = 0; c < 4; c++)
						board[k][nr][c] = board[k][nr + 1][c];
				}
			}
		}

		//3. 연한 블록 처리
		for (int i = 0; i < 2; i++) //연한 부분은 2줄
		{
			for (int c = 0; c < 4; c++)
			{
				if (board[k][top - 1][c]) //블럭이 존재
				{
					top++;
					bottom++;
					break;
				}
			}
		}
	}

	for (int r = bottom; r <= top; r++) //남아있는 블록 개수 세기
	{
		for (int c = 0; c < 4; c++)
		{
			if (board[k][r][c])
				total++;
		}
	}
}

int main()
{
	int t, x, y;

	//input
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> t >> x >> y;
		block.push_back(Block(t, x, y));
	}

	//solve
	solve(0);
	for (int i = 0; i < block.size(); i++)
	{
		swap(block[i].x, block[i].y);
		if (block[i].t == 2)
			block[i].t = 3;
		else if (block[i].t == 3)
			block[i].t = 2;
	}
	solve(1);

	//output
	cout << ans << endl;
	cout << total << endl;
}