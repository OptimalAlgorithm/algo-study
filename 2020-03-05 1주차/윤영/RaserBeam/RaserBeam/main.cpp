//
//  main.cpp
//  RaserBeam
//
//  Created by 조윤영 on 05/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#define MAX_SIZE 51

using namespace std;

int T = 0;
int n = 0;
int r = 0;
int laserY = 0;
int laserX = 0;
int nextLaserY = 0;
int nextLaserX = 0;
int laserDir = 0;

int exitY = 0;
int exitX = 0;

vector<pair<int, int>> pos;
int room[MAX_SIZE][MAX_SIZE];
struct Dir{
    int y;
    int x;
};
int historyDir[MAX_SIZE][MAX_SIZE] = {-1};

Dir moveDir[4] = {{-1,0},{0,1},{1,0},{0,-1}};

bool isLaserGetOut(int y, int x) {
    if(!(1<=y && y <=n && 1<= x && x <=n))return true;
    return false;
}
bool solution() {
    
    
    while(true) {

        //무한루프일 경우
//        if(historyDir[laserY][laserX] != -1 && historyDir[laserY][laserX] == laserDir) {
//            //방문한 적이 있고, 같은 방향으로 재방문 했다면 무한루프
//            break;
//        }

        //무한루프가 아닐 경우
        historyDir[laserY][laserX] = laserDir;//방문했던 방향 남겨주고
        nextLaserY = laserY + moveDir[laserDir].y;
        nextLaserX = laserX + moveDir[laserDir].x;

        //우향우 거울이 있다면
        if(room[nextLaserY][nextLaserX] == 1) {
            laserDir = (laserDir+1)%4;
        }
        laserY = nextLaserY;
        laserX = nextLaserX;
        
//        cout<<"["<<laserY<<"]["<<laserX<<"]"<<endl;
        //탈출했다면,
        if(isLaserGetOut(laserY, laserX))return true;
    }
    return false;
}

void input() {
    cin >> T;
    
    for(int i=0; i<T; i++) {
        memset(room, 0, sizeof(room));
        memset(historyDir, -1, sizeof(historyDir));
        
        cin >>n >> r;
        
        for(int j=0; j<r; j++) {
            int y;
            int x;
            cin >> y >> x;
            room[y][x] = 1;
        }
        cin >> laserY >> laserX;
        
        if(laserY == n+1)laserDir = 0;
        else if (laserY == 0)laserDir = 2;
        else if (laserX == 0)laserDir = 1;
        else if (laserX == n+1)laserDir = 3;
        
        //n+2를 전체 체스판의크기로 생각하면 될듯.
//        for(int i=0; i<n+2; i++) {
//            for(int j=0; j<n+2; j++) {
//                cout<<room[i][j];
//            }
//            cout<<endl;
//        }
        
        if(solution())cout<<laserY <<" "<<laserX<<endl;
        else cout<<"0 0"<<endl;
        
    }
}


int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
