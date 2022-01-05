#include <time.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define U 0 //UP
#define R 1 //RIGHT
#define D 2 //DOWN
#define L 3 //LEFT

class Robot{
public:
    int row; //로봇의 좌표가 위치한 행
    int col; //로봇의 좌표가 위치한 열
    int dir; //좌표를 기준으로 로봇의 방향(로봇의 다른 좌표가 있는 방향)
    int time; //좌표까지 이동하는데 걸린 시간

    Robot(){}
    Robot(int r, int c, int d, int t){
        this->row = r;
        this->col = c;
        this->dir = d;
        this->time =t;
    }
};

int N; //rangeCheck함수에서 n을 사용하기 위해
vector<vector<int>> Board; //ragneCheck함수에서 board를 사용하기 위해
queue<pair<Robot, Robot>> Queue; //BFS를 위한 큐(로봇의 두 좌표가 들어감)
bool visited[100][100][4] = {0}; //방문한 좌표인지 확인하기 위해

bool rangeCheck(Robot point[2]) //유효한 좌표인지 확인하는 함수
{   
    for(int i = 0; i < 2; i++) //로봇의 좌표 두 개 모두 검사
    {   
        //좌표가 보드의 범위를 넘었거나
        if(point[i].row < 0 || point[i].row >= N || point[i].col < 0 || point[i].col >= N)
            return false;
        if(visited[point[i].row][point[i].col][point[i].dir]) //이미 방문한 좌표거나
            return false;
        if(Board[point[i].row][point[i].col] == 1) return false; //벽이라면 return false
    }
    return true;
}

//회전하면서 (회전축이 아닌)좌표에 더할 값(U,R,D,L)
int rotate_add[2][4][2] = {{{+1,+1},{+1,-1},{-1,-1},{-1,+1}}, //시계
                            {{+1,-1},{-1,-1},{-1,+1},{+1,+1}}}; //반시계
                        
//회전 시 비어있어야 하는 좌표 계산을 위해
//회전축이 되는 좌표의 방향(dir) 기준(순서: U(0), R(1), D(2), L(3))
int rotate_check[2][4][2] = {{{-1,+1},{+1,+1},{+1,-1},{-1,-1}}, //시계
                            {{-1,-1},{-1,+1},{+1,+1},{+1,-1}}}; //반시계

int rotate(Robot curr_point[2], int way, int i) //회전을 위한 함수
{
    /*
        회전축 좌표의 방향(dir)이 다음처럼 바뀜
        U-시계->R   U-반시계->L
        R-시계->D   R-반시계->U
        D-시계->L   D-반시계->R     시계: U(0)->R(1)->D(2)->L(3)->U
        L-시계->U   L-반시계->D     반시계: L(3)->D(2)->R(1)->U(0)->L
    */
    
    Robot new_point[2]; //새롭게 이동할 좌표 2개
    
    //회전축이 되는 칸의 좌표는 그대로, 방향(dir)은 바뀜
    //시계방향이라면 기존 dir값에 +1, 반시계 방향이라면 +3 후에 4로 나눈 나머지가 새로운 dir값
    new_point[0] = Robot(curr_point[i].row, curr_point[i].col, (curr_point[i].dir +(way ? 3 : 1))%4, curr_point[i].time+1);
    
    //회전축이 아닌 칸의 좌표와 방향은 모두 바뀜
    //(i, (i+1)%2) -> (0, 1) or (1, 0)
    new_point[1] = Robot(curr_point[(i+1)%2].row + rotate_add[way][curr_point[i].dir][0],
                        curr_point[(i+1)%2].col + rotate_add[way][curr_point[i].dir][1], 
                        (curr_point[(i+1)%2].dir +(way ?  3 : 1))%4,
                        curr_point[(i+1)%2].time+1);

    if(rangeCheck(new_point) == false) return 0; //회전한 좌표가 유효하지 않다면 회전 못함

    //회전을 위해 비어있어야 하는 칸이 벽(1)이면 회전 못함
    if(Board[curr_point[i].row + rotate_check[way][curr_point[i].dir][0]][curr_point[i].col + rotate_check[way][curr_point[i].dir][1]] == 1) return 0;

    for(int j = 0; j < 2; j++) //회전 후, 좌표 2개 중에
    {   
        //한 좌표라도 목적지(n,n)에 도착하면 종료
        if(new_point[j].row == N-1 && new_point[j].col == N-1){
            // cout << new_point[i].time << endl;
            return new_point[j].time; //이동에 필요한 시간 return
        }
        //도착하지 않았다면 해당 좌표 방문 체크 후
        visited[new_point[j].row][new_point[j].col][new_point[j].dir] = true;
    }
    //큐에 넣기
    Queue.push(make_pair(new_point[i], new_point[(i+1)%2]));
    return 0;
}

int solution(vector<vector<int>> board)
{
    Board = board; //ragneCheck함수에서 board를 사용하기 위해
    N = board.size(); //rangeCheck함수에서 n을 사용하기 위해

    //로봇의 초기 위치에 해당하는 좌표 두개를 큐에 삽입
    Queue.push(make_pair(Robot(0,0,R,0), Robot(0,1,L,0)));
    
    //방문 체크
    visited[0][0][R] = true;
    visited[0][1][L] = true;
    
    //로봇이 1.상하좌우로 이동하고 2.회전을 하면서 유효한 위치에 있을 때마다 좌표 정보를 큐에 삽입
    while(!Queue.empty()) //큐가 비어있지 않은 동안 반복
    {   
        Robot curr_point[2]; //현재 로봇의 좌표 2개(로봇이 차지하는 칸이 2칸이므로)
        curr_point[0] = Queue.front().first; //로봇의 좌표1
        curr_point[1] = Queue.front().second; //로봇의 좌표2
        Queue.pop(); //큐의 앞 있는 원소(좌표) 삭제
 
        Robot new_point[2]; //새롭게 이동할 좌표 2개

        //상-하-좌-우 이동하며 좌표에 더할 값 (row, col)
        int add[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        //1.상하좌우로 이동하는 경우
        for(int i = 0; i < 4; i++) //0-상, 1-하, 2-좌, 3-우
        {
            for(int j = 0; j < 2; j++) //로봇의 좌표 두개
                //상하좌우 이동은 좌표의 방향(dir)이 그대로 유지됨, 시간은 +1
                new_point[j] = Robot(curr_point[j].row + add[i][0], curr_point[j].col + add[i][1], 
                                    curr_point[j].dir, curr_point[j].time + 1);

            if(!rangeCheck(new_point)) continue; //이동할 좌표가 유효하지 않다면 넘어감

            for(int i = 0; i < 2; i++) //로봇의 좌표 두개
            {   
                //로봇의 한 좌표라도 목적지(n,n)에 도착하면 종료
                if(new_point[i].row == N-1 && new_point[i].col == N-1)
                    return new_point[i].time; //이동에 필요한 시간 return

                //도착하지 않았다면 해당 좌표 방문 체크 후
                visited[new_point[i].row][new_point[i].col][new_point[i].dir] = true;
            }
            //큐에 넣기
            Queue.push(make_pair(new_point[0], new_point[1]));
        }

        //2.회전하는 경우
        for(int way = 0; way < 2; way++){ //시계 방향(0), 반시계 방향(1)
            for(int i = 0; i < 2; i++) //좌표 두개(curr_point[0], curr_point[1])를 각각 회전축으로 설정 
            {     
                int ret = rotate(curr_point, way, i); //회전 후 목적지에 도착하지 못했다면 0을 받음, 도착했다면 시간을 받음
                if(ret) return ret; //시간 return
            }
        }
    }
    //큐가 비게 되면 탐색이 끝남
    return -1; //로봇이 (n,n) 위치로 이동할 수 없을 경우 -1을 return
}

int main()
{  
    int n, x, time;

    cin >> n; //[입력] board의 한 변의 길이(5 <= n <= 100)

    //n*n배열 초기화
    vector<vector<int>> board(n, vector<int>(n, 0));
    
    for(int i = 0; i < n; i++)
    {   
        for(int j = 0; j < n; j++)
        {   
            cin >> x; //[입력] 각 board의 원소(0 또는 1)
            board[i][j] = x;
        }
    }

    clock_t start = clock(); //실행시간 측정 시작
    
    int answer = solution(board);
    cout << answer << endl; //[출력] 로봇이 (n,n) 위치까지 이동하는데 필요한 최소 시간

    clock_t end = clock(); //실행시간 측정 종료

    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}