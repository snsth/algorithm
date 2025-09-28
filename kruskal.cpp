#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ���� ����ü: �� ������ ����ġ ����
struct Edge 
{
    int u, v, w; 
    bool operator<(const Edge& other) const 
    {
        return w < other.w; // ����ġ ���� �������� ����
    }
};

// Union-Find (Disjoint Set) �ڷᱸ��
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
            parent[x] = find(parent[x]); // ��� ����
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

// Kruskal �˰��� Ŭ����
class Kruskal 
{
private:
    int n; // ���� ����
    vector<Edge> edges;
public:
    Kruskal(int nodes, int arr[6][6]) 
    {
        n = nodes;
        // ������� �� ���� ����Ʈ ��ȯ
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
        sort(edges.begin(), edges.end()); // ���� ����
        DisjointSet ds(n);
        vector<Edge> mst;
        int totalWeight = 0;

        for (auto& e : edges) 
        {
            if (ds.find(e.u) != ds.find(e.v)) { // ����Ŭ ����
                ds.unite(e.u, e.v);
                mst.push_back(e);
                totalWeight += e.w;
            }
        }

        cout << "=== Kruskal MST ��� ===\n";
        for (auto& e : mst) 
        {
            cout << e.u << " - " << e.v << " (����ġ " << e.w << ")\n";
        }
        cout << "MST �� ����ġ: " << totalWeight << endl;
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
