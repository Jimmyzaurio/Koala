#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9;

struct BIT {
    vector<int> tree;
    BIT(int n) : tree(n + 1) {}

    void Actualizar(int i, int v) {
        while (i < tree.size()) {
            tree[i] = (tree[i] + v) % MOD;
            i += i & -i;
        }
    }

    int Query(int i) {
        int sum = 0;
        while (i > 0) {
            sum = (sum + tree[i]) % MOD;
            i -= i & -i;
        }
        return sum;
    }
};
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n, 1);
    BIT acc(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < k; i++) {
        fill(acc.tree.begin() + i, acc.tree.end(), 0);
        for(int j = n - 1; j >= 0; j--) {
            acc.Actualizar(a[j], b[j]);
            b[j] = acc.Query(a[j] - 1);
            //cout << setw(4) << b[j] << " ";
        }
        //cout << endl;
    }
    cout << acc.Query(n);
    return 0;
}
