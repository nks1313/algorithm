#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int T, N;
double ans;
double DP[501][501];
string str[2];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//입력
		cin >> N >> str[0] >> str[1];


		//DP 초기화
		for (int i = 0; i < N + 1; i++) DP[i][0] = 0;
		for (int j = 1; j < N + 1; j++) DP[0][j] = 0;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (str[0][i] == str[1][j]) {
					DP[i][j] = DP[i - 1][j - 1] + 1;
				}
				else {
					DP[i][j] = (DP[i - 1][j] > DP[i][j - 1]) ? DP[i - 1][j] : DP[i][j - 1];
				}
			}
		}

		ans = (DP[N][N] / N) * 100;
		cout << fixed;
		cout.precision(2);
		cout << "#" << tc << " " << ans << "\n";
	}
}