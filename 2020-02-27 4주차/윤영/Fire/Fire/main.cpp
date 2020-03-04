//
//  main.cpp
//  Fire
//
//  Created by 조윤영 on 03/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
// 무언가를 퍼트리면서 진행할 때에는 BFS, 어떻게 진행되는지 이 문제를 토대로 계속 응용해나갈 것.
//문제 유형: BFS
//https://www.acmicpc.net/problem/4179
#include <iostream>
#include <queue>
#define MAX_SIZE 1001

using namespace std;

int R = 0;
int C = 0;

char room[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int fired[MAX_SIZE][MAX_SIZE];

int resultStaus = 0;


struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};

queue<pair<int, int>> JihunQ;
queue<pair<int, int>> fireQ;

void input() {
    cin >> R >> C;
    
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cin >> room[i][j];
            if(room[i][j] == 'F')fireQ.push({i, j});
            if(room[i][j] == 'J')JihunQ.push({i, j});

        }
    }
}

bool canMove(int y,int x) {
    if(0<=y && y<R && 0<=x && x<C )return true;
    return false;
}

int bfs() {
    while(!JihunQ.empty()) {
        int jihunQSize = JihunQ.size();
        int fireQSize = fireQ.size();
        
        resultStaus++;
        for(int i=0; i<fireQSize; i++) {
            int currentFireY = fireQ.front().first;
            int currentFireX = fireQ.front().second;
                    
            fireQ.pop();
            for(int i=0; i<4; i++) {
                int nextFireY = currentFireY + moveDir[i].y;
                int nextFireX = currentFireX + moveDir[i].x;
                        
                if(canMove(nextFireY, nextFireX)) {
                    if(room[nextFireY][nextFireX] != '#' && !fired[nextFireY][nextFireX]) {
                        fireQ.push(make_pair(nextFireY, nextFireX));
                        fired[nextFireY][nextFireX] = true;
                        room[nextFireY][nextFireX] = 'F';
                    }
                }
            }
        }
        
        while(jihunQSize--) {
            int currentY = JihunQ.front().first;
            int currentX = JihunQ.front().second;
            
            
            JihunQ.pop();
            
            for(int i=0; i<4; i++) {
                int nextY = currentY + moveDir[i].y;
                int nextX = currentX + moveDir[i].x;
                
                if(canMove(nextY, nextX)) {

                    if(!visited[nextY][nextX] && room[nextY][nextX] == '.') {
                        visited[nextY][nextX] = true;
                        JihunQ.push(make_pair(nextY, nextX));
                    }
                }
                else{//범위 밖이라면? 탈출한 것이기 때문에
                    return resultStaus;
                }
            }
        }

        
        cout<<"======================"<<endl;
        for(int i=0; i<R; i++) {
            for(int j=0; j<C; j++) {
                cout<<room[i][j];
            }
            cout<<endl;
        }
        cout<<"======================"<<endl;
    }
    return -1;
}

void solution() {
    int result = bfs();
    if(result == -1)cout<<"IMPOSSIBLE\n";
    else cout<<result<<"\n";
}


int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
