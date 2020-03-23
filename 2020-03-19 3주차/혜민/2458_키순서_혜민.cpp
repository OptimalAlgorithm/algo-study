#include <iostream>
using namespace std;
#define MAX 501

int N, M;
bool dist[MAX][MAX];
int ans = 0;

void solve()
{
	int cnt = 0;

	//플로이드 와샬
	for (int k = 1; k <= N; k++) //경유지
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (dist[i][k] == true && dist[k][j] == true) //i에서 k가는 경로가 존재하고, k에서 j가는 경로가 존재한다면
					dist[i][j] = true; //i에서 j가는 경로는 존재한다.
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		cnt = 0;

		for (int j = 1; j <= N; j++)
		{
			if (dist[i][j] || dist[j][i] || i == j) //경로가 존재 or 자기자신
				cnt++;
		}

		if (cnt == N)
			ans++;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//초기화
	for (int i = 1; i < MAX; i++)
	{
		for (int j = 1; j < MAX; j++)
				dist[i][j] = false;
	}

	//input
	int from, to;
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> from >> to;
		dist[from][to] = true;
	}

	solve();

	//output
	cout << ans << endl;
}
