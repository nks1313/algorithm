#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;
int N, M, X, from, to, T;
vector<pair<int, int>> adjList[1001];
vector<pair<int, int>> radjList[1001];
bool visited[1001];
int dist[1001];
int result[1001];
priority_queue<pair<int, int>> pq;

void go(int X, vector<pair<int, int>> adjList[1001]) {
	//pq 초기화
	while (!pq.empty()) pq.pop();
	for (int i = 1; i <= N; i++) {
		visited[i] = false; dist[i] = 0x7fffffff;
	}

	//pq에 시작점 넣고, 방문처리
	dist[X] = 0;
	pq.push({ -dist[X], X});

	while (!pq.empty()) {
		int c = pq.top().second;
		int t = -pq.top().first;
		pq.pop();
		if (visited[c]) continue;

		visited[c] = true;
		result[c] += t;

		for (int i = 0; i < adjList[c].size(); i++) {
			int n = adjList[c][i].first;
			int cost = adjList[c][i].second;
			if (!visited[n] && dist[n] > dist[c] + cost) {
				dist[n] = dist[c] + cost;
				pq.push({ -(dist[c] + cost), n });
			}
		}
		
	}
}

void solution() {
	go(X, adjList);
	go(X, radjList);
}

void input() {
	cin >> N >> M >> X;
	for (int i = 0; i < M; i++) {
		cin >> from >> to >> T;
		adjList[from].push_back({ to, T });
		radjList[to].push_back({ from, T });
	}
}

void output() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		answer = max(result[i], answer);
	}

	cout << answer << "\n";
}

int main() {
	input();
	solution();
	output();
}