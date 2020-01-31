//
//  main.cpp
//  OptimalHacking
//
//  Created by 조윤영 on 30/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//오늘의 교훈: 함수 인수값으로 큰 벡턱값을 실어보내지말자... 이게 참조하는 데에도 시간이 걸리나봐..

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAX_SIZE 10001

using namespace std;

int N = 0;
int M = 0;

vector<vector<int>> computer_relation;
vector<bool> visited;
int maxComputerRelationCnt = 0;
vector<int> printer;
int cnt = 0;


void dfs(int index) {

    visited[index] = true;

    for(int i=0; i<computer_relation[index].size(); i++) {
        int nextComptuer = computer_relation[index][i];

        if(visited[nextComptuer] != true) {
            cnt++;
            dfs(nextComptuer);
        }
    }
}


void solution() {
    
    int maxComputerRelationCnt = 0;
    
    for(int i=1; i<computer_relation.size(); i++) {
        
        visited.assign(N+1, false);
        cnt = 0;

        dfs(i);

        //2:시간초과를 줄이기 위한 시도1
        if(maxComputerRelationCnt<cnt){
            printer.clear();
            printer.push_back(i);
            maxComputerRelationCnt = cnt;
        }else if(maxComputerRelationCnt == cnt){
            printer.push_back(i);
        }
        else {}

    }

    //2:시간초과를 줄이기 위한 시도2
    for(int i=0; i<printer.size(); i++) {
        cout<<printer[i] <<" ";
    }

}

int main(int argc, const char * argv[]) {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>> N >> M;
    computer_relation.assign(N+1, vector<int>(0));


    int A = 0;
    int B = 0;

    for(int i=0; i<M; i++) {
        cin >> A >> B;
        computer_relation[B].push_back(A);
    }

    solution();

    return 0;
}


