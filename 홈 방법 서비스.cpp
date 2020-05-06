#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
int T, N, M, homeCnt, answer;
int map[22][22];
int kval[22];
int distCnt[22];
pair<int, int> home[400];
void pre() {
	for (int k = 1; k <= 21; k++) kval[k] = k * k + (k - 1) * (k - 1);
}

void init() {
	answer = 0;
	homeCnt = 0;
}

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				home[homeCnt++] = { i,j };
			}
		}
}

void init_dist() {
	for (int i = 1; i <= N + 1; i++) distCnt[i] = 0;
}

void solution() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			init_dist();
			for (int k = 0; k < homeCnt; k++) {
				int dist = abs(i - home[k].first) + abs(j - home[k].second);
				distCnt[dist]++;
			}

			int p = 0;
			for (int k = 1; k <= N + 1; k++) {
				p += distCnt[k];
				if (p * M >= kval[k]) answer = max(distCnt[k], answer);
			}
		}
	}
}


int main() {
	cin >> T;
	pre();
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		solution();
		cout << "#" << tc << " " << answer << "\n";
	}
}