#include <time.h>
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

#define MAX_QUEUE_SIZE 8

typedef struct{
    char data[MAX_QUEUE_SIZE]; //톱니 8개의 극(N극 or S극)
    int front, rear; //front는 큐의 첫 번째 요소 하나 앞, rear는 마지막 요소
}DequeType; //덱: 큐의 전단과 후단에서 모두 삽입과 삭제가 가능한 큐

void init_deque(DequeType *q) //덱을 초기화
{
    q->front = q->rear = 0;
}

void add_rear(DequeType *q, int item) //덱의 후단에 item추가(톱니바퀴 초기 상태 설정용)
{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

/*
void deque_print(DequeType *q) //원형큐 출력 함수
{
    printf("\nDEQUE(front=%d, rear=%d) = ", q->front, q->rear);
    int i = q->front;
    do{
        i = (i+1)%(MAX_QUEUE_SIZE);
        printf("%c | ", q->data[i]);
        if(i == q->rear)
            break;
    }while(i != q->front);
}
*/

void clockwise(DequeType *q) //시계방향(1) -> 덱의 마지막 요소를 전단에 추가
{   
    //delete_rear
    int prev = q->rear;
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;

    //add_front
    q->data[q->front] = q->data[prev];
    q->front = (q->front -1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void counter_clockwise(DequeType *q) //반시계 방향(-1) -> 덱의 첫 요소를 후단에 추가
{   
    //delete_front
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;

    //add_rear
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = q->data[q->front];
}

int main()
{   
    DequeType wheel[4]; //톱니바퀴(원형 덱 구현)
    int n;
    int *wheel_num;
    int *way;

    for(int i = 0; i < 4; i++) //톱니바퀴 4개
    {
        init_deque(&wheel[i]);
        for(int j = 0; j < MAX_QUEUE_SIZE; j++) //톱니 8개
        {
            char pole;
            cin >> pole; //[입력] 톱니바퀴의 상태(N극은 0, S극은 1)
            add_rear(&wheel[i], pole);
        }
    }

    cin >> n; //[입력]회전 횟수(1~10)
    wheel_num = new int[n];
    way = new int[n];

    for(int i = 0; i < n; i++)
        cin >> wheel_num[i] >> way[i]; //[입력]회전 방법(톱니바퀴 번호, 회전방향)
    
    clock_t start = clock(); //실행시간 측정 시작

    for(int i = 0; i < n; i++) //회전 횟수만큼 반복
    {
        int check[4] = {0}; //i번째 회전에서 각각의 톱니가 회전하는 방향(1:시계방향, -1:반시계방향, 0:회전x)
        check[wheel_num[i]-1] = way[i]; //지금 회전시킬 톱니바퀴의 방향 저장

        for(int j = wheel_num[i]; j < 4; j++) //오른쪽 톱니바퀴들 검사
        {
            //맞닿은 톱니는 현재 톱니바퀴의 3번과 오른쪽 톱니바퀴의 7번(12시 방향이 1번)
            if(wheel[j-1].data[(wheel[j-1].front+3) % MAX_QUEUE_SIZE] == wheel[j].data[(wheel[j].front+7) % MAX_QUEUE_SIZE])
            {
                break; //톱니끼리 맞닿은 극이 같으면 회전하지 않음(옆옆 톱니바퀴가 있어도 회전하지 않기 때문에 더 이상 검사할 필요 없음)
            }

            //극이 다르면 오른쪽 톱니바퀴의 회전방향을 반대로 설정
            else if(check[j-1] == 1){
                check[j] = -1;
            }
            else{
                check[j] = 1; 
            }
        }

        for(int j = wheel_num[i]; j >= 2; j--) //왼쪽 톱니바퀴들 검사(오른쪽과 같은 원리)
        {
            //맞닿은 톱니는 현재 톱니바퀴의 7번과 왼쪽 톱니바퀴의 3번
            if(wheel[j-1].data[(wheel[j-1].front+7) % MAX_QUEUE_SIZE] == wheel[j-2].data[(wheel[j-2].front+3)  % MAX_QUEUE_SIZE])
            {
                break;
            }
            else if(check[j-1] == 1){
                check[j-2] = -1;
            }
            else{
                check[j-2] = 1;
            }
        }

        for(int j = 0; j < 4; j++) //각각의 톱니가 회전하는 방향에 따라 회전
        {
            if(check[j] == 1)
                clockwise(&wheel[j]);
            else if(check[j] == -1)
                counter_clockwise(&wheel[j]);
        }
    }

    int score = 0; //점수

    //N극은 0 S극은 1, 12시 방향의 S극에만 점수
    for(int i = 0; i < 4; i++)
    {
        // deque_print(&wheel[i]);
        if(wheel[i].data[(wheel[i].front+1) % MAX_QUEUE_SIZE] == '1')
            score += pow(2, i); //i+1번째 톱니바퀴의 12시 방향이 S극이면 2^(i-1)점
    }

    cout << score << endl; //[출력] 총 n번 회전시킨 이후에 네 톱니바퀴의 점수의 합

    clock_t end = clock(); //실행시간 측정 종료
    printf("실행시간: %lf초", (double)(end-start)/(CLOCKS_PER_SEC)); //[출력] 실행시간
    
    return 0;
}