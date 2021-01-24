//https://www.acmicpc.net/problem/17471
//�Ը��Ǵ���


#include <iostream>
#include <vector>
#include <set>
#include <limits.h>
#include <algorithm>
#include <queue>


using namespace std;



int N; //��ü ������ ��

vector<int> population; //�ε�����° ������ �α� ��

vector<vector<int>> net; //�������

set<int> selected;

set<int> notSelected;

int answer = INT_MAX;

bool checkCon(set<int> s) { 
	
	//s ���� �ȿ� "�ִ�" ���� ������ ��� ����Ǿ� �ִ� üũ
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

	population.resize(N, 0); //�α� �� ����
	for (int i = 0; i < N; i++) {
		cin >> population[i];
	}

	net.resize(N, vector<int>(N)); //������� ����
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
		select(0, i); //i �� ��ŭ ������ �̴´�
	}


	if (answer == INT_MAX)cout << "-1";
	else cout << answer;
}
