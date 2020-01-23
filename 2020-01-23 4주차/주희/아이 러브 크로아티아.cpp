//[백준 9517] 아이 러브 크로아티아
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

int main() {
	int TNT;
	cin >> TNT;

	int safe{ 210 };

	int N;
	cin >> N;
	for (int n{ 0 }; n < N; n++) {
		int time;
		char answer;

		cin >> time >> answer;
		
		if (safe - time <= 0) {
			cout << TNT;
			system("pause");
			return 0;
		}

		if (answer == 'T') {
			safe -= time;
			TNT++;
			if (TNT > 8) TNT = 1;
		}
		else {
			safe -= time;
		}
	}



	system("pause");
	return 0;
}