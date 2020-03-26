#include <iostream>
#include <queue>
#define MAXN 21
#define SECTOR 6
using namespace std;

int N, ans = 100*20*20;
int A[MAXN][MAXN];
int p[SECTOR];
int sector[MAXN][MAXN];
bool visited[MAXN][MAXN];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
void initSector() {
	for (int i = 1; i < MAXN; i++) {
		for (int j = 1; j < MAXN; j++) {
			sector[i][j] = 0;
			visited[i][j] = false;
		}
	}
	for (int i = 1; i < SECTOR; i++) p[i] = 0;
}

void bfs(int y,int x,int rs, int re, int cs, int ce,int num) {
	queue<pair<int, int>> q;
	q.push({ y,x });
	visited[y][x] = true;
	sector[y][x] = num;

	while (!q.empty()) {
		int currR = q.front().first;
		int currC = q.front().second;
		q.pop();
		
		
		for (int k = 0; k < 4; k++) {
			int nextR = currR + dy[k];
			int nextC = currC + dx[k];

			if (nextR < rs || nextR > re || nextC < cs || nextC > ce)
				continue;
			if (sector[nextR][nextC] == 5) continue;
			if (visited[nextR][nextC]) continue;

			q.push({ nextR, nextC });
			visited[nextR][nextC] = true;
			sector[nextR][nextC] = num;
		}
	}
}

void printSector() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << sector[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}

	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			for (int d1 = 1; d1 <= N - 2; d1++) {
				if (y - d1 < 1) break;
				for (int d2 = 1; d2 <= N - 2; d2++) {
					if (x + d1 + d2 > N || y + d2 > N) {
						break;
					}
					
					initSector();

					//5번 구역 표시
					//1번 경계선
					int c = x, r = y;
					while (c <= x + d1 && r >= y - d1) {
						sector[r--][c++] = 5;
					}
					c = x, r = y;
					while (c <= x + d2 && r <= y + d2) {
						sector[r++][c++] = 5;
					}
					c = x + d1, r = y - d1;
					while (c <= x + d1 + d2 && r <= y - d1 + d2) {
						sector[r++][c++] = 5;
					}
					c = x + d2, r = y + d2;
					while (c <= x + d2 + d1 && r >= y + d2 - d1) {
						sector[r--][c++] = 5;
					}
					
					

					//1번 ~ 4번 구역 나누기
					//BFS로 구역 나누자
					//int rs = 1, re = x + d1 - 1, cs = 1, ce = y;
					int rs = 1, re = y - 1, cs = 1, ce = x + d1;
					bfs(1,1,rs, re, cs, ce, 1);
					//rs = 1, re = x + d2, cs = y + 1, ce = N;
					rs = 1, re = y - d1 + d2, cs = x + d1 + 1, ce = N;
					bfs(1,N,rs, re, cs, ce, 2);
					//rs = x+d1, re = N, cs = 1, ce = y-d1+d2-1;
					rs = y, re = N, cs = 1, ce = x + d2 - 1;
					bfs(N,1,rs, re, cs, ce, 3);
					//rs = x+d2+1, re = N, cs = y-d1+d2, ce = N;
					rs = y - d1 + d2, re = N, cs = x + d2, ce = N;
					bfs(N,N,rs, re, cs, ce, 4);
					

					//cout << x << " " << y << " " << d1 << " " << d2 << endl;
					//printSector();
					
					for (int r = 1; r <= N; r++) {
						for (int c = 1; c <= N; c++) {
							if (!sector[r][c]) sector[r][c] = 5;
							p[sector[r][c]] += A[r][c];
						}
					}

					int max = 0, min = 100 * 20 * 20;
					for (int i = 1; i < SECTOR; i++) {
						max = (max > p[i]) ? max : p[i];
						min = (min < p[i]) ? min : p[i];
					}

					ans =  (ans < max-min) ? ans : max-min;

				}
			}
		}
	}

	cout << ans << endl;

	system("pause");
}
