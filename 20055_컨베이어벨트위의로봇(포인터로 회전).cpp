#include <iostream>
using namespace std;
#define MAX 201

int N, K;
pair<int,bool> belt[MAX];
int ans = 0;

void solve()
{
	int cnt = 0;
	int up = 1; //올라가는 위치
	int down = N; //내려가는 위치
	int here, next;

	while (true)
	{
		if (cnt >= K)
			break;

		ans++; //0. 단계 증가

		//1. 벨트가 한 칸 회전한다.
		up--;
		if (up < 1)
			up = 2 * N;
		down--;
		if (down < 1)
			down = 2 * N;
		
		if (belt[down].second) //내려가는 위치에 로봇이 존재
			belt[down].second = false; //내려가는 위치에 로봇이 있다면 반드시 땅으로 내려간다.


		//2. 로봇이 이동한다
		here = down; //가장 먼저 벨트에 올라간 로봇부터
		for(int n = 1; n <= N; n++) //N개 칸만큼 로봇이 이동(그냥 N번 반복하기 위해 쓰는 용도)
		{
			next = here; //앞 칸
			here--; //현재 칸
			if (here < 1)
				here = 2 * N;

			if (belt[here].second && !belt[next].second && belt[next].first >= 1) //현재 위치에 로봇이 존재하고 && 이동하려는 칸에 로봇이 없으며 && 그 칸의 내구도가 1 이상
			{
				belt[here].second = false; //현재 칸에서 나와서
				belt[next].second = true; //앞 칸으로 이동
				belt[next].first--; //이동한 칸의 내구도가 1 줄어든다.


				if (belt[next].first <= 0) 	//내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다.
					cnt++;
			}

			//이동할 수 없다면 가만히 있는다
		}

		//3. 올라가는 위치에 로봇이 없다면 로봇을 하나 올린다.
		if (!belt[up].second && belt[up].first >= 1)
		{
			belt[up].second = true;
			belt[up].first--;

			if (belt[next].first <= 0) 	//4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다.
				cnt++;
		}

		if (belt[down].second) //내려가는 위치에 로봇이 존재
			belt[down].second = false; //내려가는 위치에 로봇이 있다면 반드시 땅으로 내려간다.

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