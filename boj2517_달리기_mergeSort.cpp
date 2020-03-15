#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define MAXN 500000
using namespace std;
//poten : 평소 실력을 입력받는 변수
//v : {평소실력, 현재등수}를 입력받는 벡터
//tmp : mergesort를 위한 임시 벡터
//ans : 결과값을 저장하는 배열

int N, poten;
int ans[MAXN];
vector<pair<int,int>> v;
vector<pair<int, int>> tmp;

//input() : 입력 함수
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> poten;
		v.push_back({ poten,i });
	}
}

//merge() : merge과정은 기존에 알고 있는 merge 과정과 같다.
//			특이점은 오른쪽 배열에서 현재 가리키고 있는 값이 왼쪽 배열에서 현재 가리키고 있는 값보다 작다면
//			왼쪽 배열의 뒷 부분은 오른쪽 배열에서 현재 가리키고 있는 값보다 무조건 크므로 그 갯수를 ans배열에 더해준다.
void merge(int left1, int right1, int left2, int right2) {
	tmp.clear();

	int a = left1, b = left2;

	while (a <= right1 && b <= right2) {
		if (v[a].first < v[b].first) {
			tmp.push_back(v[a++]);
		}
		else if(v[b].first < v[a].first) {
			//이 부분이다 현재 v[b].first < v[a].first 이므로
			//v[a+1].first , v[a+2].first ... v[right1].first은 모두 v[b].first보다 크게 되므로
			//ans[v[b].second]에 (a ~ right1) 까지의 개수를 더해준다.
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

//mergeSort() : MergeSort의 논리과정을 통해 자신보다 앞에 달리고 있는 평소 실력이 좋은 선수를 찾을 것이다.(오름차순 정렬)
void mergeSort(int left, int right) {
	if (left < right) {
		int m = (left + right) / 2;
		mergeSort(left, m);
		mergeSort(m + 1, right);

		merge(left, m, m + 1, right);
	}
}

//output() : 출력하는 함수
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