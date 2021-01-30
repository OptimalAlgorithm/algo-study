//https://www.acmicpc.net/problem/16637
//괄호 추가하기


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits.h>
#include <set>


using namespace std;


//연산자 연속으로 오는 경우 생각해야함, 두자리인경우
//중복 괄호 안되는걸 간과했다
//idx++ 연속으로쓰니까 원하는대로 안나왔음

int N;

set<char> oper = { '+', '-', '*' };
set<string> oper2 = { "+", "-", "*" };
vector<string> expr; //처음 주어지는 연산식

vector<int> pre; //0이면 먼저계산안함 1이면 괄호쳐서 먼저계산

int maxVal = INT_MIN;

int cal(string a, string op, string b) {

	//cout << "\ncal: " << a << " " << op << " " << b;
	int num1 = stoi(a);
	int num2 = stoi(b);

	int rtn;

	if (op == "+") {
		rtn = (num1 + num2);
	}
	
	if (op == "-") {
		rtn = (num1 - num2);
	}

	if (op == "*") {
		rtn =  (num1 * num2);
	}
	//cout << "num: " << num1 << " " << num2;
	//cout << "rtn: " << rtn << endl;

	return rtn;
}

void calFinal(vector<string> exp) { //마지막으로 연산 
	//cout << "final!!";
	int result = stoi(exp[0]);
	
	for (int i = 1; i < exp.size()-1; i+=2) {
		result = cal(to_string(result), exp[i], exp[i + 1]);
	}

	//cout << "\nresult:" << result;
	maxVal = max(maxVal, result);
}

void calPre() {
	//cout << "calpre";
	vector<string> exp; //괄호 결정난 부분 연산된 후 식

	int idx = 0;
	for (int i = 0; i < pre.size(); i++) {
	
		if (pre[i] == 1) { //먼저 연산
			//cout << "먼저연산";

			string tmp = to_string(cal(expr[idx], expr[idx+1], expr[idx+2]));
			idx += 3;
			//cout << "tmp: " << tmp;
			exp.push_back(tmp);
		}
		else { //나중에 연산
			//cout << "나중에연산\n";
			if (oper2.count(expr[idx]) == 1)exp.push_back(expr[idx++]);
			else {
				exp.push_back(expr[idx++]);
				exp.push_back(expr[idx++]);
			}
		}
	}
	
	if (idx == expr.size() - 1)exp.push_back(expr[idx]);
	
	//cout << "final exp: ";
	//for (auto a : exp)cout << a << " ";

	calFinal(exp);//마지막 순서대로 연산
}

void isPre(int cnt) {
	if (cnt == N / 2) {
		//cout << "\npre:";
		//for (auto a : pre)cout << a << " ";
		calPre();//괄호부분 계산
	}
	else {

		//괄호 안치기로함
		pre.push_back(0);
		isPre(cnt + 1);

		pre.pop_back();
		

		//괄호 치기로함
		if ((pre.size() != 0 && pre.back() != 1) || pre.size() == 0) { //괄호 칠거면 직전에 안쳤어야함
			pre.push_back(1);
			isPre(cnt + 1);
			pre.pop_back();
		}		
	}
}

int main() {

	cin >> N;

	string str;
	cin >> str;
	

	//string에서 vector로 바꾸기
	string tmpNum = "";
	for (int i = 0; i < str.size(); i++) {
		//cout << "\nstr.at()" << str.at(i);
		if (oper.count(str.at(i)) == 1) { //연산자인경우
			//cout << "\n연산자임";

			if (expr.size() == 0 && tmpNum == "") { //-로 시작하는 경우
				tmpNum += str.at(i);
			}
			else if (expr.size() >= 1 && oper.count(expr[expr.size() - 1].at(0)) == 1 && tmpNum == "") { //연산자가 연속으로 두번옴
				//cout << "\n연산자연속";
				tmpNum += str.at(i);
			}
			else { //연산자가 한번만 옴
				//cout << "\n연산자한번만";
				if (tmpNum != "") {
					expr.push_back(tmpNum);
					tmpNum = "";
				}
				string op = "";
				op += str.at(i);
				expr.push_back(op);

			}

		}
		else {
			//cout << "\n숫자인경우";
			tmpNum += str.at(i); //숫자인경우
		}
	}
	expr.push_back(tmpNum);
	
	
	
	isPre(0);//먼저계산할지말지결정 - 괄호치기


	cout << maxVal;

}