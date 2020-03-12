#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
struct Node {
	int s;
	int e;
	int val;
};
int n, m, a, b;
int arr[100000];
int tree[300000];
void getTree(int node ,int s, int e) {
	if (s == e) {
		tree[node] = arr[s];
	}

	getTree(node << 1, s, (s + e) >> 1 );
	getTree((node << 1) | 1, ((s + e) >> 1) + 1, e);
	tree[node]  = min(tree[node << 1], tree[(node << 1) | 1]);
}
int getMin(int node,int s, int e, int a, int b) {
	//cout << node << "规巩" << endl;
	if (b < s || a > e) return -1;
	if (s >= a && e <= b) return tree[node];

	int m1 = getTree(node << 1, s , (s+e) , a , b);
	int m2 = getTree((node << 1) | 1, a, b);
	if (m1 == -1) return m2;
	if (m2 == -1) return m1;
	else return min(m1, m2);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	//飘府 备己
	getTree(1, 0, n - 1);

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--; b--;
		cout << getMin(1, a, b) << "\n";
	}

	system("pause");
}