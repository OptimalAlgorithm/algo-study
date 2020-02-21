//
//  main.cpp
//  BipartiteGraph
//
//  Created by 조윤영 on 20/02/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

#define MAX_SIZE 20002
using namespace std;

int K = 0;
int V = 0;
int E = 0;
int vertex1, vertex2;

vector<vector<int>>graph(MAX_SIZE);
vector<int> status;
bool visited[MAX_SIZE] = {false};
bool flag = true;
vector<int> vertex;

bool coloring(int index, int color) {

    if(visited[index]!=true) {
        visited[index] = true;
        status[index] = color;

    }else{
        color = status[index];
    }
    
    int newColor = -1*color;
    
    for(int i=0; i<graph[index].size(); i++) {
        int v = graph[index][i];
        
        if(visited[v]!=true){
            visited[v]=true;
            status[v] = newColor;
            coloring(v, color);
        }
        
        if(visited[v] == true && status[v] == color) {
            flag = false;
            return false;
        }
    }
    return true;
}


void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> K;
    
    //정점: 3개, 간선의 개수:2
    for(int t=0; t<K; t++) {
        
        cin >> V >> E;
        
        for(int i=1; i<=V; i++) {
            graph[i].clear();
        }
        
        vertex.clear();
        graph.assign(E+1, {});
        status.assign(V+1, -1);
        memset(visited, false, V+1);
        flag = true;
        
        for(int i=0; i<E; i++) {
            cin >> vertex1 >> vertex2;
            graph[vertex1].push_back(vertex2);
            graph[vertex2].push_back(vertex1);
            
            vertex.push_back(vertex1);
            vertex.push_back(vertex2);
        }
        
        sort(vertex.begin(), vertex.end());
        vertex.erase(unique(vertex.begin(), vertex.end()), vertex.end());

        
        for(int i=0; i<vertex.size(); i++) {
            if(!coloring(vertex[i], 1)){
                cout<<"NO"<<endl;
                break;
            }
        }
        if(flag == true)cout<<"YES"<<endl;

    }
    
}



int main(int argc, const char * argv[]) {
    
    input();

    return 0;
}
