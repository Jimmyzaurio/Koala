#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

typedef int Flujo; // Ajustable.

typedef vector<int> Lista;
typedef pair<int, int> Par;
typedef vector<Flujo> Flujo1D;
typedef vector<Flujo1D> Flujo2D;

const Flujo FINF = 1 << 30;

// EMPAREJAMIENTO BIPARTITO
// Nodos indexados de 0 a n - 1.

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

    vector<Par> MaxEmparejamiento() {
        fill(pareja.begin(), pareja.end(), -1);
        for (int i = 0; i < n; ++i) {
            if (!lado[i]) continue; CaminoIncremental(i);
            fill(visitado.begin(), visitado.end(), false);
        }
        vector<Par> pares;
        for (int i = 0; i < n; ++i)
            if (!lado[i] && pareja[i] != -1)
                pares.push_back(Par(pareja[i], i));
        return pares; // Cardinalidad = pares.size()
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    while (cin >> n) {
        vector<vector<pii>> board(n, vector<pii>(n, pii(-1, -1)));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                char c;
                cin >> c;
                if (c == '.')
                    board[i][j] = pii(0, 0);
            }
        int col = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n;) {
                while (j < n && board[i][j].first == -1)
                    j++;
                if (j == n)
                    break;
                while (j < n && board[i][j].first != -1)
                    board[i][j].first = col, j++;
                col++;
            }
        }

        int fil = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n;) {
                while (j < n && board[j][i].first == -1)
                    j++;
                if (j == n)
                    break;
                while (j < n && board[j][i].first != -1)
                    board[j][i].second = fil, j++;
                fil++;
            }
        }

        Bipartito ans(fil + col);
        for (int i = 0; i < col; i++)
            ans.AgregarIzq(i);
        for (int i = 0; i < fil; i++)
            ans.AgregarDer(i + col);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (board[i][j].first != -1)
                    ans.AgregarArista(board[i][j].first, col + board[i][j].second);
        auto empareja = ans.MaxEmparejamiento();
        cout << empareja.size() << '\n';
    }
    return 0;
}
