//
//  main.cpp
//  CrashWallAndMove
//
//  Created by 조윤영 on 18/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//최단 경로? BFS?

#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>

#define MAX_SIZE 1001

using namespace std;

int N = 0;
int M = 0;
int canCrash = 1;

struct Dir {
    int y;
    int x;
    Dir(int _y, int _x) {
        y = _y;
        x = _x;
    }
};

struct Door{
    int y;
    int x;
    int hammerCnt;
    int depth;
    Door(int _y, int _x, int _hammerCnt, int _depth) {
        y = _y;
        x = _x;
        hammerCnt = _hammerCnt;
        depth = _depth;
    }
};

Dir moveDir[4] = {{-1,0},{1,0},{0,1},{0,-1}};
int room[MAX_SIZE][MAX_SIZE] = {0};
bool visited[MAX_SIZE][MAX_SIZE][2] = {false};

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            char numb;
            cin>> numb;
            room[i][j] = numb-'0';
        }
    }

}

bool isInBoundary(int y, int x) {
    if(0<= y && y<N && 0<= x && x<M)return true;
    
    return false;
}

int solution() {
    int answer = 2002;
    
    queue<Door> q;
    q.push(Door(0,0,1,1));
    visited[0][0][1] = true;//해머 1 있는 상태가 true
    
    while(!q.empty()) {
        
        int y = q.front().y;
        int x = q.front().x;
        int hammer = q.front().hammerCnt;
        int depth = q.front().depth;

//        cout<<"["<<y<<"]["<<x<<"]"<<endl;
        q.pop();
        
        if(y == N-1 && x == M-1){

            answer = min(answer, depth);
            continue;
        }

        for(int i=0; i<4; i++) {
            
            int nextY = y + moveDir[i].y;
            int nextX = x + moveDir[i].x;
            
            
            if(isInBoundary(nextY, nextX)) {
                if(room[nextY][nextX] == 0 && visited[nextY][nextX][hammer]!=true) {
//                    cout<<"->["<<nextY<<"]["<<nextX<<"]"<<endl;
                    visited[nextY][nextX][hammer] = true;
                    q.push(Door(nextY, nextX, hammer, depth+1));
                }else if(room[nextY][nextX] == 1) {
                    if(hammer == 1){
//                        cout<<"=>["<<nextY<<"]["<<nextX<<"]"<<endl;
                        visited[nextY][nextX][hammer-1] = true;//해머가 0인 상태에서 벽 뚫은거 true
                        q.push(Door(nextY, nextX, hammer-1, depth+1));
                    }
                }
            }
        }
//        visited[y][x] = false;
    }
    
    if(answer == 2002)return -1;
    
    return answer;
    
}

int main(int argc, const char * argv[]) {
    input();
    if(N == 1 && M == 1){
        cout<<1<<endl;
    }else{
        cout<<solution()<<endl;
    }
    return 0;
}
