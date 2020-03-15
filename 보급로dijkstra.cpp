#include <iostream>
#include <queue>
#include <utility>
#include <string>
#define MAXN 100
using namespace std;
//dist : �ش� ���������� �ִܰŸ��� ����ϴ� �迭, INF������ �ʱ�ȭ �صд�.
//checked : �ش� ������ �ִܰŸ��� Ȯ���Ǿ��ٴ� ���� ǥ���ϴ� �迭
//w : �ش� ���������� ����ġ�� �����ϴ� �迭
//dy, dx : ���� �������� �����ϴ� �� ���Ǵ� �迭
int T, N;
int dist[MAXN][MAXN];
bool checked[MAXN][MAXN];
int w[MAXN][MAXN];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

//init() : �ʱ�ȭ �ϴ� �Լ��Դϴ�.
void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = INT32_MAX;
			checked[i][j] = false;
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

//dijkstra() : dijkstra �˰����� Ȱ���ؼ� (0,0)���� ��� ���������� �ִ� �Ÿ��� ���ϴ� �Լ��Դϴ�.
//�켱���� ť�� Ȱ���Ͽ� �� ���������� �ִܰŸ��� ��� �������ݴϴ�.
void dijkstra() {
	//dist[0][0]�� 0���� �ʱ�ȭ �����ְ�
	//(dist, (y, x))���� �켱����ť pq�� �־��ݴϴ�.
	priority_queue<pair<int, pair<int, int>>> pq;
	dist[0][0] = 0;
	pq.push({ 0,{0,0} });
	
	//pq�� ���Ұ� �����ϴ� ���� �ݺ��մϴ�.
	while (!pq.empty()) {
		int y = pq.top().second.first;
		int x = pq.top().second.second;
		pq.pop();

		//���� ������ (N-1,N-1)�� ��� �̹� (N-1,N-1)������ ���ŵ� ���̹Ƿ� �ݺ����� ���������ϴ�.
		if (y == N - 1 && x == N - 1) break;

		//���� ������ �̹� �ִܰŸ��� ���ŵ� ����� �ݺ��� �������� �ѱ�ϴ�.
		if (checked[y][x]) continue;

		//���� ������ �ִܰŸ��� ���ŵǾ��ٰ� ǥ�����ݴϴ�.
		checked[y][x] = true;

		//��->��->��->�� ������ ���� ������ ���ؼ� ������ �� �ִ� �������� Ÿ�缺�� üũ�ϰ�
		//Ÿ���ϴٸ� �������ݴϴ�.
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				continue;

			//���� ������ ���� ��ϵǾ� �ִ� dist������ ���� ������ dist + ����ġ�� �� �۴ٸ�
			//�������ְ� �켱���� ť�� �־��ݴϴ�.
			if (dist[ny][nx] > dist[y][x] + w[ny][nx]) {
				dist[ny][nx] = dist[y][x] + w[ny][nx];
				pq.push({ -dist[ny][nx],{ny,nx} });
			}
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
		dijkstra();
		output(tc);
	}
}