#include <iostream>
#include <queue>

using namespace std;

int map[10][10]; //인접행렬
int visit[10] = {0}; //정점 방문 정보
queue<int> q;
int num, edge_num;

void bfs(int v)
{
    cout << v << "\n"; //[출력] 방문 정점
    q.push(v); //방문한 정점을 큐에 enQueue
    while(!q.empty()){ //큐가 비어있지 않은 동안 반복(방문한 정점의 인접한 정점 방문)
        int node = q.front();
        q.pop(); //하나의 정점 deQueue
        for(int i = 0; i < num; i++){ //정점의 수만큼 반복하면서
            if(map[node][i] == 1 && visit[i] == 0){ //간선이 존재하고 방문하지 않은 정점일 때
                visit[node] = 1; //정점 방문 표시
                cout << i << "\n"; //[출력]방문 정점
                q.push(i); //방문한 정점을 큐에 enQueue
            }
        }
    }
}

int main(void)
{
    cin >> num >> edge_num; //[압력] 정점의 개수 num, 간선의 개수 edge_num
    for(int i = 0; i < edge_num; i++)
    {
        int v1, v2;
        cin >> v1 >> v2; //[입력] 두 정점 v1과 v2
        map[v1][v2] = map[v2][v1] = 1; //간선 정보 업데이트(무방향 그래프)
    }
    bfs(1); //너비 우선 탐색 1번 정점에서 시작

    return 0;
}