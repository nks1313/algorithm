#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

pair<int, int> map[51][51];
pair<int, int> temp[51][51];
pair<int, int> possibleLand[11];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int N, M, G, R, answer, landCnt;

void copy() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			temp[i][j] = map[i][j];
		}
	}
}
int bfs() {
	int cnt = 0;
	queue<pair<int, int>> q;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j].first == 3 || map[i][j].first == 4) {
				q.push({ i,j });
			}
		}
	}
	
	int t = 0;
	while (!q.empty()) {
		t++;
		int sz = q.size();
		for (int i = 0; i < sz; i++) {
			pair<int, int> curr = q.front();
			q.pop();
			int currY = curr.first;
			int currX = curr.second;
			
			if (temp[currY][currX].first == 5) {
				continue;
			}

			for (int k = 0; k < 4; k++) {
				int nextY = currY + dy[k];
				int nextX = currX + dx[k];
				if (nextY < 1 || nextX < 1 || nextY > N || nextX > M) continue;
				if (temp[nextY][nextX].first == temp[currY][currX].first) continue;
				if (temp[nextY][nextX].first == 5) continue;
				if (temp[nextY][nextX].first == 0) continue;

				//현재 초록색 배양액
				if (temp[currY][currX].first == 3) {
					if (temp[nextY][nextX].first == 4) {
						if (temp[nextY][nextX].second != t) continue;
						else {
							temp[nextY][nextX].first = 5;
							cnt++;
							continue;
						}
					}
				}
				//현재 빨간색 배양액
				else if (temp[currY][currX].first == 4) {
					if (temp[nextY][nextX].first == 3) {
						if (temp[nextY][nextX].second != t) continue;
						else {
							temp[nextY][nextX].first = 5;
							cnt++;
							continue;
						}
					}
				}

				temp[nextY][nextX] = { temp[currY][currX].first, t };
				q.push({ nextY,nextX});
			}
		}
		
	}

	return cnt;
}
void red(int depth, int num, int visited) {
	if (depth == R) {
		//여기까지 배양액 뿌리는 작업
		copy();
		answer = max(answer,bfs());
	}

	for (int i = num; i < landCnt; i++) {
		if (visited & (1 << i)) continue;
		pair<int, int> curr = possibleLand[i];
		map[curr.first][curr.second] = { 4, 0 };
		red(depth + 1, i + 1, visited | (1 << i));
		map[curr.first][curr.second] = { 2, 0 };
	}
}

void green(int depth, int num, int visited) {
	if (depth == G) {
		red(0, 0, visited);
		return;
	}

	for (int i = num; i < landCnt; i++) {
		if (visited & (1 << i)) continue;
		pair<int, int> curr = possibleLand[i];
		map[curr.first][curr.second] = { 3, 0 };
		green(depth + 1, i + 1, visited | (1 << i));
		map[curr.first][curr.second] = { 2, 0 };
	}
}

int main() {
	cin >> N >> M >> G >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j].first;
			if (map[i][j].first == 2) {
				possibleLand[landCnt++] = { i,j };
			}
		}
	}

	//먼저 초록색 뿌릴 땅을 선택
	green(0, 0, 0);

	cout << answer;
}