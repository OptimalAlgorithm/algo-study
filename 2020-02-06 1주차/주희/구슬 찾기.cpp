//[백준 2617] 구슬찾기

#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> scaleH; //자신보다 무거운 구슬 저장
vector<vector<int>> scaleL; //자신보다 가벼운 구슬 저장

void input(int M) {
	for (int i{ 0 }; i < M; i++) {
		int A, B;
		cin >> A >> B;

		scaleH[B].push_back(A);
		scaleL[A].push_back(B);
	}
}

set<int> Icount; //중간에 올 수 없는 구슬

int temp;
vector<bool> checkIF; //확인된 구슬
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