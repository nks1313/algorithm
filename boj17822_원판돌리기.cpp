//���� T�� ȸ��
//��ȣ�� x�� ����� ������ d�������� kĭ ȸ��
//d�� 0�� ��� �ð�, 1�� ��� �ݽð�
//���ǿ� ���� ���� ������, �����ϸ鼭 ���� ���� ���� ��� ã�´�.
//�׷��� ���� �ִ� ��쿡, ���ǿ��� �����ϸ鼭 ���� ���� ��� �����.
//���� ��� ���ǿ� ���� ���� ����� ���ϰ� ��պ��� ū ������ 1�� ����, ���� ������ 1�� ���Ѵ�.
//������ T�� ȸ����Ų �� ���ǿ� ���� ���� ���� ������.

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
		
		//ȸ���ϴ� ����
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

		//���� visited �ʱ�ȭ
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