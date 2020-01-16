#include<iostream>
#include<vector>
using namespace std;

int n, m;
int cnt = -1; //웜바이러스 걸린 최초의 컴퓨터는 빼고!
vector <int> computer[101];
bool visited[101];

void input()
{
	cin >> n; //컴퓨터 개수
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int r, c;
		cin >> r >> c;
		computer[r].push_back(c);
		computer[c].push_back(r);
	}
}

void dfs(int vertex)
{
	visited[vertex] = true;
	cnt++;
	for (int i = 0; i < computer[vertex].size(); i++)
	{
		if (visited[computer[vertex][i]])
			continue;
		dfs(computer[vertex][i]);
	}
}

int main()
{
	input();
	dfs(1);
	cout << cnt << endl;
}