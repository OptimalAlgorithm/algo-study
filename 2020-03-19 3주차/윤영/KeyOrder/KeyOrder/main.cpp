//
//  main.cpp
//  KeyOrder
//
//  Created by 조윤영 on 25/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>

#define MAX_SIZE 501

using namespace std;

int N = 0;
int M = 0;

int answer = 0;
int cnt = 0;

vector<vector<int>> compareHeight;
bool visited[MAX_SIZE] = {false};

void input() {
    
    

    cin >> N >> M;
    compareHeight.assign(N+1, {});
    
    for(vector<int>::size_type i=0; i<compareHeight.size(); i++) {
        compareHeight[i].assign(N+1, 0);
    }
    
    int a, b;
    for(int i=0; i<M; i++) {
        
        cin>> a >> b;

        compareHeight[b][a] = -1;
        compareHeight[a][b] = 1;
        
    }

}

int lowerCnt = 0;
int higherCnt = 0;

void dfs(int index, int standard) {
    for(int i=1; i<compareHeight[index].size(); i++) {
        if(!visited[i]) {
            if(standard != 1 && compareHeight[index][i] == -1) {
                lowerCnt++;
                visited[i] = true;
                dfs(i, -1);
            }else if(standard != -1 && compareHeight[index][i] == 1) {
                higherCnt++;
                visited[i] = true;
                dfs(i,1);
            }
        }
        
    }

}
void solution() {
    
    for(int i=1; i<N+1; i++) {

        lowerCnt = 0;
        higherCnt = 0;
        
        visited[i] = true;
        dfs(i, 0);
        if(lowerCnt + higherCnt == N-1)answer++;
        
        memset(visited, false, N+1);
    }
    cout<<answer<<"\n";
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
