/*
    2020 상반기 카카오 인턴 코딩테스트 문제
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int number[10][3] = { {2,3,1},{0,0,0},{2,0,1},{1,0,2},
                 {0,1,0},{2,1,1},{1,1,2},
                 {0,2,0},{2,2,1},{1,2,2} };

    int lpos[2] = { 3,0 };
    int rpos[2] = { 3,2 };

    for (int i = 0; i < numbers.size(); i++) {
        int num = number[numbers[i]][0];
        int y = number[numbers[i]][1];
        int x = number[numbers[i]][2];

        //왼쪽 번호
        if (num == 0) {
            answer += 'L';
            lpos[0] = y;
            lpos[1] = x;
        }
        //오른쪽 번호
        else if (num == 1) {
            answer += 'R';
            rpos[0] = y;
            rpos[1] = x;
        }
        //가운데 번호
        else {
            int lLength = abs(y - lpos[0]) + abs(x - lpos[1]);
            int rLength = abs(y - rpos[0]) + abs(x - rpos[1]);
            if (lLength < rLength) {
                answer += 'L';
                lpos[0] = y;
                lpos[1] = x;
            }
            else if (lLength > rLength) {
                answer += 'R';
                rpos[0] = y;
                rpos[1] = x;
            }
            else {
                if (hand == "left") {
                    answer += 'L';
                    lpos[0] = y;
                    lpos[1] = x;
                }
                else {
                    answer += 'R';
                    rpos[0] = y;
                    rpos[1] = x;
                }
            }
        }
    }
    return answer;
}

/////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;
long long calculate(vector<long long> nums, vector<char> opers, map<char, int> priority) {
    stack<long long> numS;
    stack<char> operS;

    numS.push(nums[0]);
    for (int i = 0; i < opers.size(); i++) {
        if (operS.empty()) {
            operS.push(opers[i]);
        }
        else {
            while (!operS.empty()) {
                char topO = operS.top();
                if (priority[topO] < priority[opers[i]]) {
                    break;
                }
                else {
                    operS.pop();
                    long long num2 = numS.top(); numS.pop();
                    long long num1 = numS.top(); numS.pop();
                    if (topO == '+') {
                        numS.push(num1 + num2);
                    }
                    else if (topO == '-') {
                        numS.push(num1 - num2);
                    }
                    else {
                        numS.push(num1 * num2);
                    }
                }

            }
            operS.push(opers[i]);
        }
        numS.push(nums[i + 1]);
    }

    while (!operS.empty()) {
        char topO = operS.top();
        operS.pop();
        long long num2 = numS.top(); numS.pop();
        long long num1 = numS.top(); numS.pop();
        if (topO == '+') {
            numS.push(num1 + num2);
        }
        else if (topO == '-') {
            numS.push(num1 - num2);
        }
        else {
            numS.push(num1 * num2);
        }
    }

    return numS.top() < 0 ? (-1) * numS.top() : numS.top();
}

long long solution(string expression) {
    long long answer = 0;
    vector<char> opers;
    vector<long long> nums;
    string num = "";
    map<char, int> priority;
    //토크나이즈
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
            nums.push_back(stol(num));
            num = "";
            opers.push_back(expression[i]);
        }
        else {
            num += expression[i];
        }
    }
    nums.push_back(stoi(num));
    for (int i = 1; i <= 3; i++) {
        priority['+'] = i;
        for (int j = 1; j <= 3; j++) {
            if (i == j) continue;
            priority['-'] = j;
            for (int k = 1; k <= 3; k++) {
                if (i == k || j == k) continue;
                priority['*'] = k;
                answer = max(answer, calculate(nums, opers, priority));
            }
        }
    }

    return answer;
}
//////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <set>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer(2, 0);
    set<string> init;
    set<string> up;
    set<string> down;
    string leftStr;
    int left, right, length;
    for (int i = 0; i < gems.size(); i++) init.insert(gems[i]);

    //진열되어 있는 보석 한개일경우
    if (init.size() == 1) {
        answer[0] = 1; answer[1] = 1;
        return answer;
    }

    //모두 한개씩 진열되어 있는 경우
    if (init.size() == gems.size()) {
        answer[0] = 1; answer[1] = gems.size();
        return answer;
    }

    left = 1;
    length = 100001;
    for (int i = 0; i < gems.size(); i++) {
        up.insert(gems[i]);
        if (up.size() == init.size()) {
            right = i + 1;
            for (int j = right - 1; j >= left - 1; j--) {
                down.insert(gems[j]);
                if (up.size() == down.size()) {
                    left = j + 1;
                    up.erase(gems[j]);
                    break;
                }
            }

            if (right - left < length) {
                answer[0] = left;
                answer[1] = right;
                length = right - left;
            }

            leftStr = gems[left];
            left++;
            while (left < right && gems[left] == leftStr) left++;

            down.clear();
        }
    }


    return answer;
}
////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int solution(vector<vector<int>> board) {
    int answer = 0;
    int dy[4] = { -1,1,0,0 };
    int dx[4] = { 0,0,-1,1 };
    int dist[25][25];
    int N = board.size();
    queue<pair<pair<int, int>, pair<int, int>>> q;

    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dist[i][j] = 600 * 25 * 25;
    dist[0][0] = 0;

    q.push({ {0,0},{-1,0} });
    while (!q.empty()) {
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int d = q.front().second.first;
        int curDist = q.front().second.second;
        q.pop();

        if (curDist > dist[cy][cx]) continue;
        if (cy == N - 1 && cx == N - 1) continue;

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i];
            int nx = cx + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if (board[ny][nx] == 1) continue;
            int nextDist = curDist + 100;
            if ((i == 0 || i == 1) && (d == 2 || d == 3)) nextDist += 500;
            if ((d == 0 || d == 1) && (i == 2 || i == 3)) nextDist += 500;
            if (nextDist > dist[ny][nx]) continue;

            dist[ny][nx] = nextDist;

            q.push({ {ny, nx},{i,nextDist} });

        }
    }

    return dist[board.size() - 1][board.size() - 1];
}

#include <string>
#include <vector>

using namespace std;

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    bool answer = true;
    return answer;
}