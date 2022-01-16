#include <time.h>
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

#define MAX_QUEUE_SIZE 8
typedef struct{
    char data[MAX_QUEUE_SIZE];
    int front, rear;
}DequeType;

void init_deque(DequeType *q)
{
    q->front = q->rear = 0;
}

void deque_print(DequeType *q)
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

void add_rear(DequeType *q, int item)
{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

void add_front(DequeType *q, int item)
{
    q->data[q->front] = item;
    q->front = (q->front -1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

char delete_rear(DequeType *q)
{
    int prev = q->rear;
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}

char delete_front(DequeType *q)
{
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

void clockwise(DequeType *q) //시계방향(1) (delete_rear -> add_front)
{
    int prev = q->rear;
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;

    q->data[q->front] = q->data[prev];
    q->front = (q->front -1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void counter_clockwise(DequeType *q) //반시계 방향(-1) (delete_front -> add_rear) 
{
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = q->data[q->front];
}

int main()
{
    DequeType wheel[4];
    int n;

    for(int i = 0; i < 4; i++)
    {
        init_deque(&wheel[i]);
        for(int j = 0; j < MAX_QUEUE_SIZE; j++)
        {
            char pole;
            cin >> pole;
            add_rear(&wheel[i], pole);
        }
    }

    cin >> n;

    for(int i = 0; i < n; i++)
    {
        int wheel_num, way;
        cin >> wheel_num >> way;

        int check[4] = {0};
        check[wheel_num-1] = way;
        for(int j = wheel_num; j < 4; j++) //오른쪽 검사
        {
            // cout << "오른쪽: " << j << endl;
            if(wheel[j-1].data[(wheel[j-1].front+3) % MAX_QUEUE_SIZE] == wheel[j].data[(wheel[j].front+7) % MAX_QUEUE_SIZE])
            {
                break;
            }
            else if(check[j-1] == 1){
                check[j] = -1;
            }
            else{
                check[j] = 1;
            }
        }
        for(int j = wheel_num; j >= 2; j--) //왼쪽 검사
        {
            // cout << "왼쪽: " << j << endl;
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

        for(int j = 0; j < 4; j++)
        {
            // cout << check[j] <<endl;
            if(check[j] == 1)
                clockwise(&wheel[j]);
            else if(check[j] == -1)
                counter_clockwise(&wheel[j]);
        }
    }

    int score = 0;

    //N극은 0 S극은 1, S극에 점수
    for(int i = 0; i < 4; i++)
    {
        // deque_print(&wheel[i]);
        if(wheel[i].data[(wheel[i].front+1) % MAX_QUEUE_SIZE] == '1')
            score += pow(2, i);
    }

    cout << score << endl;

    return 0;
}