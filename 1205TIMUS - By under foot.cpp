#include <bits/stdc++.h>
using namespace std;

#define distancia(a, b) hypot(stations[a].first - stations[b].first, stations[a].second - stations[b].second)

typedef double Costo;
const Costo INF = 1 << 30;
typedef pair<int, int> Arista;

typedef pair<Costo, int> CostoNodo;

struct Grafo {
  int n; bool bi;
  vector<vector<CostoNodo>> ady;
  vector<int> parent;

  Grafo(int N, bool B) 
    : n(N), bi(B), ady(n), parent(n, -1) {}

  void Conecta(int u, int v, Costo c) {
    if (bi) ady[v].push_back(CostoNodo(c, u));
    ady[u].push_back(CostoNodo(c, v));
  }

  vector<Costo> dijsktra(int s) {
    vector<Costo> dist(n, INF);
    priority_queue<CostoNodo> pq;
    pq.push(CostoNodo(0, s)), dist[s] = 0;

    while (!pq.empty()) {
      Costo p = -pq.top().first;
      int u = pq.top().second; pq.pop();
      if (dist[u] < p) continue;

      for (CostoNodo arista : ady[u]) {
        int v = arista.second;
        p = dist[u] + arista.first;
        if (p < dist[v]) dist[v] = p,
          pq.push(CostoNodo(-p, v)), parent[v] = u;
      }
    }
    return dist;
  }
};

int main() {
  double foot, metro;
  int n;
  cin >> foot >> metro >> n;

  Grafo roads(n + 2, true);
  vector<pair<double, double>> stations(n);
  for (int i = 0; i < n; ++i)
    cin >> stations[i].first >> stations[i].second;

  int a, b;
  while (cin >> a >> b && a != 0 && b != 0) {
    --a, --b;
    roads.Conecta(a, b, distancia(a, b)/metro);
  }

  double iniX, iniY, finX, finY;
  cin >> iniX >> iniY >> finX >> finY;
  stations.push_back({iniX, iniY});
  stations.push_back({finX, finY});

  for (int i = 0; i < n + 2; ++i)
    for (int j = i + 1; j < n + 2; ++j)
      roads.Conecta(i, j, distancia(i, j)/foot);

  auto D = roads.dijsktra(n);
  int actual = n + 1;
  while (roads.parent[actual] != -1) {
    if ()
  }
  cout << setprecision(7) << fixed << D[n + 1] << '\n';
  return 0;
}
