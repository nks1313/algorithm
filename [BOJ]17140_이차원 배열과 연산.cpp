#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int r, c, k, rcnt, ccnt;
int A[101][101];
int temp[101];
int cnt[101];
vector<pair<int, int>> v;
void init() {
	for (int i = 1; i <= 100; i++) {
		temp[i] = 0;
		cnt[i] = 0;
	}
	v.clear();
}
int main() {
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) cin >> A[i][j];

	int answer = -1;
	rcnt = 3; ccnt = 3;
	for (int t = 0; t <= 100; t++) {
		if (A[r][c] == k) {
			answer = t;
			break;
		}

		if (rcnt >= ccnt) {
			int ccntTmp = 0;
			for (int i = 1; i <= rcnt; i++) {
				init();
				for (int j = 1; j <= ccnt; j++) {
					cnt[A[i][j]]++;
				}

				for (int j = 1; j <= 100; j++) {
					if (cnt[j] != 0) {
						v.push_back({ cnt[j],j });
					}
				}

				sort(v.begin(), v.end());

				int idx = 1;
				for (int j = 0; j < v.size(); j++) {
					temp[idx++] = v[j].second;
					temp[idx++] = v[j].first;
				}

				ccntTmp = max(ccntTmp, idx - 1);

				for (int j = 1; j <= 100; j++) {
					A[i][j] = temp[j];
				}
			}
			ccnt = ccntTmp;
		}
		else {
			int rcntTmp = 0;
			for (int i = 1; i <= ccnt; i++) {
				init();
				for (int j = 1; j <= rcnt; j++) {
					cnt[A[j][i]]++;
				}

				for (int j = 1; j <= 100; j++) {
					if (cnt[j] != 0) {
						v.push_back({ cnt[j],j });
					}
				}

				sort(v.begin(), v.end());

				int idx = 1;
				for (int j = 0; j < v.size(); j++) {
					temp[idx++] = v[j].second;
					temp[idx++] = v[j].first;
				}

				rcntTmp = max(rcntTmp, idx - 1);

				for (int j = 1; j <= 100; j++) {
					A[j][i] = temp[j];
				}
			}
			rcnt = rcntTmp;
		}
	}

	cout << answer;
}