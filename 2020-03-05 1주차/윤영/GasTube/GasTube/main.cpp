//
//  main.cpp
//  GasTube
//
//  Created by 조윤영 on 06/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 26
using namespace std;

int R = 0;
int C = 0;

char room[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

int sourceY = 0;
int sourceX = 0;

int answerY = 0;
int answerX = 0;
char answerBlock;

int missingBlockY = -1;
int missingBlockX = -1;

struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{1,0},{-1,0},{0,-1},{0,1}};


void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> R >> C;
    
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cin >>room[i][j];
            
            //시작점 저장.
            if(room[i][j] == 'M') {
                sourceY = i;
                sourceX = j;
            }
        }
    }
}

bool isInBoundary(int y,int x) {
    if(0<=y && y<R && 0<=x && x<C && room[y][x] != '.' && visited[y][x]!=true)return true;
    
    return false;
}

bool isConnectedPipeExist(int y,int x) {
    if(0<=y && y<R && 0<=x && x<C){
        return true;
    }
    
    return false;
}

char tryMatchingPipe(int dir, int prevDir) {
    
    char block;
//    cout<<"here you go:"<<prevDir<<"->"<<dir<<endl;
    if ((prevDir == 1 && dir == 3) || (prevDir == 2 && dir == 0))block = '1';
    else if((prevDir == 0 && dir == 3) || (prevDir == 2 && dir == 1))block = '2';
    else if((prevDir == 3 && dir == 1) || (prevDir == 0 && dir == 2))block = '3';
    else if((prevDir == 3 && dir == 0) ||(prevDir == 1 && dir == 2))block = '4';
    else if(prevDir == dir && (prevDir == 2|| prevDir == 3))block = '-';
    else if(prevDir == dir && (prevDir == 0 || prevDir == 1))block = '|';
    else block = '0';
    
//    cout<<"what?"<<block<<endl;
    return block;
}

void findMissingBlock(int prevY, int prevX, int y, int x, int prevDir) {
    char block;
    
    vector<int> candidate;
    
    
    missingBlockY = y;
    missingBlockX = x;
    
//    cout<<missingBlockY<<","<<missingBlockX<<endl;
    for(int i=0; i<4; i++) {
        int nextY = y + moveDir[i].y;
        int nextX = x + moveDir[i].x;
//        cout<<"시도:"<<nextY<<","<<nextX<<":"<<room[nextY][nextX]<<endl;
        if(isConnectedPipeExist(nextY, nextX) && !visited[nextY][nextX] && room[nextY][nextX] != '.'){
//            cout<<"=>"<<nextY<<","<<nextX<<":"<<room[nextY][nextX]<<endl;
            
            if(room[nextY][nextX] == '1'){
                if(isInBoundary(missingBlockY + moveDir[1].y, missingBlockX + moveDir[1].x)) {
                    candidate.push_back(1);
                }
                if(isInBoundary(missingBlockY + moveDir[2].y, missingBlockX + moveDir[2].x)) {
                    candidate.push_back(2);
                }
            }else if(room[nextY][nextX] == '2') {

                if(isInBoundary(missingBlockY + moveDir[2].y, missingBlockX + moveDir[2].x)) {
                    candidate.push_back(2);
                }
                if(isInBoundary(missingBlockY + moveDir[0].y, missingBlockX + moveDir[0].x)) {
                    candidate.push_back(0);
                }
            }else if(room[nextY][nextX] == '3') {
                if(isInBoundary(missingBlockY + moveDir[0].y, missingBlockX + moveDir[0].x)) {
                    candidate.push_back(0);
                }
                if(isInBoundary(missingBlockY + moveDir[3].y, missingBlockX + moveDir[3].x)) {
                    candidate.push_back(3);
                }
            }else if(room[nextY][nextX] == '4') {
                if(isInBoundary(missingBlockY + moveDir[3].y, missingBlockX + moveDir[3].x)) {
                    candidate.push_back(3);
                }
                if(isInBoundary(missingBlockY + moveDir[1].y, missingBlockX + moveDir[1].x)) {
                    candidate.push_back(1);
                }
            }else if(room[nextY][nextX] == '|'){
                if(isInBoundary(missingBlockY + moveDir[0].y, missingBlockX + moveDir[0].x)) {
                    candidate.push_back(0);
                }
                if(isInBoundary(missingBlockY + moveDir[1].y, missingBlockX + moveDir[1].x)) {
                    candidate.push_back(1);
                }
            }else if(room[nextY][nextX] == '-') {
                if(isInBoundary(missingBlockY + moveDir[2].y, missingBlockX + moveDir[2].x)) {
                    candidate.push_back(2);
                }
//                cout<<"엥"<<missingBlockY+moveDir[3].y<<","<<missingBlockX + moveDir[3].x;
                if(isInBoundary(missingBlockY + moveDir[3].y, missingBlockX + moveDir[3].x)) {
                    candidate.push_back(3);
                }

            }else{//+
                if(isInBoundary(missingBlockY + moveDir[i].y, missingBlockX + moveDir[i].x)) {
                    candidate.push_back(i);
                }
            }
            
            for(std::vector<int>::size_type j=0; j<candidate.size(); j++) {
                
//                cout<<y<<"("<<prevDir<<"->"<<candidate[j]<<")"<<endl;
                block = tryMatchingPipe(candidate[j], prevDir);
//                cout<<":::"<<block<<endl;
                if(block != '0') {
                    
                    answerBlock = block;
//                    cout<<"??"<<answerBlock;
                    room[y][x] = answerBlock;
//                    cout<<answerBlock;
                    return;
                }
            }
            candidate.clear();
        }
    }
    
    
    
}

int findNextDirection(char tube, int dir) {
    
    int nextDir = 0;
    switch(tube) {
        case '1':
            //"좌" -> 하 //상 -> 우
            nextDir = (dir+2)%4;
            break;
        case '2':
            //"하" -> 우  // 좌 -> 상
            nextDir = (dir+3)%4;
            break;
        case '3':
            //"하" -> 좌 // 우 -> 상
            nextDir = (dir+2)%4;
            break;
        case '4':
            //"오" -> 하 // 상->좌
            nextDir = (dir+1)%4;
            break;
        default:
            // |,-,+ => 원래 가지고 있던 방향 그대로 가는 block
            nextDir = dir;
            break;
    }
    
    return nextDir;
    
}

void dfs(int prevY, int prevX, int currentY, int currentX, int dir) {

    char currentBlock = room[currentY][currentX];
    int nextY = 0;
    int nextX = 0;
    int nextDir = 0;

    
    if(room[currentY][currentX] == 'Z')return; //끝까지 간다 +를 찾기 위해
    
    visited[currentY][currentX] = true;
    
    if(room[currentY][currentX] == '+')visited[currentY][currentX] = false;
    
    if(currentY == missingBlockY && currentX == missingBlockX) {
//        cout<<"??????????????"<<endl;
        answerBlock = '+';
        return;
    }
    
//    cout<<"["<<currentY<<","<<currentX<<":"<<room[currentY][currentX]<<"]"<<endl;
    if(room[currentY][currentX] == '.') {
        answerY = currentY+1;
        answerX = currentX+1;
        findMissingBlock(prevY, prevX, currentY, currentX, dir);
        currentBlock = room[currentY][currentX];
//        cout<<"================================"<<endl; cout<<"(수정)["<<currentY<<","<<currentX<<":"<<room[currentY][currentX]<<"]"<<endl;
//        cout<<"================================"<<endl;
//
    }

    
    
//    cout<<"->"<<currentBlock;
    
    nextDir = findNextDirection(currentBlock,dir);
    
    
    nextY = currentY + moveDir[nextDir].y;
    nextX = currentX + moveDir[nextDir].x;
    
    dfs(currentY, currentX, nextY, nextX, nextDir);
}


void solution() {
    int nextY = 0;
    int nextX = 0;
    int dir = 0;
    
    for(int i=0; i<4; i++) {
        nextY = sourceY + moveDir[i].y;
        nextX = sourceX + moveDir[i].x;
        dir = i;

        if(isInBoundary(nextY, nextX) && room[nextY][nextX] != 'Z'){
            break;
        }
    }
    
    dfs(sourceY, sourceX, nextY, nextX, dir);
    
    cout<<answerY<<" "<<answerX<<" "<<answerBlock<<endl;
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
