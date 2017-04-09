#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin  >> n;

    vector<int> dp(60006);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; ++i) {
        dp[i] = i;
        for (int j = 1; j*j <= i; ++j)
            dp[i] = min(dp[i], 1 + dp[i - j*j]);
    }

    cout << dp[n];
    return 0;
}
