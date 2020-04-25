#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
int arr[5][5][5];
int cnt = 0;
int rotateResult[5][5][5];
int maze[5][5][5];
bool visited[5][5][5];
int a[5];
int answer = 5 * 5 * 5;
int dy[6] = { 0, 0, -1, 1, 0, 0 };
int dx[6] = { -1, 1, 0, 0, 0, 0 };
int dz[6] = { 0, 0, 0, 0, -1, 1 };

struct Point {
	int y;
	int x;
	int z;
};

void bfs(int sy, int sx, int sz, int ey, int ex, int ez) {
	if (maze[sy][sx][sz] == 0 || maze[ey][ex][ez] == 0) return;

	queue<Point> q;
	q.push({ sy,sx,sz });
	visited[sy][sx][sz] = true;

	int t = -1;
	while (!q.empty()) {
		t++;
		int sze = q.size();
		for (int j = 0; j < sze; j++) {
			int currY = q.front().y;
			int currX = q.front().x;
			int currZ = q.front().z;
			q.pop();

			if (currY == ey && currX == ex && currZ == ez) {
				answer = (answer < t) ? answer : t;
				return;
			}

			for (int i = 0; i < 6; i++) {
				int nextY = currY + dy[i];
				int nextX = currX + dx[i];
				int nextZ = currZ + dz[i];


				if (nextY < 0 || nextX < 0 || nextZ < 0 || nextY > 4 || nextX > 4 || nextZ > 4) continue;
				if (visited[nextY][nextX][nextZ]) continue;
				if (maze[nextY][nextX][nextZ] == 0) continue;

				q.push({ nextY, nextX, nextZ });
				visited[nextY][nextX][nextZ] = true;
			}
		}
	}

}

void pile() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				maze[a[i]][j][k] = rotateResult[i][j][k];
			}
		}
	}
}

void init() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				visited[i][j][k] = false;
			}
		}
	}
}

void rotate(int i, int d) {
	if (d == 0) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				rotateResult[i][j][k] = arr[i][j][k];
			}
		}
	}
	else if (d == 1) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				rotateResult[i][j][k] = arr[i][4 - k][j];
			}
		}
	}
	else if (d == 2) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				rotateResult[i][j][k] = arr[i][4 - j][4 - k];
			}
		}
	}
	else if (d == 3) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				rotateResult[i][j][k] = arr[i][k][4 - j];
			}
		}
	}
}

int main() {
	//입력
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				cin >> arr[i][j][k];
			}
		}
	}

	//회전

	bool flag = false;
	rotate(0, 0);
	for (int j = 0; j < 4; j++) {
		rotate(1, j);
		for (int k = 0; k < 4; k++) {
			rotate(2, k);
			for (int l = 0; l < 4; l++) {
				rotate(3, l);
				for (int m = 0; m < 4; m++) {
					rotate(4, m);
					//쌓는다.
					for (int i = 0; i < 5; i++) a[i] = i;
					do {
						//쌓는다.
						pile();
						//입구, 출구 정한다.
						bfs(0, 0, 0, 4, 4, 4);
						if (answer == 12) {
							flag = true;
							break;
						}
						init();
						bfs(0, 4, 0, 4, 0, 4);
						if (answer == 12) {
							flag = true;
							break;
						}
						init();
						bfs(4, 0, 0, 0, 4, 4);
						if (answer == 12) {
							flag = true;
							break;
						}
						init();
						bfs(4, 4, 0, 0, 0, 4);
						if (answer == 12) {
							flag = true;
							break;
						}
						init();
					} while (next_permutation(a, a + 5));
					if (flag) break;
				}
				if (flag) break;
			}
			if (flag) break;
		}
		if (flag) break;
	}

	if (answer == 5 * 5 * 5) cout << -1;
	else cout << answer;
}