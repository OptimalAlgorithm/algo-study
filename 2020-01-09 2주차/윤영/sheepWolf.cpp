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
int wolf = 0;
int sheep = 0;
int sheepCnt = 0;
int wolfCnt = 0;

void bfs(int r, int c) {
    
    //방문했음을 알리고,
    visited[r][c] = true;
    
    int currentY = r;
    int currentX = c;
    
    int nextY = 0;
    int nextX = 0;
    
    
    for(int i=0; i<4; i++) {
        
        nextY = currentY + moveDir[i].y;
        nextX = currentX + moveDir[i].x;
        
        if(0<=nextY && nextY <R && 0<=nextX && nextX <C && room[nextY][nextX] !='#' && visited[nextY][nextX] !=true) {
            if(room[nextY][nextX] == 'v') { //wolf라면,
                wolf++;
            }else if(room[nextY][nextX] == 'o'){//sheep라면,
                sheep++;
            }
            //빈 필드 또는 늑대 또는 양일 경우 모두 다음 장소로 이동.
            bfs(nextY, nextX);
        }
    }
    return;
    
    //모두 return 했을 때
    // 우리의 양은 늑대에게 싸움을 걸 수 있고 영역 안의 양의 수가 늑대의 수보다 많다면 이기게 된다. 그렇지 않다면 늑대가 그 지역 안의 모든 양을 먹는다.
    
//    if(isWay == false) {//갈 수 있는 길이 더 이상 없을 때,
//        return;
//    }
}
void solution() {
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            wolf = 0;
            sheep = 0;
            if(room[i][j] == 'v' && visited[i][j]!=true) {
                wolf++;
                bfs(i, j);
                
                if(sheep > wolf) {
                    wolf = 0;
                }else{
                    sheep = 0;
                }
                
                sheepCnt += sheep;
                wolfCnt += wolf;
                
                
            }else if (room[i][j] == 'o' && visited[i][j]!=true) {
                sheep++;
                bfs(i, j);
                
                if(sheep > wolf) {
                    wolf = 0;
                }else{
                    sheep = 0;
                }
                
                sheepCnt += sheep;
                wolfCnt += wolf;
                
            }

        }
        
    }
    cout<<sheepCnt<<" "<<wolfCnt<<endl;
    
}
int main(int argc, const char * argv[]) {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    cin>>R>>C;
    
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            
            cin>>room[i][j];
            
        }
    }
    
    solution();
    return 0;
}
