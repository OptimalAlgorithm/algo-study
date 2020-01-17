//��

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int R, C;
	cin >> R >> C;

	//�־����� ������ �Է�
	vector<string> map;
	for (int r{ 0 }; r < R; r++) {
		string s;
		cin >> s;

		map.push_back(s);
	}

	//����
	vector<pair<int, int>> dir;
	dir.push_back(make_pair(-1, 0)); //��
	dir.push_back(make_pair(1, 0)); //��
	dir.push_back(make_pair(0, -1)); //��
	dir.push_back(make_pair(0, 1)); //��

	int sheep{ 0 }, wolf{ 0 };

	for (int i{ 0 }; i < R; i++) {
		for (int j{ 0 }; j < C; j++) {
			if (map[i][j] != 'C') {//üũ���ߴ� ���̸�
				int counto{ 0 }, countv{ 0 };
				vector<pair<int, int>> temp;
				temp.push_back(make_pair(i, j));

				while (temp.size() > 0) {
					int x = temp.back().first;
					int y = temp.back().second;

					temp.pop_back();

					for (auto a : dir) {
						int xx = x + a.first;
						int yy = y + a.second;

						if (xx >= 0 && xx < R && yy >= 0 && yy < C) {
							if (map[xx][yy] != 'C') {
								if (map[xx][yy] == '.') { //����
									map[xx][yy] = 'C'; //üũ
									temp.push_back(make_pair(xx, yy));
								}
								else if (map[xx][yy] == 'o') { //��
									map[xx][yy] = 'C'; //üũ
									temp.push_back(make_pair(xx, yy));
									counto++;
								}
								else if (map[xx][yy] == 'v') { //����
									map[xx][yy] = 'C'; //üũ
									temp.push_back(make_pair(xx, yy));
									countv++;
								}
								else {} //��Ÿ��
							}
						}
					}
				}

				if (counto > countv) sheep += counto;
				else wolf += countv;
			}
		}
	}

	cout << sheep << " " << wolf;

	system("pause");
	return 0;
}