#include <bits/stdc++.h>
using namespace std;

#define POS (i+j)&1
typedef long long Long;

pair<int, int> bishop[2];
Long acc[2];
void update(const int i, const int j, const Long sum) {
    if (sum > acc[POS]) {
        acc[POS] = sum;
        bishop[POS].first  = i;
        bishop[POS].second = j;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<vector<int>> data(N, vector<int>(N));
    vector<Long> D1(2*N + 7), D2(2*N + 7);
    acc[0] = acc[1] = -1;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            cin >> data[i][j];
            D1[i + j]       += data[i][j];
            D2[i - j + N]   += data[i][j];
        }
    
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        update(i, j, D1[i + j] + D2[i - j + N] - data[i][j]);

    cout << acc[0] + acc[1] << '\n';
    cout << bishop[0].first + 1 << ' ' << bishop[0].second + 1 << ' ';
    cout << bishop[1].first + 1 << ' ' << bishop[1].second + 1 << '\n';
    return 0;
}
