/*
�䱸����
������ �� ĭ�� �� �ϳ� ���� -> 4���� �����ϰ� �� �������� �� ����ؼ� �̵�
��ֹ�, ������ ���, �̹� ���� �������� ĭ�� ������ ������ ��� �̵� ->
���� ���̻� ������ �� ���� �� ��

�������
��� �� ĭ�� ���� �湮�� ���� �־�� ��
�Է����� �־��� ���尡 ��ֹ��θ� �̷���� ���� ����
����, ��� ĭ�� �湮�� �� ���ٸ� -1, ������ ����� �� 1000000�� �ȳ���

������
���� ���� �׽�Ʈ ���̽� /  1 <= ���� ũ�� N <= 30
1 <= ���� ũ�� M <= 30 / ��ֹ� '*' / ��ĭ '.'

���
�� �׽�Ʈ ���̽����� ��� ��ĭ�� �湮�ϴ� '�ּ� Ƚ��' ���
����, ��� ĭ�� �湮�� �� ���ٸ� -1, ������ ����� �� 1000000�� �ȳ���
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int N, M, answer;
string str[30];
bool visited[30][30];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

bool check() {
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
		if (str[i][j] == '.' && !visited[i][j]) return false;
	}
	return true;
}

void dfs(int y, int x, int cnt, int d) {
	if (d == -1) {
		int four = 0;
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i], nx = x + dx[i];
			if (ny >= 0 && nx >= 0 && ny < N && nx < M && str[ny][nx] == '.' && !visited[ny][nx]) {
				visited[ny][nx] = true;
				dfs(ny, nx, cnt + 1, i);
				visited[ny][nx] = false;
			}
			else four++;
		}

		if (four == 4) {
			if (check()) {
				answer = 0;
			}
		}
		return;
	}

	int ny = y + dy[d], nx = x + dx[d];

	if (ny >= 0 && nx >= 0 && ny < N && nx < M && str[ny][nx] == '.' && !visited[ny][nx]) {
		visited[ny][nx] = true;
		dfs(ny, nx, cnt, d);
		visited[ny][nx] = false;
		return;
	}
	
	int three = 0;
	for (int i = 0; i < 4; i++) {
		if (i == d) continue;
		int ny = y + dy[i], nx = x + dx[i];
		if (ny >= 0 && nx >= 0 && ny < N && nx < M && str[ny][nx] == '.' && !visited[ny][nx]) {
			visited[ny][nx] = true;
			dfs(ny, nx, cnt + 1, i);
			visited[ny][nx] = false;
		}
		else three++;
	}

	if (three == 3) {
		if (check()) {
			answer = min(cnt, answer);
		}
	}
}

int main() {
	int tc = 0;
	while (cin >> N >> M) {
		if (cin.eof() == true) {
			break;
		}

		
		for (int i = 0; i < N; i++) {
			cin >> str[i];
		}

		answer = 0x7fffffff;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (str[i][j] == '*') continue;
				visited[i][j] = true;
				dfs(i, j, 0, -1);
				visited[i][j] = false;
		
			}
		}
		if (answer == 0x7fffffff) {
			cout << "Case " << ++tc << ": " << -1 << "\n";
			continue;
		}
		cout << "Case " << ++tc << ": " << answer << "\n";
	}
}
