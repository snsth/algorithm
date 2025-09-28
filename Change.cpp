#include <iostream>

using namespace std;


void change(int won)
{
	int F_H = 0;
	int O_H = 0;
	int F_T = 0;
	int O_T = 0;

	while (won >= 500)
	{
		won -= 500;
		F_H++;
	}
	
	while (won >= 100)
	{
		won -= 100;
		O_H++;
	}

	while (won >= 50)
	{
		won -= 50;
		F_T++;
	}

	while (won >= 10)
	{
		won -= 10;
		O_T++;
	}
	
	cout << "500원의 개수 : " << F_H << endl;
	cout << "100원의 개수 : " << O_H << endl;
	cout << "50원의 개수 : " << F_T << endl;
	cout << "10원의 개수 : " << O_T << endl;

}

int main()
{
	change(2650);
	return 0;
}