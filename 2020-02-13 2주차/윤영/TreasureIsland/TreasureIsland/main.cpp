//
//  main.cpp
//  TreasureIsland
//
//  Created by 조윤영 on 13/02/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 51

using namespace std;

struct Dir {
    int y;
    int x;
    
    Dir(int _y, int _x) {
        y = _y;
        x = _x;
    }
};
int L = 0;
int W = 0;

char room[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE] = {false};

vector<Dir> treasure;

int longestLength = 0;
int sourceTreasureY = 0;
int sourceTreasureX = 0;
int destinationTreasureY = 0;
int destinationTreasureX = 0;

Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin>> L >> W;
    
    for(int i=0; i<L; i++) {
        for(int j=0; j<W; j++) {
            cin >> room[i][j];
        }
    }
}

bool isLand(int posY, int posX) {
    if(0<=posY &&  posY <L && 0<= posX && posX <W ){
        if(visited[posY][posX] !=true && room[posY][posX] == 'L')return true;
    }
    return false;
}

bool canMove(int posY, int posX) {
    if(0<=posY &&  posY <L && 0<= posX && posX <W ){
        if(room[posY][posX] == 'L')return true;
    }
    return false;
}

int treasureCandidate1Y = 0;
int treasureCandidate1X = 0;
int treasureCandidate2Y = 0;
int treasureCandidate2X = 0;
int resultLength = 0;

void dfs(int posY, int posX, int length) {
    if(resultLength <length){
        resultLength = length;
        treasureCandidate2Y = posY;
        treasureCandidate2X = posX;
    }
    visited[posY][posX] = true;
    
    int nextY = 0;
    int nextX = 0;
    for(int i=0; i<4; i++) {
        nextY = posY + moveDir[i].y;
        nextX = posX + moveDir[i].x;
        
        if(isLand(nextY, nextX)) {
            dfs(nextY, nextX, length+1);
        }
    }
    visited[posY][posX] = false;
}

void findTreasurePosition() {
    for(int i=0; i<L; i++) {
            for(int j=0; j<W; j++) {
                if(canMove(i, j)){
                    treasureCandidate1Y = i;
                    treasureCandidate1X = j;
                    resultLength = 0;
                    
                    dfs(i, j, 0);
                    
                    if(resultLength > longestLength) {
                        longestLength = resultLength;
                        treasure.clear();
                        treasure.push_back(Dir(treasureCandidate1Y, treasureCandidate1X));
                        treasure.push_back(Dir(treasureCandidate2Y, treasureCandidate2X));
                    }
                }
                
            }
        }
}

int shortLength = MAX_SIZE * MAX_SIZE;

void findShortCut(int currentY, int currentX, int length) {

    if(currentY == destinationTreasureY && currentX == destinationTreasureX) {
        if(length < shortLength) shortLength = length;
    }
    visited[currentY][currentX] = true;
    int nextY = 0;
    int nextX = 0;
    for(int i = 0; i<4; i++) {
        nextY = currentY + moveDir[i].y;
        nextX = currentX + moveDir[i].x;
        
        if(isLand(nextY, nextX)) {
            findShortCut(nextY, nextX, length+1);
        }
    }
    visited[currentY][currentX] = false;
}

int solution() {
    //보물이 묻힌 2곳을 찾기
    findTreasurePosition();
    
    //보물 묻인 곳 확인
    sourceTreasureY = treasure[0].y;
    sourceTreasureX = treasure[0].x;
    destinationTreasureY = treasure[1].y;
    destinationTreasureX = treasure[1].x;

    //보물 간의 최단 거리 구하기
    findShortCut(sourceTreasureY, sourceTreasureX, 0);
    return shortLength;
    
}
int main(int argc, const char * argv[]) {
    
    input();
    solution();
    cout<<shortLength;
    
    return 0;
}
