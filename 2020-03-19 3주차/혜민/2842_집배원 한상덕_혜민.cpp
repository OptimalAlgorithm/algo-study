#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX 51

int N;
char map[MAX][MAX]; 
int altitude[MAX][MAX]; //해당 좌표에 대한 고도
pair <int, int> post; //우체국
int house = 0; //집 갯수
vector <int> altitudeSort; //투포인터를 위해 고도를 따로 저장
int ans = 1000001; //결과값

queue <pair <int, int>> q;
int visited[MAX][MAX] = { 0, };
int dir[8][2] = { {-1, -1}, {-1, 0} , {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

bool bfs(int low, int high, int t)
{
	int r, c, nr, nc, cnt = 0;

	if (altitude[post.first][post.second] > high || altitude[post.first][post.second] < low) //우체국이 최고고도, 최저고도 범위에서 벗어남
		return false;

	q.push(make_pair(post.first, post.second)); //우체국에서 시작
	visited[post.first][post.second] = t;

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		for (int i = 0; i < 8; i++) //가로 세로 대각선. 8방향.
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N || visited[nr][nc] == t) //범위 벗어남 or 이미 방문
				continue;

			if (altitude[nr][nc] > high || altitude[nr][nc] < low) //최고고도, 최저고도 범위에서 벗어남
				continue;

			if (map[nr][nc] == 'K') //집을 만났다!
				cnt++;

			q.push(make_pair(nr, nc));
			visited[nr][nc] = t;
		}
	}

	if (cnt == house) //모든 집을 다 방문했으면 성공.
		return true;
	else
		return false;
}

void solve()
{
	int low = 0, high = 1, t = 1, diff;

	sort(altitudeSort.begin(), altitudeSort.end()); //고도 오름차순 정렬

	while (high < altitudeSort.size()) //투포인터
	{
		if (bfs(altitudeSort[low], altitudeSort[high], t)) //현재 고도차에서 배달 가능
		{
			diff = altitudeSort[high] - altitudeSort[low];
			ans = ans < diff ? ans : diff;

			low++;
			if (low == high)
				high++;
		}
		else //현재 고도차에서 배달 불가능
			high++;

		t++; //다음 턴. visited 초기화 안 하기 위해 사용.
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 'P') //우체국
				post = make_pair(i, j);
			else if (map[i][j] == 'K') //집
				house++;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> altitude[i][j];
			altitudeSort.push_back(altitude[i][j]);
		}
	}

	solve();

	//output
	cout << ans << endl;
}
