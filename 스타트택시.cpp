//https://www.acmicpc.net/problem/19238
//스타트 택시


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <math.h>



using namespace std;

int N, M, fuel;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int curX, curY; //택시위치

int map[30][30]; //0:빈칸 1:벽

int guest[30][30]; //손님위치

//int dest[20][20]; //도착위치

int gNum; //손님 번호

vector<pair<int, int>> dest;


void findGuestAndMove() {
	int visited[30][30] = {};

	//bfs로 손님찾기
	set<pair<int, int>> tmp; //손님 후보 저장 - 행, 열 우선순위로 자동정렬	

	int dist = 0; //손님까지 거리계산

	queue<pair<int, int>> q;
	visited[curX][curY] = 1;
	q.push(make_pair(curX, curY));

	while (true) {
		int size = q.size();

		if (size == 0) { //손님까지 못감
			cout << "-1";
			exit(0);
		}
		else dist++;

		for (int i = 0; i < size; i++) {
			pair<int, int> p = q.front();
			q.pop();


			for (int d = 0; d < 4; d++) {
				int tx = p.first + dx[d];
				int ty = p.second + dy[d];

				if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;

				if (guest[tx][ty] > 0) { //손님 발견
				//	cout << "손님발견: " << tx << " " << ty << guest;
					tmp.insert(make_pair(tx, ty));
				}
				else if (map[tx][ty] == 0 && visited[tx][ty] != 1) {
					visited[tx][ty] = 1;
					q.push(make_pair(tx, ty));
				}
			}
		}

		if (tmp.size() > 0) break;
	}

	//가장 우선순위 높은 손님이 지정됨
	curX = (*tmp.begin()).first;
	curY = (*tmp.begin()).second;


	//손님까지 이동- curX, curY에서 gX, gY로
	gNum = guest[curX][curY];
	guest[curX][curY] = 0; //손님 목록에서 제거
	//cout << "손님확인: " << curX << " " << curY << "\n";
	fuel -= dist; //연료감소


	if (fuel < 0) { //연료부족
		cout << "-1";
		exit(0);
	}
}

void moveToDest() {
	int visited[30][30] = {};

	queue<pair<int, int>> q;
	visited[curX][curY] = 1;
	q.push(make_pair(curX, curY));

	int dist = 0;

	while (true) {
		int size = q.size();

		if (size == 0) { //목적지까지 못감
			cout << "-1";
			exit(0);
		}
		//else cout << size << "size\n";

		fuel--;
		if (fuel < 0) { //연료부족
			cout << "-1";
			exit(0);
		}

		dist++;

		for (int i = 0; i < size; i++) {
			pair<int, int> p = q.front();
			q.pop();
			//cout << "좌표: " << p.first << p.second << "\n";

			for (int d = 0; d < 4; d++) {
				int tx = p.first + dx[d];
				int ty = p.second + dy[d];

				if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;

				if (tx == dest[gNum].first && ty == dest[gNum].second) { //목적지 도착
					curX = tx;
					curY = ty;

					fuel += 2 * dist;

					return;
				}
				else if (map[tx][ty] == 0 && visited[tx][ty] != 1) {
					visited[tx][ty] = 1;
					q.push(make_pair(tx, ty));
				}
			}
		}
	}
}

void simulate() {

	if (guest[curX][curY] != 0) { //현재 위치에 손님이있으면
		gNum = guest[curX][curY];
		guest[curX][curY] = 0;
	}
	else findGuestAndMove(); //가장 가까운 손님 찾아서 이동	
	//cout << "\n여기 손님 태움: " << curX << " " << curY << " " << fuel << "\n";

	//bfs로 목적지까지 이동- curX,curY에서 dest[][]에서 손님번호 나올때까지
	if (curX != dest[gNum].first || curY != dest[gNum].second) {
		moveToDest();
	}
	//cout << "여기 도착지로 이동: " << curX << " " << curY << " " << fuel << "\n";

	M--; //손님 한명 데려다줬다는 뜻
	if (M > 0)simulate(); //손님이 남아있으면 또 진행
}


int main() {
	cin >> N >> M >> fuel;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	cin >> curX >> curY; //택시위치
	curX--; curY--;

	dest.push_back(make_pair(-1, -1)); //제로패딩

	//손님 - 1번부터
	int x1, y1, x2, y2;
	for (int i = 1; i <= M; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;
		guest[x1][y1] = i;
		dest.push_back(make_pair(x2, y2));
	}

	simulate();

	cout << fuel;
}