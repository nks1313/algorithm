//������ ����� ���� �ʾҴ�.
//������ ���� �Ǵ��Ͽ� L, R�� ������ �ʾҴ�.
//������ �����Ͽ� �ٷ� �˾�ç �� �־�����
//���������ٸ� �̷� �Ǽ��� ġ������ �� �ִ�.
//������ ������ �Ĳ��� �д� ������ ������

#include <iostream>
#include <string>
using namespace std;
int N, y, x, d, lowY, lowX, highY, highX;
int dy[4] = { 1,0,-1,0 };
int dx[4] = { 0,1,0,-1 };
bool checked[101][101];
string str;
int main() {
	cin >> N;
	cin >> str;
	
	y = x = lowY = lowX = highY = highX = 50;
	checked[y][x] = true;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == 'R') {
			d = (d + 3) % 4;
		}
		else if (str[i] == 'L') {
			d = (d + 1) % 4;
		}
		else {
			y += dy[d]; x += dx[d];
			lowY = (lowY > y) ? y : lowY;
			lowX = (lowX > x) ? x : lowX;
			highY = (highY < y) ? y : highY;
			highX = (highX < x) ? x : highX;
			checked[y][x] = true;
		}
	}

	for (int i = lowY; i <= highY; i++) {
		for (int j = lowX; j <= highX; j++) {
			if (checked[i][j]) cout << '.';
			else cout << "#";
		}
		cout << "\n";
	}
}