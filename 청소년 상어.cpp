#include <iostream>
#include <queue>
#include <set>
#include <vector>



using namespace std;

int maxSum = 0;

vector<vector<pair<int, int>>> map; //����� ��ȣ, ����

//0���� ������� ��, ��, ��, ��, ��, ��, ��, �� �� �ǹ�
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int sharkX = 0, sharkY = 0, sharkDir; //��� ����

void simulate(int);
void fish();

void fish() {
    for (int n = 1; n <= 16; n++) { //�� ����� ã��

        bool flag = false;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (map[i][j].first == n) { //ã����
                    flag = true;

                    for (int d = 0; d < 8; d++) {
                        int dir = map[i][j].second + d;
                        if (dir >= 8) dir -= 8;

                        int x = i + dx[dir];
                        int y = j + dy[dir];
                        //������ �� ������ map, fish �����ϰ� break
                        if (x >= 0 && x < 4 && y >= 0 && y < 4 && map[x][y].first != -1) { //�� ������ swap

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


    //����� �̵�
    fish();


    bool moved = false; //�� �̵��ߴ���

    int tx = sharkX;
    int ty = sharkY;
    int tmpDir = sharkDir;
    int gap = 1;

    vector<vector<pair<int, int>>> map2 = map;

    //��� �̵� �� map, sum ����
    while (true) {

        int x = tx + dx[tmpDir] * gap;
        int y = ty + dy[tmpDir] * gap;

        if (x >= 0 && x < 4 && y >= 0 && y < 4) { //����� �������� �̵��ؼ� ����⸦ ���� �� �ִٸ�
            if (map[x][y].first != 0) {
                moved = true;

                //��� �̵�
                map[x][y].first = -1;

                map[tx][ty] = make_pair(0, 0);//��� �ڸ� ����

                sharkX = x; //��� ���� ����
                sharkY = y;
                sharkDir = map[x][y].second;

                //�̾ ����
                simulate(sum + map2[x][y].first);

                //��Ʈ��ŷ
                sharkX = tx;
                sharkY = ty;

                map = map2;
            }

            gap++;
        }
        else break;
    }

    if (!moved) maxSum = max(maxSum, sum); //�� ���̻� ������������ max�� ����
}

int main() {

    map.resize(4, vector<pair<int, int>>(4));

    int num, dir;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> num >> dir;

            map[i][j] = make_pair(num, --dir); //map�Է�

        }
    }

    int sum = map[0][0].first; //ó�� 0,0�� �ִ� ����� ����

    map[0][0].first = -1; //��� ��ȣ: -1
    sharkDir = map[0][0].second; //��� ����

    simulate(sum);


    cout << maxSum;
}