//
//  main.cpp
//  MovingUnit
//
//  Created by 조윤영 on 04/05/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <queue>

#define MAX_SIZE 501

using namespace std;

int N = 0;
int M = 0;

int A = 0;
int B = 0;
int K = 0;

int startY = 0;
int startX = 0;
int endY = 0;
int endX = 0;

struct Dir {
    int y;
    int x;
    
};

Dir moveDir[4] = {{-1,0},{1,0},{0,1},{0,-1}};//상 하 우 좌


int room[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];


void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>>N>>M>>A>>B>>K;

    
    int blockY = 0;
    int blockX = 0;
    
    for(int i=0; i<K; i++) {
        cin>>blockY >> blockX;
        room[blockY-1][blockX-1] = 2;
    }
    
    cin>> startY >> startX;
    cin>> endY >> endX;
    
    startY--;
    startX--;
    endY--;
    endX--;
    
}

bool isAvailable(int y, int x) {
    if(0<=y && y<N && 0<=x && x<M)return true;
    return false;
}

bool checkCanMove(int y, int x) { //*
    if(visited[y][x])return false;
    
    for(int i=y; i<y+A; i++) {
        for(int j=x; j<x+B; j++) {
            if(!isAvailable(i, j) || room[i][j] == 2)return false;
        }
    }

    visited[y][x] = true;
    return true;
}

int solution() {
    queue<pair<int,int>> q;
    
    q.push({startY, startX});
    visited[startY][startX] = true;
    int cnt = 0;
    
    while(!q.empty()) {
        int qSize = q.size();
        for(int i=0; i<qSize; i++) {
            int currentY = q.front().first;
            int currentX = q.front().second;
            
            q.pop();
            
            if(currentY == endY && currentX == endX)return cnt;
            
            for(int j=0; j<4; j++) {
                int nextY = currentY + moveDir[j].y;
                int nextX = currentX + moveDir[j].x;
                
                if(isAvailable(nextY, nextX) && checkCanMove(nextY,nextX)) {
                    q.push({nextY, nextX});
                }
            }

        }
        cnt++;
    }
    return -1;

}

int main(int argc, const char * argv[]) {
    input();
    cout<<solution()<<"\n";
    return 0;
}
