//[���� 2065] �����

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

bool compare(vector<int>A, vector<int> B) {
	if (A[0] == B[0]) { //�ð��� ������ ��ȣ ���� �°��� �ڿ�����
		return A[1] > B[1];
	}
	else return A[0] > B[0]; //�ð� �ٸ��� ���� �� �°��� �ڿ�����
}

int main() {
	int M, t, N; //�ִ�����ο�, �̵��ð�, �°� ��
	cin >> M >> t >> N;

	int TIME{ 0 }; //���� �ð�
	string SIDE{ "left" }; //������ġ
	int avail{ M }; //ž�� ���� �°� ��
	vector<int> boat; //ž���� �°�

	vector<int> arrived(N, 0); //�°� ���� �ð�

	vector<vector<int>> left; //���� ��� �°�
	vector<vector<int>> right; //������ ��� �°�

	//�ʱ� ������ �ޱ� - ����, ������ ����
	for (int i{ 0 }; i < N; i++) {
		int time;
		string side;
		cin >> time >> side;

		if (side == "left") {
			left.insert(left.begin(), { time, i });
		}
		else {
			right.insert(right.begin(), { time, i });
		}
	}

	sort(left.begin(), left.end(), compare);
	sort(right.begin(), right.end(), compare);

	//�������� ���� �°��� �ִ� ����
	while (left.size() > 0 || right.size() > 0) {

		if (SIDE == "left") {
			//�¿�� �õ�
			while (true) {
				if (left.size() == 0) break;
				if (avail > 0 && left.back()[0] <= TIME) {
					avail--;
					//cout << "TIME 1=" << TIME << "\n";
					boat.push_back(left.back()[1]);
					left.pop_back();
				}
				else break;
			}

			//�ƹ��� ���¿� ��� - �̵����� ��ٸ��� ����
			if (boat.size() == 0) {
				//�̵� ����
				if (left.size() == 0) {
					if (TIME > right.back()[0]) TIME += t;
					else TIME = right.back()[0] + t;
					SIDE = "right";
				}
				else if (((right.size() != 0) && right.back()[0] < left.back()[0])) {
					if (TIME > right.back()[0]) TIME += t;
					else TIME = right.back()[0] + t;
					SIDE = "right";
				}
				else {//��ٷ��� �¿��
					if (left.size() != 0) TIME = left.back()[0];
					while (true) {
						if (left.size() == 0) break;
						if (avail > 0 && left.back()[0] <= TIME) {
							avail--;
							//cout << "TIME 2=" << TIME << "\n";
							boat.push_back(left.back()[1]);
							left.pop_back();
						}
						else break;
					}
					//�̵�
					TIME += t;
					SIDE = "right";
					for (auto b : boat) arrived[b] = TIME;
					boat.clear();
					avail = M;
				}
			}
			else { //1���̶� ź ��� �̵�
				TIME += t;
				//cout << "TIME 3=" << TIME << "\n";
				SIDE = "right";
				for (auto b : boat) arrived[b] = TIME;
				boat.clear();
				avail = M;
			}
		}
		else {
			if (SIDE == "right") {
				//�¿�� �õ�
				while (true) {
					if (right.size() == 0) break;
					if (avail > 0 && right.back()[0] <= TIME) {
						avail--;
						boat.push_back(right.back()[1]);
						right.pop_back();
					}
					else break;
				}

				//�ƹ��� ���¿� ��� - �̵����� ��ٸ��� ����
				if (boat.size() == 0) {
					//�̵� ����
					if (right.size() == 0){
						if (TIME > left.back()[0]) TIME += t;
						else TIME = left.back()[0] + t;
						SIDE = "left";
					}
					else if (((left.size() != 0) && left.back()[0] < right.back()[0])) {
						if (TIME > left.back()[0]) TIME += t;
						else TIME = left.back()[0] + t;
						SIDE = "left";
					}
					else {//��ٷ��� �¿��
						if (right.size() != 0) TIME = right.back()[0];
						while (true) {
							if (right.size() == 0) break;
							if (avail > 0 && right.back()[0] <= TIME) {
								avail--;
								boat.push_back(right.back()[1]);
								right.pop_back();
							}
							else break;
						}
						//�̵�
						TIME += t;
						SIDE = "left";
						for (auto b : boat) arrived[b] = TIME;
						boat.clear();
						avail = M;
					}
				}
				else { //1���̶� ź ��� �̵�
					TIME += t;
					SIDE = "left";
					for (auto b : boat) arrived[b] = TIME;
					boat.clear();
					avail = M;
				}
			}
		}
	}

	for (auto a : arrived)cout << a << "\n";


	//system("pause");
	return 0;

}