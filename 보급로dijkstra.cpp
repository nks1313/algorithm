#include <iostream>
#include <queue>
#include <utility>
#include <string>
#define MAXN 100
using namespace std;
int T, N;
int dist[MAXN][MAXN];
bool checked[MAXN][MAXN];
int w[MAXN][MAXN];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = INT32_MAX;
			checked[i][j] = false;
		}
	}
}

void input() {
	cin >> N;
	string tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		for (int j = 0; j < N; j++) w[i][j] = tmp[j] - '0';
	}
}

void dijkstra() {
	priority_queue<pair<int, pair<int, int>>> pq;
	dist[0][0] = 0;
	checked[0][0] = true;
	while(!pq.empty()) {
		int y = pq.top().second.first;
		int x = pq.top().second.second;
		pq.pop();

		if (checked[y][x]) continue;
		checked[y][x] = true;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				continue;
			if (dist[ny][nx] > dist[y][x] + w[ny][nx]) {
				dist[ny][nx] = dist[y][x] + w[ny][nx];
				pq.push({ -dist[ny][nx],{ny,nx} });
			}
		}
	}
}

void output(int tc) {
	cout << "#" << tc << " " << dist[N - 1][N - 1] << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();
		init();
		dijkstra();
		print();
		output(tc);
	}
}