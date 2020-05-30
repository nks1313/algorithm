#include <iostream>
#include <algorithm>
using namespace std;

int N, answer, result[50][10];
int arr[10];
bool visited[10];
int game() {
	int score = 0;
	int start = 0;
	for (int i = 0; i < N; i++) {
		int outCnt = 0;
		bool board[5] = { false,false,false,false,false };
		
		while(true) {
			start = (start + 1) % 9;
			if (start == 0) start = 9;
			int batter = arr[start];
			int r = result[i][batter];
			board[0] = true;

			if (r > 0) {
				for (int k = 3; k >= 0; k--) {
					if (board[k]) {
						board[k] = false;
						if (k + r >= 4) {
							score++;
						}
						else {
							board[k + r] = true;
						}
					}
				}
			}
			else outCnt++;
			
			if (outCnt == 3) break;
		}
	}

	return score;
}

void setArr(int depth) {
	if (depth > 9) {
		/*for (int i = 1; i <= 9; i++) {
			cout << arr[i] << " ";
		}
		cout << "\n";*/
		answer = max(answer,game());
		return;
	}
	
	if (depth == 4) {
		setArr(depth + 1);
		return;
	}

	for (int i = 2; i <= 9; i++) {
		if (visited[i]) continue;
		visited[i] = true;
		arr[depth] = i;
		setArr(depth + 1);
		visited[i] = false;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= 9; j++) cin >> result[i][j];
	}

	visited[1] = true;
	arr[4] = 1;
	setArr(1);
	
	cout << answer << "\n";
}