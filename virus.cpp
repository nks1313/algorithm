#pragma (disable : 4996)
#include <stdio.h>
int n, m, x, y;
int p[101];

int Find(int x) {
	if (p[x] == x) {
		return x;
	}

	return p[x] = Find(p[x]);
}
void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if(x != y) p[y] = x;
}

int main() {
	scanf_s("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) p[i] = i;
	while (m-- > 0) {
		scanf_s("%d %d", &x, &y);
		Union(x, y);
	}

	int root = Find(1);
	int ans = 0;
	for (int i = 2; i <= n; i++) if (Find(i) == root) ans++;

	printf("%d", ans);

	return 0;
}
