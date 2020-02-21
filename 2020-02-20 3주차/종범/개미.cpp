// https://www.acmicpc.net/problem/3048

#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int N1, N2, T;
string Left, Right;
string ans;
int dir[27];

void simulation() {
	for (int i = 0; i < N1; i++)
		dir[i] = 1;		// 왼쪽에서 오른쪽
	for (int i = N1; i < N1 + N2; i++)
		dir[i] = -1;	// 오른쪽에서 왼쪽

	while (T--) {
		for (int i = 0; i < N1 + N2 - 1; i++) {
			if (dir[i] != dir[i + 1] && dir[i] == 1) {
				swap(dir[i], dir[i + 1]);
				swap(ans[i], ans[i + 1]);
				i++;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N1 >> N2;
	cin >> Left >> Right;
	cin >> T;

	reverse(Left.begin(), Left.end());
	ans = Left + Right;

	if (T == 0) {
		cout << ans << '\n';
	}
	else {
		simulation();
		cout << ans << '\n';
	}
	return 0;
}