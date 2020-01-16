//보이저 1호

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

	int n, m;
	cin >> n >> m;

	vector<char> str(m, '0');
	vector<vector<char>> map(n, str);


	//항성계 map 입력
	for (int i{ 0 }; i < n; i++) {
		for (int j{ 0 }; j < m; j++) {

			cin >> map[i][j];
		}
	}

	//탐사선 위치
	int pr, pc;
	cin >> pr >> pc;

	pr--;
	pc--;


	//방향
	vector<pair<int, int>> dir;
	dir.push_back(make_pair(-1, 0)); // U
	dir.push_back(make_pair(0, 1)); // R
	dir.push_back(make_pair(1, 0)); // D
	dir.push_back(make_pair(0, -1)); // L



	vector<int> record;

	//각 진행방향마다 걸리는 시간 계산
	for (int direction{ 0 }; direction < 4; direction++) {

		//걸리는 시간
		int sec{ 0 };

		//현재 진행방향
		int ddd{ direction };
		int nr = pr;
		int nc = pc;



		//////////////////////초기화 끝 이제 계산!
		while (true) {

			//한칸 이동
			nr += dir[ddd].first;
			nc += dir[ddd].second;
			sec++; //초 증가



				   //map 안에 있다면
			if (nr >= 0 && nr < n && nc >= 0 && nc < m) {

				//같은 방향으로 제자리로 돌아왔을 경우
				if (nr == pr && nc == pc && ddd == direction) {
					record.push_back(-1);
					break;
				}

				//같은 방향으로 제자리가 아닌경우
				if (map[nr][nc] == '.') {
					//아무것도 하지 않음. 그대로 진행
				}
				else if (map[nr][nc] == 'C') {
					//누적 초 저장하고 나옴
					record.push_back(sec);
					break;
				}
				else if (map[nr][nc] == '/') {
					//방향 전환
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
					//방향 전환
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
			else { //초 기록하고 종료
				record.push_back(sec);
				break;
			}
		}


	}

	int cur{ 0 };
	int curI;
	vector<string> dirN = { "U", "R", "D", "L" };

	for (int r{ 0 }; r < 4; r++) {
		//-1초인 경우 Voyager
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