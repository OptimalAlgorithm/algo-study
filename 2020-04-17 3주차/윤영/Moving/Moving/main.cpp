//
//  main.cpp
//  Moving
//
//  Created by 조윤영 on 22/04/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/11048

#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>

#define MAX_SIZE 1001

using namespace std;

int N = 0;
int M = 0;


int room[MAX_SIZE][MAX_SIZE];
int temp[MAX_SIZE][MAX_SIZE];

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> N >> M;
    
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin>>room[i][j];
        }
    }
}

void solution2() {
    
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            temp[i][j] = max(temp[i-1][j] + room[i][j], max(temp[i-1][j-1] + room[i][j], temp[i][j-1]+room[i][j]));
        }
    }
    
    cout<<temp[N][M]<<"\n";
}


int main(int argc, const char * argv[]) {
    input();
    solution2();
    return 0;
}


//메모리초과

struct Dir {
    int y;
    int x;
};

struct Info {
    int y;
    int x;
    int candyCnt;
    
    Info(int _y, int _x, int _candyCnt) {
        y = _y;
        x = _x;
        candyCnt = _candyCnt;
    };
};

Dir moveDir[3] = {{1,0},{0,1},{1,1}};

bool isInBoundary(int y, int x) {
    if(0<=y && y<N && 0<=x && x<M)return true;
    return false;
}

void solution() {
    //BFS
    
    queue<Info> q;
    int answer = 0;
    
    q.push(Info(0,0,room[0][0]));
    
    while(!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int candy = q.front().candyCnt;
        
        q.pop();
        
        if(y == N-1 && x == M-1) answer = max(answer, candy);
        
        for(int i=0; i<3; i++) {
            int nextY = y + moveDir[i].y;
            int nextX = x + moveDir[i].x;
            
            if(isInBoundary(nextY, nextX))q.push(Info(nextY, nextX, candy+room[nextY][nextX]));
            
        }
    }
    cout<<answer<<"\n";
}
