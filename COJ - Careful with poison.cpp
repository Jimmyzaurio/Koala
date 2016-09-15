#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const Long MOD = 1000000007;
const Long MAX = 2000007;

Long Exponenciar(Long a, Long n, Long m) {
    Long res = 1, p = a;
    for (; n; n >>= 1) {
        if (n & 1) res =
            (res * p) % m;
        p = (p * p) % m;
    }
    return res;
}

Long fact[MAX];
void pre(Long tam) {
    fact[0] = 1;
    for (Long i = 1; i <= tam; i++)
        fact[i] = (i * fact[i - 1]) % MOD;
}

Long combina(Long n, Long k) {
    Long num = fact[n];
    Long den = Exponenciar(((fact[n - k]) * (fact[k])) % MOD, MOD - 2, MOD);
    return (num * den) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Long N, x, y;
    pre(MAX - 5);
    while (cin >> N && N != 0) {
        cin >> x >> y;
        Long ans = 0;
        for (int i = x + 2, j = y, k = 0; k < 3; k++, i--, j++)
            ans = (ans + (combina(i + j, i) * combina(2 * N - j - i, N - i)) % MOD) % MOD;
        cout << (combina(2 * N, N) - ans + MOD) % MOD << "\n";
    }
    return 0;
}
