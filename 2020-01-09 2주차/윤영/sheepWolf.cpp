//
//  main.cpp
//  Sheep
//
//  Created by 조윤영 on 09/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 250

using namespace std;

struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};

int R = 0;
int C = 0;
char room[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE] = {false};
int sheepCnt = 0;
int wolfCnt = 0;
int tempSheepCnt = 0;
int tempWolfCnt = 0;

void dfs(int r, int c, int sheep, int wolf) {
    
    //방문했음을 알리고,
    visited[r][c] = true;
    
    int currentY = r;
    int currentX = c;
    int nextY = 0;
    int nextX = 0;
    
    int addSheep = 0;
    int addWolf = 0;
    
    tempWolfCnt = wolf;
    tempSheepCnt = sheep;
    
    bool isWay = false;
    
    for(int i=0; i<4; i++) {
        nextY = currentY + moveDir[i].y;
        nextX = currentX + moveDir[i].x;
        cout<<"["<<nextY<<"]"<<"["<<nextX<<"]"<<endl;
        if(0<=nextY && nextY <=R && 0<=nextX && nextX <=C && room[nextY][nextX] !='#' && visited[nextY][nextX] !=true) {
            isWay = true;
            if(room[nextY][nextX] == 'v') { //wolf라면,
                cout<<"늑대 또 여기 있다"<<nextY<<","<<nextX<<endl;
                addWolf++;
            }else if(room[nextY][nextX] == 'o'){//sheep라면,
                cout<<"양 또 여기 있다"<<nextY<<","<<nextX<<endl;
                addSheep++;
            }
            //빈 필드 또는 늑대 또는 양일 경우 모두 다음 장소로 이동.
            currentY = nextY;
            currentX = nextX;
            
            dfs(currentY, currentX, sheep+addSheep, wolf+addWolf);
        }
    }
    //모두 return 했을 때
    // 우리의 양은 늑대에게 싸움을 걸 수 있고 영역 안의 양의 수가 늑대의 수보다 많다면 이기게 된다. 그렇지 않다면 늑대가 그 지역 안의 모든 양을 먹는다.
    
    if(isWay == false) {//갈 수 있는 길이 더 이상 없을 때,
        if(tempSheepCnt > tempWolfCnt) {
            wolf = 0;
        }else{
            sheep = 0;
        }
        
        sheepCnt += sheep;
        wolfCnt += wolf;
        
        cout<<"늑대:"<<wolf<<"양"<<sheep<<endl;
        
        return;
    }
}
void solution() {
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            if(room[i][j] == 'v' && visited[i][j]!=true) {
                cout<<"늑대 여기 있다"<<i<<","<<j<<endl;
                dfs(i, j,0,1);
            }else if (room[i][j] == 'o' && visited[i][j]!=true) {
                cout<<"양 여기 있다"<<i<<","<<j<<endl;
                dfs(i, j, 1,0);
            }
        }
    }
    cout<<"sheep:"<<sheepCnt<<endl;
    cout<<"wolf:"<<wolfCnt<<endl;
    
}
int main(int argc, const char * argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin>>R>>C;
    
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            
            cin>>room[i][j];
            
        }
    }
    
    solution();
    return 0;
}
