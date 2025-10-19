#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Metal
{
	string Name;
	int weight;
	float value;
};

struct CompareValue
{
    bool operator()(const Metal& a, const Metal& b) const
    {
        return a.value < b.value; // value가 큰 게 먼저 오도록
    }
};

vector<Metal> metals =
{
	{"platinum", 10, 6},
	{"gold", 15, 5},
	{"silver", 25, 0.4},
	{"iron", 50, 0.1}
};


int main()
{
    const int bag_capacity = 40;  // 배낭 용량
    float total_value = 0.0f;
    int remaining = bag_capacity;

    // 최대 힙 생성 (가치가 높은 금속부터 꺼냄)
    priority_queue<Metal, vector<Metal>, CompareValue> pq;

    // 금속들을 힙에 넣기
    for (const auto& m : metals)
        pq.push(m);

    cout << "=== 선택한 금속 목록 ===\n";

    // 배낭 채우기
    while (!pq.empty() && remaining > 0)
    {
        Metal top = pq.top();
        pq.pop();

        if (top.weight <= remaining)
        {
            // 전부 담을 수 있을 때
            remaining -= top.weight;
            total_value += top.weight * top.value;
            cout << top.Name << " : " << top.weight << "g 전부 담음\n";
        }
        else
        {
            // 일부만 담을 때
            total_value += remaining * top.value;
            cout << top.Name << " : " << remaining << "g만 담음\n";
            remaining = 0; // 가득 참
        }
    }

    cout << "======================\n";
    cout << "총 가치: " << total_value << endl;
    cout << "남은 용량: " << remaining << "g" << endl;

    return 0;
}