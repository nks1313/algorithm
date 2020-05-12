#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
using namespace std;
int T, N, answer;
vector<pair<int, int>> peoples;
vector<pair<int, int>> stairs;
vector<int> dist[2];
vector<int> stairVal;

void solution(int selected) {
	priority_queue<int> pq[2];
	for (int i = 0; i < peoples.size(); i++) {
		if (selected & (1 << i)) pq[0].push((-1) * dist[0][i]);
		else pq[1].push((-1) * dist[1][i]);
	}
	int cnt[30];
	memset(cnt, 0, sizeof(cnt));
	int end1 = 0;
	while (!pq[0].empty()) {
		int d = pq[0].top()*(-1); pq[0].pop();
		int count = 0;
		int i = d + 2;
		for (; count < stairVal[0]; i++) {
			if (cnt[i] >= 3) continue;
			count++;
			cnt[i]++;
		}
		end1 = i;
	}

	memset(cnt, 0, sizeof(cnt));
	int end2 = 0;
	while (!pq[1].empty()) {
		int d = pq[1].top() * (-1); pq[1].pop();
		int count = 0;
		int i = d + 2;
		for (; count < stairVal[1]; i++) {
			if (cnt[i] >= 3) continue;
			count++;
			cnt[i]++;
		}
		end2 = i;
	}

	answer = min(answer, max(end1, end2));
	if (max(end1, end2) == 19) {
		cout << end1 << "\n";
		cout << end2 << "\n";
		cout << selected << "\n";
	}
}
void combination(int n, int depth, int num, int selected) {
	solution(selected);
	
	for (int i = num; i < n; i++) {
		combination(n, depth + 1, i + 1, selected | (1 << i));
	}
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		answer = 0x7fffffff;
		peoples.clear(); stairs.clear(); dist[0].clear(); dist[1].clear(); stairVal.clear();

		cin >> N;
		int num;

		for(int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
			cin >> num;
			if (num == 1) peoples.push_back({ i,j });
			else if (num >= 2) {
				stairVal.push_back(num);
				stairs.push_back({ i,j });
			}
		}

		//distance °è»ê
		for (int i = 0; i < stairs.size(); i++) for(int j = 0; j < peoples.size(); j++) {
			dist[i].push_back(abs(stairs[i].first - peoples[j].first) + abs(stairs[i].second - peoples[j].second));
		}

		combination(peoples.size() , 0, 0, 0);
		
		cout << "#" << tc << " " << answer << "\n";
	}
}

