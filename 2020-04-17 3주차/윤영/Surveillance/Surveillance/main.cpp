//
//  main.cpp
//  Surveillance
//
//  Created by 조윤영 on 23/04/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/15683

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX_SIZE 9

using namespace std;
struct Dir {
    int y;
    int x;
    Dir(int _y, int _x) {
        y = _y;
        x = _x;
    };
};

Dir moveDir[4] = {{0,1},{1,0},{0,-1},{-1,0}};
vector<vector<int>> CCTV = {{},{0},{0,2},{0,3},{0,2,3},{0,1,2,3}};
int switchDirCnt[6] = {0,4,2,4,4,1};

int N = 0;
int M = 0;
int room[MAX_SIZE][MAX_SIZE];
int emptyCnt = 0;
int answer = 64;

vector<pair<int,int>> pos;

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>> N>>M;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin>> room[i][j];
            
            
            if(room[i][j] == 0)emptyCnt++;
            else if(room[i][j] != 0 && room[i][j] != 6)pos.push_back({i,j});
        }
    }
}

bool isAvailable(int y, int x) {
    if(0<=y && y<N && 0<=x && x<M && room[y][x] != 6)return true;
    return false;
}

void search(int index, int empty) {

    if(index == pos.size()){
        answer = min(answer, empty);
        return;
    }
    
    int type = room[pos[index].first][pos[index].second];

    int currentY = pos[index].first;
    int currentX = pos[index].second;
    
    int zeroCnt = empty;
    
    for(int i=0; i<switchDirCnt[type]; i++) {
        int temp[MAX_SIZE][MAX_SIZE];
        memcpy(temp, room, sizeof(room));
        
        for(int j=0; j<CCTV[type].size(); j++) {

            int currentDirY = moveDir[CCTV[type][j]].y;
            int currentDirX = moveDir[CCTV[type][j]].x;
            
            int nextY = currentY + currentDirY;
            int nextX = currentX + currentDirX;
            
            while(isAvailable(nextY, nextX)) {
                if(room[nextY][nextX] == 0){
                    room[nextY][nextX] = -1;
                    zeroCnt--;
                    
                }
                nextY += currentDirY;
                nextX += currentDirX;
            }
            CCTV[type][j] = (CCTV[type][j]+1)%4;
        }
        

        search(index+1, zeroCnt);
        memcpy(room,temp, sizeof(temp)); //다시 되돌린다.
        zeroCnt = empty;
        
    }
}
void solution() {
    search(0, emptyCnt);
    cout<<answer<<"\n";
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
