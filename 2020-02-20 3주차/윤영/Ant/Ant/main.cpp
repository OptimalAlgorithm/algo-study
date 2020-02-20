//
//  main.cpp
//  Ant
//
//  Created by 조윤영 on 20/02/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define MAX_SIZE 27

using namespace std;

int N1 = 0;
int N2 = 0;
int T = 0;
int direction[MAX_SIZE];
string answer;

vector<int> movingAnt;

void input() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N1 >> N2;

    char ant1;
    char ant2;
    int directionIndex = 0;
    
    stack<char> temp;
    for(int i=0; i<N1; i++) {
        cin>> ant1;
        temp.push(ant1);
    }

    
    while(!temp.empty()) {
        answer+=temp.top();
        direction[directionIndex] = 1;
        temp.pop();
        directionIndex++;
    }

    for(int i=0; i<N2; i++) {
        cin >> ant2;
        answer+=ant2;
        direction[directionIndex] = -1;
        directionIndex++;
    }
    
    cin >> T;
}

bool isFrontAntExist(int frontAnt) {
    if(0<=frontAnt && frontAnt <answer.size())return true;
    
    return false;
}
bool checkCanJump(int dir, int frontAnt, int currentAnt) {
    
    if(direction[frontAnt] != dir) {
        //상대 개미와 가고자 하는 방향이 상반된다면
        //Jump 가능
        return true;
    }
    return false;
}

void solution() {

    //현재 마주보고 있는 개미들을 움직일 후보자 개미로 집어넣음으로써 초기화
    movingAnt.push_back(N1-1);
    
    stack<int> newAnt;
    
    for(int i=0; i<T; i++) {
//        cout<<i+1<<"+++++++++++++++++++++++++++++++++"<<endl;
        for(int i=0; i<movingAnt.size(); i++) {
            int currentAnt = movingAnt[i];
            int dir = direction[currentAnt];
            int frontAnt = currentAnt + dir; //바로 앞에 있는 상대 개미
            
            if(isFrontAntExist(frontAnt)){//상대 개미가 존재하고
                if(checkCanJump(dir, frontAnt, currentAnt)){
                    //상대 개미와 이동방향이 다르다면,
                               
                    //자리 바꾸자
//                    cout<<currentAnt<<","<<frontAnt<<endl;
                    char temp = answer[currentAnt]; //현재 개미의 알파벳
                    int tempDir = direction[currentAnt];
                    
                    answer[currentAnt] = answer[frontAnt];
                    direction[currentAnt] = direction[frontAnt];//
//                    cout<<"점프1:"<<answer<<endl;
//                    cout<<answer[frontAnt];
       
                    
                    answer[frontAnt] = temp;
                    direction[frontAnt] = tempDir;//방향과 알파벳 모두 바꿈
                    newAnt.push(frontAnt);
//                    cout<<"점프2:"<<answer;
//                    cout<<endl;
//                    cout<<"================================="<<endl;

                }
            }
        }
        
        //움직이는 중인 개미에 지금 새롭게 움직인 새로운 개미 추가
        while(!newAnt.empty()){
            movingAnt.push_back(newAnt.top());
            newAnt.pop();
        }
        
        //이동 중복 개미 제거
        sort(movingAnt.begin(), movingAnt.end());
        movingAnt.erase(unique(movingAnt.begin(), movingAnt.end()), movingAnt.end());

        
    }

}

int main(int argc, const char * argv[]) {
    
    input();

    solution();
    
    cout<<answer;
    
    return 0;
}
