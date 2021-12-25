#include <cstdio>
#include <iostream>

using namespace std;

bool inConsecutive(int data[], int n)
{
    int max_data = data[0];
    int min_data = data[0];

    //에피소드의 최대, 최소 번호 찾기
    for(int i = 0; i < n; i++)
    {
        if(data[i] > max_data)
            max_data = data[i];
        if(data[i] < min_data)
            min_data = data[i];
    }

    //max - min = n-1
    //(에피소드 최대 번호 - 에피소드 최소 번호)가 전체 에피소드의 수보다 1 작다면
    //에피소드의 번호들이 연속적인 수열로 표현될 수 있음
    return(max_data-min_data == n-1);
}

int main()
{
    int n;
    int* data;

    scanf("%d", &n); //[입력] 에피소드의 수
    data = new int[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]); //[입력] 에피소드의 번호
    }

    bool result = inConsecutive(data, n);

    if(result) //[출력] 에피소드의 번호들이 연속적인 수열로 표현될 수 있는지
    {
        printf("YES");
    }else{
        printf("NO");
    }

    delete[] data;
    return 0;
}