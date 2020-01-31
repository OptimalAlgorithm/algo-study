//
//  main.cpp
//  Virus
//
//  Created by 조윤영 on 02/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 101
using namespace std;

int N = 0;
int M = 0;

vector<vector<int>> connected_computers;

int visited[MAX_SIZE] = {false};
int answer = -1;

void solution(int index) {
    
    visited[index] = true;
    answer++;
    
    for(int i=0; i<connected_computers[index].size(); i++) {
        int currentComputer = connected_computers[index][i];
        if(visited[currentComputer]!= true)solution(currentComputer);
    }
    
}
int main(int argc, const char * argv[]) {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    

    cin>>N;
    cin>>M;
    
    connected_computers.assign(N+1, vector<int>(0));
    
    int computer1 = 0;
    int computer2 = 0;
    
   
    for(int i=0; i<M; i++) {
        
        cin>> computer1>> computer2;
        connected_computers[computer1].push_back(computer2);
        connected_computers[computer2].push_back(computer1);
    }


    solution(1);
    cout<<answer;
    return 0;
}
