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
    int dir; //좌표를 기준으로 로봇의 방향(로봇의 다른 좌표의 방향)
    int time; //좌표까지 이동하는데 걸린 시간

    Robot(){}
    Robot(int r, int c, int d, int t){
        this->row = r;
        this->col = c;
        this->dir = d;
        this->time =t;
    }
};

vector<vector<int>> Board;
bool visited[100][100][4] = {0}; //방문한 좌표인지 확인하기 위해

bool rangeCheck(Robot point[2], int n) //유효한 좌표인지 확인하는 함수
{   
    for(int i = 0; i < 2; i++) //로봇의 좌표 두개 모두 검사
    {   
        cout << "rangeCheck: " << point[i].row << ',' << point[i].col << endl;
        //보드의 범위를 넘었거나
        if(point[i].row < 0 || point[i].row >= n || point[i].col < 0 || point[i].col >= n)
        {   cout << "보드의 범위를 넘음" << endl;
            return false;
        }
        if(visited[point[i].row][point[i].col][point[i].dir]) //이미 방문한 좌표거나
        { 
            cout << "이미 방문" << endl;
            return false;
        }
        if(Board[point[i].row][point[i].col] == 1){
             cout << "벽" << endl;
             return false; //벽이라면 return false
        }
    }
    cout << "return true" << endl;
    return true;
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
   
    cout << endl;
    for(int i = 0; i < n; i++)
    {   
        for(int j = 0; j < n; j++)
            cout << board[i][j] <<' ';
        cout << endl;
    }

    Board = board; //ragneCheck함수에서 board를 사용하기 위해

    queue<pair<Robot, Robot>> Queue; //BFS를 위한 큐

    //로봇의 초기 위치에 해당하는 좌표 두개를 큐에 삽입
    Queue.push(make_pair(Robot(0,0,R,0), Robot(0,1,L,0)));
    
    //방문 체크
    visited[0][0][R] = true;
    visited[0][1][L] = true;

    while(!Queue.empty())
    {   
        Robot curr_point[2]; //현재 로봇의 좌표 2개(로봇이 차지하는 칸이 2칸이므로)
        curr_point[0] = Queue.front().first; //로봇의 좌표1
        curr_point[1] = Queue.front().second; //로봇의 좌표2
        Queue.pop();
 
        Robot new_point[2]; //이동할 좌표 2개

        //상하좌우 이동하며 좌표에 더할 값 (row, col)
        int add[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        //상하 좌우로 이동하는 경우
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 2; j++) //로봇의 좌표 두개
            {   
                //상하좌우 이동에서 방향은 그대로, 시간은 +1
                new_point[j] = Robot(curr_point[j].row + add[i][0], curr_point[j].col + add[i][1], curr_point[j].dir, curr_point[j].time + 1);
                cout << i << "로 이동: " << new_point[j].row << ',' << new_point[j].col << endl;
            }

            if(rangeCheck(new_point, n)) //이동할 좌표가 유효하다면
            {
                for(int i = 0; i < 2; i++)
                {   
                    //로봇의 한 좌표라도 목적지(n,n)에 도착하면 종료
                    if(new_point[i].row == n-1 && new_point[i].col == n-1){
                        cout << time << endl;
                        return 0;
                    }
                    //도착하지 않았다면 해당 좌표 방문 체크 후
                    visited[new_point[i].row][new_point[i].col][new_point[i].dir] = true;
                }
                //큐에 넣기
                Queue.push(make_pair(new_point[0], new_point[1]));
                cout << Queue.front().first.row << endl;
            }
            cout << "상하좌우: " << i << " 끝" << endl;
        }
        
        cout << "이동 끝 회전 시작" << endl;

        //회전을 위해 비어있어야 하는 좌표 계산
        //회전축 좌표의 방향(dir) 기준(순서: U,R,D,L)
        int rotate_check[2][4][2] = {{{-1,+1},{+1,+1},{+1,-1},{-1,-1}}, {{-1,-1},{-1,+1},{+1,+1},{+1,-1}}}; //시계, 반시계

        //회전하면서 (회전축이 아닌)좌표에 더할 값(U,R,D,L)
        int rotate_add[2][4][2] = {{{+1,+1},{+1,-1},{-1,-1},{-1,+1}}, {{+1,-1},{-1,-1},{-1,+1},{+1,+1}}}; //시계, 반시계

        //회전하는 경우
        for(int way = 0; way < 2; way++) //시계 방향(0), 반시계 방향(1)
        {
            for(int i = 0; i < 2; i++) //좌표 두개(curr_point[0], curr_point[1])를 각각 회전축으로 설정 
            {     
                cout << "dddd: " << i << endl;
                /*
                회전축 좌표의 방향을 기준으로
                U-시계->R   U-반시계->L
                R-시계->D   R-반시계->U
                D-시계->L   D-반시계->R     시계: U(0)->R(1)->D(2)->L(3)->U
                L-시계->U   L-반시계->D     반시계: L(3)->D(2)->R(1)->U(0)->L
                */
                
                //회전을 위해 비어있어야 하는 칸이 벽(1)이면 회전 못함
                if(board[curr_point[i].row + rotate_check[way][curr_point[i].dir][0]][curr_point[i].col + rotate_check[way][curr_point[i].dir][1]] == 1)
                {   cout << "안비었음" << endl; 
                    continue;
                }

                cout << "여기는?" << endl;
                //회전축이 되는 칸의 좌표는 그대로, 방향(dir)은 바뀜
                //회전축이 아닌 칸의 좌표와 방향 모두 바뀜
                if(way == 0) //시계
                {   
                    cout << "시계 회전" << endl;
                    new_point[0] = Robot(curr_point[i].row, curr_point[i].col, (curr_point[i].dir +1)%4, curr_point[i].time+1);
                    new_point[1] = Robot(curr_point[(i+1)%2].row + rotate_add[way][curr_point[i].dir][0], curr_point[(i+1)%2].col + rotate_add[way][curr_point[i].dir][1], (curr_point[i].dir +1)%4, curr_point[i].time+1);
                } 
                else //반시계
                {
                    cout << "반시계 회전" << endl;
                    new_point[0] = Robot(curr_point[i].row, curr_point[i].col, (curr_point[i].dir +3)%4, curr_point[i].time+1);
                    new_point[1] = Robot(curr_point[(i+1)%2].row + rotate_add[way][curr_point[i].dir][0], curr_point[(i+1)%2].col + rotate_add[way][curr_point[i].dir][1], (curr_point[i].dir +3)%4, curr_point[i].time+1);
                }
                cout << "회전: 축(" << new_point[0].row << ',' << new_point[0].col << "), " << new_point[1].row << ',' << new_point[1].col << endl;
            
                if(rangeCheck(new_point, n)) //이동할 좌표가 유효하다면
                {
                    for(int i = 0; i < 2; i++)
                    {   
                        //로봇의 한 좌표라도 목적지(n,n)에 도착하면 종료
                        if(new_point[i].row == n-1 && new_point[i].col == n-1){
                            cout << time << endl;
                            return 0;
                        }
                        //도착하지 않았다면 해당 좌표 방문 체크 후
                        visited[new_point[i].row][new_point[i].col][new_point[i].dir] = true;
                    }
                    //큐에 넣기
                    Queue.push(make_pair(new_point[0], new_point[1]));
                }

                cout << "축 하나 회전 하나 끝 i: " << i << endl;
            }
        }
    }

    clock_t end = clock(); //실행시간 측정 종료

    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}