//
//  main.cpp
//  GameDevelopement
//
//  Created by 조윤영 on 18/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAX_SIZE 501

using namespace std;
int N = 0;
int memory[MAX_SIZE];
int resultTime = 0;

vector<int> times;
vector<vector<int>> buildings;

void input() {
    cin >> N;

    buildings.assign(N+1, {});
    times.push_back(0);
    
    for(int i=1; i<=N; i++) {
        int time = 0;
        int numb = 0;
        
        cin>>time;
        times.push_back(time);
        while(numb != -1) {
            cin>>numb;
            if(numb != -1) buildings[i].push_back(numb);
        }
    }
//    cout<<"{";
//    for(int i=0; i<=N; i++) {
//        cout<<"{";
//        for(int j=0; j<buildings[i].size(); j++) {
//            cout<<buildings[i][j];
//        }
//        cout<<"}";
//    }
//    cout<<"}";
}


//dfs.. + 메모이제이션..
int dfs(int index, int time) {
    
//    cout<<"("<<index<<")"<<endl;
//    cout<<"+"<<times[index]<<endl;
    int tempTime = 0;
    
    
    
        
    for(int i=0; i<buildings[index].size(); i++) {
//        cout<<"("<<buildings[index][i]<<")"<<endl;
        if(memory[buildings[index][i]] == -1) {
            
            int t = dfs(buildings[index][i], time+times[buildings[index][i]]);
            
            tempTime = max(tempTime, t);
            memory[buildings[index][i]] = t-time;
        }else{
//            cout<<"+"<<time<<"+"<<memory[buildings[index][i]]<<endl;
            tempTime = max(tempTime, time+memory[buildings[index][i]]);
//            cout<<"후보"<<tempTime;
            resultTime = max(resultTime, tempTime);
//            cout<<"&&"<<resultTime<<"%%";
        }
        
    }

    time += tempTime;
    memory[index] = time;

    if(buildings[index].size() == 0){
//        cout<<"후보:"<<time;
        resultTime = max(resultTime, time);
//        cout<<">>>"<<resultTime<<endl;
    }
    
    return time;
}

void solution() {
    
    for(int i=1; i<N+1; i++) {
        memory[i] = -1;
    }
    
    for(int i = 1; i<buildings.size(); i++) {
        int time = times[i];
        int tempTime = 0;

//        cout<<"["<<i<<"]"<<endl;
        
        for(int j=0; j<buildings[i].size(); j++) {
            if(memory[buildings[i][j]] == -1) {
                resultTime = 0;
                dfs(buildings[i][j], times[buildings[i][j]]);
                
                memory[buildings[i][j]] = resultTime;
                tempTime = max(tempTime,resultTime);
                
            }else{
                tempTime = max(tempTime, memory[buildings[i][j]]);
            }
            
        }
        
//        cout<<time<<"+"<<tempTime<<"=";
        time += tempTime;
        memory[i] = time;
        cout<<time<<"\n";
        
    }
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}

