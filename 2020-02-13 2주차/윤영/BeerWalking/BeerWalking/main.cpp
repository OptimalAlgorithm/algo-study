//
//  main.cpp
//  BeerWalking
//
//  Created by 조윤영 on 13/02/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

    
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>

#define MAX_SIZE 105

using namespace std;

int t = 0;
int n = 0;

int homeCnt = 1;
int festCnt = 1;

string answer;

bool visited[MAX_SIZE];


struct Pos {
    int y;
    int x;
    
    Pos(int _y, int _x) {
        y = _y;
        x = _x;
    }
};
vector<Pos> pos;

bool checkHappy(int sourceY, int sourceX, int destinationY, int destinationX) {
    
    int dis = abs(destinationY - sourceY) + abs(destinationX - sourceX);
    
    if(dis > (20*50))return false;
    
    return true;
}



void solution(int index) {
    
    if(index == n+1) {
        answer = "happy";
        return;
    }
    for(int i=1; i<n+2; i++) {
        if(visited[i] !=true) {
            if(checkHappy(pos[index].y, pos[index].x, pos[i].y, pos[i].x)) {
                visited[i] = true;
                solution(i);
            }
        }
    }
}

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >>t;
    for(int i=0; i<t; i++) {
        //초기화
        answer = "sad";
        pos.clear();
        memset(visited, false, sizeof(visited));
        
        //입력
        cin >>n;
//        cin >> houseY >> houseX;
        int posY = 0;
        int posX = 0;
        
        for(int j=0; j<(n+homeCnt+festCnt); j++) {
            cin >>posY >> posX;
            pos.push_back(Pos(posY, posX));
        }
        
        solution(0);
        cout<<answer<<endl;
    }
}


int main(int argc, const char * argv[]) {
    input();
    
    return 0;
}
