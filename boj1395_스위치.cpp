#include <iostream>
using namespace std;
int N, M, K;
int tree[(1 << 18)];
int lazy[(1 << 18)];
void update_lazy(int node, int start, int end) {
	
	if (lazy[node] > 0) {
		
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] &= 1;
		if (lazy[node] > 0) {
			tree[node] = (end - start + 1) - tree[node];
		}

		lazy[node] = 0;
	}
}
void update(int node, int i, int j, int start, int end) {
	update_lazy(node, start, end);

	if (end < i || start > j) return;
	
	if (start >= i && end <= j) {
		lazy[node] += 1;
		update_lazy(node, start, end);
		return;
	}

	update(node * 2, i, j, start, (start + end) / 2);
	update(node * 2 + 1, i, j, (start + end) / 2 + 1, end);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
int getSum(int node, int i, int j, int start, int end) {
	update_lazy(node, start, end);

	if (end < i || start > j) return 0;
	if (start >= i && end <= j) {
		return tree[node];
	}

	return getSum(node * 2, i, j, start, (start + end) / 2) + getSum(node * 2 + 1, i, j, (start + end) / 2 + 1, end);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> M;
	int o, s, t;
	for (int i = 0; i < M; i++) {
		cin >> o >> s >> t;
		//반전
		if (!o) {
			update(1, s, t, 1, N);
		}
		//스위치 개수
		else {
			cout << getSum(1, s, t, 1, N) << "\n";
		}
	}
}