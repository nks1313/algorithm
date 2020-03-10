#include <iostream>
#include <queue>
#include <utility>
#include <cmath>
#include <algorithm>
#define MAX_VALUE 300
using namespace std;

int T, N, value, pCnt, sCnt, idx0, idx1, ans;
int dist[10][2];
pair<int, int> people[10];
pair<int, int> stair[2];
int group[10][2];
int timeArr[2];

int main() {
	ios_base::sync_with_stdio;
	cin.tie(0);
	

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		pCnt = sCnt = 0;
		ans = MAX_VALUE;
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> value;
				if (value == 1) {
					people[pCnt++] = { i,j };
				}
				else if (value > 1) {
					timeArr[sCnt] = value;
					stair[sCnt++] = { i,j };
				}
			}
		}

		//각 계단과의 거리를 배열에 저장
		for (int i = 0; i < pCnt; i++) {
			for (int j = 0; j < sCnt; j++) {
				dist[i][j] = abs(people[i].first - stair[j].first) + abs(people[i].second - stair[j].second);
			}
		}

		for (int i = 0; i < (1 << pCnt); i++) {
			//먼저 그룹을 두개로 나눈다.
			idx1 = idx0 = 0;
			for (int j = 0; j < pCnt; j++) {
				if (i & (1 << j)) {
					//그룹 1에 넣는다.
					group[idx0++][0] = j;
				}
				else {
					//그룹 2에 넣는다.
					group[idx1++][1] = j;
				}
			}

			//우선순위 큐에 넣어줌
			priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq[2];
			for (int j = 0; j < idx0; j++) {
				pq[0].push({ dist[group[j][0]][0],group[j][0]});
			}
			for (int j = 0; j < idx1; j++) {
				pq[1].push({ dist[group[j][1]][1],group[j][1] });
			}

			int tempAns = 0;
			for (int j = 0; j < 2; j++) {
				if (pq[j].size() == 0) continue;
				if (pq[j].size() <= 3) {
					int next;
					while (!pq[j].empty()) {
						next = pq[j].top().first;
						pq[j].pop();
					}
					tempAns = max(tempAns, next + 1 + timeArr[j]);
				}
				else {
					//3개 먼저 뺀다.
					int temp[3];
					for (int k = 0; k < 3; k++) {
						temp[k] = pq[j].top().first + 1 + timeArr[j];
						pq[j].pop();
					}

					int idx = 0;
					while (!pq[j].empty()) {
						int next = pq[j].top().first;
						if (next < temp[idx]) {
							temp[idx] = temp[idx] + timeArr[j];
						}
						else {
							temp[idx] = next + 1 + timeArr[j];
						}
						pq[j].pop();
						tempAns = max(tempAns, temp[idx]);
						idx = (idx + 1) % 3;
					}
				}
			}

			cout << tempAns << endl;
			ans = min(ans, tempAns);
		}

		cout << "#" << tc << " " << ans << "\n";
	}
	system("pause");
}