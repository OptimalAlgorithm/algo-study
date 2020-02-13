//[백준 9205] 맥주마시면서걸어가기
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t{ 0 }; t < T; t++) {
		int N; //편의점 수
		cin >> N;

		//집
		int homeX, homeY;
		cin >> homeX >> homeY;

		//편의점
		set<pair<int, int>> store;
		for (int i{ 0 }; i < N; i++) {
			int tx, ty;
			cin >> tx >> ty;

			store.insert(make_pair(tx, ty));
		}

		//페스티벌
		int fX, fY;
		cin >> fX >> fY;

		set<pair<int, int>> temp; //현재 위치
		temp.insert(make_pair(homeX, homeY));

		while (true) {
			set<pair<int, int>> temp2;

			int check{ 0 };

			for (auto t : temp) {
				if (abs(fX - t.first) + abs(fY - t.second) <= 1000) {
					//갈 수 있는 거리 내 페스티벌이 존재
					cout << "happy\n";
					check = 1;
					break;
				}
				else { //바로 페스티벌에 못가는 경우 갈 수 있는 편의점에 들르기

					for (auto s : store) {

						//cout << "test: " << abs(s.first - t.first) << " " << abs(s.second - t.second) << "\n";
						if (abs(s.first - t.first) + abs(s.second - t.second) <= 1000) {
							temp2.insert(s);
						}
					}
					for (auto a : temp2) store.erase(a);
				}
			}
			if (check == 1) break;
			else {
				if (temp2.size() == 0) {
					cout << "sad\n";
					break;
				}
				else {
					temp = temp2;
				}
			}

		}


	}

	//system("pause");
	return 0;
}