#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<deque>
#define MAX 0xfffffff
using namespace std;

const string GOAL = "123456780";
string s;
int dir[][2] = { -1,0,0,-1,1,0,0,1 };//上 左 下 右
map<string, int> g;
map<string, bool> visit;
int x, y;
bool flag = false;

typedef struct node {
	string s;
	int assess;
}node;
deque<node> list;

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

//哈密尔顿路径评估
int assess(const string s,string goal) {
	int count = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0')
			continue;
		int local = goal.find(s[i]);
		int step = abs(local % 3 - i % 3) + abs(local / 3 - i / 3);
		count += step;
	}
	return count;
}

//意义:看A*算法找没找到目标
bool aStar(int depth, string s,int cost) {
	vector<node> estimate;
	node start;
	start.s = s;
	start.assess = assess(s, GOAL);
	list.push_front(start);
	while (list.size()) {
		string temp = list.front().s;
		list.pop_front();
		if (assess(temp, GOAL) == 0)
			return true;
		for (int i = 0; i < 4; i++) {
			node tempN;
			if (can_move(temp, i)) {
				string back = move_to(temp, i);
				if (!visit[back]) {
					visit[back] = true;
					g[back] = g[temp] + 1;
					tempN.s = back;
					tempN.assess = assess(back, GOAL) + g[temp] + 1;
					//每次总代价递增
					if (tempN.assess < cost)
						continue;
					estimate.push_back(tempN);
				}
			}
		}
		if (estimate.size() == 0)
			cost = list.front().assess;
		sort(estimate.begin(), estimate.end(), [](node a, node b) {
			return a.assess < b.assess;
			});
		for (int i = estimate.size() - 1; i >= 0; i--) {
			list.push_front(estimate[i]);
			if (i == 0)
				cost = estimate[0].assess;
		}
    //清理vector
		estimate.clear();
	}
	return false;
}

int main() {
	cin >> s;
	g[GOAL] = 0;
	if (aStar(0, s,0))
		cout << "能找到答案\n" << 
		 g[GOAL] << endl;
	else
		cout << "不能找到答案" << endl;
	return 0;
}
