/*
요구사항
1. 가장 처음에 양분은 모든 칸에 5씩
2. M개의 나무를 땅에 심었다.
3. 같은 칸에 여러 개의 나무가 심어질 수 있다.

봄
어린 나무부터 양분 먹음,

출력
K년이 지난 후 상도의 땅에 살아있는 나무의 개수를 구하라
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
int N, M, K;
int A[11][11];
int map[11][11];
vector<int> tree[11][11];
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };
void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			vector<int> v = tree[i][j];
			int value = 0;
			for (int k = v.size() - 1; k >= 0; k--) {
				if (v[k] <= map[i][j]) {
					map[i][j] -= v[k];
					v[k]++;
				}
				else {
					value += v[k] / 2;
					v.erase(v.begin()+k);
				}
			}
			map[i][j] += value;
			tree[i][j] = v;
		}
	}
}

void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			vector<int> v = tree[i][j];
			for (int k = v.size() - 1; k >= 0; k--) {
				if (v[k] % 5 == 0) {
					for (int l = 0; l < 8; l++) {
						int nx = i + dx[l];
						int ny = j + dy[l];
						if (nx < 1 || nx > N || ny < 1 || ny > N)
							continue;
						tree[nx][ny].push_back(1);
					}
				}
			}
		}
	}
}

void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] += A[i][j];
		}
	}
}

int calc() {
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ret += tree[i][j].size();
		}
	}

	return ret;
}
int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			map[i][j] = 5;
		}
	}

	int x, y, z;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		tree[x][y].push_back(z);
	}

	for (int i = 0; i < K; i++) {
		spring();
		fall();
		winter();
	}

	cout << calc();
}