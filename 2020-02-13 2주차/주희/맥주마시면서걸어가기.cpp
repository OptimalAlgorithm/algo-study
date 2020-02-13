//[���� 9205] ���ָ��ø鼭�ɾ��
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
		int N; //������ ��
		cin >> N;

		//��
		int homeX, homeY;
		cin >> homeX >> homeY;

		//������
		set<pair<int, int>> store;
		for (int i{ 0 }; i < N; i++) {
			int tx, ty;
			cin >> tx >> ty;

			store.insert(make_pair(tx, ty));
		}

		//�佺Ƽ��
		int fX, fY;
		cin >> fX >> fY;

		set<pair<int, int>> temp; //���� ��ġ
		temp.insert(make_pair(homeX, homeY));

		while (true) {
			set<pair<int, int>> temp2;

			int check{ 0 };

			for (auto t : temp) {
				if (abs(fX - t.first) + abs(fY - t.second) <= 1000) {
					//�� �� �ִ� �Ÿ� �� �佺Ƽ���� ����
					cout << "happy\n";
					check = 1;
					break;
				}
				else { //�ٷ� �佺Ƽ���� ������ ��� �� �� �ִ� �������� �鸣��

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