#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define MAXN 500000
using namespace std;
//poten : ��� �Ƿ��� �Է¹޴� ����
//v : {��ҽǷ�, ������}�� �Է¹޴� ����
//tmp : mergesort�� ���� �ӽ� ����
//ans : ������� �����ϴ� �迭

int N, poten;
int ans[MAXN];
vector<pair<int,int>> v;
vector<pair<int, int>> tmp;

//input() : �Է� �Լ�
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> poten;
		v.push_back({ poten,i });
	}
}

//merge() : merge������ ������ �˰� �ִ� merge ������ ����.
//			Ư������ ������ �迭���� ���� ����Ű�� �ִ� ���� ���� �迭���� ���� ����Ű�� �ִ� ������ �۴ٸ�
//			���� �迭�� �� �κ��� ������ �迭���� ���� ����Ű�� �ִ� ������ ������ ũ�Ƿ� �� ������ ans�迭�� �����ش�.
void merge(int left1, int right1, int left2, int right2) {
	tmp.clear();

	int a = left1, b = left2;

	while (a <= right1 && b <= right2) {
		if (v[a].first < v[b].first) {
			tmp.push_back(v[a++]);
		}
		else if(v[b].first < v[a].first) {
			//�� �κ��̴� ���� v[b].first < v[a].first �̹Ƿ�
			//v[a+1].first , v[a+2].first ... v[right1].first�� ��� v[b].first���� ũ�� �ǹǷ�
			//ans[v[b].second]�� (a ~ right1) ������ ������ �����ش�.
			ans[v[b].second] += right1 - a + 1;
			tmp.push_back(v[b++]);
		}
	}

	if (a > right1) {
		while (b <= right2) {
			tmp.push_back((v[b++]));
		}
	}
	if (b > right2) {
		while (a <= right1) {
			tmp.push_back((v[a++]));
		}
	}

	int idx = 0;
	for (int i = left1; i <= right2; i++) {
		v[i] = tmp[idx++];
	}
}

//mergeSort() : MergeSort�� �������� ���� �ڽź��� �տ� �޸��� �ִ� ��� �Ƿ��� ���� ������ ã�� ���̴�.(�������� ����)
void mergeSort(int left, int right) {
	if (left < right) {
		int m = (left + right) / 2;
		mergeSort(left, m);
		mergeSort(m + 1, right);

		merge(left, m, m + 1, right);
	}
}

//output() : ����ϴ� �Լ�
void output() {
	for (int i = 0; i < N; i++) cout << ans[i] + 1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	mergeSort(0, N - 1);
	output();
}