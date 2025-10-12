#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

/*
 * 부산 지하철 간결 확장 버전
 * 기능:
 * 1. 출발~도착 최단 경로 탐색 (BFS)
 * 2. 각 역의 노선번호 정보 저장
 * 3. 출력 시 노선 전환(환승) 지점 표시 및 환승 횟수 계산
 */

 // ------------------- 전역 변수 -------------------
unordered_map<string, vector<string>> graph;         // 인접 리스트 그래프
unordered_map<string, vector<int>> stationLines;     // 각 역의 소속 노선 정보

// ------------------- 그래프 빌드 함수 -------------------
void addConnection(const string& a, const string& b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

// 역이 속한 노선 등록 (1~4호선)
void addLine(const string& station, int line) {
    stationLines[station].push_back(line);
}

void buildGraph() {
    // === 1호선 ===
    addLine("노포", 1); addLine("범어사", 1); addLine("남산", 1);
    addLine("두실", 1); addLine("온천장", 1); addLine("연산", 1);
    addLine("시청", 1); addLine("서면", 1); addLine("범내골", 1);

    addConnection("노포", "범어사");
    addConnection("범어사", "남산");
    addConnection("남산", "두실");
    addConnection("두실", "온천장");
    addConnection("온천장", "연산");
    addConnection("연산", "시청");
    addConnection("시청", "서면");
    addConnection("서면", "범내골");

    // === 2호선 ===
    addLine("양산", 2); addLine("남양산", 2); addLine("부산대", 2);
    addLine("장전", 2); addLine("연산", 2); addLine("서면", 2);
    addLine("부암", 2); addLine("대연", 2); addLine("경성대부경대", 2);
    addLine("광안", 2); addLine("센텀시티", 2); addLine("해운대", 2);

    addConnection("양산", "남양산");
    addConnection("남양산", "부산대");
    addConnection("부산대", "장전");
    addConnection("장전", "연산");
    addConnection("연산", "서면");
    addConnection("서면", "부암");
    addConnection("부암", "대연");
    addConnection("대연", "경성대부경대");
    addConnection("경성대부경대", "광안");
    addConnection("광안", "센텀시티");
    addConnection("센텀시티", "해운대");

    // === 3호선 ===
    addLine("대저", 3); addLine("강서구청", 3);
    addLine("덕천", 3); addLine("만덕", 3);
    addLine("연산", 3); addLine("미남", 3);

    addConnection("대저", "강서구청");
    addConnection("강서구청", "덕천");
    addConnection("덕천", "만덕");
    addConnection("만덕", "연산");
    addConnection("연산", "미남");

    // === 4호선 ===
    addLine("미남", 4); addLine("동래", 4);
    addLine("수안", 4); addLine("충렬사", 4);
    addLine("명장", 4); addLine("서동", 4);
    addLine("안락", 4); addLine("연산", 4);

    addConnection("미남", "동래");
    addConnection("동래", "수안");
    addConnection("수안", "충렬사");
    addConnection("충렬사", "명장");
    addConnection("명장", "서동");
    addConnection("서동", "안락");
    addConnection("안락", "연산");
}

// ------------------- BFS 탐색 -------------------
vector<string> bfsShortestPath(const string& start, const string& goal) {
    queue<string> q;
    unordered_map<string, bool> visited;
    unordered_map<string, string> prev;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        if (cur == goal) break;

        for (const string& next : graph[cur]) {
            if (!visited[next]) {
                visited[next] = true;
                prev[next] = cur;
                q.push(next);
            }
        }
    }

    // 경로 복원
    vector<string> path;
    if (!visited[goal]) return {};

    for (string at = goal; !at.empty(); at = prev[at]) {
        path.push_back(at);
        if (at == start) break;
    }
    reverse(path.begin(), path.end());
    return path;
}

// ------------------- 노선 정보 추적 및 출력 -------------------
int findCommonLine(const string& a, const string& b) {
    // 두 역이 속한 노선 중 공통 노선 찾기
    for (int la : stationLines[a]) {
        for (int lb : stationLines[b]) {
            if (la == lb) return la;
        }
    }
    return -1; // 공통 노선 없음 (환승)
}

void printPathWithLines(const vector<string>& path) {
    if (path.empty()) {
        cout << " 경로를 찾을 수 없습니다.\n";
        return;
    }

    cout << "\n 최단 경로 (" << path.size() - 1 << "개 역 이동)\n";

    int transfers = 0;
    int currentLine = -1;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int line = findCommonLine(path[i], path[i + 1]);
        if (line == -1) line = currentLine; // 예외 처리
        if (currentLine == -1) currentLine = line;

        cout << "[" << line << "호선] " << path[i];

        // 노선이 바뀌면 환승 표시
        if (line != currentLine && i > 0) {
            cout << " (환승)";
            transfers++;
        }
        currentLine = line;

        cout << " → ";
    }

    cout << "[" << currentLine << "호선] " << path.back() << "\n";
    cout << "총 환승 횟수: " << transfers << "회\n";
}

// ------------------- 메인 -------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    buildGraph();

    string start, goal;
    cout << "출발역 입력: ";
    cin >> start;
    cout << "도착역 입력: ";
    cin >> goal;

    vector<string> path = bfsShortestPath(start, goal);
    printPathWithLines(path);

    return 0;
}
