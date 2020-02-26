#include <iostream>
using namespace std;

int T;
int DP[13];
int fee[4];
int plan[13];

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i <= 12; i++) DP[i] = 0;
		for (int i = 0; i < 4; i++) cin >> fee[i];
		for (int i = 1; i <= 12; i++) cin >> plan[i];

		for (int i = 1; i <= 12; i++) {
			DP[i] += (DP[i - 1] + fee[0]*plan[i]);
			if (DP[i] > DP[i - 1] + fee[1]) DP[i] = DP[i - 1] + fee[1];
			if (i >= 3 && DP[i] > DP[i - 3] + fee[2]) DP[i] = DP[i - 3] + fee[2];
			if (i >= 12 && DP[i] > DP[i - 12] + fee[3]) DP[i] = DP[i - 12] + fee[3];
		}

		cout << "#" << tc << " " << DP[12] << '\n';
	}

	system("pause");

	return 0;
}