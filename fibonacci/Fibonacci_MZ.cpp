#include <iostream>
#include <vector>
using namespace std;

vector<long long> mz;  // 캐시 (전역 또는 main에서 전달 가능)

// 재귀 함수 (n번째 피보나치 수를 반환)
long long fibonacci_mz(int n) 
{
    // 음수나 0 입력 방어
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;

    // 이미 계산된 값이 있으면 그대로 반환
    if (mz[n] != -1)
        return mz[n];

    // 계산 안 된 경우 → 점화식 적용 후 저장
    mz[n] = fibonacci_mz(n - 1) + fibonacci_mz(n - 2);
    return mz[n];
}

int main() 
{
    int n;
    cout << "몇 개의 피보나치 수를 출력할까? ";
    cin >> n;

    // 메모이제이션 테이블 초기화 (-1: 아직 계산 안 함)
    mz.assign(n + 1, -1);

    cout << "피보나치 수열: ";
    for (int i = 1; i <= n; i++) 
    {
        cout << fibonacci_mz(i) << " ";
    }
    cout << endl;
    return 0;
}
