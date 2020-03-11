// https://www.acmicpc.net/problem/14238
// 시간초과..

#include<bits/stdc++.h>

using namespace std;

string record;
map<string, bool> m;
int arr[3];

void dfs(string ans) {
	if (m[ans]) return;
	if (ans.size() == record.size()) {
		cout << ans << '\n';
		exit(0);
	}

	m[ans] = true;
	for (int i = 0; i < 3; i++) {
		if (arr[i] > 0) {
			if (i == 0) {	// A를 붙인다
				arr[i]--;
				ans.push_back(char(i + 'A'));
				dfs(ans);
				ans.pop_back();
				arr[i]++;
			}
			else if (i == 1) {	// B를 붙인다
				if (ans[ans.size() - 1] != char(i + 'A')) {
					arr[i]--;
					ans.push_back(char(i + 'A'));
					dfs(ans);
					ans.pop_back();
					arr[i]++;
				}
			}
			else {
				if (ans.size() < 2) {
					if (ans[ans.size() - 1] != char(i + 'A')) {
						arr[i]--;
						ans.push_back(char(i + 'A'));
						dfs(ans);
						ans.pop_back();
						arr[i]++;
					}
				}
				else {
					if (ans[ans.size() - 1] != char(i + 'A') && ans[ans.size() - 2] != char(i + 'A')) {
						arr[i]--;
						ans.push_back(char(i + 'A'));
						dfs(ans);
						ans.pop_back();
						arr[i]++;
					}
				}
			}
		}
	}
}

void solve() {
	if (record.size() == 0) {
		cout << "-1" << '\n';
		return;
	}

	for (int i = 0; i < 3; i++) {
		if (arr[i] > 0) {
			arr[i]--;
			string start = "";
			start.push_back(char(i + 'A'));
			dfs(start);
			arr[i]++;
		}
	}
	cout << "-1" << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> record;
	for (int i = 0; i < record.size(); i++) {
		arr[record[i] - 'A']++;
	}
	solve();
	return 0;
}