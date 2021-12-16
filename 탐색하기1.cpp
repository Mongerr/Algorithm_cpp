#include <stdio.h>
#include <iostream>

using namespace std;

int findIndex(int data[], int n, int m)
{
    int index = -1; //아래 반복문에서 찾고자 하는 값을 못찾은 경우 -1을 반환하기 위해 초기화

    for(int i = 0; i <n; i++) //배열의 크기(n)만큼 반복
    {
        if(data[i] == m) //data[i]가 찾고자 하는 값 m과 일치하는 경우
            index = i; //index를 i로 치환
    }

    return index; //index 반환
}

int main()
{
    int n, m;
    int *data;

    scanf("%d %d", &n, &m); //[입력] 배열의 크기 n과 찾고자 하는 값 m
    data = new int[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]); //[입력] n개의 서로 다른 자연수
    }

    int answer = findIndex(data, n, m);
    printf("%d\n", answer); //[출력] m이 존재하는 인덱스(answer)를 정수로 출력

    delete[] data;
    return 0;
}