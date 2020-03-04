#include <iostream>
#include <string>
#define MAXN 1000
using namespace std;

int T, H, W, ans;
string inputStr;
int map[MAXN][MAXN];
int qx[MAXN * MAXN + 1];
int qy[MAXN * MAXN + 1];
int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

int main() {
	ios_base::sync_with_stdio;
	cin.tie(0);

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {

		ans = 0;
		cin >> H >> W;

		
		int front = -1, rear = -1;

		for (int i = 0; i < H; i++) {
			cin >> inputStr;
			for (int j = 0; j < W; j++) {
				if (inputStr[j] == '.') {
					map[i][j] = 0;
					qy[++rear] = i;
					qx[rear] = j;
				}
				else {
					map[i][j] = (inputStr[j] - '0');
				}
			}
		}

		while (front != rear) {
			int sz = rear - front;
			bool check = false;
			for (int i = 0; i < sz; i++) {
				int y = qy[++front];
				int x = qx[front];

				for (int j = 0; j < 8; j++) {
					int ny = y + dy[j];
					int nx = x + dx[j];

					if (ny < 0 || ny >= H || nx < 0 || nx >= W)
						continue;

					if (map[ny][nx] > 0) {
						if (--map[ny][nx] == 0) {
							check = true;
							qy[++rear] = ny;
							qx[rear] = nx;
						}
					}
				}
			}
			if (!check) break;

			ans++;
		}

		cout << "#" << tc << " " << ans << "\n";
	}
}
