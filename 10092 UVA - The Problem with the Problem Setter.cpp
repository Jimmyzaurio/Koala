#include <bits/stdc++.h>
using namespace std;

typedef int Flujo;

typedef vector<int> Lista;
typedef pair<int, int> Par;
typedef vector<Flujo> Flujo1D;
typedef vector<Flujo1D> Flujo2D;

const Flujo FINF = 1 << 30;


struct GrafoFlujo {

    int n; vector<Lista> aristas;
    Flujo2D cap, flujo; Lista padre, dist;
    
    GrafoFlujo(int N) : dist(N), padre(N), aristas(N),
        cap(N, Flujo1D(N)), flujo(N, Flujo1D(N)), n(N) {}

    void Conecta(int u, int v, Flujo c) {
        flujo[v][u] += c; // Solo dirigidas!
        cap[u][v] += c, cap[v][u] += c;
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }

    // Flujo maximo mediante Dinic O(V^2E).

    Flujo FlujoBloqueante(int u, int t, Flujo f) {
        if (u == t) return f; Flujo fluido = 0;
        for (int i = 0; i < aristas[u].size(); ++i) {
            if (fluido == f) break; int v = aristas[u][i];
            if (dist[u] + 1 > dist[v]) continue;
            Flujo fv = FlujoBloqueante(v, t,
                min(f - fluido, cap[u][v] - flujo[u][v]));
            flujo[u][v] += fv, fluido += fv;
            flujo[v][u] -= fv;
        }
        return fluido;
    }

    Flujo Dinic(int s, int t) {
        Flujo flujo_maximo = dist[t] = 0;
        while (dist[t] < INT_MAX) {
            fill(dist.begin(), dist.end(), INT_MAX);
            queue<int> q; q.push(s); dist[s] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int i = 0; i < aristas[u].size(); ++i) {
                    int v = aristas[u][i];
                    if (flujo[u][v] == cap[u][v] ||
                        dist[v] <= dist[u] + 1) continue;
                    dist[v] = dist[u] + 1, q.push(v);
                }
            }
            if (dist[t] < INT_MAX) flujo_maximo +=
                FlujoBloqueante(s, t, FINF);
        }
        return flujo_maximo;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k, p;
    while (cin >> k >> p && k != 0 && p != 0) {
        GrafoFlujo score(k + p + 2);
        int acc = 0;
        for (int i = 0; i < k; ++i) {
            int problems;
            cin >> problems;
            acc += problems;
            score.Conecta(0, 1 + i, problems);
        }
        for (int i = 0; i < p; ++i) {
            int categ;
            cin >> categ;
            for (int j = 0; j < categ; ++j) {
                int num;
                cin >> num;
                score.Conecta(num, k + i + 1, 1);
            }
        }
        for (int i = 0; i < p; ++i)
            score.Conecta(k + i + 1, k + p + 1, 1);
        int flow = score.Dinic(0, k + p + 1);
        //cout << "flow " << flow << endl;
        if (flow != acc)
            cout << "0\n";
        else {
            cout << "1\n";
            for (int i = 0; i < k; ++i) {
                bool flag = false;
                for (int j = 0; j < p; ++j)
                    if (score.flujo[1 + i][k + j + 1] == 1)
                        cout << (flag? " ": "") << j + 1, flag = true;
                cout << '\n';
            }
        }
    }
    return 0;
}
