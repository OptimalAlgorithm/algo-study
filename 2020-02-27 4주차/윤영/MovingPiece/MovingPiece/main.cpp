//
//  main.cpp
//  MovingPiece
//
//  Created by 조윤영 on 04/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/1035
//
//브루트 포스

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

char room[5][5];
vector<pair<int,int>> pieces;
void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            cin>>room[i][j];
            if(room[i][j] == '*')pieces.push_back({i,j});
        }
    }
}

int solution() {
    int answer = 0;
    
    int standardY = 2;
    int standardX = 2;
    
    for(int i=0; i<pieces.size(); i++) {
        
        if(pieces[i].first == standardY && pieces[i].second == standardX)continue;
        answer += (abs(standardY-pieces[i].first) + abs(standardX - pieces[i].second)-1);
        
    }
    
    return answer;
}
int main(int argc, const char * argv[]) {
    input();
    cout<<solution();
    return 0;
}
