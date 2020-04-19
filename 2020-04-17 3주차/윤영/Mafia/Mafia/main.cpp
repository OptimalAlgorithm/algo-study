//
//  main.cpp
//  Mafia
//
//  Created by 조윤영 on 17/04/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/1079

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX_SIZE 17
using namespace std;

void day(int nightCnt, int citizen);
void night(int nightCnt, int citizen);

int N = 0;
int room[MAX_SIZE][MAX_SIZE];
int users[MAX_SIZE];

int maxNight = 0;

int myNumb = 0;

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>> N;
    
    int guiltiness = 0;
    for(int i=0; i<N; i++) {
        cin>> guiltiness;
        users[i] = guiltiness;
    }
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin>>room[i][j];
        }
    }
    
    
    cin>> myNumb;
}


void addCrimeScore(int deadUser) {
    //나머지 유죄 점수 추가
    for(int i=0; i<N; i++) {
        if(users[i] != -1) {
            //죽은 참여자가 아니라면
            users[i] += room[deadUser][i];
        }
    }
}

void backToPrevCrimeScore(int deadUser) {
    for(int i=0; i<N; i++) {
        if(users[i] != -1) {
            //죽은 참여자가 아니라면
            users[i] -= room[deadUser][i];
        }
    }
}

void night(int nightCnt, int citizen) {
    
    if(citizen == 0){
        maxNight = max(maxNight, nightCnt);
        return;
    }

    //밤: 마피아가 사람을 지목해서 죽인다.
    //죽인 이외의 참가자들의 유죄수는 R[i][j]만큼 변한다.

    for(int i=0; i<N; i++) {
        if(users[i] != -1 && i != myNumb) {//죽지 않았으며, 마피아가 아닐 경우

            int temp_dead = users[i];
            users[i] = -1; //해당 참가자 죽인다
            addCrimeScore(i);

            day(nightCnt+1, citizen-1);//다음날은 홀수이므로 낮으로 이동.
            
            users[i] = temp_dead;
            backToPrevCrimeScore(i);

        }
    }
    
    
}

void day(int nightCnt, int citizen) {
    
    
    if(citizen == 0){
        maxNight = max(maxNight, nightCnt);
        return;
    }
    
    int maxGuilt = -1;
    int maxGuiltUser = -1;


    for(int i=0; i<N; i++) {
        if(maxGuilt<users[i]) {
            maxGuiltUser = i;
            maxGuilt = users[i];
        }
    }

    if(maxGuiltUser == myNumb){
        maxNight = max(maxNight, nightCnt);
        return;
    }
    
    int temp = users[maxGuiltUser];
    users[maxGuiltUser] = -1;
    
    night(nightCnt, citizen-1);
    
    users[maxGuiltUser] = temp;

}

void solution() {
    
    if(N%2 !=0) {//시작이 낮이라면,
        day(0, N-1);
    }
    else{//밤이라면
        night(0, N-1);
        
    }
    
    cout<<maxNight<<"\n";
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
