// https://www.acmicpc.net/problem/9517

#include<iostream>
#include<vector>

using namespace std;

int K, N;
vector<pair<int, char>> v;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> K >> N;
	for (int i = 0; i < N; i++) {
		int time;
		char answer;
		cin >> time >> answer;
		v.push_back(make_pair(time, answer));
	}

	int personNum = --K;
	int total_time = 210;
	for(int i = 0; i < v.size(); i++){
		personNum %= 8;

		int taketime = v[i].first;
		char response = v[i].second;

		if (response == 'N' || response == 'P') {	// 질문에 답이 틀린경우
			total_time -= taketime;
			if (total_time <= 0) break;
		}
		else if (response == 'T') {
			total_time -= taketime;
			if (total_time <= 0) break;
			personNum++;
		}
	}
	
	cout << personNum+1 << '\n';
	return 0;
}