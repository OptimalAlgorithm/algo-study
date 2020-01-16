//
//  main.cpp
//  Virus
//
//  Created by 조윤영 on 02/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

//더러워용.,, 죄송합니다,, 

#include <iostream>
#include <vector>
#define MAX_SIZE 101
using namespace std;

int N, M;
vector<vector<int>> connected_computers;
vector<vector<int>> connected(MAX_SIZE, vector<int>(MAX_SIZE, 0));
int visited[MAX_SIZE] = {false};
int answer = 0;

void solution(int target) {
    
    visited[target] = true;
    
    for(int i=0; i<N; i++) {
        if(connected[target][i] == 1  &&  visited[i] != true) {
            answer++;
            solution(i);//해당 타겟으로 이동
            
        }
    }
    
}
int main(int argc, const char * argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin>>N;
    cin>>M;
    
    int computer1, computer2;
    
    for(int i=0; i<M; i++) {
        cin>> computer1>> computer2;
        connected_computers.push_back({computer1, computer2});
    }
    
    for(int i=0; i<M; i++) {
        int source = connected_computers[i][0];
        int destination = connected_computers[i][1];
        connected[source][destination] = 1;
        connected[destination][source] = 1;
    }
    
//    for(int i=0; i<M; i++) {
//        for(int j=0; j<N; j++) {
//             cout<<connected[i][j];
//
//        }
//        cout<<endl;
//    }

    
    solution(1);
    cout<<answer;
    return 0;
}
