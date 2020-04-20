#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct shark {
	int r = 0;
	int c = 0;
	int s = 0;
	int d = 0;
	int z = 0;
};

int pos, R, C, M, r, c, s, d, z, answer;
int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,1,-1 };
shark* map[101][101];
shark info[10001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	//�Է��ϴ� �κ�
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		cin >> r >> c >> s >> d >> z;
		info[i] = { r, c, s, d, z };
		map[r][c] = &info[i];
	}

	if (M == 0) {
		cout << 0;
		return 0;
	}


	//������ ó��
	while (pos < C) {
		//���ÿ��� ���������� �� ĭ �̵��Ѵ�.
		pos++;

		//���ÿ��� �ִ� ���� �̴� ��� �߿��� ���� ���� ����� �� ��´�.
		//�� ������ �����ǿ��� ���� �� �������.
		for (int i = 1; i <= R; i++) {
			if (map[i][pos] != nullptr) {
				shark curr = *map[i][pos];
				//�� ��´�
				answer += curr.z;

				//�����ǿ��� �� �������.
				*map[i][pos] = { -1, -1, -1, -1, -1 };
				map[i][pos] = nullptr;
				break;
			}
		}


		//���� �������� Ŭ���� �����ش�.
		for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) map[i][j] = nullptr;



		//�� �̵��Ѵ�.
		for (int i = 1; i <= M; i++) {
			//�̹� ���� ���� �ѱ��.
			if (info[i].s == -1) continue;
			int r = info[i].r;
			int c = info[i].c;
			int s = info[i].s;
			int d = info[i].d;
			int z = info[i].z;

			//�̵����� �ش�.
			if (d == 1) r = R + (R - r);
			if (d == 4) c = C + (C - c);
			if (d == 1 || d == 2) {
				r += s;
				r = (r - 1) % (2 * R - 2) + 1;
				if (r / R) {
					r = R - r % R;
					d = 1;
				}
				else {
					d = 2;
				}
			}
			else {
				c += s;
				c = (c - 1) % (2 * C - 2) + 1;
				if (c / C) {
					c = C - c % C;
					d = 4;
				}
				else d = 3;
			}
			
			//������ ������Ʈ �Ѵ�.
			info[i] = { r,c,s,d,z };

			//��� �̵����Ѽ� �������ش�.
			if (map[r][c] == nullptr) map[r][c] = &info[i];
			else {
				if ((*map[r][c]).z < z) {
					*map[r][c] = { -1, -1, -1, -1, -1 };
					map[r][c] = &info[i];
				}
				else {
					info[i] = { -1, -1, -1, -1, -1 };
				}
			}
		}
	}

	cout << answer;
}