//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE&problemTitle=%EB%AA%A8%EC%9D%98&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
//핀볼 게임


//실수한점:
//wormholes사이즈 초기화 안해줘서 인덱스 에러남
//map[r][c] = r,c가 들어가는 값 >> 이런식은 연속 두번을 쓰면 r,c값이 바뀌어서 안됨
// >> tmp 변수 하나 잡아서 해결
//maxHits초기화 위치 잘못잡음


#include <iostream>
#include <vector>


using namespace std;


int N;

int hits; //점수

int maxHits;


vector<vector<int>> map; //블록, 웜홀, 블랙홀

vector<pair<int, int>> blackholes;

int dr[4] = { 0,0,1,-1 }; // 우 좌 하 상
int dc[4] = { 1,-1,0,0 };

vector<vector<pair<int, int>>> wormholes;

void inputMap() {

	blackholes.clear();

	wormholes.clear();
	wormholes.resize(5);

	map.clear();
	map.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			//블랙홀
			if (map[i][j] == -1)blackholes.push_back(make_pair(i, j));

			if (map[i][j] >= 6 && map[i][j] <= 10) {
				wormholes[map[i][j] - 6].push_back(make_pair(i, j));
			}
		}
	}


	//cout << "웜홀입력테스트:\n";
	//for (int i = 0; i < 5; i++) {
	//	for (auto a : wormholes[i])cout << "\ni:" << i << a.first << " " << a.second << "\n";
	//}
}

void simulate(int i, int j) {
	

	for (int d = 0; d < 4; d++) { //4방향으로 출발
		hits = 0;
		

		int r = i;
		int c = j;
		int dir = d;

		while (true) {
			//cout << "\nhits:" << hits << " r,c, dir: " << r << " " << c << " " << dir;
			r += dr[dir];
			c += dc[dir];

			//벽에 부딪힘
			if (r < 0 || r >= N || c < 0 || c >= N) { 
				//cout << "벽에 부딪힘";
				hits++;

				switch (dir) {
				case 0: //우 > 좌
					dir = 1;
					break;
				case 1: //좌 > 우
					dir = 0;
					break;
				case 2: //하 > 상
					dir = 3;
					break;
				case 3: //상 > 하
					dir = 2;
					break;
				}

				continue;
			}

			
			//블록에 만남
			if (map[r][c] >= 1 && map[r][c] <= 5) { 
				//cout << map[r][c] << "번 블록 만남";
				hits++;

				switch (map[r][c]) { //블록번호
				case 1:
					switch (dir) {
					case 0: //우
						dir = 1;
						break;
					case 1: //좌
						dir = 3;
						break;
					case 2: //하
						dir = 0;
						break;
					case 3: //상
						dir = 2;
						break;
					}

					break;
				case 2:
					switch (dir) {
					case 0: //우
						dir = 1;
						break;
					case 1: //좌
						dir = 2;
						break;
					case 2: //하
						dir = 3;
						break;
					case 3: //상
						dir = 0;
						break;
					}

					break;
				case 3:
					switch (dir) {
					case 0: //우
						dir = 2;
						break;
					case 1: //좌
						dir = 0;
						break;
					case 2: //하
						dir = 3;
						break;
					case 3: //상
						dir = 1;
						break;
					}

					break;
				case 4:
					switch (dir) {
					case 0: //우
						dir = 3;
						break;
					case 1: //좌
						dir = 0;
						break;
					case 2: //하
						dir = 1;
						break;
					case 3: //상
						dir = 2;
						break;
					}

					break;
				case 5:
					switch (dir) {
					case 0: //우
						dir = 1;
						break;
					case 1: //좌
						dir = 0;
						break;
					case 2: //하
						dir = 3;
						break;
					case 3: //상
						dir = 2;
						break;
					}

					break;
				}

				continue;
			}

			//웜홀 만남
			if (map[r][c] >= 6 && map[r][c] <= 10) { 
				//cout << "웜홀만남";
				pair<int, int> p = make_pair(r, c);
				
				if (wormholes[map[r][c] - 6][0] == p) {
			
					int tmp1 = wormholes[map[r][c] - 6][1].first;
					int tmp2 = wormholes[map[r][c] - 6][1].second;

					r = tmp1;
					c = tmp2;
				}
				else {
				
					int tmp1 = wormholes[map[r][c] - 6][0].first;
					int tmp2 = wormholes[map[r][c] - 6][0].second;

					r = tmp1;
					c = tmp2;
				}
				
				continue;

			}

			//블랙홀 만나서 종료
			if (map[r][c] == -1) {
				//cout << "블랙홀만남";
				break;
			}

			//시작위치로 와서 종료
			if (r == i && c == j) {
				//cout << "시작위치로옴";
				break;
			}
		}

		//cout << "\nHITS: " << hits << "\n";
		maxHits = max(maxHits, hits);
	}
}

int main() {

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N;
		
		inputMap();

		maxHits = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 0)simulate(i, j); //i,j위치 빈공간에서 출발
			}
		}

		cout << "#" << t << " " << maxHits << "\n";
	}
}