//[���� 2174] �κ� �ùķ��̼� 
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

int main() {

	int A, B;
	cin >> A >> B;

	int N, M;
	cin >> N >> M;

	vector<pair<int, int>> dir;
	dir.push_back(make_pair(0, 1)); //��
	dir.push_back(make_pair(1, 0)); //��
	dir.push_back(make_pair(0, -1)); //��
	dir.push_back(make_pair(-1, -0)); //��

	//�ε��� == �κ���ȣ, x��ǥ, y��ǥ, ���� 
	vector<tuple<int,int,int>> robots(N);

	for (int n{ 1 }; n <= N; n++) {
		int x, y;
		char f;
		cin >> x >> y >> f;

		if (f == 'N') f = '0';
		else if (f == 'E') f = '1';
		else if (f == 'S') f = '2';
		else f = '3';
		
		robots[n - 1] = make_tuple(x, y, (int)(f - '0'));
	}
	
	for (int m{ 0 }; m < M; m++) {
		int robot;
		char command;
		int repeat;

		cin >> robot >> command >> repeat;

		//�������� 90��
		if (command == 'L') { 
			get<2>(robots[robot - 1]) -= (repeat % 4);
			if (get<2>(robots[robot - 1]) < 0) get<2>(robots[robot - 1]) += 4;

		}//���������� 90��
		else if (command == 'R') {
			get<2>(robots[robot - 1]) += (repeat % 4);
			if (get<2>(robots[robot - 1]) > 3) get<2>(robots[robot - 1]) -= 4;

		}//������ ��ĭ
		else {
			for (int r{ 0 }; r < repeat; r++) {
				int tempX = get<0>(robots[robot - 1]) + dir[get<2>(robots[robot - 1])].first;
				int tempY = get<1>(robots[robot - 1]) + dir[get<2>(robots[robot - 1])].second;

				//���� ������ ������
				if (tempX <= 0 || tempX > A || tempY <= 0 || tempY > B) {
					cout << "Robot " << robot << " crashes into the wall";
					system("pause");
					return 0;
				}
				
				//�ٸ� �κ��� �浹�� ��
				for (int test{ 0 }; test < robots.size(); test++) {
					if (test != robot) {
						if (get<0>(robots[test]) == tempX && get<1>(robots[test]) == tempY) {
							cout << "Robot " << robot << " crashes into robot " << test+1;
							system("pause");
							return 0;
						}
					}
				}

				//�̵��ص� ���� ���� ��
				get<0>(robots[robot - 1]) = tempX;
				get<1>(robots[robot - 1]) = tempY;
			}
		}

	}
	cout << "OK";

	system("pause");
	return 0;
}