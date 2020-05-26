/*
요구사항
보드의 빈 칸에 공 하나 놓기 -> 4방향 선택하고 그 방향으로 공 계속해서 이동
장애물, 보드의 경계, 이미 공이 지나갔던 칸을 만나기 전까지 계속 이동 ->
공이 더이상 진행할 수 없을 떄 끝

제약사항
모든 빈 칸에 공이 방문한 적이 있어야 함
입력으로 주어진 보드가 장애물로만 이루어진 경우는 없음
만약, 모든 칸을 방문할 수 없다면 -1, 가능한 경로의 수 1000000개 안넘음

데이터
여러 개의 테스트 케이스 /  1 <= 세로 크기 N <= 30
1 <= 가로 크기 M <= 30 / 장애물 '*' / 빈칸 '.'

출력
각 테스트 케이스마다 모든 빈칸을 방문하는 '최소 횟수' 출력
만약, 모든 칸을 방문할 수 없다면 -1, 가능한 경로의 수 1000000개 안넘음
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
