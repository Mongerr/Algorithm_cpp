#include <iostream>

using namespace std;

int maps[10][10];
int visited[10] = {0};
int num;

void init(){ //maps(인접행렬) 초기화
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            maps[i][j] = 0; //0은 간선이 없음을 의미함
}

void dfs(int v)
{
    cout << v << endl; //[출력] 방문 정점
    visited[v] = 0; //정점 방문 정보 업데이트(방문 완료)
    for(int i = 0; i <= num; i++) //간선의 수만큼 반복하면서
    {
        if(maps[v][i] && visited[i]) //간선이 존재하고 방문하지 않은 정점일 때
            dfs(i); //정점 i로 깊이 우선 탐색
    }
}

int main(void)
{
    int v1, v2;
    init(); //maps(인접행렬) 초기화
    cin >> num; //[압력] 간선의 개수
    for(int i = 0; i < num; i++)
    {
        cin >> v1 >> v2; //[입력] 두 정점 v1과 v2
        maps[v1][v2] = maps[v2][v1] = 1; //간선 정보 업데이트(무방향 그래프)
        visited[v1] = visited[v2] = 1; //정점 방문 정보 업데이트
    }
    dfs(1); //깊이 우선 탐색 1번 정점에서 시작

    return 0;
}