//
//  main.cpp
//  SangbumBuilding
//
//  Created by 조윤영 on 21/02/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/6593
//최단거리는 무조건 BFS로 찾아야 합니다!

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#define MAX_SIZE 31

using namespace std;

int L = 0;//상범 빌딩의 층 수
int R = 0;//상범 빌딩의 한 층의 행
int C = 0;//상범 빌딩의 한 층의 열

char room[MAX_SIZE][MAX_SIZE][MAX_SIZE];//층수, 행,

int sourceLevel = 0;
int sourceY = 0;
int sourceX = 0;
int destLevel = 0;
int destY = 0;
int destX = 0;

struct Dir{
    int y;
    int x;
    int level;
};

Dir moveDir[6] = {{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,1},{0,0,-1}};

bool check(int level, int y, int x) {
    
    if(0<= level && level <L && 0<= y && y <=R && 0<= x && x <=C) return true;
    return false;
}

int bfs() {
    
    queue<Dir> q;
    q.push({sourceY, sourceX, sourceLevel});
    
    int distance = 0;
    
    while(!q.empty()) {
        
        int qSize = q.size();
        
        for(int i=0; i<qSize; i++) {
            int currentLevel = q.front().level;
            int currentY = q.front().y;
            int currentX = q.front().x;
                   
            q.pop();
            
            int nextLevel = 0;
            int nextY = 0;
            int nextX = 0;
            
            for(int j=0; j<6; j++) {
                nextLevel = currentLevel + moveDir[j].level;
                nextY = currentY + moveDir[j].y;
                nextX = currentX + moveDir[j].x;
        
                if(check(nextLevel, nextY, nextX)) {
                    if(room[nextLevel][nextY][nextX] == 'E') return distance;
                    else if (room[nextLevel][nextY][nextX] == '.') {
                        room[nextLevel][nextY][nextX] = '#';
                        q.push({nextY, nextX, nextLevel});
                    }
                    
                }
                
            }
        }
        distance++;
    
    }
    return -1;
}

void solution() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    while(true) {
        cin >> L >> R >> C;
        
        if(L == 0 && R == 0 && C == 0)break;
        
        for(int l=0; l<L; l++) {
            for(int i=0; i<R; i++) {
                for(int j=0; j<C; j++) {
                    cin >> room[l][i][j];
                    
                    if(room[l][i][j] == 'S') {
                        sourceLevel = l;
                        sourceY = i;
                        sourceX = j;
                    }
                }
            }
        }
        
        int res = bfs();
        if(res == -1)cout<<"Trapped!\n";
        else cout<<"Escaped in "<<res+1<<" minute(s).\n";

        memset(room, 0, sizeof(room));
    }
}
int main(int argc, const char * argv[]) {
    solution();
    return 0;
}

