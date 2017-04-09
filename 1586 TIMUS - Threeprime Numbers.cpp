#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

const int MOD   = 1e9 + 9;

bool is_prime(int num) {
    if (num == 2)         return true;
    if (num % 2 == 0)     return false;
    
    for (int j = 3; j*j <= num; j += 2)
        if (num % j == 0)
            return false;
    return true;
}

Long memo[9999][100];
vector<int> L[100];

Long dp(int n, int last) {
    if (n == 0)     return 1;
    if (last < 10)  return 0;

    Long &ret = memo[n][last];

    if (ret != -1)
        return ret;

    ret = 0;
    for (int i = L[last].size() - 1; i >= 0; --i)
        ret = (ret % MOD + dp(n - 1, (last * 10 + L[last][i]) % 100) % MOD) % MOD;
    return ret;
}

void precalc() {
    for (int i = 10; i < 100; ++i)
        for (int j = 0; j < 10; ++j)
            if (is_prime(i * 10 + j))
                L[i].push_back(j);
}

int main() {
    precalc();

    int n;
    cin >> n;

    Long ans = 0;
    for (int i = 0; i < 9999; ++i)
        for (int j = 0; j < 100; ++j)
            memo[i][j] = -1;

    for (int i = 10; i < 100; ++i)
        ans = (ans % MOD + dp(n - 2, i) % MOD) % MOD;
    cout << ans << '\n';
    return 0;
}
