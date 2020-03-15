#include <iostream>
#include <queue>
#include <utility>
#include <string>
#define MAXN 100
using namespace std;
//dist : 해당 정점까지의 최단거리를 기록하는 배열, INF값으로 초기화 해둔다.
//checked : 해당 정점의 최단거리가 확정되었다는 것을 표시하는 배열
//w : 해당 정점까지의 가중치를 저장하는 배열
//dy, dx : 인접 정점으로 진출하는 데 사용되는 배열
int T, N;
int dist[MAXN][MAXN];
bool checked[MAXN][MAXN];
int w[MAXN][MAXN];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

//init() : 초기화 하는 함수입니다.
void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = INT32_MAX;
			checked[i][j] = false;
		}
	}
}

//input() : 입력하는 함수 입니다.
void input() {
	cin >> N;
	string tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		for (int j = 0; j < N; j++) w[i][j] = tmp[j] - '0';
	}
}

//dijkstra() : dijkstra 알고리즘을 활용해서 (0,0)부터 모든 정점까지의 최단 거리를 구하는 함수입니다.
//우선순위 큐를 활용하여 각 정점으로의 최단거리를 계속 갱신해줍니다.
void dijkstra() {
	//dist[0][0]을 0으로 초기화 시켜주고
	//(dist, (y, x))값을 우선순위큐 pq에 넣어줍니다.
	priority_queue<pair<int, pair<int, int>>> pq;
	dist[0][0] = 0;
	pq.push({ 0,{0,0} });
	
	//pq에 원소가 존재하는 동안 반복합니다.
	while (!pq.empty()) {
		int y = pq.top().second.first;
		int x = pq.top().second.second;
		pq.pop();

		//현재 정점이 (N-1,N-1)일 경우 이미 (N-1,N-1)정점이 갱신된 것이므로 반복문을 빠져나갑니다.
		if (y == N - 1 && x == N - 1) break;

		//현재 정점이 이미 최단거리가 갱신된 경우라면 반복을 다음으로 넘깁니다.
		if (checked[y][x]) continue;

		//현재 정점을 최단거리가 갱신되었다고 표시해줍니다.
		checked[y][x] = true;

		//동->남->서->북 순으로 다음 정점에 대해서 진출할 수 있는 정점인지 타당성을 체크하고
		//타당하다면 진출해줍니다.
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				continue;

			//다음 정점의 현재 기록되어 있는 dist값보다 현재 정점의 dist + 가중치가 더 작다면
			//갱신해주고 우선순위 큐에 넣어줍니다.
			if (dist[ny][nx] > dist[y][x] + w[ny][nx]) {
				dist[ny][nx] = dist[y][x] + w[ny][nx];
				pq.push({ -dist[ny][nx],{ny,nx} });
			}
		}
	}
}

//출력하는 함수입니다.
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
		output(tc);
	}
}