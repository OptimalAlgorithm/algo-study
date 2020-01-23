//BOJ_9517_아이러브크로아티아
#include <iostream>
#include <vector>
using namespace std;

int K, N;
vector <pair<int, char>> p;

void input()
{
	cin >> K;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int time;
		char answer;
		cin >> time >> answer;
		p.push_back(make_pair(time, answer));
	}
}

void solve()
{
	int time = 210;
	int i = 0;

	while (true)
	{
		time -= p[i].first; //시간 지났음
		
		if (time <= 0)
			break;

		if (p[i].second == 'T') //맞췄음
		{
			++K; //다음 사람으로 턴 넘기기
			if (K > 8)
				K = 1;
		}

		i++; //다음 문제
	}

	cout << K;
}

int main()
{
	input();
	solve();
}
