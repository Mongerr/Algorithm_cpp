#include <cstdio>
#include <iostream>

using namespace std;

void bubbleSort(int data[], int n)
{
    for(int i = 0; i < n; i++)
    {   
        //정렬대상을 뒤에서부터 1씩 감소하면서 수행
        for(int j = 0; j < n-1-i; j++)
        {
            //인접한 두 데이터 비교, 오름차순이 아니면 자리 교환
            if(data[j] > data[j+1])
            {
                int temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    int* data;

    scanf("%d", &n); //[입력] 데이터의 수 n
    data = new int[n];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]); //[입력] 공백으로 구분된 n개의 정수
    }

    bubbleSort(data, n); //버블정렬 수행

    for(int i = 0; i < n; i++)
    {
        if(i > 0)
        {
            printf(" ");
        }
        printf("%d", data[i]); //[출력] 오름차순으로 정렬된 숫자들
    }

    delete[] data;
    return 0;
}