//
//  main.cpp
//  RobotSimulation
//
//  Created by 조윤영 on 30/01/2020.
//  Copyright © 2020 조윤영. All rights reserved.
//

//'틀렸습니다' 판정 받은 코드입니다.

#include <iostream>
#include <vector>
#define MAX_SIZE 101

using namespace std;

struct Robot {
    int y;
    int x;
    int dir;
    
    Robot(int _y, int _x, int _dir) {
        y = _y;
        x = _x;
        dir = _dir;
    }
};
struct Order {
    int targetRobot;
    char orderType;
    int cnt;
    
    Order(int _targetRobot, char _orderType, int _cnt) {
        targetRobot = _targetRobot;
        orderType = _orderType;
        cnt = _cnt;
    }
};
struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{1,0},{0,-1},{-1,0},{0,1}};

vector<Robot> robotStatus;
vector<Order> robotOrder;


int A = 0;
int B = 0;
int N = 0;
int M = 0;
int crashRobot = 0;

bool isRobotStopped = false;

int room[MAX_SIZE][MAX_SIZE];

void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> A >> B;
    cin >> N >> M;
    
    for(int i=0; i<N; i++) {
        int inputX = 0;
        int inputY = 0;
        char inputDir;
        
        int intDir = 0;
        
        cin >> inputX >> inputY >> inputDir;
        
        switch(inputDir) {
            case 'N':
                intDir = 0;
                break;
            case 'E':
                intDir = 1;
                break;
            case 'S':
                intDir = 2;
                break;
            case 'W':
                intDir = 3;
                break;
        }
        
        robotStatus.push_back(Robot(inputY, inputX, intDir));
    }
    for(int i=0; i<M; i++) {
        int inputRobot = 0;
        char inputOrderType;
        int inputCnt = 0;
        
        cin >> inputRobot >> inputOrderType >> inputCnt;
        robotOrder.push_back(Order(inputRobot-1, inputOrderType, inputCnt));
    }
}

bool checkRobotCrashtoWall (int currentRobotIndex) {
    //1:Robot X crashes into the wall
    if(0<=(robotStatus[currentRobotIndex].y-1) && (robotStatus[currentRobotIndex].y-1) <B && 0 <=(robotStatus[currentRobotIndex].x-1) && (robotStatus[currentRobotIndex].x-1) <A)return true;
    
    return false;

}
bool checkRobotCrashtoRobot (int currentRobotIndex) {
    for(int i=0; i<N; i++) {
        int currentRobotY = robotStatus[currentRobotIndex].y;
        int currentRobotX = robotStatus[currentRobotIndex].x;
        int anotherRobotY = robotStatus[i].y;
        int anotherRobotX = robotStatus[i].x;
        
        if(i != currentRobotIndex && anotherRobotY == currentRobotY && anotherRobotX == currentRobotX){
            crashRobot = i;
            return false;
        }
    }
    
    return true;
}

void doOrder(int currentRobotIndex, int orderIndex) {
    char orderType = robotOrder[orderIndex].orderType;
    
    for(int i=0; i<robotOrder[orderIndex].cnt; i++) {
        if(orderType == 'L'){
            if(robotStatus[currentRobotIndex].dir == 0)robotStatus[currentRobotIndex].dir = 3;
            else robotStatus[currentRobotIndex].dir--;
            
        }else if(orderType == 'R'){
           robotStatus[currentRobotIndex].dir = (robotStatus[currentRobotIndex].dir +1)%4;
        }else if(orderType == 'F') {
            int currentDir = robotStatus[currentRobotIndex].dir;

            robotStatus[currentRobotIndex].y += moveDir[currentDir].y;
            robotStatus[currentRobotIndex].x += moveDir[currentDir].x;
            
        }
        
        if(!checkRobotCrashtoWall(currentRobotIndex)){

            cout<<"Robot "<<currentRobotIndex+1<<" crashes into the wall";
            isRobotStopped = true;
            return;
        }
        if(!checkRobotCrashtoRobot(currentRobotIndex)) {

            cout<<"Robot "<<currentRobotIndex+1<<" crashes into robot "<<crashRobot+1;
            isRobotStopped = true;
            return;
        }
        
    }
}


void solution() {
    for(int i=0; i<M; i++) {
        
        int currentTargetRobot = (robotOrder[i].targetRobot);

        doOrder(currentTargetRobot, i);
        
        if(isRobotStopped)return;
    }
    cout<<"OK";
}
int main() {
    
    input();
    solution();
    
    return 0;
}
