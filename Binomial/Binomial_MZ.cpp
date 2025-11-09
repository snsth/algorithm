#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> mz;
//전역으로 선언한 이유: 재귀 호출이 깊어져도 같은 테이블을 참조 해 이미 계산한 값을 재사용 하기 위함
long long Binomial_mz(int n, int k)
{
	if (k > n) return 0; 
	if (k == 0 || n == k) return 1;

	if (mz[n][k] != -1) // mz[n][k]가 -1이 아니면(이미 구했으면) 그 값을 재사용함
		return mz[n][k];

	mz[n][k] = Binomial_mz(n - 1, k - 1) + Binomial_mz(n - 1, k);
	return mz[n][k];
}

int main()
{
	int n = 10, k = 2;
	mz.assign(n + 1, vector<long long>(n + 1, -1)); //값 덮어쓰기 가능하게 만들어 줌 (이미 전역으로 선언된 mz를 초기화 하기위함)
	//초기값 -1: 아직 계산되지 않았음을 의미 (캐시 미존재 표식)
	cout << Binomial_mz(n, k) << endl;
	return 0;
}