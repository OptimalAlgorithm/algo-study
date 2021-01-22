//https://www.acmicpc.net/problem/17070
//������ �ű�� 1

#include <iostream>
#include <vector>

using namespace std;

int N;

vector<vector<int>> map(32, vector<int>(32));
vector<vector<vector<long long>>>dp(32, vector<vector<long long>>(32, vector<long long>(32, 0)));

//int map[32][32];
//int dp[32][32][3]; //����, �밢��, ���� �� ����


int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int j = 1; j < N; j++) { //�� ���� ���δ� �� 1
		if (map[0][j] == 0)dp[0][j][0] = 1;
		else break;
	}

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			
			//���η� ���� - 2��������
			if (map[i][j] == 0) {
				dp[i][j][0] = dp[i][j - 1][0] + dp[i][j - 1][1];
			}

			//�밢������ ���� - 3��������
			if (map[i][j] == 0 && map[i - 1][j] == 0 && map[i][j - 1] == 0) {
				dp[i][j][1] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][2];
			}

			//���η� ���� - 2��������
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