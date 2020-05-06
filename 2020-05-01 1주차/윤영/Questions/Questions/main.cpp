//
//  main.cpp
//  Questions
//
//  Created by 조윤영 on 06/05/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/1766
//

#include <iostream>
#include <vector>
#include <queue>


using namespace std;

int N = 0;
int M = 0;


vector<int> indegree;
vector<vector<int>> follow_numb;
priority_queue<int, vector<int>, greater<int>> pq;

void input2() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> N>>M;
    indegree.assign(N+1,0);
    follow_numb.assign(N+1, {});
    
    
    int A = 0;
    int B = 0;
    for(int i=0; i<M; i++) {
        cin>> A>>B;
        
        follow_numb[A].push_back(B);
        indegree[B]++;
    }
}

void solution2() {
    for(int i=1; i <=N; i++) {
        if(indegree[i]== 0)pq.push(i);
    }
    
    while(!pq.empty()) {
        int index = pq.top();
        pq.pop();
        cout<<index<<" ";
        
        for(int i=0; i<follow_numb[index].size(); i++) {
            int targetIndex = follow_numb[index][i];
            if(--indegree[targetIndex] == 0)pq.push(targetIndex);
        }
    }
}

int main(int argc, const char * argv[]) {
    input2();
    solution2();
    return 0;
}
//2,3,4
//4,3,2


//일반 DFS 쓰고 틀린 풀이
vector<vector<int>> priority;
vector<bool> visited;

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> N>>M;
    priority.assign(N+1, {});
    visited.assign(N+1, false);
    
    int A = 0;
    int B = 0;
    for(int i=0; i<M; i++) {
        cin>>A;
        cin>>B;
        priority[B].push_back(A);
    }
    
}

void dfs(int index) {
    for(int i=0; i<priority[index].size(); i++) {
        int preIndex = priority[index][i];
        
        if(!visited[preIndex]) {
            visited[preIndex] = true;
            dfs(preIndex);
            cout<<preIndex<<" ";
        }
    }
}

void solution() {
    
    for(int i=1; i<=N; i++) {
        if(!visited[i]) {
            visited[i] = true;
            dfs(i);
            cout<<i<<" ";
        }
        
    }
    cout<<"\n";
    
}
