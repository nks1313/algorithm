/*
제한사항
1. 구역을 두 개의 선거구, 각 구역은 두 선거구 중 하나에 포함되어야..
2. 선거구는 구역을 적어도 하나 포함해야 함
3. 한 선거구에 포함된 구역은 모두 연결 되어야 한다.
4. 인접한 구역이 없을 수도 있다.
5. 두 선거구로 나눌 수 없는 경우에는 -1을 출력한다.

구해야 하는 것
두 선거구의 인구 차이의 최솟값
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N, answer;
int p[11];
bool visited[11];
vector<vector<int>> adj;
vector<int> teamA;
vector<int> teamB;
void init() {
	for (int i = 1; i <= N; i++) visited[i] = false;
}

void BFS() {
	int Acnt = teamA.size();
	int Bcnt = teamB.size();
	int Asum = 0;
	int Bsum = 0;
	queue<int> q;
	//먼저 teamA부터 BFS
	q.push(teamA[0]);
	visited[teamA[0]] = true;
	
	Acnt--;
	Asum += p[teamA[0]];
	if (Acnt != 0) {
		while (!q.empty()) {
			bool flag = false;

			int curr = q.front();
			q.pop();

			for (int i = 0; i < adj[curr].size(); i++) {
				int next = adj[curr][i];
				for (int j = 1; j < teamA.size(); j++) {
					if (teamA[j] == next && !visited[next]) {
						q.push(next);
						visited[next] = true;
						
						Acnt--;
						Asum += p[next];
						break;
					}
				}
				if (Acnt == 0) {
					break;
				}

			}
			if (Acnt == 0) break;
		}
	}
	if (Acnt != 0) return;


	//그리고 teamB BFS
	while (!q.empty()) q.pop();

	q.push(teamB[0]);
	visited[teamB[0]] = true;

	Bcnt--;
	Bsum += p[teamB[0]];
	if (Bcnt != 0) {
		while (!q.empty()) {
			bool flag = false;

			int curr = q.front();
			q.pop();

			for (int i = 0; i < adj[curr].size(); i++) {
				int next = adj[curr][i];
				for (int j = 1; j < teamB.size(); j++) {
					if (teamB[j] == next && !visited[next]) {
						q.push(next);
						visited[next] = true;

						Bcnt--;
						Bsum += p[next];
						break;
					}
				}
				if (Bcnt == 0) {
					break;
				}

			}
			if (Bcnt == 0) break;
		}
	}
	if (Bcnt != 0) return;

	answer = min(answer, abs(Asum - Bsum));
}

int main() {
	answer = 100 * 10 + 1;
	
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> p[i];

	vector<int> a;
	adj.push_back(a);

	int cnt = 0, adjNode;
	for (int i = 1; i <= N; i++) {
		cin >> cnt;
		vector<int> tmp;
		for (int j = 1; j <= cnt; j++) {
			cin >> adjNode;
			tmp.push_back(adjNode);
		}
		adj.push_back(tmp);
	}

	for (int i = 1; i < (1 << (N - 1)); i++) {
		teamA.clear();	teamB.clear();
		teamA.push_back(1);
		for (int j = 0; j < N - 1; j++) {
			//비트가 1이면 B팀에 넣어줌
			if (i & (1 << j)) {
				teamB.push_back(j + 2);
			}
			//비트가 0이면 A팀에 넣어줌
			else {
				teamA.push_back(j + 2);
			}
		}

		init();
		BFS();
	}

	if (answer == 100 * 10 + 1) cout << -1;
	else cout << answer;
}