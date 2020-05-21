/*
N명의 학생들 중 오고 가는데 가장 많은 시간을 소비하는 학생은?
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <utility>
#define INF 1000000
using namespace std;

int N, M, X;
int adj[1001][1001];
priority_queue<pair<int,int>> dist;
int result[1001];
bool visited[1001];
int main() {
	cin >> N >> M >> X;
	
	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) adj[i][j] = INF;
	for (int i = 1; i <= N; i++) adj[i][i] = 0;

	int x, y, t;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> t;
		adj[x][y] = t;
	}

	//X에서 가는 것
	for (int i = 1; i <= N; i++) if( i != X) dist.push({ -adj[X][i], i });
	visited[X] = true;

	for (int i = 1; i <= N - 1; i++) {
		int val = 0;
		int idx = 0;
		while (!dist.empty()) {
			val = -dist.top().first;
			idx = dist.top().second;
			dist.pop();
			if (!visited[idx]) break;
		}

		
		result[idx] += val;
		visited[idx] = true;

		for (int j = 1;  j <= N; j++) {
			if (visited[j]) continue;
			dist.push({-(val + adj[idx][j]),j});
		}
	}

	//X까지 가는 것
	memset(visited, false, sizeof(visited));
	while (!dist.empty()) dist.pop();

	for (int i = 1; i <= N; i++) if (i != X) dist.push({ -adj[i][X], i });
	visited[X] = true;

	for (int i = 1; i <= N - 1; i++) {
		int val = 0;
		int idx = 0;
		while (!dist.empty()) {
			val = -dist.top().first;
			idx = dist.top().second;
			dist.pop();
			if (!visited[idx]) break;
		}


		result[idx] += val;
		visited[idx] = true;

		for (int j = 1; j <= N; j++) {
			if (visited[j]) continue;
			dist.push({ -(val + adj[j][idx]),j });
		}
	}

	int answer = 0;
	for (int i = 1; i <= N; i++) answer = max(answer, result[i]);

	cout << answer;
}