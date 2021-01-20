//https://www.acmicpc.net/problem/14503
//로봇 청소기



//세로 크기 N과 가로 크기 M


// 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽


#include <iostream>
#include <vector>

using namespace std;


int N, M;

int cnt = 0;

int dx[4] = { -1,0,1,0 }; //북 동 남 서
int dy[4] = { 0,1,0,-1 };

vector<vector<int>> map;//빈 칸은 0, 벽은 1

vector<vector<int>> visited;



void simulate(int r, int c, int d) {

	//cout << "\n\nR  C  D: " << r << " " << c << " " << d << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			//cout << visited[i][j];
		}
		//cout << "\n";
	}

	if (visited[r][c] == 0) {
		visited[r][c] = 1;
		cnt++;
	}


	for (int dir = 1; dir <= 4; dir++) {

		int nextDir = d - dir;
		if (nextDir < 0)nextDir += 4;
		//cout << "nextDir: " << nextDir << "\n";
		int tx = r + dx[nextDir];
		int ty = c + dy[nextDir];

		if (tx > 0 && tx < N - 1 && ty > 0 && ty < M - 1) {
			if (visited[tx][ty] == 0 && map[tx][ty] != 1) {
				simulate(tx, ty, nextDir);
				return;
			}
		}
	}

	//4방향 청소가 이미되어있음

	//후진 좌표
	int tx = r - dx[d];
	int ty = c - dy[d];

	if (tx == 0 || tx == N - 1 || ty == 0 || ty == M - 1 || map[tx][ty] == 1) { //후진못함
		cout << cnt;
		exit(0);
	}

	//후진 가능
	simulate(tx, ty, d);


}


int main() {
	cin >> N >> M;

	int r, c, d;
	cin >> r >> c >> d;

	map.resize(N, vector<int>(M));
	visited.resize(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] == 1) visited[i][j] = 2;
		}
	}

	simulate(r, c, d);

	cout << cnt;
}