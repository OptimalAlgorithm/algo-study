//https://www.acmicpc.net/problem/17825
//�ֻ��� ������


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;



//1����-��������, ������ <<ũ�� �ձ� ��>>
int map1[21] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };

//2���� <<10���� ����������, ����>>
int map2[8] = { 10, 13,16,19,25,30,35,40 };

//3���� <<20���� ���� ����>>
int map3[7] = { 20, 22,24,25,30,35,40 };

//4���� <<30���� ��������, ����>>
int map4[8] = { 30, 28,27,26,25,30,35,40 };



struct Player {
	int map; //���° �ʿ�
	int idx; //���° �ε�������

	bool out; //�����ߴ���

	Player(int m, int i, bool b) {
		map = m;
		idx = i;
		out = b;
	}
};

vector<Player> players; //i��° �ε����� i��° �� (0~3)

int dice[10]; //�ֻ��� ��ȣ

int maxSum = 0; //����� ��: �ִ���

vector<int> getArrPoint(int map, int idx, int cnt) { //num��° ���� m���� i��°���� cnt��ŭ �̵����� �� ������ ���
	//�ʹ�ȣ, �ε���, ������ ĭ�� �� ��ȯ
	//�����ؼ� ������ ��� -1, -1��ȯ
	//cout << "\n" << map << "��° �� " << idx << "��°���� " << cnt << "��ŭ �����̸� ";
	vector<int> rtn(3, 0);


	while (true) {
		if (cnt == 0)break;
		switch (map) { //�ʹ�ȣ
		case 1: //10,20,30 �����ϴ��� ����


			for (int i = 1; i <= cnt; i++) { //���� ���� �� ��ŭ
				if (idx + 1 <= 20) {
					idx++;
					cnt--;
				}
				else { //��������
					rtn[0] = -1;
					rtn[1] = -1;
					return rtn;
				}
			}


			if (map1[idx] == 10 && cnt == 0) {
				map = 2; //2�� ��
				idx = 0; //ù��° �ε����� �̵�
				break;
			}
			else if (map1[idx] == 20 && cnt == 0) {
				map = 3; //3�� ��
				idx = 0; //ù��° �ε����� �̵�
				break;
			}
			else if (map1[idx] == 30 && cnt == 0) {
				map = 4; //4�� ��
				idx = 0; //ù��° �ε����� �̵�
				break;
			}

			break;//case�� break

		case 2:

			for (int i = 1; i <= cnt; i++) { //���� ���� �� ��ŭ
				if (idx + 1 < 8) {
					idx++;
					cnt--;
				}
				else { //��������
					rtn[0] = -1;
					rtn[1] = -1;
					return rtn;

					break;
				}
			}


			break;

		case 3:

			for (int i = 1; i <= cnt; i++) { //���� ���� �� ��ŭ
				if (idx + 1 < 7) {
					idx++;
					cnt--;
				}
				else { //��������

					rtn[0] = -1;
					rtn[1] = -1;
					return rtn;

					break;
				}
			}

			break;

		case 4:

			for (int i = 1; i <= cnt; i++) { //���� ���� �� ��ŭ
				if (idx + 1 < 8) {
					idx++;
					cnt--;
				}
				else { //��������

					rtn[0] = -1;
					rtn[1] = -1;
					return rtn;

					break;
				}
			}


			break;
		}
	}

	rtn[0] = map;
	rtn[1] = idx;
	switch (map) {
	case 1:
		rtn[2] = map1[idx];
		break;
	case 2:
		rtn[2] = map2[idx];
		break;
	case 3:
		rtn[2] = map3[idx];
		break;
	case 4:
		rtn[2] = map4[idx];
		break;
	}
	//cout << rtn[0] << "�� " << rtn[1] << "��°�� " << rtn[2] << "��ŭ ���ؼ� ����\n";
	return rtn;
}

void dfs(int index, int sum) {
	if (index == 10) { //10�� �� �̵�
		maxSum = max(maxSum, sum);
		return;
	}
	else {
		//10�� ������ ���� ���� �̹� �� �����ѰŸ� return
		bool isFinished = true;

		for (int i = 0; i < 4; i++) {
			if (players[i].out == false)isFinished = false;
		}

		if (isFinished) {
			maxSum = max(maxSum, sum);
			return;
		}

		//���� �������� ���� ���� �ϳ��� ������ ���� �� �����ؼ� ����
		for (int i = 0; i < 4; i++) {
			//�����ؼ� ���� �� ���� 
			if (players[i].out == true)continue;

			//������ ���ϱ�
			vector<int> arr = getArrPoint(players[i].map, players[i].idx, dice[index]);

			//�����ؼ� ����
			if (arr[0] == -1 && arr[1] == -1) {
				players[i].out = true; //������
				dfs(index + 1, sum + arr[2]); //�̾ ����
				players[i].out = false; //��Ʈ��ŷ
				continue;
			}

			//�����ϴ°� �ƴ϶�� �ߺ�����üũ
			bool dbcheck = false;
			for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
				if (players[j].map == arr[0] && players[j].idx == arr[1] && players[j].out == false)dbcheck = true;
			}

			//�ٸ��� �ߺ� üũ
			if (arr[0] == 1 && arr[1] == 5) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 2 && players[j].idx == 0 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 2 && arr[1] == 0) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 1 && players[j].idx == 5 && players[j].out == false)dbcheck = true;
				}
			}


			if (arr[0] == 1 && arr[1] == 10) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 3 && players[j].idx == 0 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 3 && arr[1] == 0) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 1 && players[j].idx == 10 && players[j].out == false)dbcheck = true;
				}
			}

			if (arr[0] == 1 && arr[1] == 15) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 4 && players[j].idx == 0 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 4 && arr[1] == 0) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 1 && players[j].idx == 15 && players[j].out == false)dbcheck = true;
				}
			}

			if (arr[0] == 1 && arr[1] == 20) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 2 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
					if (players[j].map == 3 && players[j].idx == 6 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 2 && arr[1] == 7) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 1 && players[j].idx == 20 && players[j].out == false)dbcheck = true;
					if (players[j].map == 3 && players[j].idx == 6 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 3 && arr[1] == 6) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 2 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
					if (players[j].map == 1 && players[j].idx == 20 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 4 && arr[1] == 7) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 2 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
					if (players[j].map == 3 && players[j].idx == 6 && players[j].out == false)dbcheck = true;
					if (players[j].map == 1 && players[j].idx == 20 && players[j].out == false)dbcheck = true;
				}
			}

			if (arr[0] == 2 && arr[1] == 4) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 3 && players[j].idx == 3 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 3 && arr[1] == 3) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 2 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 4 && arr[1] == 4) {
				for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
					if (players[j].map == 3 && players[j].idx == 3 && players[j].out == false)dbcheck = true;
					if (players[j].map == 2 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
				}
			}

			pair<int, int> cmp1 = make_pair(arr[0], arr[1]);

			set<pair<int, int>> set30;
			set30.insert(make_pair(2, 5));
			set30.insert(make_pair(3, 4));
			set30.insert(make_pair(4, 5));

			for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
				pair<int, int> cmp2 = make_pair(players[j].map, players[j].idx);
				if (set30.count(cmp1) == 1 && set30.count(cmp2) == 1 && players[j].out == false)dbcheck = true;
			}


			set<pair<int, int>> set35;
			set35.insert(make_pair(2, 6));
			set35.insert(make_pair(3, 5));
			set35.insert(make_pair(4, 6));

			for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
				pair<int, int> cmp2 = make_pair(players[j].map, players[j].idx);
				if (set35.count(cmp1) == 1 && set35.count(cmp2) == 1 && players[j].out == false)dbcheck = true;
			}


			set<pair<int, int>> set40;
			set40.insert(make_pair(2, 7));
			set40.insert(make_pair(3, 6));
			set40.insert(make_pair(4, 7));

			for (int j = 0; j < 4; j++) { //������ �ߺ� üũ
				pair<int, int> cmp2 = make_pair(players[j].map, players[j].idx);
				if (set40.count(cmp1) == 1 && set40.count(cmp2) == 1 && players[j].out == false)dbcheck = true;
			}




			if (!dbcheck) { //�ߺ��ȵȴٸ�

				//������ �ӽ�����, �� ��ġ ����
				Player tmpP = players[i];

				players[i].map = arr[0];
				players[i].idx = arr[1];

				//�̾ ����
				dfs(index + 1, sum + arr[2]);

				//��Ʈ��ŷ
				players[i] = tmpP;

			}
		}

	}

}


int main() {

	//0~3�� �� ������ġ�� ��
	for (int i = 0; i < 4; i++) {
		//1����, 0��° �ε������� ����, ������������
		Player p = { 1,0,false };
		players.push_back(p);
	}

	for (int i = 0; i < 10; i++) {
		cin >> dice[i]; //�ֻ��� �Է�
	}

	dfs(0, 0); //�ֻ��� 0��°�ε���, ����0���� ����Ž�� ����

	cout << maxSum;
}