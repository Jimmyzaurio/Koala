#include <bits/stdc++.h>
using namespace std;

struct Node{
	int rlen, flen, line;
	bool visit;
	Node() :rlen(-1), flen(-1), line(-1), visit(false){}
};

const int MAXN = 1e5 + 10;
vector<int>table[MAXN];
vector<Node>v(MAXN);

void BFS(int s, int f, int r) {
	queue<int> Q;
	v[r].rlen = 0;
	Q.push(r);

	while (!Q.empty()) {
		int src = Q.front(); Q.pop();
		for (int u : table[src])
		if (v[u].rlen == -1){
			v[u].rlen = v[src].rlen + 1;
			Q.push(u);
		}
	}

	v[f].flen = 0;
	Q.push(f);
	while (!Q.empty()) {
		int src = Q.front(); Q.pop();
		for (int u : table[src])
		if (v[u].flen == -1) {
			v[u].flen = v[src].flen + 1;
			Q.push(u);
		}
	}

	v[s].line = v[s].rlen;
	Q.push(s);
	while (!Q.empty()) {
		int src = Q.front(); Q.pop();
		v[src].visit = true;
		for (int u : table[src]) {
			if (v[u].flen != v[src].flen - 1) 
				continue;
			v[u].line = max(v[u].line, v[src].line);
			v[u].line = min(v[u].line, v[u].rlen);
			if (!v[u].visit) {
				Q.push(u);
				v[u].visit = true;
			}
		}
	}
	cout << v[f].line << '\n';
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, s, f, r;

	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		table[a].push_back(b);
		table[b].push_back(a);
	}

	cin >> s >> f >> r;
	BFS(s, f, r);
}
