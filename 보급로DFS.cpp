#include <iostream>
#include <queue>
#include <utility>
#include <string>
#define MAXN 100
using namespace std;
//dist : �ش� ���������� �ִܰŸ��� ����ϴ� �迭, INF������ �ʱ�ȭ �صд�.
//w : �ش� ���������� ����ġ�� �����ϴ� �迭
//dy, dx : ���� �������� �����ϴ� �� ���Ǵ� �迭
int T, N, ans;
int dist[MAXN][MAXN];
int w[MAXN][MAXN];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

//init() : �ʱ�ȭ �ϴ� �Լ��Դϴ�.
void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//dist���� int���� �ִ����� �������ݴϴ�.
			dist[i][j] = INT32_MAX;
		}
	}
}

//input() : �Է��ϴ� �Լ� �Դϴ�.
void input() {
	cin >> N;
	string tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		for (int j = 0; j < N; j++) w[i][j] = tmp[j] - '0';
	}
}

//DFS() : DFS�� �����ϴ� �Լ��Դϴ�.
void DFS(int y, int x) {
	//���� ���������� �Ÿ��� �̹� ���� (N-1,N-1)������ �Ÿ����� ũ�ٸ�
	//���̻� �� �κ��� �� �ʿ䰡 �����Ƿ� �ٷ� return ���ݴϴ�.
	if (dist[y][x] > dist[N-1][N-1]) return;

	//(N-1,N-1)���� �����Ͽ��ٸ� return ���ݴϴ�.
	if (y == N - 1 && x == N - 1) return;


	//���������� �� -> �� -> �� -> �� ������ Ž���մϴ�.
	//���� ����ġ�� �������� �������� �ִܰŸ��� ã�����ؼ�
	//(0,0)���� (N-1,N-1)�� �������� x��ǥ y��ǥ�� �����ϴ�
	//��, ������ �ۿ� ���� ������ �������� �����Ƿ�
	//�̸� greedy�� ������� �����Ͽ� ���� ��, �� �������� �������ݴϴ�.
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N)
			continue;

		//���� ������ ���� ����� dist���� ���� ������ dist + ����ġ���� ũ�ٸ� �������ְ�
		//���� �������� �����մϴ�.
		if (dist[ny][nx] > dist[y][x] + w[ny][nx]) {
			dist[ny][nx] = dist[y][x] + w[ny][nx];
			DFS(ny, nx);
		}
	}

}

//����ϴ� �Լ��Դϴ�.
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