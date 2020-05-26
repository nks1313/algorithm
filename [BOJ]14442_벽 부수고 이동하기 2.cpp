/*
�䱸����
0�� �̵��� �� �ִ� �� / 1�� �̵��� �� ���� ��
(1,1) -> (N, M)���� �̵��ϴµ� �ִ� ��η� �̵��Ѵ�.
���� �μ��� �̵��ϴ� ���� �� �� ��ΰ� ª�����ٸ� ���� K�� ���� �μ��� �� ����

�������
�����ϴ� ĭ�� ������ ĭ�� �����ؼ� ����.

������
1 <= N <= 1000 / 1 <= M <= 1000/ 1 <= K

���
�ִ� �Ÿ� ���, �Ұ��� �� ���� -1 ���
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