//�������� ���̷��� M�� Ȱ�����·� ����
//Ȱ�� ���̷����� ��Ȱ�� ���̷����� �ִ� ĭ���� ���� ��Ȱ�� ���̷����� Ȱ������ ����
//��� �� ĭ�� ���̷����� �۶߸��� �ּ� �ð��� ���ϱ�
//���� ��� ��ĭ�� ���̷����� �� �۶߸��� -1 ���
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
int N, M, answer, cnt;
int map[51][51];
bool visited[51][51];
pair<int, int> selected[10];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
vector<pair<int, int>> virus;

int bfs(int cnt) {
	//Ȱ���� ���̷����� ť�� �־��ش�.
	queue<pair<int, int>> q;
	for (int i = 0; i < M; i++) {
		q.push(selected[i]);
		visited[selected[i].first][selected[i].second] = true;
	}

	int t = -1;
	while (!q.empty()) {
		t++;
		if (cnt == 0) {
			break;
		}
		int sz = q.size();
		for (int i = 0; i < sz; i++) {
			int cy = q.front().first;
			int cx = q.front().second;
			q.pop();

			for (int j = 0; j < 4; j++) {
				int ny = cy + dy[j];
				int nx = cx + dx[j];
				if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
				if (map[ny][nx] == 1) continue;
				if (visited[ny][nx]) continue;
				if (map[ny][nx] == 0) cnt--;
				q.push({ ny,nx });
				visited[ny][nx] = true;
			}
		}	
	}
	
	if (cnt != 0) t = 2500;

	return t;

}
void init() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visited[i][j] = false;
		}
	}
}
void dfs(int depth, int start) {
	//M���� ���� ���
	if (depth == M) {
		init();
		answer = min(answer, bfs(cnt));
		return;
	}

	for (int i = start; i < virus.size(); i++) {
		selected[depth] = virus[i];
		dfs(depth + 1, i + 1);
	}
}
int main() {
	answer = 2500;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) cnt++;
			if (map[i][j] == 2) virus.push_back({ i,j });
		}
	}

	//M���� �̴´�.
	dfs(0, 0);

	if (answer == 2500) cout << -1;
	else cout << answer;

	return 0;
}