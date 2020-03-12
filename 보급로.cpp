#include <iostream>
#include <string>
#define QUEUE_SIZE 30000
using namespace std;

struct Node {
	int y;
	int x;
	int dist;
};
int T, N, front, rear;
int map[100][100];
int cache[100][100];// INT_MAX로 초기화 해준다.
int dy[4] = { 0,1, 0, -1 };
int dx[4] = { 1,0 ,-1, 0};
Node queue[QUEUE_SIZE];

void solve() {
	rear = (rear + 1) % QUEUE_SIZE;
	queue[rear] = { 0, 0, 0 };
	cache[0][0] = 0;
	while (front != rear) {
		front = (front + 1) % QUEUE_SIZE;
		Node curr = queue[front];
		int y = curr.y;
		int x = curr.x;
		int dist = curr.dist;
		if (dist != cache[y][x]) continue;
		//cout << y << " " << x << " " << dist<< "\n";
		for (int i = 0; i < 2; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (cache[y][x] + map[ny][nx] >= cache[ny][nx]) continue;
			//cout << 1 << endl;
			cache[ny][nx] = cache[y][x] + map[ny][nx];
			rear = (rear + 1) % QUEUE_SIZE;
			queue[rear] = { ny, nx, cache[ny][nx] };
		}
	}
}

void init() {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) cache[i][j] = INT32_MAX;
	front = rear = -1;
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();

		cin >> N;
		string input;
		for (int i = 0; i < N; i++) {
			cin >> input;
			for (int j = 0; j < N; j++) {
				map[i][j] = input[j] - '0';
			}
		}

		solve();

		cout << "#" << tc << " " << cache[N - 1][N - 1] << "\n";
	}
}
