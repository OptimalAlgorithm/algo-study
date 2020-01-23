//BOJ_9517_���̷���ũ�ξ�Ƽ��
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
		time -= p[i].first; //�ð� ������
		
		if (time <= 0)
			break;

		if (p[i].second == 'T') //������
		{
			++K; //���� ������� �� �ѱ��
			if (K > 8)
				K = 1;
		}

		i++; //���� ����
	}

	cout << K;
}

int main()
{
	input();
	solve();
}
