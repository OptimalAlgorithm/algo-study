#include <iostream>
#include <queue>
#include <set>
#include <vector>



using namespace std;

int maxSum = 0;

vector<vector<pair<int, int>>> map; //물고기 번호, 방향

//0부터 순서대로 ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 를 의미
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int sharkX = 0, sharkY = 0, sharkDir; //상어 정보

void simulate(int);
void fish();

void fish() {
    for (int n = 1; n <= 16; n++) { //각 물고기 찾기

        bool flag = false;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (map[i][j].first == n) { //찾으면
                    flag = true;

                    for (int d = 0; d < 8; d++) {
                        int dir = map[i][j].second + d;
                        if (dir >= 8) dir -= 8;

                        int x = i + dx[dir];
                        int y = j + dy[dir];
                        //움직일 수 있으면 map, fish 갱신하고 break
                        if (x >= 0 && x < 4 && y >= 0 && y < 4 && map[x][y].first != -1) { //상어가 없으면 swap

                            pair<int, int> p = map[x][y];

                            map[x][y] = map[i][j];
                            map[x][y].second = dir;

                            map[i][j] = p;

                            break;

                        }
                    }


                }
                if (flag) break;
            }
            if (flag) break;
        }
    }
}

void simulate(int sum) {


    //물고기 이동
    fish();


    bool moved = false; //상어가 이동했는지

    int tx = sharkX;
    int ty = sharkY;
    int tmpDir = sharkDir;
    int gap = 1;

    vector<vector<pair<int, int>>> map2 = map;

    //상어 이동 시 map, sum 갱신
    while (true) {

        int x = tx + dx[tmpDir] * gap;
        int y = ty + dy[tmpDir] * gap;

        if (x >= 0 && x < 4 && y >= 0 && y < 4) { //상어의 방향으로 이동해서 물고기를 먹을 수 있다면
            if (map[x][y].first != 0) {
                moved = true;

                //상어 이동
                map[x][y].first = -1;

                map[tx][ty] = make_pair(0, 0);//상어 자리 비우기

                sharkX = x; //상어 정보 갱신
                sharkY = y;
                sharkDir = map[x][y].second;

                //이어서 진행
                simulate(sum + map2[x][y].first);

                //백트래킹
                sharkX = tx;
                sharkY = ty;

                map = map2;
            }

            gap++;
        }
        else break;
    }

    if (!moved) maxSum = max(maxSum, sum); //상어가 더이상 못움직였으면 max값 갱신
}

int main() {

    map.resize(4, vector<pair<int, int>>(4));

    int num, dir;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> num >> dir;

            map[i][j] = make_pair(num, --dir); //map입력

        }
    }

    int sum = map[0][0].first; //처음 0,0에 있는 물고기 먹음

    map[0][0].first = -1; //상어 번호: -1
    sharkDir = map[0][0].second; //상어 방향

    simulate(sum);


    cout << maxSum;
}