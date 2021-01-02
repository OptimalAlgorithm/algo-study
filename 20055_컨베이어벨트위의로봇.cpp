#include <iostream>
using namespace std;
#define MAX 201

int N, K;
pair<int,bool> belt[MAX];
int ans = 0;

void solve()
{
	pair<int, bool> tmp;
	int cnt = 0;

	while (true)
	{
		if (cnt >= K)
			break;

		ans++; //0. 단계 증가

		//1. 벨트가 한 칸 회전한다.
		tmp = belt[2 * N];
		for (int i = 2 * N; i > 1; i--)
			belt[i] = belt[i - 1];
		belt[1] = tmp;

		if (belt[N].second) //내려가는 위치에 로봇이 존재
			belt[N].second = false; //내려가는 위치에 로봇이 있다면 반드시 땅으로 내려간다.

		//2. 로봇이 이동한다		
		belt[0].second = true; //올라가는 위치에 로봇이 없다면 로봇을 하나 올린다.
		for (int i = N - 1; i >= 0; i--) //가장 먼저 벨트에 올라간 로봇부터
		{
			if (belt[i].second && !belt[i + 1].second && belt[i + 1].first >= 1) //현재 위치에 로봇이 존재하고 && 이동하려는 칸에 로봇이 없으며 && 그 칸의 내구도가 1 이상
			{
				belt[i].second = false; //현재 칸에서 나와서
				belt[i + 1].second = true; //앞 칸으로 이동
				belt[i + 1].first--; //이동한 칸의 내구도가 1 줄어든다.

				if (belt[i + 1].first <= 0) 	//내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다.
					cnt++;
			}

			//이동할 수 없다면 가만히 있는다
		}

		if (belt[N].second) //내려가는 위치에 로봇이 존재
			belt[N].second = false; //내려가는 위치에 로봇이 있다면 반드시 땅으로 내려간다.
	}
}

int main()
{
	//input
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++)
		cin >> belt[i].first;

	solve();

	//output
	cout << ans << endl;
}