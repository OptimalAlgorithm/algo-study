#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int tc;
int n;
int map[1001][1001] = { 0, }; //������
vector <pair<int, int>> tile; //Ÿ�� ��ġ ���� (*�� ����)
int dir[6][2]{ { -1,1 },{ -2,0 },{ -1,-1 },{ 1,-1 },{ 2,0 },{ 1,1 } }; //6���� ������� �̵�.
																	   //     2
																	   //     ��
																	   //   3| *| 1
																	   //   4|  | 6
																	   //     �� 
																	   //     5

int numCnt[6] = { 0, };

void fill_resource(int r, int c)
{
	int check[6] = { true, true, true, true, true, true };
	int minIdx = 0;  //�ڿ���ȣ

					 //üũ
	for (int i = 0; i < 6; i++) //�ֺ� Ÿ���� �ڿ� ����
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];

		if (map[nr][nc] > 0)
			check[map[nr][nc]] = false; //����1. ���ο� Ÿ���� �̹� ä���� ������ Ÿ�Ͽ� ����ִ� �ڿ��� �ٸ� �ڿ��̾�� �Ѵ�.
	}

	numCnt[0] = 10000; // (1 �� n �� 10000)
	for (int i = 1; i <= 5; i++) //����3. �׷��� ��쵵 ���� �������, ��ȣ�� ���� ���� �����Ѵ�.
	{
		if (check[i]) //���� 1�� �����ϸ鼭
			minIdx = numCnt[minIdx] <= numCnt[i] ? minIdx : i; //����2. ������ �ڿ��� ���� ������ ��쿡��, ���忡 ���� ���� ��Ÿ�� �ڿ��� �����Ѵ�.
	}


	//�ڿ� �Ҵ�
	tile.push_back(make_pair(r, c)); //Ÿ�� ����
	map[r][c] = map[r + 1][c] = minIdx; //Ÿ�Ͽ� �ڿ� �Ҵ�(���� ����)
	numCnt[minIdx]++; //����� �ڿ� ���� �߰�
}

void init(int r, int c)
{
	//�ʱ�ȭ
	memset(numCnt, 0, sizeof(numCnt));
	memset(map, 0, sizeof(map));
	tile.clear();

	tile.push_back(make_pair(r, c)); //Ÿ�� ����(0��° �ε��� �������)

									 //ù��° Ÿ�� ����
	tile.push_back(make_pair(r, c)); //Ÿ�� ����
	map[r][c] = map[r + 1][c] = 1; //Ÿ�Ͽ� �ڿ� �Ҵ�(���� ����)
	numCnt[1]++; //����� �ڿ� ���� �߰�
}

void solve()
{
	int r = 500, c = 500;
	int tileIdx = 1;
	int prevr = r + dir[5][0], prevc = c + dir[5][1];

	init(r, c);

	while (1) //��ġ ťó�� ����.
	{
		int i = 0;

		if (tile.size() > n)
			return;

		r = tile[tileIdx].first;
		c = tile[tileIdx].second;

		for (i = 0; i < 6; i++) //6������ �湮
		{
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];

			if (nr == prevr && nc == prevc) //���� �ֽ��� Ÿ�� ��ġ�� ã�´�.
				break;
		}
		++i; //�ֽ� Ÿ�� ��ġ �������� ����.
		if (i >= 6)
			i -= 6;

		while (1) //������������ �ݽð�� ���鼭
		{
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];

			if (map[nr][nc] > 0) //�̹� ���ڰ� ä���� �ִ� ��� ����.
				break;

			//���ο� Ÿ�� ä���
			fill_resource(nr, nc);

			++i; //���� Ÿ�Ϸ�
			if (i >= 6)
				i -= 6;
		}

		prevr = tile[tile.size() - 1].first; //���� �ֽ��� Ÿ�� ��ġ ����.
		prevc = tile[tile.size() - 1].second;
		tileIdx++; //���� Ÿ�Ͽ� ���ؼ� 6�� ���� �湮.
	}
}

void print()
{
	cout << endl;;
	for (int i = 470; i < 530; i++)
	{
		for (int j = 470; j < 530; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
}

int main()
{
	cin >> tc;
	for (int i = 1; i <= tc; i++)
	{
		cin >> n;
		solve();
		cout << map[tile[n].first][tile[n].second] << endl;
		//print();
	}
}