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

    std::cout << "=== std 정렬 함수 데모 ===\n";
    std::cout << "1. std::sort (기본 정렬)\n";
    std::cout << "2. std::stable_sort (안정 정렬)\n";
    std::cout << "3. std::partial_sort (상위 K개 정렬)\n";
    std::cout << "4. std::nth_element + stable_partition 조합 (Top-K)\n";
    std::cout << "5. std::partial_sort_copy (부분 복사 정렬)\n";
    std::cout << "6. std::is_sorted 검사\n";
    std::cout << "번호 선택: ";

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
        print_data(data, "std::sort (오름차순)");
        break;
    }
    case 2: 
    {
        std::stable_sort(data.begin(), data.end(), cmp_asc);
        print_data(data, "std::stable_sort (오름차순, 안정정렬)");
        break;
    }
    case 3: 
    {
        std::partial_sort(data.begin(), data.begin() + K, data.end(), cmp_desc);
        print_data(data, "std::partial_sort (상위 K개 내림차순 정렬)");
        break;
    }
    case 4: 
    {
        // 기존 코드 기반
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
        print_data(working, "nth_element + stable_partition 조합 (Top-K 정렬)");
        break;
    }
    case 5: 
    {
        std::vector<Item> dest(K);
        std::partial_sort_copy(data.begin(), data.end(), dest.begin(), dest.end(), cmp_desc);
        print_data(dest, "std::partial_sort_copy (Top-K 복사 정렬)");
        break;
    }
    case 6: 
    {
        bool sorted = std::is_sorted(data.begin(), data.end(), cmp_asc);
        std::cout << (sorted ? "이미 오름차순으로 정렬되어 있습니다.\n"
            : "정렬되어 있지 않습니다.\n");

        auto until_it = std::is_sorted_until(data.begin(), data.end(), cmp_asc);
        if (until_it != data.end()) 
        {
            std::cout << "이 지점까지는 정렬됨: value=" << until_it->value
                << " (id=" << until_it->id << ")\n";
        }
        break;
    }
    default:
        std::cout << "잘못된 입력입니다.\n";
        break;
    }

    return 0;
}
