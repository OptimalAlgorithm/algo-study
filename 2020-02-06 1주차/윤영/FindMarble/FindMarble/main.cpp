//
//  main.cpp
//  FindMarble
//
//  Created by 조윤영 on 06/02/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 100
using namespace std;

int N = 0;
int M = 0;

//중간에 넣는 방법이 가장 빠른 경우는 무엇?

vector<int> marbles;

vector<vector<int>> heavyMarbles; //각 구슬 인덱스의 무게보다 무거운 것을 담는 공간
vector<vector<int>> lightMarbles; //각 구슬 인덱스의 무게보다 가벼운 것을 담는 공간

vector<bool> visited;
int answer = 0;
int cnt = -1;
bool isFlag = false;

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    
    for(int i=0; i<N+1; i++) {
        //이때 marbles[0] 공간은 사용하지 않는다.
        marbles.push_back(i);
    }
    
    heavyMarbles.assign(N+1, {});
    lightMarbles.assign(N+1, {});
    
    int heavyMarble = 0;
    int lightMarble = 0;
    
    
    for(int i = 0; i<M; i++) {
        cin >> heavyMarble >> lightMarble;
        heavyMarbles[lightMarble].push_back(heavyMarble);
        lightMarbles[heavyMarble].push_back(lightMarble);
    }


}

void dfs(int index, bool isHeavyMarble) {
    
    visited[index] = true;
    
    cnt++;
    
    if(cnt > N/2) {
        answer++;
        isFlag = true;
        return;
    }
    
    if(isHeavyMarble == true) {

        for(int j=0; j<heavyMarbles[index].size(); j++) {
        
            if(visited[heavyMarbles[index][j]] != true){
                dfs(heavyMarbles[index][j], true);
                if(isFlag == true)return;
            }
        }
    }
    else{
        for(int j=0; j<lightMarbles[index].size(); j++) {
            if(visited[lightMarbles[index][j]] != true) { dfs(lightMarbles[index][j], false);
                if(isFlag == true)return;
            }
        }
    }

}

void solution() {
    
    //보다 무거운 인덱스 몇개인지 먼저 서칭
    for(int i=1; i<heavyMarbles.size(); i++) {
        visited.clear();
        visited.assign(N+1, false);
        cnt = -1;
        isFlag = false;
        dfs(i, true);
    }
    
//    보다 가벼운 인덱스몇개인지 서칭
    for(int i=1; i<lightMarbles.size(); i++) {
        visited.clear();
        visited.assign(N+1, false);
        cnt = -1;
        isFlag = false;
        dfs(i, false);
    }
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    cout<<answer;
    return 0;
}
