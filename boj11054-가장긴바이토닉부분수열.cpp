#include <iostream>
using namespace std;
int A[1000];
int DP[2][1000];
int N,ans;


int main() {
	cin >> N;
	for (int i = 0; i < N; i++) DP[0][i] = DP[1][i] = 1;
	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < N; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (A[j] < A[i] && DP[0][j] >= DP[0][i]) {
				DP[0][i] = DP[0][j] + 1;
			}

			if (A[j] > A[i]) {
				if(DP[0][j] >= DP[1][i])
					DP[1][i] = DP[0][j] + 1;

				if (DP[1][j] >= DP[1][i])
					DP[1][i] = DP[1][j] + 1;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		ans = (ans > DP[0][i]) ? ans : DP[0][i];
		ans = (ans > DP[1][i]) ? ans : DP[1][i];
	}

	cout << ans << endl;
}