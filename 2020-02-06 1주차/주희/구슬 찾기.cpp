//[���� 2617] ����ã��

#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> scaleH; //�ڽź��� ���ſ� ���� ����
vector<vector<int>> scaleL; //�ڽź��� ������ ���� ����

void input(int M) {
	for (int i{ 0 }; i < M; i++) {
		int A, B;
		cin >> A >> B;

		scaleH[B].push_back(A);
		scaleL[A].push_back(B);
	}
}

set<int> Icount; //�߰��� �� �� ���� ����

int temp;
vector<bool> checkIF; //Ȯ�ε� ����
void checkH(int num) {
	for (auto a : scaleH[num]) {
		if (checkIF[a] == false) {
			checkIF[a] = true;
			temp++;
			checkH(a);
		}
	}
}

void checkL(int num) {
	for (auto a : scaleL[num]) {
		if (checkIF[a] == false) {
			checkIF[a] = true;
			temp++;
			checkL(a);
		}
	}


}

int main(){
	int N, M;
	cin >> N >> M;

	scaleH.resize(N + 1);
	scaleL.resize(N + 1);

	input(M);
	
	for (int i{ 1 }; i <= N; i++) {
		temp = 0;
		checkIF = vector<bool>(N + 1, false);
		checkIF[i] = true;

		checkH(i);
		if (temp >= N / 2 + 1) Icount.insert(i);
	}
	
	for (int i{ 1 }; i <= N; i++) {
		temp = 0;
		checkIF = vector<bool>(N + 1, false);
		checkIF[i] = true;

		checkL(i);
		if (temp >= N / 2 + 1) Icount.insert(i);
	}

	cout << Icount.size();

	//system("pause");
	return 0;
}