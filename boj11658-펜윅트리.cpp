#include <iostream>
using namespace std;
int N, M;
long long fenwickTree[1025][1025];
long long arr[1025][1025];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> fenwickTree[i][j];
			arr[i][j] = fenwickTree[i][j];
			//같은 행에서의 합을 먼저 구함
			int tmp = j - 1;
			int sum = 0;
			while ((tmp & (-tmp)) < (j & (-j)) && (tmp & (-tmp)) != 0) {
				sum += fenwickTree[i][tmp];
				tmp -= tmp & (-tmp);
			}
			fenwickTree[i][j] += sum;
		}
	}
	//같은 열에서의 합을 구함
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			int tmp = i - 1;
			int sum = 0;
			while ((tmp & (-tmp)) < (i & (-i)) && (tmp & (-tmp)) != 0) {
				sum += fenwickTree[tmp][j];
				tmp -= tmp & (-tmp);
			}
			fenwickTree[i][j] += sum;
		}
	}
	int w, x1, y1, x2, y2, c;
	while (M--) {
		cin >> w;
		if (w & 1) {
			cin >> x1 >> y1 >> x2 >> y2;
			long long ans = 0;
			for (int i = x2; i > 0; i -= (i & (-i))) {
				for (int j = y2; j > 0; j -= (j & (-j))) {
					ans += fenwickTree[i][j];
				}
			}

			for (int i = x1 - 1; i > 0; i -= (i & (-i))) {
				for (int j = y2; j > 0; j -= (j & (-j))) {
					ans -= fenwickTree[i][j];
				}
			}

			for (int i = x2; i > 0; i -= (i & (-i))) {
				for (int j = y1 - 1; j > 0; j -= (j & (-j))) {
					ans -= fenwickTree[i][j];
				}
			}

			for (int i = x1 - 1; i > 0; i -= (i & (-i))) {
				for (int j = y1 - 1; j > 0; j -= (j & (-j))) {
					ans += fenwickTree[i][j];
				}
			}
			cout << ans << "\n";
		}
		else {
			cin >> x1 >> y1 >> c;
			int value = c - arr[x1][y1];
			arr[x1][y1] = c;
			for (int i = x1; i <= N; i += (i & (-i))) {
				for (int j = y1; j <= N; j += (j & (-j))) {
					fenwickTree[i][j] += value;
				}
			}
		}
	}

}