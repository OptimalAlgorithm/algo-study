//[백준 11559] puyo puyo

#include <iostream>
#include <vector>

using namespace std;


vector<vector <char>> puyo(12, vector<char>(6, '.'));

int puyoCount{ 0 }; // 연쇄
vector<vector<int>> dir = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } }; //방향

void input() {
	for (int i{ 0 }; i < 12; i++) {
		for (int j{ 0 }; j < 6; j++) {
			cin >> puyo[i][j];
		}
	}
	return;
}

bool popPuyo() {
	int popCount{ 0 };
	vector<vector<int>> visited(12, vector<int>(6, 0)); //0=방문X  1=방문O
	for (int i{ 0 }; i < 12; i++) {
		for (int j{ 0 }; j < 6; j++) {
			if (puyo[i][j] != '.' && visited[i][j] == 0) {
				visited[i][j] = 1;

				vector<vector<int>> temp;
				vector<vector<int>> tempLS;
				temp.push_back({ i,j });
				tempLS.push_back({ i,j });

				while (temp.size() > 0) {
					for (auto d : dir) {
						int x = temp.back()[0] + d[0];
						int y = temp.back()[1] + d[1];

						if (x >= 0 && x < 12 && y >= 0 && y < 6) {
							if (puyo[x][y] == puyo[i][j]) {
								if (visited[x][y] == 0) {
									visited[x][y] = 1;
									temp.insert(temp.begin(), { x,y });
									tempLS.push_back({ x,y });
								}
							}
						}
					}
					temp.pop_back();
				}

				if (tempLS.size() >= 4) {
					for (auto a : tempLS) puyo[a[0]][a[1]] = '.';
					popCount++;
				}

			}
		}
	}

	if (popCount == 0) return false;
	else return true;
}

void puyoDown() {
	for (int j{ 0 }; j < 6; j++) {
		vector<int> templist;
		for (int i{ 0 }; i <12; i++) {
			if (puyo[i][j] != '.') templist.push_back(puyo[i][j]);
		}

		for (int t{ 0 }; t < templist.size(); t++) {
			puyo[12 - templist.size() + t][j] = templist[t];
		}
		for (int t{ 0 }; t < 12 - templist.size(); t++) {
			puyo[t][j] = '.';
		}

	}
	return;
}


int main() {

	input();

	while (true) {
		if (popPuyo()) {
			puyoCount++;
			puyoDown();


		}
		else break;
	}

	cout << puyoCount;

	//system("pause");
	return 0;
}