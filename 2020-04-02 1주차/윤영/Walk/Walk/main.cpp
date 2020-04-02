//
//  main.cpp
//  Walk
//
//  Created by 조윤영 on 02/04/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 1001

using namespace std;

int H = 0;
int W = 0;
int N = 0;

int room[MAX_SIZE][MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];

struct Dir {
    int y;
    int x;
};

int answerY = 0;
int answerX = 0;

Dir moveDir[2] = {{1,0},{0,1}};
int visited[MAX_SIZE][MAX_SIZE][2];

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>>H >> W >> N;
    
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            cin>>room[i][j];
        }
    }
}


//O(W*H) - 정답
void dfs(int y, int x) {
    if (y >= H || x >= W) {
        answerY = y;
        answerX = x;
        return;
    }
    
    int nextY = 0;
    int nextX = 0;
    
    if(room[y][x] == 1) {
        if(dp[y][x] == 1){
            nextY = y+moveDir[1].y;
            nextX = x+moveDir[1].x;
        }else{
            nextY = y+moveDir[0].y;
            nextX = x+moveDir[0].x;
        }
    }else{//0
        if(dp[y][x] == 1){
            nextY = y+moveDir[0].y;
            nextX = x+moveDir[0].x;
        }else{
            nextY = y+moveDir[1].y;
            nextX = x+moveDir[1].x;
        }
        
    }
    
    dfs(nextY, nextX);
}
void setDirection() {
    dp[0][0] = N;
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            if(room[i][j] == 1) {//오른쪽
                dp[i+1][j] += dp[i][j]/2;
                dp[i][j+1] += (dp[i][j]%2 == 0)?dp[i][j]/2:dp[i][j]/2+1;
                
            }else {
                dp[i+1][j] += (dp[i][j] % 2 == 0) ? dp[i][j] / 2 : dp[i][j] / 2 + 1;
                dp[i][j + 1] += dp[i][j] / 2;
            }

        }
    }
    
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            dp[i][j] %=2;
        }
    }
}

void solution() {
    setDirection();
    dfs(0,0);
}

//O(W+H)*N의 방법 - 시간초과
//void dfs(int y, int x) {
//    if(y==H-1) {
//        answerY = y+1;
//        answerX = x;
//        return;
//    }else if(x == W-1){
//        answerY = y;
//        answerX = x+1;
//        return;
//    }
//    int streetDir = room[y][x];
//
//    int nextY = y+moveDir[streetDir].y;
//    int nextX = x+moveDir[streetDir].x;
//
//    room[y][x] = (room[y][x]==0)?1:0;
//
//    dfs(nextY, nextX);
//
//}
//void solution() {
//    for(int i=0; i<N; i++) {
//        dfs(0,0);
//    }
//    cout<<answerY+1<<" "<<answerX+1<<"\n";
//}



int main(int argc, const char * argv[]) {
    input();
    solution();
    
    cout<<answerY+1<<" "<<answerX+1<<"\n";
    return 0;
}
