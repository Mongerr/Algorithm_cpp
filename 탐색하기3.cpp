#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

int findIndex(int data[], int n)
{   
    int sum = 0, x =0; //평균과 가장 가까운 데이터의 인덱스 x 초기화
    for(int i = 0; i < n; i++)
    {
        sum += data[i]; //모든 데이터의 합 sum
    }

    for(int i = 0; i < n; i++)
    {
        //sum = 평균*n
        //sum과 각 데이터 값*n 사이의 거리(절댓값) -> 각 데이터 값의 평균과의 거리
        int dx = abs(n*data[x] - sum);
        int di = abs(n*data[i] - sum);

        if(dx > di) //평균과 더 가까운 데이터가 존재하면
            x = i; //인덱스 값 x를 갱신
    }
    return x+1; //배열의 인덱스는 0부터 시작하므로 1을 더함
}

int main()
{
    int n;
    int *data;

    scanf("%d", &n); //[입력] 데이터의 수 n
    data = new int[n];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]); //[입력] 각 수치 데이터(-100,000 이상 100,000 이하의 정수)
    }

    int answer = findIndex(data, n); //가장 평균과 가까운 데이터의 번호(answer)
    printf("%d %d\n", answer, data[answer-1]); //[출력] 평균과 가장 거리가 가까운 데이터의 번호와 그 값

    delete[] data;
    return 0;
}