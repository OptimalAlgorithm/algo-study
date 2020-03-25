//
//  main.cpp
//  PutOperation
//
//  Created by 조윤영 on 25/03/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

#define MAX_SIZE 1000000000

using namespace std;

int N = 0;
vector<int>numbers;
int op[4] = {0,0,0,0};

struct Status {
    int index;
    int plus;
    int minus;
    int multiple;
    int division;
    int sum;
    
    Status(int _index, int _plus, int _minus, int _multiple, int _division, int _sum) {
        index = _index;
        plus = _plus;
        minus = _minus;
        multiple = _multiple;
        division = _division;
        sum = _sum;
    }
};

void input() {
    cin >> N;
    int numb = 0;
    
    for(int i=0; i<N; i++) {
        cin >>numb;
        numbers.push_back(numb);
    }
    
    for(int i=0; i<4; i++) {
        cin>>op[i];
    }
}

void solution() {
    int maxAnswer = -MAX_SIZE;
    int minAnswer = MAX_SIZE;
    
    queue<Status> q;
    q.push(Status(1,op[0],op[1],op[2],op[3], numbers[0]));
    
    
    while(!q.empty()){
        
        int index = q.front().index;
        int plusCnt = q.front().plus;
        int minusCnt = q.front().minus;
        int multipleCnt = q.front().multiple;
        int divisionCnt = q.front().division;
        int sum = q.front().sum;

        q.pop();
        
        
        if(index == N) {
            //연산하고 비교
            maxAnswer = max(maxAnswer, sum);
            minAnswer = min(minAnswer, sum);
            
            continue;
        }
        

        
        if(plusCnt >0)q.push(Status(index+1, plusCnt-1, minusCnt, multipleCnt, divisionCnt, sum+numbers[index]));
        if(minusCnt >0)q.push(Status(index+1, plusCnt, minusCnt-1, multipleCnt, divisionCnt, sum - numbers[index]));
        if(multipleCnt >0)q.push(Status(index+1, plusCnt, minusCnt, multipleCnt-1, divisionCnt, sum * numbers[index]));
        if(divisionCnt >0)q.push(Status(index+1, plusCnt, minusCnt, multipleCnt, divisionCnt-1, sum / numbers[index]));
        
        
        

    }
    
    
    cout<<maxAnswer<<endl;
    cout<<minAnswer<<endl;
}

int main(int argc, const char * argv[]) {
    input();
    solution();
    return 0;
}
