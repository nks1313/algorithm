#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int N, K, answer;
vector<int> map[13][13];
int board[13][13];
pair<pair<int, int>, pair<int, int>> horse[11];
int dy[] = { 0, 0, 0, -1, 1 };
int dx[] = { 0, 1, -1, 0, 0 };

//���� 4�� �̻� ���̰ų� ���� 1000 �Ѿ�� �����ϴ� �Լ�
void solution() {
	for (int turn = 1; turn <= 1000; turn++) {
		for (int n = 1; n <= K; n++) {
			//���� ��ġ ����.
			int y = horse[n].first.first;
			int x = horse[n].first.second;
			int z = horse[n].second.first;
			int d = horse[n].second.second;
			
			int ny = y + dy[d];
			int nx = x + dx[d];

			//���� ��ġ�� ������ ����ų� �Ķ������� Ȯ���ϰ� ���� �ٲ��ش�.
			if (ny < 1 || nx < 1 || ny > N || nx > N || board[ny][nx] == 2) {
				ny -= dy[d]; nx -= dx[d];
				if (d == 1) d = 2;
				else if (d == 2) d = 1;
				else if (d == 3) d = 4;
				else d = 3;
				ny += dy[d]; nx += dx[d];
				horse[n].second.second = d;
			}

			//�ٲ� ���⵵ ���ٸ� ������ �ִ´�.
			if (ny < 1 || nx < 1 || ny > N || nx > N || board[ny][nx] == 2) {
				continue;
			}
			//���� ��ġ�� ����϶�
			else if (board[ny][nx] == 0) {
				int sz = z + 1;
				while(map[y][x].size() >= sz) {
					map[ny][nx].push_back(map[y][x][z]);
					horse[map[y][x][z]] = { {ny,nx},{ map[ny][nx].size() - 1, horse[map[y][x][z]].second.second} };
					map[y][x].erase(map[y][x].begin() + z);
				}

				if (map[ny][nx].size() >= 4) {
					answer = turn;
					return;
				}
			}
			//���� ��ġ�� �������϶�
			else if (board[ny][nx] == 1) {
				int sz = map[y][x].size();
				for (int i = sz - 1; i >= z; i--) {
					map[ny][nx].push_back(map[y][x][i]);
					horse[map[y][x][i]] = { {ny,nx},{ map[ny][nx].size() - 1, horse[map[y][x][i]].second.second}};
					map[y][x].pop_back();
				}

				if (map[ny][nx].size() >= 4) {
					answer = turn;
					return;
				}
			}
		}
	}

	answer = -1;
	return;
}
int main() {
	//�Է�
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}

	int y, x, d;
	for (int i = 1; i <= K; i++) {
		cin >> y >> x >> d;
		horse[i] = { {y,x},{0,d} };
		map[y][x].push_back(i);
	}

	solution();

	cout << answer;
}