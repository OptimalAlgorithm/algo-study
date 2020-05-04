//
//  main.cpp
//  MakeBridge2
//
//  Created by 조윤영 on 02/05/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/17472
//
//하나로 연결된 경우를 캐치하는 것이 관건
//풀이 보고 다시 풀기

#include <iostream>
#include <queue>
#include <algorithm>

#define MAX_SIZE 11
#define LAND_CNT 7

using namespace std;

void builtBridge(int prevY, int prevX, int prevLand, int y,int x, int dir, int cnt);
void findPlaceToBuilt(int startY, int startX);

int N = 0;
int M = 0;
int room[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int land[LAND_CNT];

int bridgeCnt = 0;
int minBridgeCnt = MAX_SIZE*MAX_SIZE;

int landNumb = 2;
int landConnected = 0;
queue<pair<int,int>> landPiece;

struct Dir {
    int y;
    int x;
    
};

vector<vector<int>> land_relation;

Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> N >> M;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin>> room[i][j];
        }
    }
}

queue<pair<int,int>> relations_island;

bool isInBoundary(int y,int x) {
    if(0<=y && y<N && 0<=x && x<M)return true;
    
    return false;
}
void searchSameLand() {
    while(!landPiece.empty()){
        
        int currentY = landPiece.front().first;
        int currentX = landPiece.front().second;
        landPiece.pop();
        
        for(int i=0; i<4; i++) {
            int nextY = currentY + moveDir[i].y;
            int nextX = currentX + moveDir[i].x;
            if(isInBoundary(nextY, nextX)) {
                if(room[nextY][nextX] == 1){
                    room[nextY][nextX] = landNumb;
                    landPiece.push({nextY, nextX});
                }
            }
        }
    }
    
    landNumb++;
}

void checkIsConnectedInOne() {
    
}

void findPlaceToBuilt(int startY, int startX) {
    for(int i=startY; i<N; i++) {
        for(int j=0; j<M; j++) {
            int currentLandNumb = room[i][j];
            cout<<i<<","<<j<<endl;
            if(!visited[i][j] && currentLandNumb != 0 && !land[currentLandNumb]) {
                visited[i][j] = true;
                for(int d=0; d<4; d++) {
                    int nextY = i + moveDir[d].y;
                    int nextX = j + moveDir[d].x;
                    
                    //다리를 놓을 공간이 있는가?
                    if(isInBoundary(nextY, nextX) && room[nextY][nextX] == 0){
                        land[currentLandNumb] = true;
                        landConnected++;
                        cout<<"["<<i<<"]["<<j<<"]->";
                        cout<<"["<<nextY<<"]["<<nextX<<"]:";
                        builtBridge(i, j,currentLandNumb,nextY, nextX, d, 1);
                        
                        land[currentLandNumb] = false;
                        landConnected--;
                    }
                }
                
                
            }
        }
    }
}

void builtBridge(int prevY, int prevX, int prevLand, int y,int x, int dir, int cnt) {
    
    int currentY = y;
    int currentX = x;
    int newLandNumb = 0;
    while(true) {
        int nextY = currentY + moveDir[dir].y;
        int nextX = currentX + moveDir[dir].x;
        if(isInBoundary(nextY, nextX)) {
            if(room[nextY][nextX] == 0) {
                cout<<"("<<nextY<<")("<<nextX<<")"<<endl;
                cnt++;
                currentY = nextY;
                currentX = nextX;
            }else if(room[nextY][nextX] == prevLand){
                return;
            }
            else{
                visited[nextY][nextX] = true;
                cout<<nextY<<","<<nextX<<endl;
                newLandNumb = room[nextY][nextX];
                
                
                break;
            }
        }else return;
    }
    cout<<"------------------Good---------"<<endl;
    if(cnt >=2) {
        cout<<"cnt:"<<cnt;
        
        bool alreadyVisited = false;
        cout<<newLandNumb<<endl;
        if(!land[newLandNumb]) {
            land[newLandNumb] = true;
            landConnected++;
            
        }else{
            alreadyVisited = true;
        }
        
        bridgeCnt += cnt;
        
        cout<<"연결된 섬의 총 수:"<<landConnected<<endl;
        
        if(landConnected == landNumb-2) {
            cout<<"======================="<<endl;
            cout<<"=>"<<bridgeCnt<<endl;
            minBridgeCnt = min(minBridgeCnt, bridgeCnt);
            cout<<"결과:"<<minBridgeCnt<<endl;
            cout<<"======================="<<endl;
            
        }else{
            //다른 섬에 무사히 연결되었고, 그 길이가 2 이상일 때,
            cout<<"이어서 시작!"<<y<<","<<x<<endl;
            findPlaceToBuilt(prevY, prevX);
            
        }
        
        bridgeCnt -= cnt;
        if(!alreadyVisited){
            land[newLandNumb] = false;
            landConnected--;
        }
    }
}

void solution() {
    //섬 지역 구분하기
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(room[i][j] == 1){
                room[i][j] = landNumb;
                landPiece.push({i,j});
                searchSameLand();
            }
        }
    }
    
    land_relation.assign(landNumb, {});
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cout<<room[i][j];
        }
        cout<<endl;
    }
    
    //처음부터 끝까지 훑으면서 섬을 마주치면 좌우상하에 다리 놓을 자리가 있는지 확인해본다.
    findPlaceToBuilt(0,0);
    
    cout<<"********"<<endl;
    cout<<minBridgeCnt<<"\n";
    cout<<"********"<<endl;
}
int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
