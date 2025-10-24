#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minCoins(int n, const vector<int>& coins) 
{
    vector<int> dp(n + 1, 1e9); // 매우 큰 수로 초기화
    dp[0] = 0; // 0원을 만들 때 필요한 동전 수는 0개

    for (int i = 1; i <= n; i++) 
    {
        for (int coin : coins) 
        {
            if (i - coin >= 0) 
            {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[n] == 1e9 ? -1 : dp[n]; // 불가능한 경우 -1 반환
}

int main() 
{
    vector<int> coins = { 1, 5, 6 };
    for (int i : {1, 4, 5, 6, 9, 10, 20}) 
    {
        cout << i << " -> " << minCoins(i, coins) << "개" << endl;
    }
    return 0;
}
