#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

template<class T>
struct SegTree {
  T dato, lazy; int i, d;
  SegTree* izq, *der;

  SegTree(int I, int D)
    : izq(NULL), der(NULL),
      i(I), d(D), dato(), lazy(0) {}

  ~SegTree() {
    if (izq) delete izq;
    if (der) delete der;
  }

  T Construir() {
    if (i == d) return dato = T();
    int m = (i + d) >> 1;
    izq = new SegTree(i, m);
    der = new SegTree(m + 1, d);
    return dato = izq->Construir() +
                  der->Construir();
  }

  void propagate() {
    if (lazy != 0) {
      if (izq) {
        izq->lazy = izq->lazy + lazy;
        der->lazy = der->lazy + lazy;
      }
      dato += lazy;
      lazy = 0;
    }
  }

  T ActualizarRango(int l, int r, T v) {
    propagate();
    if (r < i || d < l) return dato;
    if (l <= i && d <= r) {
      dato += v;
      if (izq) {
        izq->lazy += v;
        der->lazy += v;
      }
      return dato;
    }
    return dato = izq->ActualizarRango(l, r, v) +
                  der->ActualizarRango(l, r, v);
  }

  T Query(int a, int b) {
    if (b < i || d < a) return T();
    propagate();
    if (a <= i && d <= b) return dato;
    return izq? izq->Query(a, b) +
                der->Query(a, b): T();
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<vector<int>> divs(300007);
  divs[1].push_back(1);
  for (int i = 2; i <= 300000; ++i) {
    for (int j = 1; j * j <= i; ++j)
      if (i % j == 0)
        divs[i].push_back(j);
      divs[i].push_back(i);
  }

  int n, q;
  cin >> n;

  vector<Long> data(n);
  SegTree<Long> experiment(0, n - 1);
  experiment.Construir();

  for (int i = 0; i < n; ++i)
    cin >> data[i];

  cin >> q;
  for (int i = 0; i < q; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int num;
      cin >> num;
      Long ans = 0;
      for (int d : divs[num]) {
        //cout << experiment.Query(d - 1, d - 1) << "  " ;
        ans += experiment.Query(d - 1, d - 1);
      }
      //cout << "\\\n";
      cout << ans + data[num - 1] << '\n';
    } else {
      int l, r, d;
      cin >> l >> r >> d;
      if (d > 0)
        experiment.ActualizarRango(l - 1, r - 1, d);
    }
  }
  return 0;
}
