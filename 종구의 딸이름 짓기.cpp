#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;
int T, N, M;
int dx[2] = { 0,1 };
int dy[2] = { 1,0 };
vector<string> nameList;
string ans, inputStr;
string cache[2000][2000];
bool visited[2000][2000];

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;
		nameList.clear();
		ans = "";
		for (int i = 0; i < N; i++)for (int j = 0; j < M; j++)	visited[i][j] = false;

		for (int i = 0; i < N; i++) {
			cin >> inputStr;
			nameList.push_back(inputStr);
		}

		priority_queue<pair<char, pair<int, int>>,vector<pair<char, pair<int, int>>>,greater<pair<char, pair<int, int>>>> pq;
		pq.push({ nameList[0][0] , {0,0} });
		vector < pair<char, pair<int, int>>> tmp;
		while (!pq.empty()) {
			char topC = pq.top().first;
			int topI = pq.top().second.first;
			int topJ = pq.top().second.second;

			int size = pq.size();
			for(int s = 0; s < size;s++){
				char c = pq.top().first;
				int i = pq.top().second.first;
				int j = pq.top().second.second;
				pq.pop();

				if (topC == c) {
					for (int idx = 0; idx < 2; idx++) {
						int ni = i + dy[idx];
						int nj = j + dx[idx];
						if (ni >= N || nj >= M) continue;
						if (visited[ni][nj]) continue;

						visited[ni][nj] = true;
						tmp.push_back({ nameList[ni][nj],{ni,nj} });
					}
				}
			}

			ans += topC;
			for (int i = 0; i < tmp.size(); i++) pq.push(tmp[i]);
			tmp.clear();
		}

		cout << "#" << tc << " " << ans << "\n";
	}
}

