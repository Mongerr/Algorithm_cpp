#include <cstdio>
#include <iostream>

using namespace std;

//주어진 범위의 최소값의 위치를 반환하는 함수
int getMinIndexInRange(int data[], int n, int begin, int end)
{
    int min = begin; //min을 탐색할 가장 첫(왼쪽) 인덱스 begin으로 초기화 
    for(int i = begin+1; i <= end; i++) //탐색할 가장 마지막(오른쪽) 인덱스 end까지 반복
    {
        if(data[i] < data[min]) //최소값의 인덱스 갱신
            min = i;
    }
    return min; //주어진 범위의 최소값의 위치(인덱스) 반환
}

void selectionSort(int data[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int minIndex = getMinIndexInRange(data, n, i, n-1); //배열의 범위(i~n-1)에서 최소값의 위치 minIndex

        //구한 최소값과 i번째 요소의 위치를 변경
        int tmp = data[i];
        data[i] = data[minIndex];
        data[minIndex] = tmp;
    }
}

int main()
{
    int n;
    int *data;

    scanf("%d", &n); //[입력] 전체 데이터의 수 n
    data = new int[n];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]); //[입력] 정수형 데이터 n개 입력
    }

    selectionSort(data, n); //선택정렬 수행 -> data 배열을 오름차순으로 정렬

    for(int i = 0; i < n; i++)
    {
        if(i > 0)
        {
            printf(" "); //각 데이터는 하나의 공백으로 구분
        }
        printf("%d", data[i]); //[출력] 한줄에 n개의 데이터를 오름차순으로 정렬하여 출력
    }

    delete[] data;
    return 0;
}