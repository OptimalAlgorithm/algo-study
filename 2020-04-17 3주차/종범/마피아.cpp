// https://www.acmicpc.net/problem/1079

#include<bits/stdc++.h>
using namespace std;

const int MAX = 17;
int N, ans;
int MAP[MAX];		// 유죄지수
int R[MAX][MAX];	// 유죄지수 변동지수
bool alive[MAX];	// 생존여부
int mafia;

void MAP_change(int i) {
	for (int j = 0; j < N; j++) {
		if (!alive[j]) continue;
		MAP[j] += R[i][j];
	}
}

void MAP_reverse(int i) {
	for (int j = 0; j < N; j++) {
		if (!alive[j]) continue;
		MAP[j] -= R[i][j];
	}
}

void brute(int citizen, char day, int cnt) {
	if (!alive[mafia]) {		// 마피아가 죽었다는건 낮에 죽었다는 뜻
		ans = max(ans, cnt);
		return;
	}
	if (citizen == 0) {			// 시민이 0이라는건 마피아가 최종까지 살았다는 뜻
		ans = max(ans, cnt);
		return;
	}

	if (day == 'n') {		// 밤인경우
		for (int i = 0; i < N; i++) {
			if (i == mafia || !alive[i]) continue;		// 마피아거나 시민이 이미 죽은 경우
			alive[i] = false;
			MAP_change(i);
			brute(citizen - 1, 'a', cnt + 1);
			MAP_reverse(i);
			alive[i] = true;
		}
	}
	else if (day == 'a') {	// 낮인경우
		int person = 0, maxMAP = 0;
		for (int i = N - 1; i >= 0; i--) {	// 유죄지수 높으면서 가장 아래번호 인 사람 구하기
			if (!alive[i]) continue;
			if (MAP[i] >= maxMAP) {
				maxMAP = MAP[i];
				person = i;
			}
		}
		alive[person] = false;
		if (person == mafia)
			brute(citizen, 'n', cnt);
		else
			brute(citizen - 1, 'n', cnt);
		alive[person] = true;
	}
}

void solve() {
	memset(alive, true, sizeof(alive));

	if (N % 2 == 0)	// 밤
		brute(N - 1, 'n', 0);
	else			// 낮;
		brute(N - 1, 'a', 0);

	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> MAP[i];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> R[i][j];
	cin >> mafia;
	solve();
	return 0;
}