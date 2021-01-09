//https://www.acmicpc.net/problem/17825
//주사위 윷놀이


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;



//1번맵-시작포함, 끝제외 <<크게 둥근 맵>>
int map1[21] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };

//2번맵 <<10에서 오른쪽으로, 위로>>
int map2[8] = { 10, 13,16,19,25,30,35,40 };

//3번맵 <<20에서 수직 위로>>
int map3[7] = { 20, 22,24,25,30,35,40 };

//4번맵 <<30에서 왼쪽으로, 위로>>
int map4[8] = { 30, 28,27,26,25,30,35,40 };



struct Player {
	int map; //몇번째 맵에
	int idx; //몇번째 인덱스인지

	bool out; //도착했는지

	Player(int m, int i, bool b) {
		map = m;
		idx = i;
		out = b;
	}
};

vector<Player> players; //i번째 인덱스에 i번째 말 (0~3)

int dice[10]; //주사위 번호

int maxSum = 0; //출력할 답: 최대합

vector<int> getArrPoint(int map, int idx, int cnt) { //num번째 말이 m번맵 i번째에서 cnt만큼 이동했을 때 도착점 계산
	//맵번호, 인덱스, 더해질 칸의 합 반환
	//도착해서 나가는 경우 -1, -1반환
	//cout << "\n" << map << "번째 맵 " << idx << "번째에서 " << cnt << "만큼 움직이면 ";
	vector<int> rtn(3, 0);


	while (true) {
		if (cnt == 0)break;
		switch (map) { //맵번호
		case 1: //10,20,30 도착하는지 조심


			for (int i = 1; i <= cnt; i++) { //남은 스텝 수 만큼
				if (idx + 1 <= 20) {
					idx++;
					cnt--;
				}
				else { //나간거임
					rtn[0] = -1;
					rtn[1] = -1;
					return rtn;
				}
			}


			if (map1[idx] == 10 && cnt == 0) {
				map = 2; //2번 맵
				idx = 0; //첫번째 인덱스로 이동
				break;
			}
			else if (map1[idx] == 20 && cnt == 0) {
				map = 3; //3번 맵
				idx = 0; //첫번째 인덱스로 이동
				break;
			}
			else if (map1[idx] == 30 && cnt == 0) {
				map = 4; //4번 맵
				idx = 0; //첫번째 인덱스로 이동
				break;
			}

			break;//case문 break

		case 2:

			for (int i = 1; i <= cnt; i++) { //남은 스텝 수 만큼
				if (idx + 1 < 8) {
					idx++;
					cnt--;
				}
				else { //나간거임
					rtn[0] = -1;
					rtn[1] = -1;
					return rtn;

					break;
				}
			}


			break;

		case 3:

			for (int i = 1; i <= cnt; i++) { //남은 스텝 수 만큼
				if (idx + 1 < 7) {
					idx++;
					cnt--;
				}
				else { //나간거임

					rtn[0] = -1;
					rtn[1] = -1;
					return rtn;

					break;
				}
			}

			break;

		case 4:

			for (int i = 1; i <= cnt; i++) { //남은 스텝 수 만큼
				if (idx + 1 < 8) {
					idx++;
					cnt--;
				}
				else { //나간거임

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
	//cout << rtn[0] << "맵 " << rtn[1] << "번째로 " << rtn[2] << "만큼 더해서 도착\n";
	return rtn;
}

void dfs(int index, int sum) {
	if (index == 10) { //10번 다 이동
		maxSum = max(maxSum, sum);
		return;
	}
	else {
		//10번 던지기 전에 말이 이미 다 도착한거면 return
		bool isFinished = true;

		for (int i = 0; i < 4; i++) {
			if (players[i].out == false)isFinished = false;
		}

		if (isFinished) {
			maxSum = max(maxSum, sum);
			return;
		}

		//아직 도착하지 않은 말이 하나라도 있으면 다음 말 선택해서 진행
		for (int i = 0; i < 4; i++) {
			//도착해서 나간 말 제외 
			if (players[i].out == true)continue;

			//도착점 구하기
			vector<int> arr = getArrPoint(players[i].map, players[i].idx, dice[index]);

			//도착해서 나감
			if (arr[0] == -1 && arr[1] == -1) {
				players[i].out = true; //내보냄
				dfs(index + 1, sum + arr[2]); //이어서 진행
				players[i].out = false; //백트래킹
				continue;
			}

			//도착하는게 아니라면 중복도착체크
			bool dbcheck = false;
			for (int j = 0; j < 4; j++) { //같은맵 중복 체크
				if (players[j].map == arr[0] && players[j].idx == arr[1] && players[j].out == false)dbcheck = true;
			}

			//다른맵 중복 체크
			if (arr[0] == 1 && arr[1] == 5) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 2 && players[j].idx == 0 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 2 && arr[1] == 0) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 1 && players[j].idx == 5 && players[j].out == false)dbcheck = true;
				}
			}


			if (arr[0] == 1 && arr[1] == 10) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 3 && players[j].idx == 0 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 3 && arr[1] == 0) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 1 && players[j].idx == 10 && players[j].out == false)dbcheck = true;
				}
			}

			if (arr[0] == 1 && arr[1] == 15) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 4 && players[j].idx == 0 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 4 && arr[1] == 0) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 1 && players[j].idx == 15 && players[j].out == false)dbcheck = true;
				}
			}

			if (arr[0] == 1 && arr[1] == 20) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 2 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
					if (players[j].map == 3 && players[j].idx == 6 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 2 && arr[1] == 7) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 1 && players[j].idx == 20 && players[j].out == false)dbcheck = true;
					if (players[j].map == 3 && players[j].idx == 6 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 3 && arr[1] == 6) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 2 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
					if (players[j].map == 1 && players[j].idx == 20 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 4 && arr[1] == 7) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 2 && players[j].idx == 7 && players[j].out == false)dbcheck = true;
					if (players[j].map == 3 && players[j].idx == 6 && players[j].out == false)dbcheck = true;
					if (players[j].map == 1 && players[j].idx == 20 && players[j].out == false)dbcheck = true;
				}
			}

			if (arr[0] == 2 && arr[1] == 4) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 3 && players[j].idx == 3 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 3 && arr[1] == 3) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 2 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
					if (players[j].map == 4 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
				}
			}
			if (arr[0] == 4 && arr[1] == 4) {
				for (int j = 0; j < 4; j++) { //같은맵 중복 체크
					if (players[j].map == 3 && players[j].idx == 3 && players[j].out == false)dbcheck = true;
					if (players[j].map == 2 && players[j].idx == 4 && players[j].out == false)dbcheck = true;
				}
			}

			pair<int, int> cmp1 = make_pair(arr[0], arr[1]);

			set<pair<int, int>> set30;
			set30.insert(make_pair(2, 5));
			set30.insert(make_pair(3, 4));
			set30.insert(make_pair(4, 5));

			for (int j = 0; j < 4; j++) { //같은맵 중복 체크
				pair<int, int> cmp2 = make_pair(players[j].map, players[j].idx);
				if (set30.count(cmp1) == 1 && set30.count(cmp2) == 1 && players[j].out == false)dbcheck = true;
			}


			set<pair<int, int>> set35;
			set35.insert(make_pair(2, 6));
			set35.insert(make_pair(3, 5));
			set35.insert(make_pair(4, 6));

			for (int j = 0; j < 4; j++) { //같은맵 중복 체크
				pair<int, int> cmp2 = make_pair(players[j].map, players[j].idx);
				if (set35.count(cmp1) == 1 && set35.count(cmp2) == 1 && players[j].out == false)dbcheck = true;
			}


			set<pair<int, int>> set40;
			set40.insert(make_pair(2, 7));
			set40.insert(make_pair(3, 6));
			set40.insert(make_pair(4, 7));

			for (int j = 0; j < 4; j++) { //같은맵 중복 체크
				pair<int, int> cmp2 = make_pair(players[j].map, players[j].idx);
				if (set40.count(cmp1) == 1 && set40.count(cmp2) == 1 && players[j].out == false)dbcheck = true;
			}




			if (!dbcheck) { //중복안된다면

				//기존값 임시저장, 말 위치 변경
				Player tmpP = players[i];

				players[i].map = arr[0];
				players[i].idx = arr[1];

				//이어서 진행
				dfs(index + 1, sum + arr[2]);

				//백트래킹
				players[i] = tmpP;

			}
		}

	}

}


int main() {

	//0~3번 말 시작위치에 둠
	for (int i = 0; i < 4; i++) {
		//1번맵, 0번째 인덱스에서 시작, 아직도착안함
		Player p = { 1,0,false };
		players.push_back(p);
	}

	for (int i = 0; i < 10; i++) {
		cin >> dice[i]; //주사위 입력
	}

	dfs(0, 0); //주사위 0번째인덱스, 총합0으로 완전탐색 시작

	cout << maxSum;
}