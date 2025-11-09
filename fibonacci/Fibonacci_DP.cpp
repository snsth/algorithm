#include <iostream>
#include <vector>
using namespace std;

vector<long long> fibonacci_dp(int n) 
{
    vector<long long> fib(n + 1, 0);

    if (n >= 1) fib[1] = 1;
    if (n >= 2) fib[2] = 1;

    for (int i = 3; i <= n; i++) 
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib;
}

int main() 
{
    int n;
    cout << "몇 개의 피보나치 수를 출력할까? ";
    cin >> n;

    vector<long long> fib = fibonacci_dp(n);

    cout << "피보나치 수열: ";
    for (int i = 1; i <= n; i++) 
    {
        cout << fib[i] << " ";
    }
    cout << endl;
    return 0;
}
