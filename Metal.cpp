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
        return a.value < b.value; // value�� ū �� ���� ������
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
    const int bag_capacity = 40;  // �賶 �뷮
    float total_value = 0.0f;
    int remaining = bag_capacity;

    // �ִ� �� ���� (��ġ�� ���� �ݼӺ��� ����)
    priority_queue<Metal, vector<Metal>, CompareValue> pq;

    // �ݼӵ��� ���� �ֱ�
    for (const auto& m : metals)
        pq.push(m);

    cout << "=== ������ �ݼ� ��� ===\n";

    // �賶 ä���
    while (!pq.empty() && remaining > 0)
    {
        Metal top = pq.top();
        pq.pop();

        if (top.weight <= remaining)
        {
            // ���� ���� �� ���� ��
            remaining -= top.weight;
            total_value += top.weight * top.value;
            cout << top.Name << " : " << top.weight << "g ���� ����\n";
        }
        else
        {
            // �Ϻθ� ���� ��
            total_value += remaining * top.value;
            cout << top.Name << " : " << remaining << "g�� ����\n";
            remaining = 0; // ���� ��
        }
    }

    cout << "======================\n";
    cout << "�� ��ġ: " << total_value << endl;
    cout << "���� �뷮: " << remaining << "g" << endl;

    return 0;
}