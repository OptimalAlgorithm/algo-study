//
//  main.cpp
//  PuyoPuyo
//
//  Created by 조윤영 on 06/02/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>

#define N 12
#define M 6

using namespace std;

char room[N][M];
int visited[N][M] = {false};

vector<pair<int, int>>track;
int puyoCnt = 0;

int answer = 0;
struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};

struct Puyo {
    int y;
    int x;
    int dir;
    
    Puyo(int _y, int _x, int _dir) {
        y = _y;
        x = _x;
        dir = _dir;
    }
};

vector<Puyo> puyo; //쀼요가 터진 위치와 방향

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j< M; j++) {
            cin >>room[i][j];

        }
    }
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j< M; j++) {
            cout <<"["<<room[i][j]<<"]";

        }
        cout<<endl;
    }
}

bool checkIsSameColor(int posY, int posX, char color) {
    if(0 <=posY && posY <= N && 0 <= posX && posX <= M) {
        if(visited[posY][posX] != true && room[posY][posX] == color)return true;
    }
    
    return false;
}

void dfs(int posY, int posX, int color) {
    
    puyoCnt++;
    cout<<"++";
    
    track.push_back({posY, posX}); //뿌요들의 집합을 저장한다.
    visited[posY][posX] = true;
    
    
    int nextY = 0;
    int nextX = 0;
    
    for(int i=0; i<4; i++) {
        nextY = posY + moveDir[i].y;
        nextX = posX + moveDir[i].x;
        cout<<"("<<nextY<<","<<nextX<<")";
        if(checkIsSameColor(nextY, nextX, color)){
            
            dfs(nextY, nextX, color);
        }
    }
    
    
}

void solution() {
    
    
    
    while(true) {
        for(int i=N-1; i>=0; i--) {
            for(int j=M-1; j>=0; j--) {
                
                if(room[i][j] != '.' && visited[i][j] != true) {
                    puyoCnt = 0;
                    cout<<"**************************";
                    cout<<"["<<i<<","<<j<<"]";
                    cout<<"**************************"<<endl;
                    
                    dfs(i, j, room[i][j]);
                    
                    cout<<"cnt:"<<puyoCnt;
                    if(puyoCnt >= 4) { //뿌요들이 4개 이상이라면,
                        cout<<"뿌요가 4개 이상이군!";
                        answer++;

                    }else {
                        for(int i=0; i<puyoCnt; i++) {
                            track.pop_back();
                        }
                    }
                    cout<<endl;
                    
                }
            }
            
        }
        
        //뿌요들 터트리고, 위의 뿌요들 내려오게 만들기
        //기존 뿌요 자리에는 . 집어넣기
        //그런데 뿌요들 하나도 없으면 return false;
        if(track.size() != 0) {
            for(int i=0; i<track.size(); i++) {
                cout<<"["<<track[i].first<<","<<track[i].second<<"]";

                int puyoY = track[i].first;
                int puyoX = track[i].second;

                for(int i=puyoY; i>=0; i--) {
                    if(i == 0){
                        room[0][puyoX] = '.';
                    }
                    else {
                        room[i][puyoX] = room[i-1][puyoX];
                    }
                }

                for(int i=0; i<track.size(); i++) {
                    if(track[i].second == puyoX)track[i].first++;
                }
                cout<<endl;
                for(int i=0; i<N; i++) {
                    for(int j=0; j<M; j++) {
                        cout<<"["<<room[i][j]<<"]";
                    }
                    cout<<endl;
                }
            }

            track.clear();


            //방문 초기화
            for(int i=0; i<N; i++) {
                for(int j=0; j<M; j++) {
                    visited[i][j] = false;
                }
            }

        }else{
            break;
        }

    }

    
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    cout<<answer;
    return 0;
}


