//https://www.acmicpc.net/problem/17471
//게리맨더링


#include <iostream>
#include <vector>
#include <set>
#include <limits.h>
#include <algorithm>
#include <queue>


using namespace std;



int N; //전체 구역의 수

vector<int> population; //인덱스번째 구역의 인구 수

vector<vector<int>> net; //인접행렬

set<int> selected;

set<int> notSelected;

int answer = INT_MAX;

bool checkCon(set<int> s) { 
	
	//s 집합 안에 "있는" 선거 구들이 모두 연결되어 있는 체크
	int cnt = 1;

	queue<int> q;
	q.push(*s.begin());
	

	vector<int> visited(N, 0);
	visited[q.front()] = 1;

	while (!q.empty()) {
		int p = q.front();
		q.pop();

		for (auto a : s) {
			if (net[p][a] == 1 && visited[a] == 0) {
				visited[a] = 1;
				q.push(a);
				cnt++;
			}
		}
	}

	if (cnt != s.size())return false;
	else return true;	
}

void select(int idx, int cnt) {
	if (cnt == 0) {

		notSelected.clear();
		for (int i = 0; i < N; i++) {
			if (selected.count(i) == 0)notSelected.insert(i);
		}

		if (checkCon(selected) && checkCon(notSelected)) {
			int firstArea = 0;
			int secondArea = 0;

			for (int i = 0; i < N; i++) {
				if (selected.count(i) == 1)firstArea += population[i];
				else secondArea += population[i];
			}

			answer = min(answer, abs(firstArea - secondArea));
		}
		else return;
	}
	else {
		for (int i = idx; i <= N - cnt; i++) {
			selected.insert(i);
			select(i + 1, cnt - 1);
			selected.erase(i);
		}
	}
}


int main() {
	cin >> N;

	population.resize(N, 0); //인구 수 저장
	for (int i = 0; i < N; i++) {
		cin >> population[i];
	}

	net.resize(N, vector<int>(N)); //인접행렬 저장
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;

		int tmp;
		for (int j = 0; j < num; j++) {
			cin >> tmp;
			tmp--;

			net[tmp][i] = 1;
			net[i][tmp] = 1;
		}
	}

	for (int i = 1; i <= N / 2; i++) {
		select(0, i); //i 수 만큼 구역을 뽑는다
	}


	if (answer == INT_MAX)cout << "-1";
	else cout << answer;
}
