#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<set>
#include<map>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<iomanip>
#include<deque>
#include<sstream>
using namespace std;

const string GOAL = "123456780";
string s;
int dir[][2] = { -1,0,0,-1,1,0,0,1 };//上 左 下 右
deque<string> list;
map<string, int> g;
map<string, bool> visit;
int x, y;

void swap(char& a, char& b) {
	char temp = a;
	a = b;
	b = temp;
}
bool can_move(string s, int n) {
	int temp[3][3], a = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp[i][j] = s[a++] - '0';
			if (temp[i][j] == 0) {
				x = i;
				y = j;
			}
		}
	}
	if ((x == 0 && n == 0) || (x == 2 && n == 2) || (y == 0 && n == 1) || (y == 2 && n == 2))
		return false;
	return true;
}
string move_to(string s, int n) {
	string temp = s;
	int nx = x + dir[n][0], ny = y + dir[n][1];
	swap(temp[x * 3 + y], temp[nx * 3 + ny]);
	return temp;
}

int dfs(string s) {
	list.push_front(s);
	g[s] = 0;
	visit[s] = true;
	while (list.size()) {
		string temp = list.front();
		list.pop_front();
		if (temp == "123456780")
			return g[temp];
		for (int i = 0; i < 4; i++) {
			if (can_move(temp, i)) {
				string back = move_to(temp, i);
				if (!visit[back]) {
					visit[back] = true;
					if (g[back])
						g[back] = (g[temp] + 1) < g[back] ? g[temp] + 1 : g[back];
					else
						g[back] = g[temp] + 1;
					list.push_back(back);
				}
			}
		}
	}
	return -1;
}
int main() {
	cin >> s;
	int ans = dfs(s);
	cout << ans << endl;
	return 0;
}
