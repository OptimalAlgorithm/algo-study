#include <iostream>
#include <cstring>
using namespace std;
#define MAX 100001

int T, N;
int arr[MAX];
int visited[MAX];
int rslt;
int ans = 0;

int dfs(int i, int target)
{
	if (visited[i] >= 2 ) //이미 판별이 끝났음.
		return -1;

	if (i == target || visited[i] == 1) //사이클 형성 가능(본인 혼자 팀 or 이번 턴에 방문한 애들 중 일부)
		return i;

	visited[i] = 1; //현재 방문 중
	rslt = dfs(arr[i], target);

	if(rslt == -1)
		visited[i] = 3; //사이클이 될 수 없음.
	else if(rslt > 0) 
		visited[i] = 2; //사이클

	if (rslt == i) //사이클의 시작점. 이후부터는 사이클이 될 수 없으므로 -1을 리턴.
		rslt = -1;
	return rslt;
}

void solve()
{
	memset(visited, 0, sizeof(visited));

	for (int i = 1; i <= N; i++)
	{
		if (visited[i] > 0) //이미 방문하여 판별이 끝났음.
			continue;
		
		visited[i] = 1; //현재 방문 중
		rslt = dfs(arr[i], i);

		if (rslt == -1)
			visited[i] = 3; //사이클이 될 수 없음.
		if (rslt > 0)
			visited[i] = 2; //사이클
	}

	ans = 0;
	for (int i = 1; i <= N; i++)
	{
		if (visited[i] != 2) //사이클 = 팀 인 것 빼고.
			ans++;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);


	cin >> T;
	for (int t = 0; t < T; t++)
	{
		//input
		cin >> N;
		for (int i = 1; i <= N; i++)
			cin >> arr[i];

		solve();

		//output
		cout << ans << endl;
	}
}