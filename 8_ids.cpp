#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<map>
using namespace std;

const string GOAL = "123456780";
string s;
int dir[][2] = { -1,0,0,-1,1,0,0,1 };//上 左 下 右
map<string, int> g;
int x, y;
int deep;
bool flag = false;//标记是否找到答案

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
bool ids(int depth, string s) {
	if (depth == deep) {
		if (flag)
			return true;
		if (s == GOAL)
			return true;
		return false;
	}
	for (int i = 0; i < 4; i++) {
		if (can_move(s, i)) {
			string back = move_to(s, i);
			g[back] = depth + 1;
			if (ids(depth + 1, back))
				flag = true;
		}
	}
	return flag;
}
int main() {
	cin >> s;
	g["123456780"] = -1;
	for (deep = 1;; deep++) {
		if (ids(0, s)) {
			flag = true;
			break;
		}
	}
	cout << g["123456780"] << endl;
	return 0;
}
