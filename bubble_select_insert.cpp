#include <iostream>
#include <vector>
using namespace std;

// -----------------------------------------------------------
// 버블 정렬 (Bubble Sort)
// 인접한 두 요소를 비교하며 큰 값을 뒤로 보내는 방식
// -----------------------------------------------------------
void bubbleSort(vector<int>& arr) 
{
    int n = arr.size();

    // 배열 전체를 순회
    for (int i = 0; i < n - 1; i++) 
    {

        // 마지막 i개는 정렬 완료 상태
        for (int j = 0; j < n - 1 - i; j++) 
        {

            // 인접한 두 값을 비교하여 크면 교환
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// -----------------------------------------------------------
// 선택 정렬 (Selection Sort)
// 매 단계에서 가장 작은 값을 찾아 앞으로 보내는 방식
// -----------------------------------------------------------
void selectionSort(vector<int>& arr) 
{
    int n = arr.size();

    // i번째 위치에 올 최소값을 찾음
    for (int i = 0; i < n - 1; i++) 
    {
        int minIndex = i;

        // i 이후 값 중 최소값의 인덱스를 탐색
        for (int j = i + 1; j < n; j++) 
        {
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j;
            }
        }

        // 최소값을 i번째 위치와 교환
        swap(arr[i], arr[minIndex]);
    }
}

// -----------------------------------------------------------
// 삽입 정렬 (Insertion Sort)
// 이미 정렬된 부분에 값을 삽입하는 방식
// -----------------------------------------------------------
void insertionSort(vector<int>& arr) 
{
    int n = arr.size();

    // 두 번째 원소부터 시작
    for (int i = 1; i < n; i++) 
    {
        int current = arr[i];  // 삽입할 값
        int j = i - 1;

        // 현재 값보다 큰 요소를 한 칸씩 뒤로 이동
        while (j >= 0 && arr[j] > current) 
        {
            arr[j + 1] = arr[j];
            j--;
        }

        // 올바른 위치에 삽입
        arr[j + 1] = current;
    }
}

// -----------------------------------------------------------
// 테스트용 출력 함수
// -----------------------------------------------------------
void printArray(const vector<int>& arr) 
{
    for (int v : arr) cout << v << " ";
    cout << endl;
}

int main() 
{
    vector<int> a = { 5, 2, 9, 1, 3 };
    vector<int> b = a;
    vector<int> c = a;

    cout << "기본 배열: ";
    printArray(a);

    bubbleSort(a);
    cout << "버블 정렬 결과: ";
    printArray(a);

    selectionSort(b);
    cout << "선택 정렬 결과: ";
    printArray(b);

    insertionSort(c);
    cout << "삽입 정렬 결과: ";
    printArray(c);

    return 0;
}
