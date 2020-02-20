//[백준 3048] 개미

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	int N1, N2;
	cin >> N1 >> N2;

	int T;
	string s1, s2;

	cin >> s1 >> s2 >> T;

	//개미, 방향
	vector<vector<char>> ants;

	//오른쪽진행 개미 ants에 입력
	for (int i{ N1 - 1 }; i >= 0; i--) {
		ants.push_back({ s1[i], 'R' });
	}

	//왼쪽진행 개미 ants에 입력
	for (int i{ 0 }; i < N2; i++) {
		ants.push_back({ s2[i], 'L' });
	}

	for (int t{ 0 }; t < T; t++) {
		for (int i{ 0 }; i < N1 + N2 - 1; i++) {
			//진행 방향이 다를 경우
			if (ants[i][1] == 'R' && ants[i + 1][1] == 'L') {
				vector<char> tmp = ants[i];

				ants[i] = ants[i + 1];
				ants[i + 1] = tmp;
				i++;
			}

			//같으면 그냥 넘어감
		}
	}

	for (auto a : ants) cout << a[0];

	//system("pause");
	return 0;
}