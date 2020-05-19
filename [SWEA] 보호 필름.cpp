/*
구해야 하는 것 : 약품 투입 최소 횟수!
*/
#include <iostream>
#include <algorithm>
using namespace std;
int T, N, M, K, answer;
int map[13][20];
int tmp[13][20];
int arr[13];
bool check(int map[][20]) {
	bool flag = false;
	for (int j = 0; j < M; j++) {
		int status = 2, cnt = 0, maxV = 0;
		for (int i = 0; i < N; i++) {
			if (map[i][j] != status) {
				maxV = max(cnt, maxV);
				status = map[i][j];
				cnt = 1;
			}
			else cnt++;
			if (cnt >= K) break;
		}
		maxV = max(cnt, maxV);
		if (maxV < K) return false;
	}
	return true;
}

void copy() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) tmp[i][j] = map[i][j];
}
void perm(int depth, int cnt) {
	if (cnt >= answer) return;
	
	if (depth == N) {
		copy();
		
		for (int i = 0; i < N; i++) {
			if (arr[i] == 2) continue;
			for (int j = 0; j < M; j++) tmp[i][j] = arr[i];
		}

		if (check(tmp)) {
			answer = min(answer, cnt);
		}

		return;
	}

	arr[depth] = 0;
	perm(depth + 1, cnt + 1);
	arr[depth] = 1;
	perm(depth + 1, cnt + 1);
	arr[depth] = 2;
	perm(depth + 1, cnt);
	
}
int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K;
		for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> map[i][j];

		//초기화
		answer = K;

		//1. 먼저 확인한다.
		if (check(map)) {
			cout << "#" << tc << " " << 0 << "\n";
		}

		//2. 모든 행에 대해서 0과 1의 값을 부여한다.
		perm(0, 0);
		cout << "#" << tc << " " << answer << "\n";
	}
}