//
//  main.cpp
//  FriendNetwork
//
//  Created by 조윤영 on 27/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/4195

#include <iostream>
#include <map>
#include <cstring>

#define MAX_SIZE 200002

using namespace std;


int T = 0;
int F = 0;

//MAP + DFS 풀이(시도해보기)

//Union-Find:Disjoint-Set 풀이

int parent[MAX_SIZE];
int numb[MAX_SIZE];

int findParent(int index) {
//    cout<<"["<<index<<"]"<<endl;
    if(parent[index] == index)return index;
    else return parent[index] = findParent(parent[index]);
    
}

void merge(int a, int b){
    
    
    if(a != b) {
//        cout<<"둘이 다른 집합!"<<endl;
        parent[b] = a;
        numb[a] += numb[b];
    }
    
    cout<<numb[a]<<"\n";
    
}

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin>>T;
    for(int i=0; i<T; i++) {
        cin>>F;
        
        map<string,int> m;
        
        // 초기화
        for(int j=1; j<=2*F; j++) {
            parent[j] = j; //부모노드
            numb[j] = 1; //친구 수
       }
        
        int index = 0;
        
        for(int j=0; j<F; j++) {
            
            
            string friend1, friend2;
            
            cin >> friend1 >> friend2;
            
            //해당하는 이름의 키값이 존재하지 않는다면, (해당 키값에 대한 value가 없다면)
            if(m.count(friend1) == 0) {
                m[friend1] = ++index;
            }
            
            if(m.count(friend2) == 0) {
                m[friend2] = ++index;
            }
            
            int parent1 = findParent(m[friend1]);
            int parent2 = findParent(m[friend2]);
//            cout<<">>"<<endl;
//            cout<<"1:"<<parent1<<",2:"<<parent2<<endl;
            
            merge(parent1, parent2);
            
            
        }
        
        
    }
    
}

int main(int argc, const char * argv[]) {
    input();
    return 0;
}
