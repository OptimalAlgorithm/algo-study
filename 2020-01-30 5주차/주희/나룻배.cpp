//[백준 2065] 나룻배

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

bool compare(vector<int>A, vector<int> B) {
	if (A[0] == B[0]) { //시간이 같으면 번호 작은 승객이 뒤에오게
		return A[1] > B[1];
	}
	else return A[0] > B[0]; //시간 다르면 빨리 온 승객이 뒤에오게
}

int main() {
	int M, t, N; //최대수용인원, 이동시간, 승객 수
	cin >> M >> t >> N;

	int TIME{ 0 }; //현재 시간
	string SIDE{ "left" }; //현재위치
	int avail{ M }; //탑승 가능 승객 수
	vector<int> boat; //탑승한 승객

	vector<int> arrived(N, 0); //승객 도착 시간

	vector<vector<int>> left; //왼쪽 대기 승객
	vector<vector<int>> right; //오른쪽 대기 승객

	//초기 데이터 받기 - 왼쪽, 오른쪽 따로
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

	//도착하지 못한 승객이 있는 동안
	while (left.size() > 0 || right.size() > 0) {

		if (SIDE == "left") {
			//태우기 시도
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

			//아무도 못태운 경우 - 이동할지 기다릴지 결정
			if (boat.size() == 0) {
				//이동 선택
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
				else {//기다려서 태우기
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
					//이동
					TIME += t;
					SIDE = "right";
					for (auto b : boat) arrived[b] = TIME;
					boat.clear();
					avail = M;
				}
			}
			else { //1명이라도 탄 경우 이동
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
				//태우기 시도
				while (true) {
					if (right.size() == 0) break;
					if (avail > 0 && right.back()[0] <= TIME) {
						avail--;
						boat.push_back(right.back()[1]);
						right.pop_back();
					}
					else break;
				}

				//아무도 못태운 경우 - 이동할지 기다릴지 결정
				if (boat.size() == 0) {
					//이동 선택
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
					else {//기다려서 태우기
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
						//이동
						TIME += t;
						SIDE = "left";
						for (auto b : boat) arrived[b] = TIME;
						boat.clear();
						avail = M;
					}
				}
				else { //1명이라도 탄 경우 이동
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