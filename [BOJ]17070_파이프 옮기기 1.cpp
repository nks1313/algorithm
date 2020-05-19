/*
요구사항
N*N / (r,c) / 행렬 번호 1부터 시작
파이프 총 3방향 

데이터
3 <= N <= 16 / 빈칸 0, 벽 1
*/
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
int N, answer;
int map[17][17];
bool range(int y, int x) {
	if (y < 1 || x < 1 || y > N || x > N) return false;
	return true;
}
bool check(int y, int x, int status) {
	int ny, nx;
	if (status == 0) {
		ny = y; nx = x + 1;
		if (!range(ny, nx) || map[ny][nx] == 1) return false;
	}
	else if (status == 1) {
		ny = y + 1; nx = x;
		if (!range(ny, nx) || map[ny][nx] == 1) return false;
	}
	else {
		ny = y + 1; nx = x + 1;
		if (!range(ny, nx) || map[ny][nx] == 1 || !range(ny - 1, nx) || map[ny - 1][nx] == 1
			|| !range(ny, nx - 1) || map[ny][nx - 1] == 1) return false;
	}
	return true;
}
void solution(int y,int x,int status) {
	if (y == N && x == N) {
		answer++;
		return;
	}

	if (status == 0) {
		if (check(y, x, 0)) solution(y, x + 1, 0);
		if (check(y, x, 2)) solution(y + 1, x + 1, 2);
	}
	else if (status == 1) {
		if (check(y, x, 1)) solution(y + 1, x, 1);
		if (check(y, x, 2)) solution(y + 1, x + 1, 2);
	}
	else {
		if (check(y, x, 0)) solution(y, x + 1, 0);
		if (check(y, x, 1)) solution(y + 1, x, 1);
		if (check(y, x, 2)) solution(y + 1, x + 1, 2);
	}
}
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) cin >> map[i][j];

	solution(1,2,0);
	cout << answer << "\n";
}