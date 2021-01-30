//https://www.acmicpc.net/problem/16637
//��ȣ �߰��ϱ�


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits.h>
#include <set>


using namespace std;


//������ �������� ���� ��� �����ؾ���, ���ڸ��ΰ��
//�ߺ� ��ȣ �ȵǴ°� �����ߴ�
//idx++ �������ξ��ϱ� ���ϴ´�� �ȳ�����

int N;

set<char> oper = { '+', '-', '*' };
set<string> oper2 = { "+", "-", "*" };
vector<string> expr; //ó�� �־����� �����

vector<int> pre; //0�̸� ���������� 1�̸� ��ȣ�ļ� �������

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

void calFinal(vector<string> exp) { //���������� ���� 
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
	vector<string> exp; //��ȣ ������ �κ� ����� �� ��

	int idx = 0;
	for (int i = 0; i < pre.size(); i++) {
	
		if (pre[i] == 1) { //���� ����
			//cout << "��������";

			string tmp = to_string(cal(expr[idx], expr[idx+1], expr[idx+2]));
			idx += 3;
			//cout << "tmp: " << tmp;
			exp.push_back(tmp);
		}
		else { //���߿� ����
			//cout << "���߿�����\n";
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

	calFinal(exp);//������ ������� ����
}

void isPre(int cnt) {
	if (cnt == N / 2) {
		//cout << "\npre:";
		//for (auto a : pre)cout << a << " ";
		calPre();//��ȣ�κ� ���
	}
	else {

		//��ȣ ��ġ�����
		pre.push_back(0);
		isPre(cnt + 1);

		pre.pop_back();
		

		//��ȣ ġ�����
		if ((pre.size() != 0 && pre.back() != 1) || pre.size() == 0) { //��ȣ ĥ�Ÿ� ������ ���ƾ����
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
	

	//string���� vector�� �ٲٱ�
	string tmpNum = "";
	for (int i = 0; i < str.size(); i++) {
		//cout << "\nstr.at()" << str.at(i);
		if (oper.count(str.at(i)) == 1) { //�������ΰ��
			//cout << "\n��������";

			if (expr.size() == 0 && tmpNum == "") { //-�� �����ϴ� ���
				tmpNum += str.at(i);
			}
			else if (expr.size() >= 1 && oper.count(expr[expr.size() - 1].at(0)) == 1 && tmpNum == "") { //�����ڰ� �������� �ι���
				//cout << "\n�����ڿ���";
				tmpNum += str.at(i);
			}
			else { //�����ڰ� �ѹ��� ��
				//cout << "\n�������ѹ���";
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
			//cout << "\n�����ΰ��";
			tmpNum += str.at(i); //�����ΰ��
		}
	}
	expr.push_back(tmpNum);
	
	
	
	isPre(0);//������������������� - ��ȣġ��


	cout << maxVal;

}