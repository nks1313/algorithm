#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
int T, N, W, H, answer;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int wallStone[5][15][12];
bool visited[15][12];

void init() {
	answer = 15 * 12;
}
void input() {
	cin >> N >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> wallStone[0][i][j];
		}
	}
}

void copy(int depth) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			wallStone[depth + 1][i][j] = wallStone[depth][i][j];
			visited[i][j] = false;
		}
	}
}

void select(int depth) {
	if (depth == N) {
		int cnt = 0;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (wallStone[N][i][j] > 0) cnt++;
			}
		}
		answer = min(answer, cnt);
		return;
	}

	//벽돌을 떨어뜨릴 위치 선정
	int endCnt = 0;
	for (int j = 0; j < W; j++) {
		copy(depth);
		int nd = depth + 1;
		int i = 0;
		while (i < H && !wallStone[nd][i][j]) i++;
		
		if (i == H) {
			endCnt++;
			continue;
		}

		//벽돌 지워주는 과정
		queue<pair<int, int>> q;
		q.push({ i,j });
		visited[i][j] = true;
		while (!q.empty()) {
			int si = q.front().first;
			int sj = q.front().second;
			q.pop();

			int ni, nj;
			for (int k = 0; k < 4; k++) {
				ni = si, nj = sj;
				for (int l = 1; l < wallStone[nd][si][sj]; l++) {
					ni += dy[k], nj += dx[k];
					if (ni < 0 || nj < 0 || ni >= H || nj >= W) continue;
					if (!wallStone[nd][ni][nj]) continue;
					if (visited[ni][nj]) continue;

					q.push({ ni,nj });
					visited[ni][nj] = true;
				}
			}
			wallStone[nd][si][sj] = 0;
		}


		//벽돌 옮겨주기
		for (int j = 0; j < W; j++) {
			int zeroCnt = 0;
			for (int i = H - 1; i >= 0; i--) {
				if (!wallStone[nd][i][j]) zeroCnt++;
				else {
					wallStone[nd][i + zeroCnt][j] = wallStone[nd][i][j];
					if (zeroCnt != 0) wallStone[nd][i][j] = 0;
				}
			}
		}


		select(depth + 1);
	}

}
int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();

		select(0);
		cout << "#" << tc << " " << answer << "\n";
	}
}