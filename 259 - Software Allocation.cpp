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

    // Flujo maximo mediante Edmonds-Karp O(VE^2).

    Flujo ActualizarFlujo(int u, Flujo f) {
        int p = padre[u];
        if (p == u) return f;
        f = ActualizarFlujo(p, min(f,
            cap[p][u] - flujo[p][u]));
        flujo[p][u] += f;
        flujo[u][p] -= f;
        return f;
    }

    Flujo AumentarFlujo(int s, int t) {
        fill(padre.begin(), padre.end(), -1);
        queue<int> q; q.push(s); padre[s] = s;
        while (!q.empty()) {
            int u = q.front();
            q.pop(); if (u == t) break;
            for (int i = 0; i < aristas[u].size(); ++i) {
                int v = aristas[u][i];
                if (flujo[u][v] == cap[u][v] ||
                    padre[v] != -1) continue;
                padre[v] = u, q.push(v);
            }
        }
        if (padre[t] == -1) return 0;
        return ActualizarFlujo(t, FINF);
    }

    Flujo EdmondsKarp(int s, int t) {
        Flujo flujo_maximo = 0, f;
        while (f = AumentarFlujo(s, t))
            flujo_maximo += f;
        return flujo_maximo;
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


#define FUENTE 0
#define POZO 37
#define IZQ 1
#define DER 11

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string cad;
    while (getline(cin, cad)) {
        int total = 0;
        GrafoFlujo red(38);
        do {
            int app = cad[0] - 'A' + DER;
            int users = cad[1] - '0';
            for (int i = 3; i < cad.size() - 1; ++i)
                red.Conecta(IZQ + cad[i] - '0', app, 1);
            red.Conecta(app, POZO, users);
            total += users;

            getline(cin, cad);
        } while (!cad.empty());

        for (int i = 0; i < 10; i++)
            red.Conecta(FUENTE, IZQ + i, 1);
        
        int flow = red.Dinic(FUENTE, POZO);
        if (flow != total)
            cout << '!';
        else {
            for (int i = 0; i < 10; ++i) {
                bool found = false;
                for (int j = 0; j < 26 && !found; ++j)
                    if (red.flujo[IZQ + i][DER + j] == 1)
                        cout << (char)('A' + j), found = true;
                if (!found)
                    cout << '_';
            }
        }
        cout << '\n';
    }
    return 0;
}
