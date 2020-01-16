//
//  main.cpp
//  RedGreen_yoon
//
//  Created by 조윤영 on 16/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 101

using namespace std;

int N = 0;
int normalPeopleCatchColor = 0;
int redGreenPeopleCatchColor = 0;

char room[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE] = {false};
bool visitedRedGreen[MAX_SIZE][MAX_SIZE] = {false};

bool isGreenOrRed = false;

struct Dir{
    int y;
    int x;
};

Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};

//적록색약인 사람: 빨 초를 구분하지 못하는 사람인듯

//1. 적록색약이 아닌 사람 먼저 계산하기

//새로운 색 판별하는 필터
bool checkIfNewColor(int posY,int posX) {
    if(0<=posY && posY<N && 0<=posX && posX <N )
        if(visited[posY][posX] != true )return true;
    
    return false;
}

//적록
bool checkIfNewColorGreenRed(int posY, int posX) {
    if(0<=posY && posY<N && 0<=posX && posX <N )
        if(visitedRedGreen[posY][posX] != true)return true;

    return false;
}

//비적록색약에 해당하는 필터
bool checkIfSameColorNormal(int posY, int posX, char targetColor) {
    if(0<=posY && posY <N && 0<=posX && posX <N )
        if(visited[posY][posX] !=true && room[posY][posX] == targetColor)return true;

    return false;
}

bool checkIfSameColorGreenRed(int posY, int posX, char targetColor) {
    if(targetColor == 'R' || targetColor == 'G') {
        if(0<=posY && posY <N && 0<=posX && posX <N )
            if(visitedRedGreen[posY][posX] !=true)
                if(room[posY][posX] == 'R' || room[posY][posX] =='G')return true;
    }else{
        if(0<=posY && posY <N && 0<=posX && posX <N )
            if(visitedRedGreen[posY][posX] !=true && room[posY][posX] == targetColor)return true;
    }

    return false;
}


void dfs(int posY, int posX, char color, bool isRedGreen) {
    int currentY = posY;
    int currentX = posX;
    
    int nextY = 0;
    int nextX = 0;
    
    cout<<"["<<currentY<<","<<currentX<<"]";
    
    
    if(isRedGreen == false) {
        visited[currentY][currentX] = true;
        for(int i=0; i<4; i++) {
            nextY = currentY + moveDir[i].y;
            nextX = currentX + moveDir[i].x;
            if(checkIfSameColorNormal(nextY, nextX, color) == true)dfs(nextY, nextX, color, false);
            
        }
    }else{
        visitedRedGreen[currentY][currentX] = true;
        for(int i=0; i<4; i++) {
            nextY = currentY + moveDir[i].y;
            nextX = currentX + moveDir[i].x;
            if(checkIfSameColorGreenRed(nextY, nextX, color) == true)dfs(nextY, nextX, color, true);
            
        }
    }

    return;
    
}

void solution() {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            //여기서 적록색약인 사람이랑 아닌 사람이랑 구분하기
            if(checkIfNewColor(i,j) == true) {
                cout<<endl;
                cout<<"*********************"<<endl;
                cout<<"정상"<<endl;
                cout<<"*********************"<<endl;
                normalPeopleCatchColor++;
                dfs(i, j, room[i][j], false);
            }
            if(checkIfNewColorGreenRed(i, j) == true) {
                cout<<endl;
                cout<<"*********************"<<endl;
                cout<<"적색"<<endl;
                cout<<"*********************"<<endl;
                redGreenPeopleCatchColor++;
                dfs(i, j, room[i][j], true);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin>>N;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin>>room[i][j];
        }
    }

    solution();
    cout<<"정답:"<<endl;
    cout<<normalPeopleCatchColor<<","<<endl;
    cout<<redGreenPeopleCatchColor;
    return 0;
}
