//https://www.acmicpc.net/problem/20061
//���̳뵵�̳� 2

#include <iostream>


using namespace std;

void simulate(int, int, int);
void blue(int, int, int);
void green(int, int, int);
void blueDown();
void greenDown();
int count();

void printBoard();


int points = 0;
int board[10][10];


void printBoard() {

    cout << "\n\nboard: \n";
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 10; c++) {
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }
    for (int r = 4; r < 10; r++) {
        for (int c = 0; c < 4; c++) {
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }
}


void simulate(int t, int x, int y) {
    blue(t, x, y);
    green(t, x, y);
    blueDown();
    greenDown();
}

void blue(int t, int x, int y) {
    switch (t) {
    case 1: //ũ�Ⱑ 1��1�� ����� (x, y)�� ���� ���
        while (true) {
            if (y + 1 < 10 && board[x][y + 1] == 0) y++;
            else break;
        }
        board[x][y] = 1;
        break;
    case 2: //ũ�Ⱑ 1��2�� ����� (x, y), (x, y+1)�� ���� ���
        while (true) {
            if (y + 2 < 10 && board[x][y + 2] == 0) y++;
            else break;
        }
        board[x][y] = 1;
        board[x][y + 1] = 1;
        break;
    case 3: //ũ�Ⱑ 2��1�� ����� (x, y), (x+1, y)�� ���� ���
        while (true) {
            if (y + 1 < 10 && board[x][y + 1] == 0 && board[x + 1][y + 1] == 0) y++;
            else break;
        }
        board[x][y] = 1;
        board[x + 1][y] = 1;
        break;
    }
}

void green(int t, int x, int y) {
    switch (t) {
    case 1: //ũ�Ⱑ 1��1�� ����� (x, y)�� ���� ���
        while (true) {
            if (x + 1 < 10 && board[x + 1][y] == 0) x++;
            else break;
        }
        board[x][y] = 1;
        break;
    case 2: //ũ�Ⱑ 1��2�� ����� (x, y), (x, y+1)�� ���� ���
        while (true) {
            if (x + 1 < 10 && board[x + 1][y] == 0 && board[x + 1][y + 1] == 0) x++;
            else break;
        }
        board[x][y] = 1;
        board[x][y + 1] = 1;
        break;
    case 3: //ũ�Ⱑ 2��1�� ����� (x, y), (x+1, y)�� ���� ���
        while (true) {
            if (x + 2 < 10 && board[x + 2][y] == 0) x++;
            else break;
        }
        board[x][y] = 1;
        board[x + 1][y] = 1;
        break;
    }
}

void blueDown() {
    //�� �� �� �����ϰ� down
    bool full;

    while (true) {
        full = false;
        for (int col = 9; col >= 4; col--) {
            bool flag = true;

            for (int row = 0; row < 4; row++) { //�������� Ȯ��
                if (board[row][col] == 0) {
                    flag = false;
                    break;
                }
            }

            if (flag) { //����á���� ��ĭ�� �̵�
                full = true;
                points++;
                for (int c = col; c > 4; c--) {
                    for (int r = 0; r < 4; r++) {
                        board[r][c] = board[r][c - 1];
                    }
                }

                for (int r = 0; r < 4; r++) {
                    board[r][4] = 0;
                }
            }
        }

        if (!full)break;
    }

    //���� �Ķ� ���� Ȯ���ϰ� down
    int cnt = 0;
    for (int col = 4; col <= 5; col++) {
        for (int row = 0; row < 4; row++) {
            if (board[row][col] == 1) { //���ѿ��� ��� ����Ȯ��
                cnt++;
                break;
            }
        }
    }

    for (int col = 9; col >= 6; col--) { //���ѿ��� ������ŭ ������
        for (int row = 0; row < 4; row++) {
            board[row][col] = board[row][col - cnt];
        }
    }

    for (int col = 4; col <= 5; col++) { //���ѿ��� �� �����
        for (int row = 0; row < 4; row++) {
            board[row][col] = 0;
        }
    }
}

void greenDown() {
    //�� �� �� �����ϰ� down

    bool full;

    while (true) {
        full = false;

        for (int row = 9; row >= 4; row--) {
            bool flag = true;

            for (int col = 0; col < 4; col++) { //�������� Ȯ��
                if (board[row][col] == 0) {
                    flag = false;
                    break;
                }
            }

            if (flag) { //����á���� ��ĭ�� �̵�
                points++;
                full = true;
                for (int r = row; r > 4; r--) {
                    for (int c = 0; c < 4; c++) {
                        board[r][c] = board[r - 1][c];
                    }
                }

                for (int c = 0; c < 4; c++) {
                    board[4][c] = 0;
                }
            }
        }

        if (!full)break;
    }

    //���� �ʷ� ���� Ȯ���ϰ� down
    int cnt = 0;
    for (int row = 4; row <= 5; row++) {
        for (int col = 0; col < 4; col++) {
            if (board[row][col] == 1) { //���ѿ��� ��� ����Ȯ��
                cnt++;
                break;
            }
        }
    }

    for (int row = 9; row >= 6; row--) { //���ѿ��� ������ŭ ������
        for (int col = 0; col < 4; col++) {
            board[row][col] = board[row - cnt][col];
        }
    }

    for (int row = 4; row <= 5; row++) { //���ѿ��� �� �����
        for (int col = 0; col < 4; col++) {
            board[row][col] = 0;
        }
    }

}

int count() {
    int cnt = 0;

    //�ʷ� ��� ī����
    for (int r = 6; r < 10; r++) {
        for (int c = 0; c < 4; c++) {
            cnt += board[r][c];
        }
    }

    //�Ķ� ��� ī����
    for (int r = 0; r < 4; r++) {
        for (int c = 6; c < 10; c++) {
            cnt += board[r][c];
        }
    }

    return cnt;
}

int main() {

    int N;
    cin >> N;


    int t, x, y;
    for (int i = 0; i < N; i++) {
        cin >> t >> x >> y;

        simulate(t, x, y);


    }
    /*
    int t, x, y;
    while (true) {
       cin >> t >> x >> y;
       simulate(t, x, y);
       printBoard();
    }*/

    //printBoard();
    cout << points << "\n" << count();
}