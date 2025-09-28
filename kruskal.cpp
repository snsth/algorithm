#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 간선 구조체: 두 정점과 가중치 저장
struct Edge 
{
    int u, v, w; 
    bool operator<(const Edge& other) const 
    {
        return w < other.w; // 가중치 기준 오름차순 정렬
    }
};

// Union-Find (Disjoint Set) 자료구조
class DisjointSet 
{
private:
    vector<int> parent, rank;
public:
    DisjointSet(int n) 
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) 
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // 경로 압축
        return parent[x];
    }
    void unite(int x, int y) 
    {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
};

// Kruskal 알고리즘 클래스
class Kruskal 
{
private:
    int n; // 정점 개수
    vector<Edge> edges;
public:
    Kruskal(int nodes, int arr[6][6]) 
    {
        n = nodes;
        // 인접행렬 → 간선 리스트 변환
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) 
            {
                if (arr[i][j] != 0) {
                    edges.push_back({ i, j, arr[i][j] });
                }
            }
        }
    }

    void runMST() 
    {
        sort(edges.begin(), edges.end()); // 간선 정렬
        DisjointSet ds(n);
        vector<Edge> mst;
        int totalWeight = 0;

        for (auto& e : edges) 
        {
            if (ds.find(e.u) != ds.find(e.v)) { // 사이클 방지
                ds.unite(e.u, e.v);
                mst.push_back(e);
                totalWeight += e.w;
            }
        }

        cout << "=== Kruskal MST 결과 ===\n";
        for (auto& e : mst) 
        {
            cout << e.u << " - " << e.v << " (가중치 " << e.w << ")\n";
        }
        cout << "MST 총 가중치: " << totalWeight << endl;
    }
};

int main() {
    int arr[6][6] = 
    {
        {0,8,0,2,4,0},
        {8,0,1,4,0,2},
        {0,1,0,0,1,0},
        {2,4,0,0,3,7},
        {4,0,0,3,0,9},
        {0,2,1,7,9,0}
    };

    Kruskal k(6, arr);
    k.runMST();

    return 0;
}
