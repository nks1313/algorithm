#include <iostream>
#include <queue>
#include <utility>
#include <string>
#define MAXN 100
using namespace std;
//dist : 해당 정점까지의 최단거리를 기록하는 배열, INF값으로 초기화 해둔다.
//w : 해당 정점까지의 가중치를 저장하는 배열
//dy, dx : 인접 정점으로 진출하는 데 사용되는 배열
int T, N, ans;
int dist[MAXN][MAXN];
int w[MAXN][MAXN];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

//init() : 초기화 하는 함수입니다.
void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//dist값을 int형의 최댓값으로 설정해줍니다.
			dist[i][j] = INT32_MAX;
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

//DFS() : DFS를 수행하는 함수입니다.
void DFS(int y, int x) {
	//현재 정점까지의 거리가 이미 계산된 (N-1,N-1)까지의 거리보다 크다면
	//더이상 뒷 부분은 볼 필요가 없으므로 바로 return 해줍니다.
	if (dist[y][x] > dist[N-1][N-1]) return;

	//(N-1,N-1)까지 도달하였다면 return 해줍니다.
	if (y == N - 1 && x == N - 1) return;


	//인접정점을 동 -> 남 -> 서 -> 북 순서로 탐색합니다.
	//보통 가중치가 존재하지 않을때는 최단거리를 찾기위해서
	//(0,0)에서 (N-1,N-1)로 가기위해 x좌표 y좌표가 증가하는
	//동, 남으로 밖에 다음 정점을 진행하지 않으므로
	//이를 greedy한 방식으로 생각하여 먼저 동, 남 방향으로 진행해줍니다.
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N)
			continue;

		//다음 정점의 현재 저장된 dist값이 현재 정점의 dist + 가중치보다 크다면 갱신해주고
		//다음 정점으로 진출합니다.
		if (dist[ny][nx] > dist[y][x] + w[ny][nx]) {
			dist[ny][nx] = dist[y][x] + w[ny][nx];
			DFS(ny, nx);
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

		dist[0][0] = 0;
		DFS(0, 0);
		output(tc);
	}
}