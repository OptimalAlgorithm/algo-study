// https://www.acmicpc.net/problem/17822
// 19년 하반기 무선사업부 1번

#include<bits/stdc++.h>
using namespace std;

typedef struct {
	int x, d, k;
}Cmd;

const int MAX = 50;
int N, M, T, ans;
int MAP[MAX][MAX];
bool visited[MAX][MAX];
bool flag;
vector<Cmd> v;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

// 평균 작업
void working() {
	int sum = 0, cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] != 0) {
				sum += MAP[i][j];
				cnt++;
			}
		}
	}

	double middle = (double)sum / cnt;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] != 0) {
				if (MAP[i][j] < middle) MAP[i][j] += 1;
				else if (MAP[i][j] > middle) MAP[i][j] -= 1;
			}
		}
	}
}

// 인접한 수 지우기
void remove_num() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) continue;
			int temp = MAP[i][j];
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 0 || nx >= N) continue;
				if (ny < 0) {
					ny = M - 1;
					if (MAP[nx][ny] == temp) {
						visited[nx][ny] = true;
						flag = true;
					}
				}
				else if (ny >= M) {
					ny = 0;
					if (MAP[nx][ny] == temp) {
						visited[nx][ny] = true;
						flag = true;
					}
				}
				else {
					if (MAP[nx][ny] == temp) {
						visited[nx][ny] = true;
						flag = true;
					}
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (visited[i][j]) MAP[i][j] = 0;
}

void simulation() {
	for (int idx = 0; idx < v.size(); idx++) {
		flag = false;			// 인접한 수가 하나도 지워지지 않는 경우에 평균작업을 실시하기 위한 flag
		int x = v[idx].x;		// x의 배수인 원판을 돌리자
		int d = v[idx].d;		// 0이면 시계, 1이면 반시계
		int k = v[idx].k;		// 회전 횟수

		queue<int> q;			// 배수에 해당하는 판넘버 구하기
		for (int i = 0; i < N; i++) {
			if ((i + 1) % x == 0) {
				q.push(i);
			}
		}

		if (d == 0) {			// 시계 방향
			int size = q.size();
			for (int i = 0; i < size; i++) {
				int num = q.front();
				q.pop();
				for (int cnt = 0; cnt < k; cnt++) {
					int temp = MAP[num][M - 1];
					for (int j = M - 2; j >= 0; j--) {
						MAP[num][j + 1] = MAP[num][j];
					}
					MAP[num][0] = temp;
				}
			}
		}
		else if (d == 1) {			// 반시계 방향
			int size = q.size();
			for (int i = 0; i < size; i++) {
				int num = q.front();
				q.pop();
				for (int cnt = 0; cnt < k; cnt++) {
					int temp = MAP[num][0];
					for (int j = 1; j < M; j++) {
						MAP[num][j - 1] = MAP[num][j];
					}
					MAP[num][M - 1] = temp;
				}
			}
		}
		remove_num();
		memset(visited, false, sizeof(visited));
		if (!flag) working();
	}
}

void Print() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			ans += MAP[i][j];
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N >> M >> T;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];

	for (int i = 0; i < T; i++) {
		int x, d, k;
		cin >> x >> d >> k;
		v.push_back({ x,d,k });
	}

	simulation();
	Print();
	return 0;
}