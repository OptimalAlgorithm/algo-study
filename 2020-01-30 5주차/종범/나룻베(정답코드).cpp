// https://www.acmicpc.net/problem/2065

#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

typedef struct {
	int time; string pos; int idx;
}Passenger;

const int MAX = 10000;
int M, t, N;	// 최대 수용인원, 강 이동시간, 명렁 개수
queue<Passenger> L, R;	// 왼쪽 오른쪽 대기열을 나눈다
char pos = 'L';		// 배의 현재위치
int arriveTime[MAX];	// 도착시간 출력을 위한 배열

void simulation() {
	int time = 0;

	while (L.size() + R.size() != 0) {
		int flag = 0;
		if (L.size() != 0 && L.front().time <= time) {
			flag = 1;
			if (pos == 'L') {
				pos = 'R';
				int cnt = 0;
				while (L.size() != 0 && L.front().time <= time && cnt < M) {
					arriveTime[L.front().idx] = time + t;
					L.pop();
					cnt++;
				}
				time += t;
			}
			else {
				time += t;
				int cnt = 0;
				while (L.size() != 0 && L.front().time <= time && cnt < M) {
					arriveTime[L.front().idx] = time + t;
					L.pop();
					cnt++;
				}
				time += t;
			}
		}
		if (R.size() != 0 && R.front().time <= time) {
			flag = 1;
			if (pos == 'R') {
				pos = 'L';
				int cnt = 0;
				while (R.size() != 0 && R.front().time <= time && cnt < M) {
					arriveTime[R.front().idx] = time + t;
					R.pop();
					cnt++;
				}
				time += t;
			}
			else {
				time += t;
				int cnt = 0;
				while (R.size() != 0 && R.front().time <= time && cnt < M) {
					arriveTime[R.front().idx] = time + t;
					R.pop();
					cnt++;
				}
				time += t;
			}
		}
		if (flag == 0) {
			time++;
		}
	}
	for (int i = 0; i < N; i++) {
		cout << arriveTime[i] << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> M >> t >> N;
	for (int i = 0; i < N; i++) {
		Passenger p;
		cin >> p.time >> p.pos;
		p.idx = i;
		if (p.pos == "left")L.push(p);
		else R.push(p);
	}

	simulation();
	return 0;
}