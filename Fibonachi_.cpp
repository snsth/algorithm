#include <iostream>
#include <vector>

using namespace std;

vector<int> fibonachi(int n)
{
	vector<int> fib(n);

	if (n > 0) fib[0] = 1;
	if (n > 1) fib[1] = 1;

	for (int i = 2; i < n; i++)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib;
}

int main()
{
	int n;
	cout << "�� ���� �Ǻ���ġ ���� ����ұ�?";
	cin >> n;

	vector<int> fib = fibonachi(n);

	cout << "�Ǻ���ġ ����: ";
	for (int i = 0; i < fib.size(); i++) 
	{
		cout << fib[i] << " ";
	}
	return 0;
}