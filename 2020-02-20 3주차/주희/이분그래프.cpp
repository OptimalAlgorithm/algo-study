//[���� 1707] �̺� �׷��� 

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int V, E;

vector<vector<int>> connected; //�׷����� �������
vector<int> team; //0�� ����, 1��, 2��

bool ans;

void checkTeam(int v) {
	for (auto a : connected[v]) {
		if (team[a] == team[v]) {
			ans = false;
			//cout << "�갡 ����" << v;
			break;
		}
		else {
			if (team[a] == 0) {
				if (team[v] == 1) team[a] = 2;
				else team[a] = 1;

				checkTeam(a);
			}
		}
	}
	return;
}

int main() {
	int T;
	cin >> T;

	for (int t{ 0 }; t < T; t++) {
		//�Է�, �ʱ�ȭ
		cin >> V >> E;

		connected.clear();
		connected.resize(V);

		team.clear();
		team.resize(V, 0);

		ans = true;

		//connected�� �Է�
		for (int e{ 0 }; e < E; e++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;

			connected[a].push_back(b);
			connected[b].push_back(a);
		}

		for (int v{ 0 }; v < V; v++) {
			if (team[v] == 0) {
				team[v] = 1;
				checkTeam(v);
			}
		}

		if (ans == true) cout << "YES\n";
		else cout << "NO\n";

	}

	//system("pause");
	return 0;
}