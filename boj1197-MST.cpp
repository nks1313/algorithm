#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define MAXV 10001
#define MAXE 100001
using namespace std;
int V, E, u, v, c;
int p[MAXV];
vector<pair<int, pair<int, int>>> dist;

int Find(int x) {
	if (x == p[x]) return x;
	return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if(x != y) p[y] = x;
}

int main() {

	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> c;
		dist.push_back({ c,{u,v} });
	}
	sort(dist.begin(), dist.end());
	cout << 1 << endl;
	for (int i = 0; i <= V; i++) p[i] = i;
	int ans = 0;
	for (int i = 0; i < dist.size();i++) {
		c = dist[i].first;
		u = dist[i].second.first;
		v = dist[i].second.second;
		if (Find(u) != Find(v)) {
			Union(u, v);
			ans += c;
		}
	}
	cout << 3 << endl;
	cout << ans << '\n';
	system("pause");
	return 0;
}