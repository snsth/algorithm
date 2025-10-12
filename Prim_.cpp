#include <iostream>
#include <limits.h> // INT_MAX ���
using namespace std;

#define V 6 // ���� ���� ����

void Prim_algorithm(int graph[V][V])
{
    int parent[V];   // MST�� ������ �θ� �迭
    int key[V];      // �� ������ �ּ� ��� (���ſ�)
    bool inMST[V];   // MST�� ���ԵǾ����� ����

    // 1. �ʱ�ȭ
    for (int i = 0; i < V; i++) 
    {
        key[i] = INT_MAX; //�� �迭�� key���� �ִ�� ���� -> �ּҰ��� ����ġ�� �־�� �ϴ� 0���� �����Ǿ� ������ �� ��
        inMST[i] = false; //�� �迭�� MST�� ���Ե��� ���� ������ ����
    }

    // 2. ���� ���� (0��) ����
    key[0] = 0;    // �������� ����� 0
    parent[0] = -1; // ��Ʈ ����̹Ƿ� �θ� ����

    // 3. ��� ���� ���Ե� ������ �ݺ�
    for (int count = 0; count < V - 1; count++) 
    {
        // (1) MST�� ���Ե��� ���� ���� �� �ּ� key�� ���� ã��
        int minKey = INT_MAX, u = -1;

        for (int v = 0; v < V; v++)
        {
            if (!inMST[v] && key[v] < minKey)
            {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true; // ���õ� ������ MST�� ����

        // (2) ���� �������� key�� ����
        for (int v = 0; v < V; v++) 
        {
            // ������ �����ϰ�, MST�� ���Ե��� �ʾ�����, �� ���� ����̶�� ����
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = graph[u][v];
                cout << "���� �߰�: " << u << " - " << v << " (����ġ " << graph[u][v] << ")\n";
            }
        }
    }

    // 4. ��� ���
    cout << "����\t����ġ\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
}

int main()
{
    int arr[6][6] =
    {
        {0, 8, 0, 2, 4, 0},
        {8, 0, 1, 4, 0, 2},
        {0, 1, 0, 0, 1, 0},
        {2, 4, 0, 0, 3, 7},
        {4, 0, 0, 3, 0, 9},
        {0, 2, 1, 7, 9, 0}
    };

    Prim_algorithm(arr);

    return 0;
}
