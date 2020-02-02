//
//  main.cpp
//  Tomato_yoon
//
//  Created by 조윤영 on 16/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

#define MAX_SIZE 1001

using namespace std;

int M = 0;
int N = 0;
int room[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE] = {false};

queue <pair<int, int>> ripenTomato;
queue<pair<int, int>> temp;
int day = 0;
int notRipen = 0;

struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{-1, 0},{1, 0},{0, -1}, {0, 1}};

void input() {
    cin >> M >> N;
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >>room[i][j];

            int currentRoom = room[i][j];

            if(currentRoom == 0) notRipen++;
            else if (currentRoom == 1) {
                ripenTomato.push(make_pair(i, j));
                visited[i][j] = true;
            }
        }
    }
}

bool checkIfTomatoIsNotRipe(int posY, int posX) {
    if(0<= posY && posY <N && 0<=posX && posX <M) {

        if(visited[posY][posX] != true && room[posY][posX] == 0) {
            return true;
        }
    }
    return false;
}

void bfs() {
        while(!ripenTomato.empty()) {
            int currentPosY = ripenTomato.front().first;
            int currentPosX = ripenTomato.front().second;

            ripenTomato.pop();

            for(int i =0; i<4; i++) {
                int nextY = currentPosY + moveDir[i].y;
                int nextX = currentPosX + moveDir[i].x;

                if(checkIfTomatoIsNotRipe(nextY, nextX)) {//이동한 자리에 토마토가 익지 않았다면
                    room[nextY][nextX] = 1;
                    notRipen--;
                    temp.push(make_pair(nextY, nextX));
                    visited[nextY][nextX] = true;
                }

            }


        }

}

void solution() {
    while(true) {

        bfs();
        
        if (temp.empty()) {
            if (notRipen > 0)day = -1;
            
            break;
        }
        
        while(!temp.empty() ){
            ripenTomato.push(temp.front());
            temp.pop();
        }
        
        day++;

    }
}
int main() {
    
    input();

    if(notRipen == 0) {
        day = 0;
        cout<< day;
    }else{
        solution();
        cout<<day;
    }

    return 0;
}

//시간초과되었던 나의 코드...
//vector<pair<int, int>> tomato;
//int tomatoCnt = 0;
//int redTomatoCnt = 0;
//int totalTime = 0;
//void input() {
//
//}
//bool checkIfTomatoIsNotRipe(int posY, int posX) {
//    if(0<= posY && posY <M && 0<=posX && posX <N) {
//
//        if(visited[posY][posX] != true && room[posY][posX] == 0) {
//            return true;
//        }
//    }
//    return false;
//}
//
//
//void bfs(int posY, int posX) {
//
//    int nextY = 0;
//    int nextX = 0;
////    cout<<"level:"<<totalTime<<"["<<posY<<"]"<<"["<<posX<<"]"<<endl;
//
//    visited[posY][posX] = true;
//
//    for(int i=0; i<4; i++) {
//        nextY = posY + moveDir[i].y;
//        nextX = posX + moveDir[i].x;
//
//        if(checkIfTomatoIsNotRipe(nextY, nextX) == true) {
////            cout<<"level:"<<totalTime<<"["<<nextY<<"]"<<"["<<nextX<<"]"<<endl;
//            visited[nextY][nextX] = true;
//            room[nextY][nextX] = 1; //추가
//            tomato.push_back(make_pair(nextY, nextX));
//        }
//    }
//
//    return;
//}
//
//void solution() {
//    int posY = 0;
//    int posX = 0;
//    while(tomato.size() != tomatoCnt) {
//
//        if(totalTime >=tomatoCnt){
//            totalTime = -1;
//            return;
//        }
//
//        int tempSize = tomato.size();
////        cout<<"지금 익은 토마토 갯수:!!!!";
////        cout<<tomato.size()<<endl;
//        for(int i=0; i<tempSize; i++) {
//
//            posY = tomato[i].first;
//            posX = tomato[i].second;
//
////            cout<<"출발"<<endl;
//
//            bfs(posY, posX);
//        }
//        totalTime++;
//    }
//
//}
//
//
//int main(int argc, const char * argv[]) {
//    cin.tie(0);
//    ios_base::sync_with_stdio(false);
//
//    cin>>N;
//    cin>>M;
//
//    tomatoCnt = M*N;
//
//    for(int i=0; i<M; i++) {
//        for(int j=0; j<N; j++) {
//            cin>>room[i][j];
//            if(room[i][j] == 1) {
//                tomato.push_back(make_pair(i, j));
//                visited[i][j] = true;
//                redTomatoCnt++;
//            }
//
//            if(room[i][j] == -1)tomatoCnt--;
////            if(room[i][j] !=0 || room[i][j] !=1 || room[i][j] !=-1)return 0;
//
//        }
//    }
//
//    if(redTomatoCnt == tomatoCnt)return 0;
//
//    solution();
//    cout<<totalTime;
//
//    return 0;
//}
