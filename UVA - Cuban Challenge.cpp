#include <bits/stdc++.h>
using namespace std;

typedef int Flujo;

typedef vector<int> Lista;
typedef pair<int, int> Par;
typedef vector<Flujo> Flujo1D;
typedef vector<Flujo1D> Flujo2D;

struct Bipartito {
    int n; Lista pareja;
    vector<Lista> aristas;
    vector<bool> lado, visitado;

    Bipartito(int N) : lado(N), pareja(N),
        visitado(N), aristas(N), n(N) {}

    void AgregarArista(int u, int v) {
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }

    void AgregarIzq(int u) { lado[u] = true; }
    void AgregarDer(int u) { lado[u] = false; }

    int CaminoIncremental(int u) {
        visitado[u] = true;
        for (int i = 0; i < aristas[u].size(); ++i)
            if (pareja[aristas[u][i]] == -1)
                return pareja[aristas[u][i]] = u;
        for (int i = 0; i < aristas[u].size(); ++i) {
            int v = aristas[u][i];
            if (visitado[pareja[v]]) continue;
            if (CaminoIncremental(pareja[v]) != -1)
                return pareja[v] = u;
        }
        return -1;
    }

    vector<Par> MaxEmp() {
        fill(pareja.begin(), pareja.end(), -1);
        for (int i = 0; i < n; ++i) {
            if (!lado[i]) continue; CaminoIncremental(i);
            fill(visitado.begin(), visitado.end(), false);
        }

        vector<Par> pares;
        for (int i = 0; i < n; ++i)
            if (!lado[i] && pareja[i] != -1)
                pares.push_back(Par(pareja[i], i));
        return pares;
    }
};

#define ACT tablero[i][j]
#define IZQ tablero[i][j + 1]
#define DOWN tablero[i + 1][j]

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, caso = 1;
    while (cin >> n >> m && n != 0 && m != 0) {
        int conta = 0;
        vector<vector<int>> tablero(n, vector<int>(m, -1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char c;
                cin >> c;
                if (c == '.')
                    tablero[i][j] = conta++;
            }
        }

        Bipartito grafo(conta);
        bool color = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                color = !color;
                if (tablero[i][j] == -1)
                    continue;
                if (color)
                    grafo.AgregarIzq(ACT);
                else
                    grafo.AgregarDer(ACT);
            }
            if (m % 2 == 0)
                color = !color;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (tablero[i][j] == -1)
                    continue;
                if (j != m - 1 && IZQ != -1)
                    grafo.AgregarArista(ACT, IZQ);
                if (i != n - 1 && DOWN != -1)
                    grafo.AgregarArista(ACT, DOWN);
            }
        }
        auto fichas = grafo.MaxEmp();
        int ans = conta - 2*fichas.size();
        cout << "Case #" << caso++ << ": ";
        cout << ans/2 + (ans%2 == 1) << '\n';
    }
    return 0;
}
