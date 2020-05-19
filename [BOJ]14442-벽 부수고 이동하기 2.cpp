/*
요구사항
0은 이동할 수 있는 곳 / 1은 이동할 수 업는 벽
(1,1) -> (N, M)까지 이동하는데 최단 경로로 이동한다.
벽을 부수고 이동하는 것이 좀 더 경로가 짧아진다면 벽을 K개 까지 부수는 거 가능

제약사항
시작하는 칸과 끝나는 칸도 포함해서 센다.

데이터
1 <= N <= 1000 / 1 <= M <= 1000/ 1 <= K

출력
최단 거리 출력, 불가능 할 때는 -1 출력
*/

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;
int N, M, K, answer;
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };
int map[1000][1000];
int DP[11][1000][1000];
struct node {
	int k;
	int y;
	int x;
	int dist;
};

void bfs() {
	queue<node> q;
	q.push({ 0,0,0,1 });
	DP[0][0][0] = 1;
	while (!q.empty()) {
		int k = q.front().k;
		int y = q.front().y;
		int x = q.front().x;
		int dist = q.front().dist;
		q.pop();

		if (y == N - 1 && x == M - 1) {
			answer = dist;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (!map[ny][nx]) {
				if (DP[k][ny][nx]) continue;
				q.push({ k, ny, nx, dist + 1 });
				DP[k][ny][nx] = DP[k][y][x] + 1;
			}
			else {
				if (k == K) continue;
				if (DP[k + 1][ny][nx]) continue;
				q.push({ k + 1, ny, nx, dist + 1 });
				DP[k+1][ny][nx] = DP[k][y][x] + 1;
			}
		}
	}
}
int main() {
	cin >> N >> M >> K;

	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		for (int j = 0; j < M; j++) {
			map[i][j] = str[j] - '0';
		}
	}

	answer = 0x7fffffff;
	bfs();

	if (answer == 0x7fffffff) cout << -1;
	else {
		cout << answer;
	}
}