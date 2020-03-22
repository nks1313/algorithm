#include <iostream>
using namespace std;
int N, M;
int A[1000001];
long long S[1000001];
long long ans;
int cnt[1000];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
		S[i] = S[i - 1] + A[i];
	}

	for (int i = 0; i <= N; i++) {
		cnt[S[i] % M]++;
	}
	for (int i = 0; i < M; i++) {
		if (cnt[i] > 1) {
			ans += cnt[i] * (cnt[i] - 1) / 2;
		}
	}

	cout << ans << "\n";
}