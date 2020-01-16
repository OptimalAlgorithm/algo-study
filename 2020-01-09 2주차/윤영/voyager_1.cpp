//
//  main.cpp
//  Voyager_1
//
//  Created by 조윤영 on 09/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <stack>

#define MAX_SIZE 500
#define U 0
#define D 1
#define L 2
#define R 3

using namespace std;

char room[MAX_SIZE][MAX_SIZE];

int resultSignalLength = 0;
int resultDirection = 0;
int N = 0;
int M = 0;
int PR = 0;
int PC = 0;

int answerSignalLength = 0;
char answerSignalDirection;

struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{-1,0},{1,0},{0,1},{0,-1}};// 상 하 우 좌

void dfs(int y, int x, int direction, int signalL) {
    int currentY = y;
    int currentX = x;
    
    //원래 가던 방향으로 가야함.
    int nextY = currentY+moveDir[direction].y;
    int nextX = currentX+moveDir[direction].x;
    
    int rotationNextY = 0;
    int rotationNextX = 0;
    int rotationDirection = 0;
    
    bool isWay = false;
    
    if(0<=nextY && nextY <=N && 0<=nextX && nextX<=M && room[nextY][nextX] !='C') {
        isWay = true;
        
        signalL +=1;
        if(room[nextY][nextX] == '/') {
            
            signalL +=1;
            rotationNextY = nextY + moveDir[(direction+2)%4].y;
            rotationNextX = nextX + moveDir[(direction+2)%4].x;
            
            if(0<=rotationNextY && rotationNextY <=N && 0<=rotationNextX && rotationNextX<=M && room[rotationNextY][rotationNextX] !='C'){
                nextY = rotationNextY;
                nextX  = rotationNextX;
                
                cout<<"꺾기 후 이동["<<nextY<<"]"<<"["<<nextX<<"]"<<endl;
                
            } else{
                resultSignalLength = signalL;
                resultDirection = direction;
                return;
            }
            
            direction =(direction+2)%4;
            
        }else if(room[nextY][nextX] == '\\') {
            signalL +=1;
            switch(direction) {
                case U:
                    rotationNextY = nextY + moveDir[L].y;
                    rotationNextX = nextX + moveDir[L].x;
                    rotationDirection = L;
                    break;
                case D:
                    rotationNextY= nextY + moveDir[R].y;
                    rotationNextX= nextX + moveDir[R].x;
                    rotationDirection = R;
                    break;
                case L:
                    rotationNextY = nextY + moveDir[U].y;
                    rotationNextX = nextX + moveDir[U].x;
                    rotationDirection = U;
                    break;
                case R:
                    rotationNextY = nextY + moveDir[D].y;
                    rotationNextX = nextX + moveDir[D].x;
                    rotationDirection = D;
                    break;
            }
             if(0<=rotationNextY && rotationNextY <=N && 0<=rotationNextX && rotationNextX<=M && room[rotationNextY][rotationNextX] !='C'){
                 nextY = rotationNextX;
                 nextX = rotationNextY;
                 direction = rotationDirection;
                 
             }else{
                 resultSignalLength = signalL;
                 resultDirection = direction;
                 return;
                 
             }
            cout<<"꺾기 후 이동["<<nextY<<"]"<<"["<<nextX<<"]"<<endl;
            
        }else{
            cout<<"이동["<<nextY<<"]"<<"["<<nextX<<"]"<<endl;
        }
        currentY = nextY;
        currentX = nextX;
        
        
        dfs(currentY, currentX, direction, signalL);
    }
    
    if(isWay == false) {//더 이상 갈 방향이 없기 때문에 시그널 전파 종료
        resultSignalLength = signalL;
        resultDirection = direction;
    }
    
    
}

//시그널이 인접한 칸으로 이동하는데 걸리는 시간은 1초이다.
//탐사선이 어느 방향으로 시그널을 보내면, 시그널이 항성계 내부에 있는 시간이 최대가 되는지 구하는 프로그램을 작성하시오.
void solution() {
    //room[PR][PC];
    
    int currentY = PR;
    int currentX = PC;
    int nextY = 0;
    int nextX = 0;
    int direction = 0;
    int length = 0;
    
    cout<<"["<<currentY<<"]"<<"["<<currentX<<"]"<<endl;
    // 상 하 우 좌
    for(int i=0; i<4; i++) { //MARK: 디버깅 위해 수정: 1-> 4로 수정 핋요!
        nextY = currentY + moveDir[i].y;
        nextX = currentX + moveDir[i].x;
        
        
        if(0<=nextY && nextY <=N && 0<=nextX && nextX<=M && room[nextY][nextX] != 'C') {
            length =1;
            if(room[nextY][nextX] == '/'){
                length+=1;
                //우 -> 상 +2
                //좌 -> 하 +2
                //하 -> 좌 +2
                //상 -> 우 +2
                nextY += moveDir[(i+2)%4].y;
                nextX += moveDir[(i+2)%4].x;
                direction = i;

            }else if(room[nextY][nextX] == '\\') {
                length+=1;
                //switch 안쓰고싶은데 ...
                //FIME: 구조 고칠 것
                switch(i) {
                    case U:
                        nextY+=moveDir[L].y;
                        nextX+=moveDir[L].x;
                        direction = L;
                        break;
                    case D:
                        nextY+=moveDir[R].y;
                        nextX+=moveDir[R].x;
                        direction = R;
                        break;
                    case L:
                        nextY+=moveDir[U].y;
                        nextX+=moveDir[U].x;
                        direction = U;
                        break;
                    case R:
                        nextY+=moveDir[D].y;
                        nextX+=moveDir[D].x;
                        direction = D;
                        break;
                }
            }
            
            currentY = nextY;
            currentX = nextX;
            cout<<"이동["<<nextY<<"]"<<"["<<nextX<<"]"<<endl;
            dfs(nextY, nextX, direction, length);

        }
        
        if(resultSignalLength > answerSignalLength) {
            answerSignalLength = resultSignalLength;
            switch(resultDirection) {
                case U: answerSignalDirection = U;break;
                case D: answerSignalDirection = D; break;
                case L: answerSignalDirection = L; break;
                case R: answerSignalDirection = R; break;
            }
            
        }
        
        cout<<i<<"회전 결과"<<answerSignalDirection<<endl;
        cout<<i<<"길이 결과"<<answerSignalLength;

    }
    return;
}


int main(int argc, const char * argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin>> N >> M;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin>>room[i][j];
        }
    }
    
    cin >> PR >> PC;
    PR-=1;
    PC-=1;
    solution();
    
    cout<<"legnthL"<<answerSignalLength<<endl;
    cout<<"direction:"<<answerSignalDirection;
    
    return 0;
}
