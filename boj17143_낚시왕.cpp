//ĭ���� �ִ� �� �Ѹ���
//���� ũ�� �ӵ��� ����
//���ÿ��� ÷�� 1���� ��ĭ ����
//1�ʵ��� �������� �Ͼ -> ���� ������ �� ������ ĭ���� �̵��ϸ� �̵��� ����
//1. ������ ��ĭ �̵�
//2. ���ÿ��� �ִ� ���� ���� ����� ��� ���� -> ��� �����
//3. ��� �̵�
// ��� : �־��� �ӵ��� �̵�, ĭ/�� , ��� �Ѿ�� ���� �ݴ�� �ٲ�
//�̵��� ��ģ�� �� �θ��� �̻� ������, ũ�Ⱑ ū �� ��� ��Ƹ���
// ���ÿ��� ���� ��� ũ���� ���� ���غ���
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int R, C, M, r, c, s, d, z, pos, ans;
int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,1,-1 };
//{{����, ũ��},{�ӵ�,�����Ÿ�}}
vector<vector<pair<pair<int, int>,int>>> shark;
vector<vector<pair<pair<int, int>, int>>> temp;
int main() {
	//�Է�
	cin >> R >> C >> M;
	for (int i = 0; i <= R; i++) {
		vector<pair<pair<int, int>, int>> row;
		for (int j = 0; j <= C; j++) {
			pair<pair<int, int>, int> e = { {0,0,},0 };
			row.push_back(e);
		}
		shark.push_back(row);
	}

	if (M == 0) {
		cout << ans << "\n";
		return 0;
	}
	
	//��� ���� �Է�
	while (M--) {
		cin >> r >> c >> s >> d >> z;
		shark[r][c] = {{d,z}, s};
	}


	while (pos < C) {
		//���ÿ� �̵�
		pos++;
		//���� ����� ��� ����
		for (int i = 1; i <= R; i++) {
			if (shark[i][pos].first.first != 0) {
				//ans�� ũ�� �߰�
				ans += shark[i][pos].first.second;
				//��� ����
				shark[i][pos] = { {0,0},0 };
				break;
			}
		}
		
		//temp�� ����ش�.
		temp.clear();
		for (int i = 0; i <= R; i++) {
			vector<pair<pair<int, int>, int>> row;
			for (int j = 0; j <= C; j++) {
				pair<pair<int, int>, int> e = { {0,0,},0 };
				row.push_back(e);
			}
			temp.push_back(row);
		}

		//����Ȱ� ��� �̵������ش�.
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++) {
				if (shark[i][j].first.first != 0) {
					int cr = i, cc = j;
					int cd = shark[i][j].first.first;
					int cz = shark[i][j].first.second;
					int cs = shark[i][j].second;
					cr += cs * dy[cd];
					cc += cs * dx[cd];
				
					while (cr <= 0 || cc <= 0 || cr > R || cc > C) {
						if (cr <= 0) { cr = -1 * (cr) + 2; cd = 2; }
					    else if (cc <= 0) { cc = -1 * (cc) + 2; cd = 3;}
						else if (cr > R) { 
							int r = (cr-1) % (R * 2 - 2) + 1;
							int q;
							q = r / R;
							r = r % R;
							if (q) { cr = R - r; cd = 1; }
							else { cr = r; cd = 2; }
						}
						else if (cc > C) {
							int r = (cc-1) % (C * 2 - 2) + 1;
							int q;
							q = r / C;
							r = r % C;
							if (q) { cc = C - r; cd = 4; }
							else { cc = r; cd = 3; }
						}
					}
				
					//�̵� ���� �ش�.
					if (temp[cr][cc].first.first != 0) {
						if(temp[cr][cc].first.second < cz)
							temp[cr][cc] = { {cd, cz},cs };						
					}
					else temp[cr][cc] = { {cd, cz}, cs };
				}
			}
		}


		//�ٽ� �������ش�.
		shark.clear();
		shark.resize(temp.size());
		shark.assign(temp.begin(), temp.end());
	}

	cout << ans << "\n";
	
}