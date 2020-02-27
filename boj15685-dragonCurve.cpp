#include <iostream>
#include <vector>
using namespace std;
int N, ans, x, y, d, g, currG;
int dy[4] = { 0,-1,0,1 };
int dx[4] = { 1,0,-1,0 };
bool visited[101][101];
vector<int> DC;

int main() {
	cin >> N;
	
	while (N-- > 0) {
		cin >> x >> y >> d >> g;
		
		DC.clear();
		currG = 0;
		visited[y][x] = true;
		y += dy[d];	x += dx[d];
		visited[y][x] = true;
		DC.push_back(d);

		while (currG < g) {
			int sz = DC.size();
			for (int i = sz - 1; i >= 0; i--) {
				d = (DC[i] + 1) % 4;
				y += dy[d];	x += dx[d];
				visited[y][x] = true;
				DC.push_back(d);
			}
			currG++;
		}
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (visited[i][j] && visited[i + 1][j] && visited[i][j + 1] && visited[i + 1][j + 1]) ans++;
		}
	}

	cout << ans << endl;
	system("pause");
	return 0;
}