//
//  main.cpp
//  TurmProject
//
//  Created by 조윤영 on 05/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include<cstring>
#define MAX_SIZE 100001
using namespace std;

int T = 0;
int n = 0;

int teamCnt = 0;
vector<int> teamPick;
bool visited [MAX_SIZE];

bool isTeam = false;

void dfs(int source, int index) {
    visited[index] = true;
    teamCnt--;
    
    if(teamPick[index] == source){
        isTeam = true;
        return;
    }
    
    if(!visited[teamPick[index]]) dfs(source, teamPick[index]);
    if(isTeam != true) {
        visited[index] = false;
        teamCnt++;
    }
}

void solution() {
    for(int i=1; i<teamPick.size(); i++) {
        isTeam = false;
        
        //혼자 팀을 하고싶은 경우,
        if(teamPick[i] == i){
            teamCnt--;
            visited[i] = true;
        }
        else if(!visited[i]){
            dfs(i, i);
            visited[i] = true;
             for(int j=1; j<n+1; j++) {
            }
        }
    }
}

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> T;
    for(int i=0; i<T; i++) {
        cin >> n;
        teamCnt = n;
        teamPick.assign(n+1, 0);
        memset(visited, false, sizeof(visited));
        for(int j=1; j<n+1; j++) {
            cin>>teamPick[j];
        }
        solution();

        cout<<teamCnt<<"\n";
    }
}



int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
