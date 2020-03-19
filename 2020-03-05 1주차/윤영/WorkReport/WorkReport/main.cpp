//
//  main.cpp
//  WorkReport
//
//  Created by 조윤영 on 17/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//
//https://www.acmicpc.net/board/view/14234

#include <iostream>
#include <vector>

using namespace std;

string workers;
vector<char> answer;
string s_answer;

string visited = "000";

bool findAnswer = false;

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    
    cin>>workers;
    
}

void dfs() {
    
    if(answer.size() == workers.size()) {
        
        for(int i=0; i<answer.size(); i++) s_answer += answer[i];
        
        findAnswer = true;
        return;
    }
    
    for(int i=0; i<workers.size(); i++) {
        if(visited[i] != 1) {
            
            if(workers[i] == 'C') {
                if((answer.size()>=1 && answer[answer.size()-1] == 'C') ||
                   (answer.size() >=2 && answer[answer.size()-2] == 'C')) {
                    continue;
                }
            }
            if(workers[i] == 'B') {
                if((answer.size()>=1 && answer[answer.size()-1] == 'B')) {
                    continue;
                }
            }
            
            //위 조건에 걸려 continue하지 않았다면,
            answer.push_back(workers[i]);
            visited[i] = 1;
            
            dfs();
            
            if(findAnswer)return;
            
            answer.pop_back();
            visited[i] = 0;
        }
    }
}
string solution() {
    
    
    for(int i=0; i<workers.size(); i++) {
        
        answer.push_back(workers[i]);
        visited[i] = 1;
        
        dfs();
        
        if(findAnswer)return s_answer;
        
        answer.pop_back();
        visited[i] = 0;
    }
    return "-1";
}

int main(int argc, const char * argv[]) {
    input();
    cout<<solution()<<endl;
    return 0;
}
