#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define MAXN 500000
using namespace std;

int N, poten, base;
int tree[(1 << 20)];
int ans[MAXN];
vector<pair<int,int>> v;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> poten;
		v.push_back({ poten,i });
	}
}
int query(int left, int right) {
	int ret = 0;
	while (left < right) {
		if (left & 1) ret += tree[left++];
		if (!(right & 1)) ret += tree[right--];
		left >>= 1;	right >>= 1;
	}
	if (left == right) ret += tree[left];
	return ret;
}
void update(int idx) {
	tree[idx] = 1;
	while (idx >>= 1) {
		tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
	}
}
void solve() {
	//��� �Ƿ´�� ������ �ؼ� ���� �Ƿ� ������������
	//�ڱ⺸�� �ռ� �ִ� �������߿� �ڽź��� �Ƿ� ���������� ��������� ã��
	//���� ��ġ���� ���ش�.
	for (base = 1; base < N; base <<= 1);
	for (int i = 0; i < N; i++) {
		int idx = v[i].second;
		ans[idx] = idx - query(base, base + idx - 1) + 1;
		update(base + idx);
	}
}
void output() {
	for (int i = 0; i < N; i++) cout << ans[i] << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	sort(v.begin(),v.end());
	solve();
	output();
}