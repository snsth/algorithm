#include <iostream>
#include <limits.h> // INT_MAX 사용
using namespace std;

#define V 6 // 정점 개수 정의

void Prim_algorithm(int graph[V][V])
{
    int parent[V];   // MST를 저장할 부모 배열
    int key[V];      // 각 정점의 최소 비용 (갱신용)
    bool inMST[V];   // MST에 포함되었는지 여부

    // 1. 초기화
    for (int i = 0; i < V; i++) 
    {
        key[i] = INT_MAX; //각 배열의 key값을 최대로 설정 -> 최소값의 가중치를 넣어야 하니 0으로 설정되어 있으면 안 됌
        inMST[i] = false; //각 배열이 MST에 포함되지 않은 것으로 설정
    }

    // 2. 시작 정점 (0번) 설정
    key[0] = 0;    // 시작점의 비용은 0
    parent[0] = -1; // 루트 노드이므로 부모 없음

    // 3. 모든 정점 포함될 때까지 반복
    for (int count = 0; count < V - 1; count++) 
    {
        // (1) MST에 포함되지 않은 정점 중 최소 key값 정점 찾기
        int minKey = INT_MAX, u = -1;

        for (int v = 0; v < V; v++)
        {
            if (!inMST[v] && key[v] < minKey)
            {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true; // 선택된 정점을 MST에 포함

        // (2) 인접 정점들의 key값 갱신
        for (int v = 0; v < V; v++) 
        {
            // 간선이 존재하고, MST에 포함되지 않았으며, 더 작은 비용이라면 갱신
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = graph[u][v];
                cout << "간선 추가: " << u << " - " << v << " (가중치 " << graph[u][v] << ")\n";
            }
        }
    }

    // 4. 결과 출력
    cout << "간선\t가중치\n";
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
