#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10100;
typedef pair<int, int> pii;
const int INF = 1 << 30;

int dir[6][2] = {2, 1, 0, 2, -2, 1, -2, -1, 0, -2, 2, -1};
map<pii, int> mp, mmp;
pii p[MAXN];
int cnt[10];
bool vis[10];
int res[MAXN];

void dfs(pii u, int id, int di) {
  if (id >= MAXN) return;
  fill(vis, vis + 10, false);
  pii v;
  for (;;) {
    int x = u.first  + dir[di][0];
    int y = u.second + dir[di][1];
    v = make_pair(x, y);
    if (mp[v])
      vis[mp[v]] = true;
    else
      break;
    di = (di + 6 - 1) % 6;
  }
  int tc = INF, ta = -1;
  for (int i = 1; i < 6; ++i) {
    if (vis[i]) continue;
    if (cnt[i] < tc) {
      tc = cnt[i];
      ta = i;
    }
  }
  cnt[ta]++;
  mp[u] = ta;
  res[id] = ta;
  dfs(v, id + 1, (di + 3) % 6);
}

void init() {
  res[1] = 1;
  mp[make_pair(0, 0)] = 1;
  cnt[1] = 1;
  dfs(make_pair(2, 1), 2, 3);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  init();
  int t;
  cin >> t;
  while (t--) {
    int x; 
    cin >> x;
    cout << res[x] << '\n';
  }
  return 0;
}
