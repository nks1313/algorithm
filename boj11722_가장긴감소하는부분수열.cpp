#include <iostream>
using namespace std;
int A[1000];
int DP[1000];
int N,ans;


int main() {
	cin >> N;
	for (int i = 0; i < N; i++) DP[i] = 1;
	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < N; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (A[j] > A[i] && DP[j] >= DP[i]) {
				DP[i] = DP[j] + 1;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		ans = (ans > DP[i]) ? ans : DP[i];
	}

	cout << ans << endl;
}