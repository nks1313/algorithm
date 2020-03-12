#include <iostream>
#include <queue>
#include <utility>
using namespace std;
int T, N;
int p[1000];
double x[1000];
double y[1000];
double E;
int Find(int x) {
	if (x == p[x]) return p[x];
	return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x != y) p[y] = x;
}

void init() {
	for (int i = 0; i < N; i++) p[i] = i;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 0; i < N; i++) cin >> x[i];
		for (int i = 0; i < N; i++) cin >> y[i];
		cin >> E;
		init();
		priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> pq;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j) continue;
				double dist = (x[i] - x[j]) * (x[i] - x[j]);
				dist += (y[i] - y[j]) * (y[i] - y[j]);
				pq.push({ dist,{i,j} });
			}
		}

		double ans = 0;
		for (int i = 0; i < N - 1; i++) {
			while (!pq.empty()) {
				pair<double, pair<int, int>> curr = pq.top();
				pq.pop();
				if (Find(curr.second.first) != Find(curr.second.second)) {
					ans += curr.first;
					Union(curr.second.first, curr.second.second);
					break;
				}
			}
		}
		ans += 0.5;
		cout << "#" << tc << " " << long long(ans * E) << "\n";
	}
	return 0;
}