#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;

	vector<string> map;
	//���� �Է�
	for (int i{ 0 }; i < N; i++) {
		string s;
		cin >> s;

		map.push_back(s);
	}

	vector<string> map2;
	map2 = map;


	//���� �̵� - ��, ��, ��, ��
	vector<pair<int, int>> dir;
	dir.push_back(make_pair(-1, 0));
	dir.push_back(make_pair(1, 0));
	dir.push_back(make_pair(0, -1));
	dir.push_back(make_pair(0, 1));


	//���ϻ����� �ƴѰ��
	int color1{ 0 };
	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < N; j++) {
			if (map[i][j] != 'C') {

				char value = map[i][j];
				map[i][j] = 'C';


				vector<pair<int, int>> temp;
				temp.push_back(make_pair(i, j));

				while (temp.size() > 0) {
					int x = temp.back().first;
					int y = temp.back().second;

					temp.pop_back();

					for (auto a : dir) {
						int xx = x + a.first;
						int yy = y + a.second;

						if (xx >= 0 && xx < N && yy >= 0 && yy < N) {
							if (map[xx][yy] == value) {
								map[xx][yy] = 'C';
								temp.push_back(make_pair(xx, yy));
							}
						}
					}

				}
				color1++;
			}
		}
	}

	//���ϻ����� ���
	int color2{ 0 };
	//������ �ʷ����� �� �ٲ�
	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < N; j++) {
			if (map2[i][j] == 'R') map2[i][j] = 'G';
		}
	}
	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < N; j++) {
			if (map2[i][j] != 'C') {

				char value = map2[i][j];
				map2[i][j] = 'C';


				vector<pair<int, int>> temp;
				temp.push_back(make_pair(i, j));

				while (temp.size() > 0) {
					int x = temp.back().first;
					int y = temp.back().second;

					temp.pop_back();

					for (auto a : dir) {
						int xx = x + a.first;
						int yy = y + a.second;

						if (xx >= 0 && xx < N && yy >= 0 && yy < N) {
							if (map2[xx][yy] == value) {
								map2[xx][yy] = 'C';
								temp.push_back(make_pair(xx, yy));
							}
						}
					}

				}
				color2++;
			}
		}
	}



	cout << color1 << " " << color2;

	//system("pause");
	return 0;
}