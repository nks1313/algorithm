#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
using namespace std;
int T, K;
map<string, vector<string>> m;
map<string, bool> visited;
string ans;
int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> K;
		string str1, str2;
		for (int k = 0; k < K; k++) {
			cin >> str1 >> str2;
			m[str1].push_back(str2);
			m[str2].push_back(str1);
		}

		for (auto e : m) {
			//아직 방문하지 않았다면
			bool flag = false;
			if (visited.find(e.first) == visited.end()) {
				queue<string> q;
				visited[e.first] = true;
				q.push(e.first);

				while (!q.empty()) {
					string cur = q.front();
					bool state = visited[cur];
					q.pop();

					for (auto s : m[cur]) {
						if (visited.find(s) == visited.end()) {
							visited[s] = ~state;
							q.push(s);
						}
						else {
							if (visited[s] == state) {
								ans = "NO";
								flag = true;
								break;
							}
						}
					}
					if (flag) break;
				}
			}
			if (flag) break;
			ans = "YES"
		}


	}
}