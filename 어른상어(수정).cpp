#include <iostream>
#include <vector>
#include <set>

using namespace std;

//함수선언
void simulate();
bool onlyShark();
void swim();
void smell();


int N, M, K; //격자칸크기, 상어수, 냄새시간

vector<vector<int>> map; //map

vector<int> sharkDir;//상어의 현재 방향

vector<vector<vector<int>>> dirPri; //상어 방향 우선순위

vector<vector<pair<int, int>>> sharkSmell; //상어 냄새정보 저장 -  {상어번호, 남은 초}

// 1, 2, 3, 4는 각각 위, 아래, 왼쪽, 오른쪽을 의미한다. - 0번째는 아무것도 아님
int dx[5] = { 3,-1,1,0,0 };
int dy[5] = { 3,0,0,-1,1 };

int seconds = 0;

void simulate() {
	if (!onlyShark()) {
		seconds++; //1번 상어만 남은게 아니라면 초 증가
		if (seconds > 1000) {
			seconds = -1;
			return;
		}
		/*
		cout << "\n\n\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << map[i][j] << " ";
			}
			cout << "\n";
		}
		*/
	}
	else return; //1번 상어만 남았다면 바로 종료

	swim(); //상어 이동 - map, smell 갱신


	simulate();
}

void swim() { //상어 이동 - map, smell 갱신
	vector<vector<int>> map2(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] != 0) {
				int a = map[i][j];
				//a번 상어 마다 이동
				bool flag = false;
				switch (sharkDir[a]) {
				case 1:
					for (auto b : dirPri[a][0]) { //우선 빈공간 확인
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][0]) { //빈공간 없다면 자신의 냄새로 이동
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;
				case 2:

					for (auto b : dirPri[a][1]) { //우선 빈공간 확인
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][1]) { //빈공간 없다면 자신의 냄새로 이동
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;

				case 3:
					for (auto b : dirPri[a][2]) { //우선 빈공간 확인
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][2]) { //빈공간 없다면 자신의 냄새로 이동
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;
				case 4:

					for (auto b : dirPri[a][3]) { //우선 빈공간 확인
						int x = i + dx[b];
						int y = j + dy[b];

						if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y] == make_pair(0, 0)) {
							flag = true;

							sharkDir[a] = b;
							if (map2[x][y] == 0 || map2[x][y] > a)map2[x][y] = a;

							break;
						}
					}

					if (!flag) {
						for (auto b : dirPri[a][3]) { //빈공간 없다면 자신의 냄새로 이동
							int x = i + dx[b];
							int y = j + dy[b];

							if (x >= 0 && x < N && y >= 0 && y < N && sharkSmell[x][y].first == a) {

								sharkDir[a] = b;
								map2[x][y] = a;

								break;
							}
						}
					}

					break;
				}


			}
		}
	}


	smell(); //냄새 감소시키기 - K인칸 제외하고

	//K인칸 냄새 갱신
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map2[i][j] != 0) {
				sharkSmell[i][j] = make_pair(map2[i][j], K);
			}
		}
	}
	map = map2;

}

void smell() { //냄새 감소시키기 - K인칸 제외하고
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (sharkSmell[i][j].second == 1) {
				sharkSmell[i][j] = make_pair(0, 0);
			}
			else if (sharkSmell[i][j].second != 0) {
				sharkSmell[i][j].second--;
			}
		}
	}
}

//1번 상어만 남았는지 체크
bool onlyShark() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] > 1) return false; //1번 외 상어가 발견되면 false
		}
	}

	//1번 상어만 남았다면 true
	return true;
}

int main() {
	cin >> N >> M >> K;

	sharkSmell.resize(N, vector<pair<int, int>>(N, make_pair(0, 0)));


	//map입력
	map.resize(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			cin >> map[i][j];

			if (map[i][j] != 0) sharkSmell[i][j] = make_pair(map[i][j], K);
		}
	}

	//초기 상어 방향 입력
	sharkDir.resize(M + 1);
	sharkDir.push_back(0);
	for (int i = 1; i <= M; i++) {
		cin >> sharkDir[i];
	}

	//상어 방향 우선순위 입력
	vector<vector<int>> v;
	dirPri.push_back(v); //상어번호는 1번부터이니까 공백을 0번째 자리에 채운다

//M개의 상어 방향 이동 우선순위 입력
	for (int i = 0; i < M; i++) {
		vector<vector<int>> tmp(4, vector<int>(4));
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> tmp[i][j];
			}
		}
		dirPri.push_back(tmp);
	}

	//상어이동 시작

	simulate();

	cout << seconds;

}