//
//  main.cpp
//  Tomato_yoon
//
//  Created by 조윤영 on 16/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 1001

using namespace std;

int M = 0;
int N = 0;
int room[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE] = {false};
int answer = 0;
vector<pair<int, int>> tomato;
int tomatoCnt = 0;
int redTomatoCnt = 0;

struct Dir {
    int y;
    int x;
};

int totalTime = 0;

Dir moveDir[4] = {{-1, 0},{1, 0},{0, -1}, {0, 1}};

bool checkIfTomatoIsNotRipe(int posY, int posX) {
    if(0<= posY && posY <N && 0<=posX && posX <M) {
        
        if(visited[posY][posX] != true && room[posY][posX] == 0) {
            return true;
        }
    }
    return false;
}


void dfs(int posY, int posX) {
    
    int nextY = 0;
    int nextX = 0;
    cout<<"level:"<<totalTime<<"["<<posY<<"]"<<"["<<posX<<"]"<<endl;
    
    
    
    visited[posY][posX] = true;
    
    for(int i=0; i<4; i++) {
        nextY = posY + moveDir[i].y;
        nextX = posX + moveDir[i].x;
         
        if(checkIfTomatoIsNotRipe(nextY, nextX) == true) {
            cout<<"level:"<<totalTime<<"["<<nextY<<"]"<<"["<<nextX<<"]"<<endl;
            visited[nextY][nextX] = true;
            tomato.push_back(make_pair(nextY, nextX));
//            dfs(nextY, nextX, relativeTime+1);
        }
    }
    
    return;
}

void solution() {
    int posY = 0;
    int posX = 0;
    while(tomato.size() != tomatoCnt) {
        
        if(totalTime >=tomatoCnt){
            totalTime = -1;
            return;
        }
        
        int tempSize = tomato.size();
        cout<<"지금 익은 토마토 갯수:!!!!";
        cout<<tomato.size()<<endl;
        for(int i=0; i<tempSize; i++) {
            
            posY = tomato[i].first;
            posX = tomato[i].second;
            
            cout<<"출발"<<endl;
            
            dfs(posY, posX);
        }
        totalTime++;
    }
    
}


int main(int argc, const char * argv[]) {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin>>M;
    cin>>N;
    
    tomatoCnt = M*N;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin>>room[i][j];
            if(room[i][j] == 1) {
                tomato.push_back(make_pair(i, j));
                visited[i][j] = true;
                redTomatoCnt++;
            }
            
            if(room[i][j] == -1)tomatoCnt--;
            if(room[i][j] !=0 || room[i][j] !=1 || room[i][j] !=-1)return 0;
            
        }
    }
    
    if(redTomatoCnt == tomatoCnt)return 0;

    solution();
    cout<<totalTime;
    
    return 0;
}
