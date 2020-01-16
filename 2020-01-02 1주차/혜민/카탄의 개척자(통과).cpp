#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int tc;
int n;
int map[1001][1001] = { 0, }; //게임판
vector <pair<int, int>> tile; //타일 위치 저장 (*을 저장)
int dir[6][2]{ { -1,1 },{ -2,0 },{ -1,-1 },{ 1,-1 },{ 2,0 },{ 1,1 } }; //6각형 모양으로 이동.
																	   //     2
																	   //     ㅡ
																	   //   3| *| 1
																	   //   4|  | 6
																	   //     ㅡ 
																	   //     5

int numCnt[6] = { 0, };

void fill_resource(int r, int c)
{
	int check[6] = { true, true, true, true, true, true };
	int minIdx = 0;  //자원번호

					 //체크
	for (int i = 0; i < 6; i++) //주변 타일의 자원 조사
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];

		if (map[nr][nc] > 0)
			check[map[nr][nc]] = false; //조건1. 새로운 타일은 이미 채워진 인접한 타일에 들어있는 자원과 다른 자원이어야 한다.
	}

	numCnt[0] = 10000; // (1 ≤ n ≤ 10000)
	for (int i = 1; i <= 5; i++) //조건3. 그러한 경우도 여러 가지라면, 번호가 작은 것을 선택한다.
	{
		if (check[i]) //조건 1에 부합하면서
			minIdx = numCnt[minIdx] <= numCnt[i] ? minIdx : i; //조건2. 가능한 자원이 여러 가지인 경우에는, 보드에 가장 적게 나타난 자원을 선택한다.
	}


	//자원 할당
	tile.push_back(make_pair(r, c)); //타일 저장
	map[r][c] = map[r + 1][c] = minIdx; //타일에 자원 할당(숫자 저장)
	numCnt[minIdx]++; //사용한 자원 개수 추가
}

void init(int r, int c)
{
	//초기화
	memset(numCnt, 0, sizeof(numCnt));
	memset(map, 0, sizeof(map));
	tile.clear();

	tile.push_back(make_pair(r, c)); //타일 저장(0번째 인덱스 버리기용)

									 //첫번째 타일 셋팅
	tile.push_back(make_pair(r, c)); //타일 저장
	map[r][c] = map[r + 1][c] = 1; //타일에 자원 할당(숫자 저장)
	numCnt[1]++; //사용한 자원 개수 추가
}

void solve()
{
	int r = 500, c = 500;
	int tileIdx = 1;
	int prevr = r + dir[5][0], prevc = c + dir[5][1];

	init(r, c);

	while (1) //마치 큐처럼 동작.
	{
		int i = 0;

		if (tile.size() > n)
			return;

		r = tile[tileIdx].first;
		c = tile[tileIdx].second;

		for (i = 0; i < 6; i++) //6개지점 방문
		{
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];

			if (nr == prevr && nc == prevc) //가장 최신의 타일 위치를 찾는다.
				break;
		}
		++i; //최신 타일 위치 다음부터 시작.
		if (i >= 6)
			i -= 6;

		while (1) //시작지점부터 반시계로 돌면서
		{
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];

			if (map[nr][nc] > 0) //이미 숫자가 채워져 있는 경우 종료.
				break;

			//새로운 타일 채우기
			fill_resource(nr, nc);

			++i; //다음 타일로
			if (i >= 6)
				i -= 6;
		}

		prevr = tile[tile.size() - 1].first; //가장 최신의 타일 위치 저장.
		prevc = tile[tile.size() - 1].second;
		tileIdx++; //다음 타일에 대해서 6개 지점 방문.
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