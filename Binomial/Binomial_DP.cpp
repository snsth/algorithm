#include <iostream>
#include <vector>

using namespace std;

long long binomial_DP(int n, int k) 
{
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));

    for (int i = 0; i <= n; i++) 
    {
        for (int j = 0; j <= min(i, k); j++)  //i보다 큰 k는 필요없음(0이기 때문에) k보다 큰 j도 필요없음 (조건 완료) 그래서 min을 씀
        {
            if (j == 0 || j == i)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    return dp[n][k];
}

int main() 
{
    int n = 10, k = 2;
    cout << "DP 방식: " << binomial_DP(n, k) << "\n";
    return 0;
}