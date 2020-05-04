//
//  main.cpp
//  Picnic
//
//  Created by 조윤영 on 29/04/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/2026
//재귀를 통한 조합 구현(*)

#include <iostream>
#include <vector>
#define MAX_SIZE 901

using namespace std;

int K = 0;
int N = 0;
int F = 0;

int friends[MAX_SIZE][MAX_SIZE];
int friend_cnt[MAX_SIZE];
int visited[MAX_SIZE];
bool findFriends = false;

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> K >> N >> F;
    
    int friend1 = 0;
    int friend2 = 0;
    
    for(int i=0; i<F; i++) {
        cin>> friend1 >> friend2;
        friends[friend1][friend2] = true;
        friends[friend2][friend1] = true;
        
        friend_cnt[friend1]++;
        friend_cnt[friend2]++;
    }
    
}
void output() {
    for(int i=1; i<=N; i++) {
        if(visited[i])cout<<i<<"\n";
    }
}


bool isAvailable(int index) {
    for(int i=1; i<=N; i++) {
        if(visited[i]) {
            if(friends[index][i] == false)return false;
        }
    }
    
    return true;
}
void dfs(int prevIndex, int cnt) {
    if(findFriends == true)return;
    
    if(cnt == K) {
        output();
        findFriends = true;
        return;
    }
    
    for(int i=prevIndex+1; i<=N; i++) {
        if(friends[prevIndex][i] && isAvailable(i)) {
            visited[i] = true;
            dfs(i, cnt+1);
            visited[i] = false;
        }
    }
}

void solution() {
    for(int i=1; i<=N; i++) {
        if(friend_cnt[i] <K-1)continue;
        if(findFriends == true)return;
        
        visited[i] = true;
        dfs(i,1);
        visited[i] = false;
    }
    
    if(findFriends == false)cout<< -1 <<"\n";
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
