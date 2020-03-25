#include <iostream>
using namespace std;
int N, M, K;
long long tree[(1 << 22)];
long long lazy[(1 << 22)];
long long A[1000000];
long long getTree(int node, int start, int end) {
	if (start == end) {
		return tree[node] = A[start];
	}
	else {
		return tree[node] =  getTree(node * 2, start, (start + end) / 2) + getTree(node * 2 + 1, (start + end) / 2 + 1, end);
	}
}

void update_lazy(int node, int start, int end) {
	tree[node] += lazy[node]*(end - start+1);

	if (start != end) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}

	lazy[node] = 0;
}

void add(int node, int start, int end, int i, int j, long long value) {
	if (lazy[node] != 0) update_lazy(node, start, end);
	if (i > end || j < start) return;
	
	if (start >= i && end <= j) {
		lazy[node] += value;
		update_lazy(node, start, end);
		return;
	}
	
	add(node * 2, start, (start + end) / 2, i, j, value);
	add(node * 2 + 1, (start + end) / 2 + 1, end, i, j, value);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long getSum(int node, int start, int end, int i,int j) {
	if (lazy[node] != 0) update_lazy(node, start, end);
	if (i > end || j < start) return 0;
	
	if (start >= i && end <= j) {
		return tree[node];
	}

	return getSum(node * 2, start, (start + end) / 2, i, j) + getSum(node * 2 + 1, (start + end) / 2 + 1, end, i, j);
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) cin >> A[i];
	getTree(1, 0, N - 1);

	int a, b, c, d;
	for (int i = 0; i < M + K; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			add(1, 0, N - 1, b - 1, c - 1, d);
		}
		else if (a == 2) {
			cin >> b >> c;
			cout << getSum(1, 0, N-1, b - 1, c - 1) << "\n";
		}
	}
}