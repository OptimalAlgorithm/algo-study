//https://www.acmicpc.net/problem/17070
//파이프 옮기기 1

#include <iostream>
#include <vector>

using namespace std;

int N;

vector<vector<int>> map(32, vector<int>(32));
vector<vector<vector<long long>>>dp(32, vector<vector<long long>>(32, vector<long long>(32, 0)));

//int map[32][32];
//int dp[32][32][3]; //가로, 대각선, 세로 로 도착


int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int j = 1; j < N; j++) { //맨 윗줄 가로는 다 1
		if (map[0][j] == 0)dp[0][j][0] = 1;
		else break;
	}

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			
			//가로로 도착 - 2가지가능
			if (map[i][j] == 0) {
				dp[i][j][0] = dp[i][j - 1][0] + dp[i][j - 1][1];
			}

			//대각선으로 도착 - 3가지가능
			if (map[i][j] == 0 && map[i - 1][j] == 0 && map[i][j - 1] == 0) {
				dp[i][j][1] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][2];
			}

			//세로로 도착 - 2가지가능
			if (map[i][j] == 0) {
				dp[i][j][2] = dp[i - 1][j][1] + dp[i - 1][j][2];
			}

		}
	}

	long long answer = 0;
	answer += dp[N - 1][N - 1][0];
	answer += dp[N - 1][N - 1][1];
	answer += dp[N - 1][N - 1][2];
	cout << answer;

}