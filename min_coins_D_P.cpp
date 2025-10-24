#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minCoins(int n, const vector<int>& coins) 
{
    vector<int> dp(n + 1, 1e9); // �ſ� ū ���� �ʱ�ȭ
    dp[0] = 0; // 0���� ���� �� �ʿ��� ���� ���� 0��

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

    return dp[n] == 1e9 ? -1 : dp[n]; // �Ұ����� ��� -1 ��ȯ
}

int main() 
{
    vector<int> coins = { 1, 5, 6 };
    for (int i : {1, 4, 5, 6, 9, 10, 20}) 
    {
        cout << i << " -> " << minCoins(i, coins) << "��" << endl;
    }
    return 0;
}
