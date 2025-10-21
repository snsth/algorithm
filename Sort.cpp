#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

struct Item 
{
    int value;
    std::string id;
    size_t orig_idx;
};

void print_data(const std::vector<Item>& v, const std::string& title) 
{
    std::cout << "\n== " << title << " ==\n";
    for (size_t i = 0; i < v.size(); ++i) 
    {
        std::cout << i << ": (value=" << v[i].value
            << ", id=" << v[i].id
            << ", orig=" << v[i].orig_idx << ")\n";
    }
}

int main() 
{
    std::vector<Item> data = 
    {
        {50, "id0", 0}, {20, "id1", 1}, {50, "id2", 2}, {40, "id3", 3},
        {50, "id4", 4}, {30, "id5", 5}, {60, "id6", 6}, {60, "id7", 7},
        {10, "id8", 8}, {50, "id9", 9}, {70, "id10", 10}, {60, "id11", 11}
    };

    size_t K = 5;

    std::cout << "=== std ���� �Լ� ���� ===\n";
    std::cout << "1. std::sort (�⺻ ����)\n";
    std::cout << "2. std::stable_sort (���� ����)\n";
    std::cout << "3. std::partial_sort (���� K�� ����)\n";
    std::cout << "4. std::nth_element + stable_partition ���� (Top-K)\n";
    std::cout << "5. std::partial_sort_copy (�κ� ���� ����)\n";
    std::cout << "6. std::is_sorted �˻�\n";
    std::cout << "��ȣ ����: ";

    int choice;
    std::cin >> choice;

    auto cmp_asc = [](const Item& a, const Item& b) 
        {
        return a.value < b.value;
        };
    auto cmp_desc = [](const Item& a, const Item& b) 
        {
        return a.value > b.value;
        };

    switch (choice) 
    {
    case 1: 
    {
        std::sort(data.begin(), data.end(), cmp_asc);
        print_data(data, "std::sort (��������)");
        break;
    }
    case 2: 
    {
        std::stable_sort(data.begin(), data.end(), cmp_asc);
        print_data(data, "std::stable_sort (��������, ��������)");
        break;
    }
    case 3: 
    {
        std::partial_sort(data.begin(), data.begin() + K, data.end(), cmp_desc);
        print_data(data, "std::partial_sort (���� K�� �������� ����)");
        break;
    }
    case 4: 
    {
        // ���� �ڵ� ���
        std::vector<Item> tmp = data;
        auto kth_pos = tmp.begin() + (K - 1);
        std::nth_element(tmp.begin(), kth_pos, tmp.end(), cmp_desc);
        int threshold = kth_pos->value;

        auto is_greater = [threshold](const Item& it) 
        {
            return it.value > threshold;
        };
        std::vector<Item> working = data;
        auto mid_it = std::stable_partition(working.begin(), working.end(), is_greater);
        std::stable_sort(working.begin(), mid_it, cmp_desc);
        std::sort(mid_it, working.end(), cmp_asc);
        print_data(working, "nth_element + stable_partition ���� (Top-K ����)");
        break;
    }
    case 5: 
    {
        std::vector<Item> dest(K);
        std::partial_sort_copy(data.begin(), data.end(), dest.begin(), dest.end(), cmp_desc);
        print_data(dest, "std::partial_sort_copy (Top-K ���� ����)");
        break;
    }
    case 6: 
    {
        bool sorted = std::is_sorted(data.begin(), data.end(), cmp_asc);
        std::cout << (sorted ? "�̹� ������������ ���ĵǾ� �ֽ��ϴ�.\n"
            : "���ĵǾ� ���� �ʽ��ϴ�.\n");

        auto until_it = std::is_sorted_until(data.begin(), data.end(), cmp_asc);
        if (until_it != data.end()) 
        {
            std::cout << "�� ���������� ���ĵ�: value=" << until_it->value
                << " (id=" << until_it->id << ")\n";
        }
        break;
    }
    default:
        std::cout << "�߸��� �Է��Դϴ�.\n";
        break;
    }

    return 0;
}
