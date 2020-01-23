// https://www.acmicpc.net/problem/2174

#include<iostream>
#include<vector>

using namespace std;

typedef struct {
	int x, y, dir;
}Robot;

const int MAX = 100;
int A, B, N, M;
int MAP[MAX][MAX];
bool finish;
vector<Robot> v;
vector<pair<pair<int, char>, int>> cmd;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void show() {
	cout << "--------------------" << '\n';
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < B; j++) {
			cout << MAP[i][j] << ' ';
		}
		cout << '\n';
	}
}

int left_rotate(int dir) {
	if (dir == 0) return 2;
	else if (dir == 1) return 3;
	else if (dir == 2) return 1;
	else if (dir == 3) return 0;
}

int right_rotate(int dir) {
	if (dir == 0) return 3;
	else if (dir == 1) return 2;
	else if (dir == 2) return 0;
	else if (dir == 3) return 1;
}

void simulation() {
	int RobotNum, cnt;
	char whatcmd;
	for (int i = 0; i < cmd.size(); i++) {
		RobotNum = cmd[i].first.first;		//명령이 작용할 로봇
		whatcmd = cmd[i].first.second;		//어떤 멍령인지
		cnt = cmd[i].second;				//명령 횟수
		
		//show();
		if (whatcmd == 'L') {
			int dir = v[RobotNum - 1].dir;
			cnt %= 4;
			for (int k = 0; k < cnt; k++) 
				dir = left_rotate(dir);
			v[RobotNum - 1].dir = dir;
		}
		else if (whatcmd == 'R') {
			int dir = v[RobotNum - 1].dir;
			cnt %= 4;
			for (int k = 0; k < cnt; k++) 
				dir = right_rotate(dir);
			v[RobotNum - 1].dir = dir;
		}
		else if (whatcmd == 'F') {
			MAP[v[RobotNum - 1].x][v[RobotNum - 1].y] = 0; // F명령인 경우에만 지워줘야함

			int x = v[RobotNum - 1].x;
			int y = v[RobotNum - 1].y;
			int dir = v[RobotNum - 1].dir;

			for (int k = 0; k < cnt; k++) {
				x += dx[dir];
				y += dy[dir];
				if (x < 0 || x >= A || y < 0 || y >= B) {	// 벽 밖으로 나간 경우
					cout << "Robot " << RobotNum << " crashes into the wall" << '\n';
					finish = true;
					break;
				}
				else if (MAP[x][y] != 0) {	// 다른 로봇이랑 부딫힌 경우
					cout << "Robot " << RobotNum << " crashes into robot " << MAP[x][y] << '\n';
					finish = true;
					break;
				}
			}
			if (finish) break;

			MAP[x][y] = RobotNum;
			v[RobotNum - 1].x = x;
			v[RobotNum - 1].y = y;
		}
	}
}

int dir_conversion(char dir) {
	if (dir == 'E') return 0;
	else if (dir == 'W') return 1;
	else if (dir == 'S') return 3;
	else if (dir == 'N') return 2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> B >> A >> N >> M;
	for (int i = 1; i <= N; i++) {
		Robot R;
		char dir;
		cin >> R.y >> R.x >> dir;
		R.x -= 1;
		R.y -= 1;
		MAP[R.x][R.y] = i;
		R.dir = dir_conversion(dir);
		v.push_back(R);
	}

	for (int i = 0; i < M; i++) {
		int RobotNum, cnt;
		char c;
		cin >> RobotNum >> c >> cnt;
		cmd.push_back(make_pair(make_pair(RobotNum, c), cnt));
	}

	simulation();
	if (finish == false) 
		cout << "OK" << '\n';
	return 0;
}