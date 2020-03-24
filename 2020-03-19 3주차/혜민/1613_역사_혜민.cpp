#include <iostream>
using namespace std;
#define MAX 401
#define INF 1000000000
int N, K, S;
int edge[MAX][MAX] = { 0, };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int from, to;

	//초기화
	for (int i = 1; i < MAX; i++)
	{
		for (int j = 1; j < MAX; j++)
		{
			if (i != j)
				edge[i][j] = INF;
		}
	}

	//input
	cin >> N >> K;
	for (int i = 0; i < K; i++)
	{
		cin >> from >> to;
		edge[from][to] = 1;
	}

	//floyd
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (edge[i][j] > edge[i][k] + edge[k][j]) //최단거리 갱신
					edge[i][j] = edge[i][k] + edge[k][j];
			}
		}
	}

	cin >> S;
	for (int i = 0; i < S; i++)
	{
		cin >> from >> to;

		//output
		if (edge[from][to] != INF)
			cout << "-1" << endl;
		else if (edge[to][from] != INF)
			cout << "1" << endl;
		else
			cout << "0" << endl;
	}
}
