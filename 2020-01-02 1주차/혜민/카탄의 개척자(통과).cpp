#include<iostream>
#include<vector>
using namespace std;

int n, m;
int cnt = -1; //�����̷��� �ɸ� ������ ��ǻ�ʹ� ����!
vector <int> computer[101];
bool visited[101];

void input()
{
	cin >> n; //��ǻ�� ����
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