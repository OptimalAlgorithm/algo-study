#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 11

int N;
int num[MAX];
int op[4];
vector<int> v;

void recursive(int n, int prev)
{
	int rslt;

	if (n >= N)
	{
		v.push_back(prev);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (op[i] <= 0) // 연산자 선택불가
			continue;

		op[i]--; //연산자 선택

		switch (i)
		{
		case 0:
			rslt = prev + num[n];
			break;
		case 1:
			rslt = prev - num[n];
			break;
		case 2:
			rslt = prev * num[n];
			break;
		case 3:
			rslt = prev / num[n];
			break;
		}

		recursive(n + 1, rslt); // 다음 숫자로 넘기기
		op[i]++;
	}
}

void solve()
{
	recursive(1, num[0]);
	sort(v.begin(), v.end());
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> N; 
	for (int i = 0; i < N; i++) //숫자
		cin >> num[i];
	for (int i = 0; i < 4; i++) //덧셈, 뺄셈, 곱셈, 나눗셈
		cin >> op[i];

	solve();

	//output
	cout << v[v.size() - 1] << endl << v[0];
}
