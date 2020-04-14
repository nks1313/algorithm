//칸에는 최대 상어가 한마리
//상어는 크기 속도를 가짐
//낚시왕은 첨에 1번열 한칸 왼쪽
//1초동안 다음일이 일어남 -> 가장 오른쪽 열 오른쪽 칸으로 이동하면 이동을 멈춤
//1. 오른쪽 한칸 이동
//2. 낚시왕이 있는 열에 제일 가까운 상어 잡음 -> 상어 사라짐
//3. 상어 이동
// 상어 : 주어진 속도로 이동, 칸/초 , 경계 넘어가면 방향 반대로 바뀜
//이동을 마친후 사어가 두마리 이상 있으면, 크기가 큰 상어가 모두 잡아먹음
// 낚시왕이 잡은 상어 크기의 합을 구해보기
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int R, C, M, r, c, s, d, z, pos, ans;
int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,1,-1 };
//{{방향, 크기},{속도,남은거리}}
vector<vector<pair<pair<int, int>,int>>> shark;
vector<vector<pair<pair<int, int>, int>>> temp;
int main() {
	//입력
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
	
	//상어 정보 입력
	while (M--) {
		cin >> r >> c >> s >> d >> z;
		shark[r][c] = {{d,z}, s};
	}


	while (pos < C) {
		//낚시왕 이동
		pos++;
		//가장 가까운 상어 잡음
		for (int i = 1; i <= R; i++) {
			if (shark[i][pos].first.first != 0) {
				//ans에 크기 추가
				ans += shark[i][pos].first.second;
				//상어 제거
				shark[i][pos] = { {0,0},0 };
				break;
			}
		}
		
		//temp를 비워준다.
		temp.clear();
		for (int i = 0; i <= R; i++) {
			vector<pair<pair<int, int>, int>> row;
			for (int j = 0; j <= C; j++) {
				pair<pair<int, int>, int> e = { {0,0,},0 };
				row.push_back(e);
			}
			temp.push_back(row);
		}

		//복사된거 상어 이동시켜준다.
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
				
					//이동 시켜 준다.
					if (temp[cr][cc].first.first != 0) {
						if(temp[cr][cc].first.second < cz)
							temp[cr][cc] = { {cd, cz},cs };						
					}
					else temp[cr][cc] = { {cd, cz}, cs };
				}
			}
		}


		//다시 복사해준다.
		shark.clear();
		shark.resize(temp.size());
		shark.assign(temp.begin(), temp.end());
	}

	cout << ans << "\n";
	
}