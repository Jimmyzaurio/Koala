#include <bits/stdc++.h>
using namespace std;

#define proba second
#define tramo first

typedef double Costo;
typedef pair<int, double> Peso;
typedef pair<Peso, int> CostoPeso;
int const INF = 1 << 30;
typedef pair<Costo, int> CostoNodo;
typedef pair<CostoNodo, int> Arista;

struct Grafo {
  int n; bool bi;
  vector<vector<CostoNodo>> ady;
  vector<int> parent;

  Grafo(int N, bool B) 
    : n(N), bi(B), ady(N) {}

  void Conecta(int u, int v, Costo c) {
    if (bi) ady[v].push_back(CostoNodo(c, u));
    ady[u].push_back(CostoNodo(c, v));
  }

  vector<Peso> Dijkstra(int s) {
    vector<Peso> dist(n, Peso(INF, INF));
    parent = vector<int>(n, -1);
    priority_queue<CostoPeso, vector<CostoPeso>, greater<CostoPeso>> pq;
    
    pq.push(CostoPeso(Peso(0, 0.0), s)), dist[s] = Peso(0, 0.0);

    while (!pq.empty()) {
      Peso p = pq.top().first;
      int u = pq.top().second; pq.pop();
      if (dist[u] < p) continue;

      for (CostoNodo arista : ady[u]) {
        int v = arista.second;
        p = Peso(dist[u].tramo + 1, dist[u].proba 
                                    + arista.first*(1.0 - arista.first));
        if (p < dist[v]) dist[v] = p, parent[v] = u;
          pq.push(CostoPeso(p, v));
      }
    }
    return dist;
  }

};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int n, m, s, t;

  cin >> n >> m >> s >> t;
  Grafo islas(n, true);
  for (int i = 0; i < m; ++i) {
    int a, b;
    double p;
    cin >> a >> b >> p;
    islas.Conecta(--a, --b, p/100.0);
  }
  auto D = islas.Dijkstra(s - 1);
  
  vector<int> ans;
  int actual = t - 1;
  while ((actual = islas.parent[actual]) != -1)
    ans.push_back(actual + 1);  

  cout << ans.size() + 1 << " " << fixed << setprecision(6) << D[t - 1].second << '\n';
  for (int i = ans.size() - 1; i >= 0; --i)
    cout << ans[i] << ' ';
  cout << t << '\n';
  return 0;
}
