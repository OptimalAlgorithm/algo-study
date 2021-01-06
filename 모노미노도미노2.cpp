//https://www.acmicpc.net/problem/20061
//모노미노도미노 2

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
    case 1: //크기가 1×1인 블록을 (x, y)에 놓은 경우
        while (true) {
            if (y + 1 < 10 && board[x][y + 1] == 0) y++;
            else break;
        }
        board[x][y] = 1;
        break;
    case 2: //크기가 1×2인 블록을 (x, y), (x, y+1)에 놓은 경우
        while (true) {
            if (y + 2 < 10 && board[x][y + 2] == 0) y++;
            else break;
        }
        board[x][y] = 1;
        board[x][y + 1] = 1;
        break;
    case 3: //크기가 2×1인 블록을 (x, y), (x+1, y)에 놓은 경우
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
    case 1: //크기가 1×1인 블록을 (x, y)에 놓은 경우
        while (true) {
            if (x + 1 < 10 && board[x + 1][y] == 0) x++;
            else break;
        }
        board[x][y] = 1;
        break;
    case 2: //크기가 1×2인 블록을 (x, y), (x, y+1)에 놓은 경우
        while (true) {
            if (x + 1 < 10 && board[x + 1][y] == 0 && board[x + 1][y + 1] == 0) x++;
            else break;
        }
        board[x][y] = 1;
        board[x][y + 1] = 1;
        break;
    case 3: //크기가 2×1인 블록을 (x, y), (x+1, y)에 놓은 경우
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
    //꽉 찬 열 삭제하고 down
    bool full;

    while (true) {
        full = false;
        for (int col = 9; col >= 4; col--) {
            bool flag = true;

            for (int row = 0; row < 4; row++) { //가득찬지 확인
                if (board[row][col] == 0) {
                    flag = false;
                    break;
                }
            }

            if (flag) { //가득찼으면 한칸씩 이동
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

    //연한 파랑 영역 확인하고 down
    int cnt = 0;
    for (int col = 4; col <= 5; col++) {
        for (int row = 0; row < 4; row++) {
            if (board[row][col] == 1) { //연한영역 블록 존재확인
                cnt++;
                break;
            }
        }
    }

    for (int col = 9; col >= 6; col--) { //연한영역 개수만큼 내리기
        for (int row = 0; row < 4; row++) {
            board[row][col] = board[row][col - cnt];
        }
    }

    for (int col = 4; col <= 5; col++) { //연한영역 다 지우기
        for (int row = 0; row < 4; row++) {
            board[row][col] = 0;
        }
    }
}

void greenDown() {
    //꽉 찬 행 삭제하고 down

    bool full;

    while (true) {
        full = false;

        for (int row = 9; row >= 4; row--) {
            bool flag = true;

            for (int col = 0; col < 4; col++) { //가득찬지 확인
                if (board[row][col] == 0) {
                    flag = false;
                    break;
                }
            }

            if (flag) { //가득찼으면 한칸씩 이동
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

    //연한 초록 영역 확인하고 down
    int cnt = 0;
    for (int row = 4; row <= 5; row++) {
        for (int col = 0; col < 4; col++) {
            if (board[row][col] == 1) { //연한영역 블록 존재확인
                cnt++;
                break;
            }
        }
    }

    for (int row = 9; row >= 6; row--) { //연한영역 개수만큼 내리기
        for (int col = 0; col < 4; col++) {
            board[row][col] = board[row - cnt][col];
        }
    }

    for (int row = 4; row <= 5; row++) { //연한영역 다 지우기
        for (int col = 0; col < 4; col++) {
            board[row][col] = 0;
        }
    }

}

int count() {
    int cnt = 0;

    //초록 블록 카운팅
    for (int r = 6; r < 10; r++) {
        for (int c = 0; c < 4; c++) {
            cnt += board[r][c];
        }
    }

    //파란 블록 카운팅
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