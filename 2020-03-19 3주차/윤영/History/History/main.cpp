//
//  main.cpp
//  History
//
//  Created by 조윤영 on 19/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#define MAX_SIZE 401

using namespace std;

int N = 0;
int K = 0;
int S = 0;

int room[MAX_SIZE][MAX_SIZE];

//플로이드와샬로 푼 코드
/*한가지 케이스이면 DFS/BFS가 빠른 것이 맞지만
Floyd는 한번만 수행하면 각 케이스에 대해 O(1)로 찾아낼 수 있으므로 O(n^3)이 되지만
BFS의 경우에는 각 케이스에 대해 O(n^2)하는 것.*/

//다른 사람들 코드도 꼭 참고해볼 것

void setRoom() {
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            for(int h=1; h<=N; h++) {
                if(room[j][i] == -1 && room[i][h] == -1){
                    room[j][h] = -1;
                    room[h][j] = 1;
                }
            }
        }
    }
}

void solution() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int a = 0;
    int b = 0;
    
    cin >> N >> K;
    
    for(int i=0; i<K; i++) {
        cin>> a >> b;
        room[a][b] = -1;
        room[b][a] = 1;
    }
    
    setRoom();
    
    cin>> S;
    
    for(int i=0; i<S; i++) {
        cin>> a >> b;
        if(room[a][b] == 0) cout<<0<<"\n";
        else cout<<room[a][b]<<"\n";
    }
}


int main() {
    solution();
    return 0;
}



//DFS로 돌려서 시간초과 난 아래 코드
//bool findIt = false;
//vector<vector<int>> events;
//vector<pair<int,int>> questions;
//vector<bool> visited;
//void input() {
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);
//
//    int a, b;
//
//    cin >> N >> K;
//    events.assign(N+1, {});
//    visited.assign(N+1, false);
//
//    for(int i=0; i<K; i++) {
//        cin >> a >> b;
//        events[a].push_back(b); //a를 거쳐야 b사건이 일어나므로
//    }
//
//    cin >> S;
//
//    for(int i=0; i<S; i++) {
//        cin >> a >> b;
//        questions.push_back({a,b});
//    }
//}
//
//void dfs(int index, int target) {
//
////    cout<<"["<<index<<"]"<<endl;
//    if(index == target){
//        findIt = true;
//        return;
//    }
//
//
//    for(int i=0; i<events[index].size(); i++) {
//        if(!visited[events[index][i]]) {
//
//            visited[events[index][i]] = true;
//            dfs(events[index][i], target);
//            visited[events[index][i]] = false;
//
//            if(findIt == true)return;
//        }
//    }
//
//    return;
//}
//
//void solution() {
//
//    for(int i=0; i<questions.size(); i++) {
//        dfs(questions[i].first, questions[i].second);
//        if(findIt == true){
//            cout<<-1<<"\n";
//            findIt = false;
//            continue;
//        }
//
//        dfs(questions[i].second, questions[i].first);
//        if(findIt == true) {
//            cout<<1<<"\n";
//            findIt = false;
//            continue;
//        }
//
//        cout<<0<<"\n";
//
//    }
//}
//
//int main(int argc, const char * argv[]) {
//    input();
//    solution();
//    return 0;
//}
