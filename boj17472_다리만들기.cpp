#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
int N, M;
int p[7];
int map[10][10];
bool visited[10][10];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int distArr[7][7];
vector<pair<int, pair<int, int>>>dist;

int Find(int x) {
	if (x == p[x]) return x;
	return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if(x != y) p[y] = x;
}

void printMap() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cout << map[y][x] << " ";
		}
		cout << endl;
	}
}

int main() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}

	//전처리
	//가장자리의 좌표와 방향을 설정해주고
	//각각의 섬을 numbering 해준다.
	queue < pair<pair<int, int>, int>> totalQ;
	int num = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (!map[y][x]) continue;
			if (visited[y][x]) continue;
			num++;

			queue<pair<int, int>> q;
			q.push({ y,x });
			visited[y][x] = true;
			map[y][x] = num;
			while (!q.empty()) {
				int currY = q.front().first;
				int currX = q.front().second;
				q.pop();

				for (int k = 0; k < 4; k++) {
					int nextY = currY + dy[k];
					int nextX = currX + dx[k];
					if (nextY >= N || nextY < 0 || nextX >= M || nextX < 0) continue;
					if (!map[nextY][nextX]) {
						totalQ.push({ {currY,currX} ,k });
					}
					else {
						if (visited[nextY][nextX]) continue;

						visited[nextY][nextX] = true;
						q.push({ nextY, nextX });
						map[nextY][nextX] = num;
					}
				}
			}
		}
	}

	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			distArr[i][j] = 100;
		}
	}

	//그래프 만들기
	while (!totalQ.empty()) {
		int currY = totalQ.front().first.first;
		int currX = totalQ.front().first.second;
		int currD = totalQ.front().second;
		totalQ.pop();
		int u = map[currY][currX];
		int w = 0;
		//cout << currY << " " << currX << endl;
		int nextY = currY + dy[currD];
		int nextX = currX + dx[currD];

		while (nextY < N && nextY >= 0 && nextX < M && nextX >= 0) {
			if (map[nextY][nextX] != 0) {
				int v = map[nextY][nextX];
				if (u != v && w != 1) {
					distArr[u][v] = min(distArr[u][v], w);
					distArr[v][u] = distArr[u][v];
				}
				break;
			}

			w++;
			nextY += dy[currD];
			nextX += dx[currD];
		}
	}

	for (int i = 1; i <= num; i++) {
		for (int j = i + 1; j <= num; j++) {
			if(distArr[i][j] != 100)
				dist.push_back({ distArr[i][j],{i,j} });
		}
	}

	sort(dist.begin(), dist.end());
	for (int i = 1; i <= num; i++) p[i] = i;


	int ans = 0;
	for (int i = 0; i < dist.size(); i++) {
		int w = dist[i].first;
		int u = dist[i].second.first;
		int v = dist[i].second.second;

		if (Find(u) != Find(v)) {
			Union(u, v);
			ans += w;
		}
	}
	
	for (int i = 1; i < num; i++) {
		if (Find(i) != Find(i + 1)) {
			ans = -1;
			break;
		}
	}
	cout << ans << endl;

	system("pause");
}