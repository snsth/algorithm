#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Item // 물건들의 값을 저장할 구조체
{
	string name;
	int weight;
	int value;
};


int main()
{
	vector <Item> items =
	{
		{"silver",   10,  60},
		{"gold",     20, 100},
		{"platinum", 30, 120},
		{"diamond",  40, 200}
	};

	int BP = 50; // 배낭 크기
	vector<int> dp(BP + 1, 0);  
	// dp[w]는 배낭 허용 무게가 w일 때 얻을 수 있는 최대 가치
    // 크기 BP+1로 생성 (0~BP까지 사용)

	for (const auto& item : items) // 
	{
		for (int w = BP; w >= item.weight; w--) // 
		{
			dp[w] = max(dp[w], dp[w - item.weight] + item.value);
		}
	}
	cout << "배낭 최대 값어치 = " << dp[BP] << endl;
	return 0;
}