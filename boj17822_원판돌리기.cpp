//원판 T번 회전
//번호가 x의 배수인 원판을 d방향으로 k칸 회전
//d가 0인 경우 시계, 1인 경우 반시계
//원판에 수가 남아 있으면, 인접하면서 수가 같은 것을 모두 찾는다.
//그러한 수가 있는 경우에, 원판에서 인접하면서 같은 수를 모두 지운다.
//없는 경우 원판에 적힌 수의 평균을 구하고 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더한다.
//원판을 T번 회전시킨 후 원판에 적힌 수의 합을 구하자.

#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int N, M, T, x, d, k, answer;
int map[51][51];
bool visited[51][51];
int temp[51];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int main() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	while (T--) {
		cin >> x >> d >> k;
		
		//회전하는 과정
		if (d == 1) k = (M - k);

		for (int i = x; i <= N; i += x) {
			for (int j = 1; j <= M; j++) {
				int nj = (j + k) % M;
				if (nj == 0) nj = M;
				temp[nj] = map[i][j];
			}

			for (int j = 1; j <= M; j++) {
				map[i][j] = temp[j];
			}
		}

		//먼저 visited 초기화
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				visited[i][j] = false;
			}
		}

		bool flag = false;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (map[i][j] == 0) continue;
				if (visited[i][j]) continue;
				int num = map[i][j];

				queue<pair<int, int>> q;
				q.push({ i,j });
				visited[i][j] = true;

				while (!q.empty()) {
					int cy = q.front().first;
					int cx = q.front().second;
					q.pop();

					for (int k = 0; k < 4; k++) {
						int ny = cy + dy[k];
						int nx = cx + dx[k];

						if (nx == 0) nx = M;
						if (nx == M + 1) nx = 1;

						if (ny < 1 || ny > N) continue;
						if (map[ny][nx] != num) continue;
						if (visited[ny][nx]) continue;

						flag = true;

						q.push({ ny,nx });
						visited[ny][nx] = true;
						map[cy][cx] = 0;
						map[ny][nx] = 0;
					}
				}
				
			}
		}

		if (!flag) {
			double aver = 0;
			int cnt = 0;
			
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (map[i][j] > 0) {
						aver += map[i][j];
						cnt++;
					}
				}
			}
		
			aver /= cnt;
		
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if(map[i][j] == 0) continue;
					
					if (map[i][j] > aver) {
						map[i][j]--;
					}
					else if (map[i][j] < aver) {
						map[i][j]++;
					}
				}
			}
		}

	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			answer += map[i][j];
		}
	}

	cout << answer;
}