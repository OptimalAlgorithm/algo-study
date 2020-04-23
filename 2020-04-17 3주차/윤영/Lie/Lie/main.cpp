//
//  main.cpp
//  Lie
//
//  Created by 조윤영 on 22/04/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int N = 0;
int M = 0;
int knowTruthCnt = 0;
int answer = 0;

vector<bool> isTruthParty;
vector<vector<int>> invitors;
vector<vector<int>> participating_party;
vector<bool> visited;
map<int,bool> m;

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> N >> M;
    invitors.assign(M+1, {});
    participating_party.assign(N+1, {});
    isTruthParty.assign(M+1, false);
    visited.assign(N+1, false);

    cin>> knowTruthCnt;
    
    int truthPeopleNumb = 0;
    for(int i=0; i<knowTruthCnt; i++) {
        cin>> truthPeopleNumb;
        m[truthPeopleNumb] = true;
    }
    
    int cnt = 0;
    int numb = 0;

    for(int i=0; i<M; i++) {
        cin>> cnt;
        if(cnt == 0){
//            cin>>numb;
//            invitors[i].push_back(0);
            answer++;
        }
        else{
            for(int j=0; j<cnt; j++) {
                cin>>numb;
                invitors[i].push_back(numb);
                participating_party[numb].push_back(i);
                
            }
        }
        
    }
}

void checkPrevParty(int partyIndex, int peopleNumb){
//    cout<<"("<<peopleNumb<<")";
    for(int i=0; i<participating_party[peopleNumb].size(); i++) {
        int prev_party = participating_party[peopleNumb][i];
        
        if(prev_party == partyIndex)continue;
        
        if(!isTruthParty[prev_party]) {

            isTruthParty[prev_party] = true;
            //최근에 진실을 알게 되었다면, 이전의 파티에서도 진실을 말한 것으로 수정.
            bool changeState = false;
            for(int j=0; j<invitors[prev_party].size(); j++) {
                if(!m[invitors[prev_party][j]]) {
                    
//                    cout<<"->"<<invitors[prev_party][j];
                    checkPrevParty(prev_party, invitors[prev_party][j]);
                    if(!m[invitors[prev_party][j]]){
                        changeState = true;
                        m[invitors[prev_party][j]] = true;
                    }
                    
                }
            }
//            cout<<prev_party;
//            if(visited[prev_party])cout<<"방문한 적 있음";
            if(visited[prev_party] && changeState == true){
//                cout<<partyIndex<<"--"<<endl;
                answer--;
            }
            
        }
    }
}

void solution() {
    queue<int> q;
    
    for(int i=0; i<M; i++) {
//        cout<<"["<<i<<"]";
        visited[i] = true;
        
        bool truth = false;
        
        if(invitors[i].size()==  0)continue;
        
        for(int j=0; j<invitors[i].size(); j++) {
            q.push(invitors[i][j]);
            if(m[invitors[i][j]]){
//                cout<<"진실아는 사람있음:"<<invitors[i][j];
                truth = true;
            }
        }
            
        if(truth) {//진실을 아는 사람이 파티장에 있었다면?
            isTruthParty[i] = true;
            
            for(int j=0; j<invitors[i].size(); j++) {
                int peopleNumb = invitors[i][j];
                    
                if(!m[peopleNumb]) {
                    
                    //타고들어가자 이전에 참여했던 파티.
                    checkPrevParty(i,peopleNumb);
                    m[peopleNumb] = true;
                    
                }
                q.pop();
            }
        }else {
            
//            cout<<i<<"++"<<endl;
            answer++;
        }
       
    }
    
    cout<<answer<<"\n";
}
int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}


/*
 4 3
 1 1
 
 (1)1 2
 (2)1 3
 (3)2 3 4
 =============
 
 3 2
 1 1

 (1)2 3
 (2)1 2 =>진실을 말함 근데 m[2]== true가 아니므로 타고들어간다 참석했던 모든 파티를
 지나쳐온 파티에서 거짓말을 했는지 안했는지 체크하면서 오면 나중에 백트래킹할 때 모두 탐색할지 안할지 판단 가능
 =============
 4 4
 1 1
 2 1 2
 1 3
 2 3 4
 0
 =>3
 =============
 4 4
 1 1
 2 3 2
 3 4 1 3
 2 4 1
 0
 =>1
 =============
 3 2
 1 1
 2 2 3
 2 1 2
 =>0
 ============
 3 4
 2 1 3
 2 2 3
 1 2
 1 3
 2 1 3
 ->0
 
 ============
 3 4
 1 3
 1 3
 1 2
 2 1 3
 2 2 3
 =>0
 ============
 4 3
 1 4
 3 1 3 4
 1 1
 4 1 2 3 4
 =>0
 =============
 5 3
 1 3
 3 1 2 4
 3 1 4 5
 1 3
 =>2
 
 =============
 6 5

 1 6

 2 4 5

 2 1 2

 2 2 3

 2 3 4

 2 5 6
 =>0
 
 ==============
 6 5

 1 6

 2 4 5

 2 1 2

 2 2 3

 2 3 4

 2 5 6
 =>0
 
 ==============
 3 4
 2 1 3
 0
 1 2
 2 2 3
 2 1 3
 ->1
 
 
 */
