//������ 1ȣ

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

	int n, m;
	cin >> n >> m;

	vector<char> str(m, '0');
	vector<vector<char>> map(n, str);


	//�׼��� map �Է�
	for (int i{ 0 }; i < n; i++) {
		for (int j{ 0 }; j < m; j++) {

			cin >> map[i][j];
		}
	}

	//Ž�缱 ��ġ
	int pr, pc;
	cin >> pr >> pc;

	pr--;
	pc--;


	//����
	vector<pair<int, int>> dir;
	dir.push_back(make_pair(-1, 0)); // U
	dir.push_back(make_pair(0, 1)); // R
	dir.push_back(make_pair(1, 0)); // D
	dir.push_back(make_pair(0, -1)); // L



	vector<int> record;

	//�� ������⸶�� �ɸ��� �ð� ���
	for (int direction{ 0 }; direction < 4; direction++) {

		//�ɸ��� �ð�
		int sec{ 0 };

		//���� �������
		int ddd{ direction };
		int nr = pr;
		int nc = pc;



		//////////////////////�ʱ�ȭ �� ���� ���!
		while (true) {

			//��ĭ �̵�
			nr += dir[ddd].first;
			nc += dir[ddd].second;
			sec++; //�� ����



				   //map �ȿ� �ִٸ�
			if (nr >= 0 && nr < n && nc >= 0 && nc < m) {

				//���� �������� ���ڸ��� ���ƿ��� ���
				if (nr == pr && nc == pc && ddd == direction) {
					record.push_back(-1);
					break;
				}

				//���� �������� ���ڸ��� �ƴѰ��
				if (map[nr][nc] == '.') {
					//�ƹ��͵� ���� ����. �״�� ����
				}
				else if (map[nr][nc] == 'C') {
					//���� �� �����ϰ� ����
					record.push_back(sec);
					break;
				}
				else if (map[nr][nc] == '/') {
					//���� ��ȯ
					switch (ddd) {
					case 0:
						ddd = 1;
						break;
					case 1:
						ddd = 0;
						break;
					case 2:
						ddd = 3;
						break;
					case 3:
						ddd = 2;
						break;
					default:
						break;
					}
				}
				else {
					//���� ��ȯ
					switch (ddd) {
					case 0:
						ddd = 3;
						break;
					case 1:
						ddd = 2;
						break;
					case 2:
						ddd = 1;
						break;
					case 3:
						ddd = 0;
						break;
					default:
						break;
					}
				}



			}
			else { //�� ����ϰ� ����
				record.push_back(sec);
				break;
			}
		}


	}

	int cur{ 0 };
	int curI;
	vector<string> dirN = { "U", "R", "D", "L" };

	for (int r{ 0 }; r < 4; r++) {
		//-1���� ��� Voyager
		if (record[r] == -1) {
			cout << dirN[r] << "\n" << "Voyager";
			//system("pause");
			return 0;
		}
		else {
			if (record[r] > cur) {
				cur = record[r];
				curI = r;
			}
		}
	}

	//cout << "**************records: ";
	//for (auto a : record) cout << a << " ";





	cout << dirN[curI] << "\n" << record[curI];
	//system("pause");
	return 0;
}