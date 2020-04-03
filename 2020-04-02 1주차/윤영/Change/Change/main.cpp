//
//  main.cpp
//  Change
//
//  Created by 조윤영 on 02/04/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

//데이터의 존재 유무만 알고싶을 때 쓰는 set
#include <set>

#define MAX_SIZE 1000000

using namespace std;

string N;
int K = 0;
vector<char> numbs;
priority_queue<int> q;

int input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> N >> K;
    
    if(N.size() == 1 ||(N.size() == 2 && stoi(N) % 10 == 0))return -1;

    return 0;
}

void bfs(string numb) {
    
    queue<string> q;
    q.push(numb);
    
    int cnt = 0;
    int max = 0;
    
    while(!q.empty() && cnt < K) {
        
        int qSize = q.size();
        
        set<string> visited;
        
        for(int i=0; i<qSize; i++) {
            string currentN = q.front();
            q.pop();
            
            for(int j=0; j<N.size()-1; j++) {
                for(int h=j+1; h<N.size(); h++) {
                    
                    //첫 번째 위치와 교환할 상대가 0이라면 continue;
                    if(j==0 && currentN[h]== '0') continue;
                    
                    swap(currentN[j], currentN[h]);
                    
                    //swap해서 만들어진 해당 currentN은 만들어진 적이 없는 숫자임
                    if(visited.find(currentN) == visited.end()) {
                        
                        //K번의 교환을 했으며 (K번의 교환을 하는 후보 많음)
                        //K번의 교환을 한 이전의 가장 큰 후보보다 크다면?
                        if(cnt == K-1 && max <stoi(currentN)) {
                            
                            max = stoi(currentN);//max 교체
                        }
                        
                        q.push(currentN);
                        visited.insert(currentN);
                    }
                    
                    swap(currentN[j], currentN[h]);
                    //다른 위치의 숫자와도 교환하고 기록해야하므로 교환했던 것 다시 되돌리기
                }
            }
        }
        
        cnt++;//~번째 교환 수행 모두 끝냈고 다음 횟수의 교환으로 넘어간다.
    }
    
    if(cnt != K) cout<<-1<<"\n";
    else cout<<max<<"\n";
  
}

void solution() {

    bfs(N);
    
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if(input()==-1)cout<<-1;
    else solution();
    return 0;
}

