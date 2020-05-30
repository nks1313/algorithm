#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <stack>
using namespace std;

int t, sm, sc, si, arr[100001], loop[4096], oCnt[4096];
string oper, in;

int main() {
	cin >> t;
	while (t--) {

		stack<pair<char, int>> s;

		cin >> sm >> sc >> si;
		cin >> oper >> in;
		memset(arr, 0, sizeof(int) * sm);
		memset(oCnt, 0, sizeof(int) * sc);
		for (int i = 0; i < sc; i++) loop[i] = -1;

		//loop 짝 만들기
		for (int i = 0; i < oper.size(); i++) {
			if (oper[i] == '[') {
				s.push({ '[',i });
			}
			else if (oper[i] == ']') {
				if (!s.empty()) {
					if (s.top().first == '[') {
						loop[s.top().second] = i;
						loop[i] = s.top().second;
						s.pop();
					}
				}
			}
		}
		
		//명령어 돌면서 해당되는 것 적절한 처리 하기
		int ptr = 0, oIdx = 0, iIdx = 0, cnt = 0;
		bool isLoop = false;
		while (oIdx < sc) {
			//cout << 1 << "\n";
			if (cnt >= 50000000) {
				isLoop = true;
				break;
			}

			if (oper[oIdx] == '-') {
				if (--arr[ptr] == -1) arr[ptr] = 255;
				oIdx++;
			}
			else if (oper[oIdx] == '+') {
				if (++arr[ptr] == 256) arr[ptr] = 0;
				oIdx++;
			}
			else if (oper[oIdx] == '<') {
				if (--ptr == -1) ptr = sm - 1;
				oIdx++;
			}
			else if (oper[oIdx] == '>') {
				if (++ptr == sm) ptr = 0;
				oIdx++;
			}
			else if (oper[oIdx] == '[') {
				oCnt[oIdx]++;
				if (arr[ptr] == 0) oIdx = loop[oIdx];
				else oIdx++;
			}
			else if (oper[oIdx] == ']') {
				oCnt[oIdx]++;
				if (arr[ptr] != 0) oIdx = loop[oIdx];
				else oIdx++;
			}
			else if (oper[oIdx] == ',') {
				if (iIdx < si) arr[ptr] = in[iIdx++];
				else arr[ptr] = 255;
				oIdx++;
			}
			else if (oper[oIdx] == '.') {
				oIdx++;
			}

			cnt++;
		}
		for (int i = 0; i < sc; i++) {
			cout << oCnt[i] << " ";
		}
		cout << "\n";
		if (!isLoop) {
			cout << "Terminates\n";
		}
		else {
			int idx = 0, maxV = 0;;
			for (int i = oIdx; i < sc; i++) {
				if (oper[i] == ']' && oCnt[i] > 0) {
					idx = i;
				}
			}

			cout << "Loops" << " " << loop[idx] << " " << idx << "\n";
		}
	}
	return 0;
}